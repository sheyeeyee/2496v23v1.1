#include "api.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"

using namespace pros;
using namespace c;
using namespace std;

// TODO Move these
double encoderAvg() { return (LB.get_position() + RB.get_position()) / 2; }
void chasMove(int voltageL, int voltageR) 
{
    LM.move_voltage(voltageL);
    LM.move_voltage(voltageL);
    LB.move_voltage(voltageL);
    RF.move_voltage(voltageR);
    RM.move_voltage(voltageR);
    RB.move_voltage(voltageR);
}

class pid
{
    private:
        double vKp, vKi, vKd;
        double integral, derivative;
        double error, prev_Error;
        double maxIntegral, maxIntegralInterval;

    public:
        pid(double vKp, double vKi, double vKd, double maxIntegral, double maxIntegeralInterval)
        {
            this->vKp = vKp;
            this->vKi = vKi;
            this->vKd = vKd;
            this->maxIntegral = maxIntegral;
            this->maxIntegralInterval = maxIntegeralInterval;
        }
        double calcPID(int target, int current)
        {
            prev_Error = error;
            error = target - current;
            derivative = std::abs(error - prev_Error);
            if (target < 0) derivative *= -1;

            // Max error that can add to integral
            if (std::abs(error) < maxIntegralInterval) integral += error;
            else integral = 0;
            // Max total integral
            if (integral >= 0) integral = std::min(integral, maxIntegral); 
            else integral = std::max(integral, -maxIntegral);

            return (vKp * error) + (vKi * integral) - (vKd * derivative);
        }
};

class headingControl
{
    private:
        double headingError;
        double initialHeading;
        double sensitivity;

    public:
        headingControl(double initialHeading, double sensitivity) 
        { 
            this->initialHeading = initialHeading; 
            this->sensitivity = sensitivity;
        }
        int calcHeading()
        {
            if (initialHeading > 180) initialHeading = (360 - initialHeading); // Converts 360 Degrees to 180
            if (imu.get_heading() < 180) headingError = initialHeading - imu.get_heading(); // Turns Heading Negative for Oposite Direction
            else headingError = ((360 - imu.get_heading()) - initialHeading);
            
            return headingError * sensitivity;
        }
};

class controllerDisplay
{
    private:
        int cycle;
    public:
        void pidStraight(int target, double pidVoltage, double headingError)
        {
            if (cycle % 10 == 0) con.clear(); 
            else if (cycle % 5 == 0) {
                cycle++;
                if ((cycle+1) % 3 == 0) con.print(0, 0, "Error: %2f", target-encoderAvg()); 
                if ((cycle+2) % 3 == 0) con.print(1, 0, "Voltage: %2f", pidVoltage);
                if ((cycle+3) % 3 == 0) con.print(2, 0, "HeadingError: %f", headingError);
            }
        }
        void pidTurn(int target, double pidVoltage)
        {
            if (cycle % 10 == 0) con.clear(); 
            else if (cycle % 5 == 0) {
                cycle++;
                if ((cycle+1) % 3 == 0) con.print(0, 0, "Error: %2f", target-imu.get_heading()); 
                if ((cycle+2) % 3 == 0) con.print(1, 0, "Voltage: %2f", pidVoltage);
                // if ((cycle+3) % 3 == 0) con.print(2, 0, "HeadingError: %f", headingError);
            }
        }
};

void driveStraight(int target, double timeout, double minTarget, double vKp, double vKi, double vKd)
{
    // PID & Heading Control Objects
    pid straightPid(vKp, vKi, vKd, STRAIGHT_MAX_INTEGRAL, STRAIGHT_INTEGRAL_KI);
    headingControl straightHeading(imu.get_heading(), 160);
    controllerDisplay pidDisplay; // Move to parent loop

    int breakoutCount, time;

    while(true)
    {
        double pidVoltage = straightPid.calcPID(target, encoderAvg()); // Heading Control
        double headingError = straightHeading.calcHeading(); // Heading Control

        chasMove((pidVoltage + headingError), (pidVoltage - headingError));
        if (abs(target - encoderAvg()) <= minTarget) breakoutCount++;
        if (breakoutCount >= 20 || time > timeout) break;

        pidDisplay.pidStraight(target, pidVoltage, headingError);

        time += 10;
        delay(10);
    }
}

// Todo Change to absolute rotation
void driveTurn(int target, double timeout, double minTarget, double vKp, double vKi, double vKd)
{
    // PID & Heading Control Objects
    pid turnPid(vKp, vKi, vKd, STRAIGHT_MAX_INTEGRAL, STRAIGHT_INTEGRAL_KI);
    controllerDisplay pidDisplay; // Move to parent loop

    int breakoutCount, time;

    while(true)
    {
        // TODO Needs to be replaced with agolorithm to decide whether to turn left or right based on absolute rotation
        double heading = imu.get_heading();
        if (imu.get_heading() > 180) heading = ((360 - heading) * -1); // Converts 0-360 Degrees to -180-180
        double pidVoltage = turnPid.calcPID(target, heading);

        chasMove((pidVoltage ), (-pidVoltage));
        if (abs(target - imu.get_heading()) <= minTarget) breakoutCount++;
        if (breakoutCount >= 20 || time > timeout) break;

        pidDisplay.pidTurn(target, pidVoltage);

        time += 10;
        delay(10);
    }
}