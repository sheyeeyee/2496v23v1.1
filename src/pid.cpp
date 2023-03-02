#include "api.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"

using namespace pros;
using namespace c;
using namespace std;

// Global Variables
int timeL = 0;

// TODO Move these
double encoderAvg() { return ((LB.get_position() + RB.get_position()) / 2.0); }
void chasMove(int voltageL, int voltageR) 
{
    LM.move(voltageL);
    LM.move(voltageL);
    LB.move(voltageL);
    RF.move(voltageR);
    RM.move(voltageR);
    RB.move(voltageR);
}
void tarePos()
{
    LF.tare_position();
    LB.tare_position();
    LM.tare_position();
    RF.tare_position();
    RM.tare_position();
    RB.tare_position();
}

double integral;

class pid
{
    private:
        double vKp, vKi, vKd;
        double derivative;
        double error, prev_Error;
        double maxIntegral, integralStart;
        double voltage, prevVoltage;
        bool slewOn = true; 
        double slewRate;

    public:
        pid(double vKp, double vKi, double vKd, double maxIntegral, double integralStart, double slew)
        {
            this->vKp = vKp;
            this->vKi = vKi;
            this->vKd = vKd;
            this->maxIntegral = maxIntegral;
            this->integralStart = integralStart;
            this->slewRate = slew;
        }
        double calcPID(int target, int current)
        {
            prev_Error = error;
            error = target - current;
            derivative = error - prev_Error;
            if (target < 0) derivative *= -1;

            // Max error that can add to integral
            if (std::abs(error) <= integralStart) integral += error * 0.4;
            else integral = 0;
            // Max total integral
            if (integral >= 0) integral = std::min(integral, maxIntegral); 
            else integral = std::max(integral, -maxIntegral);
            
            prevVoltage = voltage;
            voltage = (vKp * error) + (vKi * integral) - (vKd * derivative);

            // Slew
            if (slewOn)
            {
                if (abs(voltage) <= abs(prevVoltage) + abs(slewRate)) slewOn = false;
                else voltage = prevVoltage + slewRate;
            } 

            return voltage;
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
            if (initialHeading > 180.0) initialHeading = (360.0 - initialHeading); // Converts 360 Degrees to 180
            if (imu.get_heading() < 180.0) headingError = initialHeading - imu.get_heading(); // Turns Heading Negative for Oposite Direction
            else headingError = ((360.0 - imu.get_heading()) - initialHeading);
            
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
            if (timeL % 100 == 0) con.clear(); 
            else if (timeL % 50 == 0) 
            {
			cycle++;
            if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", target-encoderAvg()); 
            if ((cycle+2) % 3 == 0) con.print(1, 0, "Integral: %2f", integral); //autstr //%s
            if ((cycle+3) % 3 == 0) con.print(2, 0, "Heading: %f", imu.get_heading());
		    }
        }
        void pidTurn(int target, double pidVoltage)
        {
            if (timeL % 100 == 0) con.clear(); 
            else if (timeL % 50 == 0) 
            {
                cycle++;
                if ((cycle+1) % 3 == 0) con.print(0, 0, "Error: %2f", target-imu.get_heading()); 
                if ((cycle+2) % 3 == 0) con.print(1, 0, "Voltage: %2f", pidVoltage);
                // if ((cycle+3) % 3 == 0) con.print(2, 0, "HeadingError: %f", headingError);
            }
        }
};

void driveStraight(int target, double timeout, double minTarget, double vKp, double vKi, double vKd, double slew, double maxIntegral, double integralStart)
{
    // PID & Heading Control Objects
    pid straightPid(vKp, vKi, vKd, maxIntegral, integralStart, slew);
    headingControl straightHeading(imu.get_heading(), 0);
    controllerDisplay pidDisplay; // Move to parent loop

    int breakoutCount;

    while(true)
    {
        double pidVoltage = straightPid.calcPID(target, encoderAvg()); // Heading Control
        double headingError = straightHeading.calcHeading(); // Heading Control

        chasMove((pidVoltage + headingError), (pidVoltage - headingError));
        if (abs(target - encoderAvg()) <= minTarget) breakoutCount++;
        if (breakoutCount >= 20 || timeL > timeout) break;

        pidDisplay.pidStraight(target, pidVoltage, headingError);

        timeL += 10;
        delay(10);
    }
    chasMove(0, 0);
}

// Todo Change to absolute rotation
void driveTurn(int target, double timeout, double minTarget, double vKp, double vKi, double vKd, double slew)
{
    // PID & Heading Control Objects
    pid turnPid(vKp, vKi, vKd, STRAIGHT_MAX_INTEGRAL, STRAIGHT_INTEGRAL_KI, slew);
    controllerDisplay pidDisplay; // Move to parent loop

    int breakoutCount;

    while(true)
    {
        // TODO Needs to be replaced with agolorithm to decide whether to turn left or right based on absolute rotation
        double heading = imu.get_heading();
        if (imu.get_heading() > 180) heading = ((360 - heading) * -1); // Converts 0-360 Degrees to -180-180
        double pidVoltage = turnPid.calcPID(target, heading);

        chasMove((pidVoltage ), (-pidVoltage));
        if (abs(target - imu.get_heading()) <= minTarget) breakoutCount++;
        if (breakoutCount >= 20 || timeL > timeout) break;

        pidDisplay.pidTurn(target, pidVoltage);

        timeL += 10;
        delay(10);
    }
    chasMove(0, 0);
}