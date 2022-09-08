#include "api.h"
// #include "auton.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
// #include "<valarray>"
// #include "<sstream>"
// #include "<string>"


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

    // con.print(0, 0, "%2f", (integral * 0.035));

    return power;
}

//driving straight
void driveStraight(int target) {
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    //  double start_head = 0; 
    // double end_head = 0;
    float voltage;
    float encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    
    con.clear();
    // double error_range_time = 0;
    

    resetEncoders();
    

    while(true) {
        if (target < 1000){ 
             
        }
        encoderAvg = (LB.get_position() + RB.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
        if(init_heading > 180){
            init_heading = 360 - init_heading;
        }

        if(imu.get_heading() < 180){
            heading_error = init_heading - imu.get_heading();
        }
        else{
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }
        
        heading_error = heading_error * 1500;

        chasMove((voltage + heading_error), (voltage + heading_error), (voltage - heading_error), (voltage - heading_error));
        
        if (abs(target - encoderAvg) <= 15) count++;
        if (count >= 20) break;

        delay(10);
        con.print(0, 0, "%2f", encoderAvg);
        // con.print(1, 0, "%2f", encoderAvg);
    }
    // chasMove(0, 0, 0, 0);
    motor_brake (7);
    motor_brake (8);
    motor_brake (9);
    motor_brake (10);
}

void driveTurn(int target) { //target is inputted in autons
    setConstants(107, 120, 0);
    // cout << target << endl;

    float voltage;
    float position;
    int count = 0;
    
    while(true) {

        position = imu.get_heading(); //this is where the units are set to be degrees
        voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
        // con.print(1, 0, "%2f", voltage);
        
        chasMove(voltage, voltage, -voltage, -voltage);
        
        if (abs(target - position) <= 0.1) count++; 
        if (count >= 50) break;
        con.print(0, 0, "%2f", target-position);
        delay(10);
        // con.print(0, 0, "%2f", target);
    }

    chasMove(0, 0, 0, 0);
}
