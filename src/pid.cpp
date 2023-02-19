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
float slew;
float error; //amount from target
float viewvol;
bool slewOn = true;

float prevError; //how is this specified/calculated??
float h;

int integral;
int derivative;

float power; //voltage provided to motors at any given time to reach the target
float prevPower;


//driving straight
void driveStraight(int target, float kp, float ki, float kd, float timeout) {

    float voltage;
    int count = 0;
    double init_heading = imu.get_heading();
    double heading_error = 0;
    int cycle = 0; // Controller Display Cycle
    int time = 0;
    
    setConstants(kp, ki, kd);
    con.clear();
    resetEncoders();

    while(true) {
        // TODO move to thread | temp cata reset
        // if (catalim.get_value() == false) CATA.move(-127);
        // else CATA.move(0);

        voltage = calcPID(target, encoderAvg(), STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
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
        if (abs(target - encoderAvg()) <= 5) count++;
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
        
        if (abs(target - position) <= 0.35) count++; 
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