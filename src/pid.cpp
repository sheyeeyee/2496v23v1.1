#include "api.h"
// #include "auton.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include <valarray>

using namespace pros;
using namespace c;
using namespace std;

//constants used for calculating power/voltage
float vKp;
float vKi;
float vKd;

float error; //amount from target
float prevError; //how is this specified/calculated??

int integral;

float power; //voltage provided to motors at any given time to reach the target


void setConstants(float kp, float ki, float kd) {
    vKp = kp;
    vKi = ki;
    vKd = kd;
}

void resetEncoders() { //reset the chassis motors every time a target is reached
    LF.tare_position(); //or set_zero_position(0) or set_zero_position(LF.get_position()); (sets current encoder position to 0)
    LB.tare_position();
	RF.tare_position();
	RB.tare_position();
}

//setting method for driving straight or turning (pos neg voltages change directions)
void chasMove(int voltageLF, int voltageLB, int voltageRF, int voltageRB) { //voltage to each chassis motor
    LF.move_voltage(voltageLF);
    LB.move_voltage(voltageLB);
    RF.move_voltage(voltageRF);
    RB.move_voltage(voltageRB);
}

float calcPID(int target, float input, int integralKi, int maxIntegral) { //basically tuning i here
    error = target - input;
    
    if(std::abs(error) < integralKi) {
        integral += error;
    }
    else {
        integral = 0;
    }

    if(integral >= 0) {
        integral = std::min(integral, maxIntegral); //min means take whichever value is smaller btwn integral and maxI
        //integral = integral until integral is greater than maxI (to keep integral limited to maxI)
    }
    else {
        integral = std::max(integral, -maxIntegral); //same thing but negative max
    }
    
    // derivative = error - prevError 

    power = (vKp * error) + (vKi * integral); //+ (vKd * derivative);

    return power;
}

//driving straight
void driveStraight(int target) {
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    
    float voltage;
    float encoderAvg;
    int count = 0;

    resetEncoders();

    while(true) {
        encoderAvg = (LB.get_position() + RB.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);

        chasMove(voltage, voltage, voltage, voltage);
        
        if (abs(target - encoderAvg) <= 3) count++;
        if (count >= 20) break;

        delay(10);
        con.print(0, 0, "%2f", encoderAvg);
    }
    
    chasMove(0, 0, 0, 0);
}

void driveTurn(int target) { //target is inputted in autons
    setConstants(TURN_KP, TURN_KI, TURN_KD);

    float voltage;
    float position;
    int count = 0;

    while(true) {
        position = imu.get_rotation(); //this is where the units are set to be degrees
        voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
        
        chasMove(voltage, voltage, -voltage, -voltage);
        
        if (abs(target - position) <= 1.5) count++; 
        if (count >= 20) break;
        
        delay(10);
    }

    chasMove(0, 0, 0, 0);
}