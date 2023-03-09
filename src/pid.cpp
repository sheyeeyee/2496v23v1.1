#include "api.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"

using namespace pros;
using namespace c;
using namespace std;

// TODO Move these
double encoderAvg() { return ((LB.get_position() + RB.get_position()) / 2.0); }
void chasMove(int voltageL, int voltageR) 
{
    LF.move(voltageL);
    LB.move(voltageL);
    RF.move(voltageR);
    RB.move(voltageR);
}
void tarePos()
{
    LF.tare_position();
    LB.tare_position();
    RF.tare_position();
    RB.tare_position();
}

double integral;

class pid
{
    private:
        double vKp, vKi, vKd;
        double derivative;
        double error, prevError;
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
        double calcPID(double target, double input)
        {
            prevError = error;
            error = target - input;
            derivative = error - prevError;

            // Max error that can add to integral
            if (std::abs(error) <= integralStart) integral += error * vKi;
            else integral = 0;
            // Max total integral
            if (integral >= 0) integral = std::min(integral, maxIntegral); 
            else integral = std::max(integral, -maxIntegral);
            
            prevVoltage = voltage;
            voltage = (vKp * error) + (integral) - (vKd * derivative);

            // // Deceleration Slew
            // if (slewOn && abs(target) < 25 && voltage >= abs(prevVoltage) - abs(slewRate))
            //     voltage = prevVoltage - slewRate;
           
            return voltage;
        }
        // Getters
        double getError() { return error; }
        double getIntegral() { return integral; }
        double getDerivative() { return derivative; }
        double getVoltage() { return voltage; }
        double getvKp() { return vKp; }
        double getvKi() { return vKi; }
        double getvKd() { return vKd; }
        double getMaxIntegral() { return maxIntegral; }
        double getIntegralStart() { return integralStart; }
        double getSlewRate() { return slewRate; }
        bool getSlewOn() { return slewOn; }


};

class headingControl // Rework to PID style
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
        int calcHeading(double target, double input)
        {
            if (initialHeading > 180.0) initialHeading = (360.0 - initialHeading); // Converts 360 Degrees to 180
            if (imu.get_heading() < 180.0) headingError = initialHeading - imu.get_heading(); // Turns Heading Negative for Oposite Direction
            else headingError = ((360.0 - imu.get_heading()) - initialHeading);
            
            if (abs(target-input) <= 15) sensitivity = 0; // Stops Heading Error when close to target
            return headingError * sensitivity;
        }
        void setSensitivity(double sensitivity) { this->sensitivity = sensitivity; }
};

class controllerDisplay
{
    private:
        int cycle;
        int timeL;
    public:
        controllerDisplay(int timeL)
        {
            this->timeL = timeL;
        }
        void pidStraight(int target, double pidVoltage, double headingError, int timeL)
        {
            this->timeL = timeL;
            if (timeL % 100 == 0) con.clear(); 
            else if (timeL % 50 == 0) 
            {
			cycle++;
            if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", target-encoderAvg()); 
            if ((cycle+2) % 3 == 0) con.print(1, 0, "Integral: %2f", integral); //autstr //%s
            if ((cycle+3) % 3 == 0) con.print(2, 0, "TimeL: %i", timeL);
		    }
        }
        void pidTurn(int target, double pidVoltage, int timeL)
        {
            this->timeL = timeL;
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

class pidData
{
    private:
        int timeout;
        double vKp, vKi, vKd;
        double maxIntegral, integralStart;
        double slewRate;
        vector<double> error, integral, derivative, voltage, encoder;
        vector<bool> slewOn;
        vector<int> timeL;
    public:
        pidData(pid pidInput, int timeout) // TODO pidInput should be part of private
        {
            this->vKp = pidInput.getvKp();
            this->vKi = pidInput.getvKi();
            this->vKd = pidInput.getvKd();
            this->maxIntegral = pidInput.getMaxIntegral();
            this->integralStart = pidInput.getIntegralStart();
            this->slewRate = pidInput.getSlewRate();
            this->timeout = timeout;
        }
        void addData(pid pidInput, int time)
        {
            error.push_back(pidInput.getError());
            integral.push_back(pidInput.getIntegral());
            derivative.push_back(pidInput.getDerivative());
            voltage.push_back(pidInput.getVoltage());
            slewOn.push_back(pidInput.getSlewOn());
            encoder.push_back(encoderAvg());
            timeL.push_back(time);
        }
        void printDataPID()
        {
            printf("PID Values  |  Time Elapsed: %i\n", timeL[timeL.size()-1]);
            printf("vKp: %f\n", vKp);
            printf("vKi: %f\n", vKi);
            printf("vKd: %f\n", vKd);
            printf("Max Integral: %f\n", maxIntegral);
            printf("Integral Start: %f\n", integralStart);
            printf("Slew Rate: %f\n", slewRate);
            printf("Timeout: %i  |  TError: %i\n", timeout, timeout-timeL[timeL.size()-1]);
            printf("\n ---------- \n");
        }
        void printDataError()
        {
            printf("(Time,Error): ");
            for (int i = 0; i < error.size(); i++) 
            { printf("(%i, %f),", timeL[i], error[i]); }
        }
        void printDataIntegral()
        {
            printf("(Time,Integral): ");
            for (int i = 0; i < integral.size(); i++) 
            { printf("(%i, %f),", timeL[i], integral[i]); }
        }
        void printDataDerivative()
        {
            printf("(Time,Derivative): ");
            for (int i = 0; i < derivative.size(); i++) 
            { printf("(%i, %f),", timeL[i], derivative[i]); }
        }
        void printDataVoltage()
        {
            printf("(Time,Voltage): ");
            for (int i = 0; i < voltage.size(); i++) 
            { printf("(%i, %f),", timeL[i], voltage[i]); }
        }
        void printDataSlew()
        {
            printf("(Time,Slew): ");
            for (int i = 0; i < slewOn.size(); i++) 
            { printf("(%i, %i),", timeL[i], (int)slewOn[i]); }
        }
        void printDataDesmos()
        {
            printf("Point Data  |  Total Elements: %i\n", error.size()*5);
            printDataError();
            printf("\n ---------- \n");
            printDataIntegral();
            printf("\n ---------- \n");
            printDataDerivative();
            printf("\n ---------- \n");
            printDataVoltage();
            printf("\n ---------- \n");
            printDataSlew();
            printf("\n ---------- \n");
        }
};

void driveStraight(int target, double timeout, double minTarget, double vKp, double vKi, double vKd, double slew, double maxIntegral, double integralStart)
{
    int breakoutCount; 
    int timeL = 0;

    // PID & Heading Control Objects
    pid straightPid(vKp, vKi, vKd, maxIntegral, integralStart, slew);
    pidData straightPidData(straightPid, timeout);
    pid headingPid(0,0,0,0,0,0); // These values should not be changed
    headingControl straightHeading(imu.get_heading(), 0);
    controllerDisplay pidDisplay(timeL); // Move to parent loop
    
    while(true)
    {
        double pidVoltage = straightPid.calcPID(target, encoderAvg()); // Heading Control
        double headingError = straightHeading.calcHeading(target, encoderAvg()); // Heading Control
        headingError = headingPid.calcPID(0, headingError); // Heading Control

        chasMove((pidVoltage + headingError), (pidVoltage - headingError));
        if (abs(target - encoderAvg()) <= minTarget) breakoutCount++;
        if (breakoutCount >= 20 || timeL > timeout)
        {
            straightPidData.printDataPID();
            straightPidData.printDataDesmos();
            break;
        }

        pidDisplay.pidStraight(target, pidVoltage, headingError, timeL);

        timeL += 10;
        if (timeL % 20 == 0) straightPidData.addData(straightPid, timeL); // 0.05s
        delay(10);
    }
    chasMove(0, 0);
}

// Todo Change to absolute rotation
void driveTurn(int target, double timeout, double minTarget, double vKp, double vKi, double vKd, double slew)
{
    int breakoutCount;
    int timeL;

    // PID & Heading Control Objects
    pid turnPid(vKp, vKi, vKd, STRAIGHT_MAX_INTEGRAL, STRAIGHT_INTEGRAL_KI, slew);
    controllerDisplay pidDisplay(timeL); // Move to parent loop

    while(true)
    {
        // TODO Needs to be replaced with agolorithm to decide whether to turn left or right based on absolute rotation
        double heading = imu.get_heading();
        if (imu.get_heading() > 180) heading = ((360 - heading) * -1); // Converts 0-360 Degrees to -180-180
        double pidVoltage = turnPid.calcPID(target, heading);

        chasMove((pidVoltage ), (-pidVoltage));
        if (abs(target - imu.get_heading()) <= minTarget) breakoutCount++;
        if (breakoutCount >= 20 || timeL > timeout) break;

        pidDisplay.pidTurn(target, pidVoltage, timeL);

        timeL += 10;
        delay(10);
    }
    chasMove(0, 0);
}