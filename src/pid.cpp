#include "api.h"
// #include "auton.h"
#include "main.h"
#include "pid.h"
#include "robot.h"
#include "auton.h"
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
float viewvol;

float prevError; //how is this specified/calculated??
float h;

int integral;
int derivative;

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
    RM.tare_position();
	LM.tare_position();
}

//setting method for driving straight or turning (pos neg voltages change directions)
void chasMove(int voltageLF, int voltageLB, int voltageLM, int voltageRF, int voltageRB, int voltageRM) { //voltage to each chassis motor
    LF.move_voltage(voltageLF);
    LM.move_voltage(voltageLB);
    LB.move_voltage(voltageLB);
    RF.move_voltage(voltageRF);
    RM.move_voltage(voltageRF);
    RB.move_voltage(voltageRB);
}

float calcPID(int target, float input, int integralKi, int maxIntegral) { //basically tuning i here
    prevError = error;
    error = target - input;
    
    if(std::abs(error) < integralKi) {
        integral += error;
    } else {
        integral = 0;
    }

    if(integral >= 0) {
        integral = std::min(integral, maxIntegral); //min means take whichever value is smaller btwn integral and maxI
        //integral = integral until integral is greater than maxI (to keep integral limited to maxI)
    } else {
        integral = std::max(integral, -maxIntegral); //same thing but negative max
    }
    
    derivative = std::abs(error - prevError);

    if (target < 0){
        derivative *= -1;
    }

    power = (vKp * error) + (vKi * integral) - (vKd * derivative); //+ (vKd * derivative);

    // con.print(0, 0, "%2f", (integral * 0.035));

    return power;
}

//driving straight
void driveStraight(int target) {
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    int timeout = 3500;
    if (target < 850){
        int timeout = 1800;
    } else{
    int timeout = 3500;
    }
    //  double start_head = 0; 
    // double end_head = 0;
    if (abs(target) > 1500){
         setConstants(63.5, 0.63, 950); //0.4
    } else if(abs(target) > 1050){
         setConstants(44, 0.25, 475); //0.4
    } else if (abs(target) > 900){
         setConstants(44, 0.25, 485); //0.4
    } else {
        setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    }

    // if (target < 0){
    //      setConstants(53, 0.4, 878); //0.4
    // } else{
    //      setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    // }

    float voltage;
    float encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    int time = 0;
    
    con.clear();
    // double error_range_time = 0;

    resetEncoders();
    

    while(true) {
        // temp cata reset
        if (catalim.get_value() == false) CATA.move(-127);
        else CATA.move(0);

        encoderAvg = (LB.get_position() + RB.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
        viewvol = voltage;
        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        }
        else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }
        
        heading_error = heading_error * 0;//70 //160
        h = 1 / error;
        if (h > 100){
           h = 30;
        }

        h = h * 160; ////-20000

        chasMove( (voltage + heading_error + h), (voltage + heading_error  + h), (voltage + heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h));
        if (abs(target - encoderAvg) <= 2.5) count++;
        if (count >= 20 || time > timeout){
            CATA.move(0);
            break;
        } 

        delay(10);
        
        // con.print(0, 0, "%2f", encoderAvg); //encoderAvg
        // con.print(2, 0, "%2f", voltage);

        if (time % 100 == 0) con.clear(); else if (time % 50 == 0) {
			cycle++;
            if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", encoderAvg); 
            if ((cycle+2) % 3 == 0) con.print(1, 0, "Volatge: %2f", voltage); //autstr //%s
            // if ((cycle+3) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}
        time += 10;
    }
    // chasMove(0, 0, 0, 0);
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}

void driveTurn(int target) { //target is inputted in autons
    setConstants(TURN_KP, TURN_KI, TURN_KD);
    int timeout = 2100;
    imu.tare_heading();
    int time = 0;

    // if ((target == -16) || (target == -8)){
    //     setConstants(1200, 0.425, 10000);
    // }

    // if (abs(target) <= 20){
    //      setConstants(1200, 0.425, 10000); //0.4
    // } 
    // else if (abs(target) < 45){
    //      setConstants(1800, 0.425, 18000);
    // }
    // else if (abs(target) < 75){
    //     setConstants(2000, 0.05, 19000);
    // }
    // else if (abs(target) < 100){
    //     setConstants(1800, 0.425, 19000);
    // }
    // else {
    //     setConstants(1800, 0.01, 18000);
    // }


    
    //over // 200 150 0
    //under 82 190 0
    //kd profile one// 200 190 100
    //kd profile two// 200 190 130
    //kd profile three // 1000 190 939
    // 300 160 80
    //600 160 540
    //1000 110 925
    //1000 120 939
    // cout << target << endl;

    float voltage;
    float position;
    int count = 0;
    
    while(true) {
        // temp cata reset
        if (catalim.get_value() == false) CATA.move(-127);
        else CATA.move(0);

        position = imu.get_heading(); //this is where the units are set to be degrees
        if (position > 180) {
            position = ((360 - position) * -1);
        }

        voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
        // con.print(1, 0, "%2f", voltage);
        
        chasMove(voltage, voltage, voltage, -voltage, -voltage, -voltage);
        
        if (abs(target - position) <= 0.3) count++; //0.35
        if (count >= 20 || time > timeout) {
            imu.tare_heading();
            break;
        }
        con.print(0, 0, "%2f", target-position);

        time += 10;
        delay(10);
    }

    chasMove(0, 0, 0, 0, 0, 0);
}





//////////////////////////////////////////////
void driveSlow(int target) {
    setConstants(20, 0.5, 800);
    int timeout = 4000;
    // 10 .5 400
    //  double start_head = 0; 
    // double end_head = 0;

    float voltage;
    float encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    int time = 0;
    
    con.clear();
    // double error_range_time = 0;
    

    resetEncoders();
    

    while(true) {
        // temp cata rest
        if (catalim.get_value() == false) CATA.move(-127); 
        else CATA.move(0);

        encoderAvg = (LB.get_position() + RB.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
        viewvol = voltage;
        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        }
        else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }
        
        heading_error = heading_error * 160;//70
        h = 1 / error;
        if (h > 100){
           h = 30;
        }

        h = h * 0000; ////-20000

        chasMove( (voltage + heading_error + h), (voltage + heading_error  + h), (voltage + heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h));
        if (abs(target - encoderAvg) <= 5) count++;
         if (count >= 20 || time > timeout) break;

        if (time % 100 == 0) con.clear(); else if (time % 50 == 0) {
			cycle++;
            if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", encoderAvg); 
            if ((cycle+2) % 3 == 0) con.print(1, 0, "Volatge: %2f", voltage); //autstr //%s
            // if ((cycle+3) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}

        time += 10;
        delay(10);
    }
    // chasMove(0, 0, 0, 0);
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}

void driveSmall(int target) {
    setConstants(52, 0.35, 878);
    int timeout = 1500;
    // 10 .5 400
    //  double start_head = 0; 
    // double end_head = 0;

    float voltage;
    float encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    int time = 0;
    
    con.clear();
    resetEncoders();
    
    while(true) {
        encoderAvg = (LB.get_position() + RB.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
        viewvol = voltage;

        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        }
        else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }
        
        heading_error = heading_error * 160;//70
        h = 1 / error;
        if (h > 100){
           h = 30;
        }

        h = h * 0000; ////-20000

        chasMove( (voltage + heading_error + h), (voltage + heading_error  + h), (voltage + heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h));
        if (abs(target - encoderAvg) <= 5) count++;
         if (count >= 20 || time > timeout) break;

        delay(10);

        if (time % 100 == 0) con.clear(); else if (time % 50 == 0) {
			cycle++;
            if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", encoderAvg); 
            if ((cycle+2) % 3 == 0) con.print(1, 0, "Volatge: %2f", voltage); //autstr //%s
            // if ((cycle+3) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}
        time += 10;
    }
    // chasMove(0, 0, 0, 0);
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}

//drive shoot
void driveShoot(int target) {
    setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    int timeout = 3500;
    if (target < 850){
        int timeout = 1800;
    } else{
    int timeout = 3500;
    }
    //  double start_head = 0; 
    // double end_head = 0;
    if (target < 0){
         setConstants(55, 0.5, 878); //0.4
    } else{
         setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
    }

    float voltage;
    float encoderAvg;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    int time = 0;
    
    con.clear();
    // double error_range_time = 0;

    resetEncoders();
    

    while(true) {
        // temp cata reset
        if((220 < time) || (catalim.get_value() == false)){
            CATA.move(-127);
        }
        else CATA.move(0);

        encoderAvg = (LB.get_position() + RB.get_position()) / 2;
        voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
        viewvol = voltage;
        if(init_heading > 180) {
            init_heading = (360 - init_heading);
        }

        if(imu.get_heading() < 180) {
            heading_error = init_heading - imu.get_heading();
        }
        else {
            heading_error = ((360 - imu.get_heading()) - init_heading);
        }
        
        heading_error = heading_error * 160;//70
        h = 1 / error;
        if (h > 100){
           h = 30;
        }

        h = h * 0000; ////-20000

        chasMove( (voltage + heading_error + h), (voltage + heading_error  + h), (voltage + heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h), (voltage - heading_error + h));
        if (abs(target - encoderAvg) <= 5) count++;
        if (count >= 20 || time > timeout){
            CATA.move(0);
            break;
        } 

        delay(10);
        
        // con.print(0, 0, "%2f", encoderAvg); //encoderAvg
        // con.print(2, 0, "%2f", voltage);

        if (time % 100 == 0) con.clear(); else if (time % 50 == 0) {
			cycle++;
            if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %2f", encoderAvg); 
            if ((cycle+2) % 3 == 0) con.print(1, 0, "Volatge: %2f", voltage); //autstr //%s
            // if ((cycle+3) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}
        time += 10;
    }
    // chasMove(0, 0, 0, 0);
    LF.brake();
    LM.brake();
    LB.brake();
    RF.brake();
    RM.brake();
    RB.brake();
}