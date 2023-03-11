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
    LM.move(voltageL);
    LB.move(voltageL);
    RF.move(voltageR);
    RM.move(voltageR);
    RB.move(voltageR);
}
void tarePos()
{
    LF.tare_position();
    LM.tare_position();
    LB.tare_position();
    RF.tare_position();
    RM.tare_position();
    RB.tare_position();
}

// struct pidParams
// {
//     double vKp, vKi, vKd;
//     double maxIntegral, integralStart;
//     bool slewOn; 
//     double slewRate;
//     double target;
//     int timeout;
//     double tolerance;
//     int toleranceCount;
// };

class pid
{
    private:
        pidParams params;
        double error, prevError;
        double voltage, prevVoltage;
        double derivative;
        double integral;

    public:
        pid(pidParams inputParams)
        {
            params.vKp = inputParams.vKp;
            params.vKi = inputParams.vKi;
            params.vKd = inputParams.vKd;
            params.maxIntegral = inputParams.maxIntegral;
            params.integralStart = inputParams.integralStart;
            params.slewRate = inputParams.slewRate;
        }
        double calcPID(double input)
        {
            prevError = error;
            error = params.target - input;
            derivative = error - prevError;

            // Max error that can add to integral
            if (std::abs(error) <= params.integralStart) integral += error * params.vKi;
            else integral = 0;
            // Max total integral
            if (integral >= 0) integral = std::min(integral, params.maxIntegral); 
            else integral = std::max(integral, -params.maxIntegral);
            
            prevVoltage = voltage;
            voltage = (params.vKp * error) + (integral) - (params.vKd * derivative);

            // // Deceleration Slew
            // if (slewOn && abs(target) < 25 && voltage >= abs(prevVoltage) - abs(slewRate))
            //     voltage = prevVoltage - slewRate;
           
            return voltage;
        }
        // Getters
        double getError() { return error; }
        double getVoltage() { return voltage; }
        double getDerivative() { return derivative; }
        double getIntegral() { return integral; }
        pidParams getParams() { return params; }


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
        int calcHeading(double input)
        {
            if (initialHeading > 180.0) initialHeading = (360.0 - initialHeading); // Converts 360 Degrees to 180
            if (imu.get_heading() < 180.0) headingError = initialHeading - imu.get_heading(); // Turns Heading Negative for Oposite Direction
            else headingError = ((360.0 - imu.get_heading()) - initialHeading);
            
            if (abs(initialHeading-input) <= 15) sensitivity = 0; // Stops Heading Error when close to target
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
        void pidStraight(pid pidInput, int timeL)
        {
            this->timeL = timeL;
            if (timeL % 100 == 0) con.clear(); 
            else if (timeL % 50 == 0) 
            {
                cycle++;
                if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", pidInput.getParams().target-encoderAvg()); 
                if ((cycle+2) % 3 == 0) con.print(1, 0, "Integral: %2f", pidInput.getIntegral());
                if ((cycle+3) % 3 == 0) con.print(2, 0, "Heading: %f", imu.get_heading());
		    }
        }
        void pidTurn(pid pidInput, int timeL)
        {
            this->timeL = timeL;
            if (timeL % 100 == 0) con.clear(); 
            else if (timeL % 50 == 0) 
            {
                cycle++;
                if ((cycle+1) % 3 == 0) con.print(0, 0, "Error: %2f", pidInput.getParams().target-imu.get_heading()); 
                if ((cycle+2) % 3 == 0) con.print(1, 0, "Voltage: %2f", pidInput.getVoltage());
                // if ((cycle+3) % 3 == 0) con.print(2, 0, "HeadingError: %f", headingError);
            }
        }
};

class pidData
{
    private:
        pidParams params;
        vector<double> error, integral, derivative, voltage, encoder;
        vector<bool> slewOn;
        vector<int> timeL;
    public:
        pidData(pid pidInput) // TODO pidInput should be part of private
        {
            params = pidInput.getParams();
        }
        void addData(pid pidInput, int time)
        {
            error.push_back(pidInput.getError());
            integral.push_back(pidInput.getIntegral());
            derivative.push_back(pidInput.getDerivative());
            voltage.push_back(pidInput.getVoltage());
            slewOn.push_back(params.slewOn);
            encoder.push_back(encoderAvg());
            timeL.push_back(time);
        }
        void printDataPID()
        {
            printf("PID Values  |  Time Elapsed: %i\n", timeL[timeL.size()-1]);
            printf("vKp: %f\n", params.vKp);
            printf("vKi: %f\n", params.vKi);
            printf("vKd: %f\n", params.vKd);
            printf("Max Integral: %f\n", params.maxIntegral);
            printf("Integral Start: %f\n", params.integralStart);
            printf("Slew Rate: %f\n", params.slewRate);
            printf("Timeout: %i  |  TError: %i\n", params.timeout, params.timeout-timeL[timeL.size()-1]);
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

void driveStraight(pidParams params)
{
    int breakoutCount; 
    int timeL = 0;

    // Control Objects
    // pid headingPid(headingParams); // PID Based Heading Control // pidParams headingParams;
    headingControl straightHeading(imu.get_heading(), 5);
    pid straightPid(params);
    pidData straightPidData(straightPid);
    controllerDisplay pidDisplay(timeL); // Move to parent loop

    straightPidData.addData(straightPid, timeL); // 0s Initial Data
    while(true)
    {
        double pidVoltage = straightPid.calcPID(encoderAvg()); // Heading Control
        double headingError = straightHeading.calcHeading(imu.get_heading()); // Heading Control
        // headingError = headingPid.calcPID(0, headingError); // Heading Control

        chasMove((pidVoltage + headingError), (pidVoltage - headingError));
        if (abs(params.target - encoderAvg()) <= params.tolerance) breakoutCount++;
        if (breakoutCount >= params.toleranceCount || timeL > params.timeout)
        {
            straightPidData.printDataPID();
            straightPidData.printDataDesmos();
            break;
        }

        pidDisplay.pidStraight(straightPid, timeL);

        timeL += 10;
        if (timeL % 20 == 0) straightPidData.addData(straightPid, timeL); // 0.05s
        delay(10);
    }
    chasMove(0, 0);
}

// Todo Change to absolute rotation
void driveTurn(pidParams params)
{
    int breakoutCount;
    int timeL;

    // PID & Heading Control Objects
    pid turnPid(params);
    controllerDisplay pidDisplay(timeL); // Move to parent loop

    while(true)
    {
        // TODO Needs to be replaced with agolorithm to decide whether to turn left or right based on absolute rotation
        double heading = imu.get_heading();
        if (imu.get_heading() > 180) heading = ((360 - heading) * -1); // Converts 0-360 Degrees to -180-180
        double pidVoltage = turnPid.calcPID(heading);

        chasMove((pidVoltage ), (-pidVoltage));
        if (abs(params.target - imu.get_heading()) <= params.tolerance) breakoutCount++;
        if (breakoutCount >= 20 || timeL > params.timeout) break;

        pidDisplay.pidTurn(turnPid, timeL); //hello, this is a test to see if this works or not, Hi i'm tyler

        timeL += 10;
        delay(10);
    }
    chasMove(0, 0);
}

// class pidTranslation // Trnaslation Layer to allow for current autons to work on this platform
// {
//     private:
//         pidParams params;
    
//     public:
        void straight(int target)
        {
            pidParams params;
            params.target = target;
            params.tolerance = 3;
            params.toleranceCount = 20;
            params.timeout = 3500;
            if (abs(params.target) < 350) {
                params.vKp = 0.85;
                params.vKi = 0.1;
                params.vKp = 9;
            } else {
                params.vKp = 0.535;
                params.vKi = 0.28;
                params.vKp = 7.6;
            }
            params.integralStart = 40;
            params.maxIntegral = 14.5;

            driveStraight(params);
        }
// };