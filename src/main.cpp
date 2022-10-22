// basically run all of the code here (PID, auton, etc.)

#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "robot.h"

using namespace pros;
using namespace std;


// void resetEncoders() { //we can't add this to main.h because main.h doesn't
// refer to robot.h (where LF, LB, etc. are located) 	LF.tare_position(); //or
// set_zero_position(0) or set_zero_position(LF.get_position()); (sets current
// encoder position to 0) 	LB.tare_position(); 	RF.tare_position();
// 	RB.tare_position();
// }

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
  static bool pressed = false;
  pressed = !pressed;
  if (pressed) {
    pros::lcd::set_text(2, "I was pressed!");
  } else {
    pros::lcd::clear_line(2);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::lcd::initialize();
  pros::lcd::set_text(1, "Hello PROS User!");

  pros::lcd::register_btn1_cb(on_center_button);
  optical.set_led_pwm(100);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    //add auton selector here
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

// int max_flywheel_speed = 480;
// int cycle = 0;
// bool indexerToggle = false;
// //int indexerstate = -1;
// // int indexerprevstate = -1;
// bool anglerToggle = false; 
// bool expandToggle = false;
// bool speedToggle = false;
// bool deployExpansion = false;
// int slowSpeed = 80;
// int fastSpeed = 105;

int atn = 1;
string autstr;

int max_flywheel_speed = 480;
int flywheel_voltage = 105;
int cycle = 0;
bool indexerToggle = false;
int wait = 900;
int wait2 = 250;
// int indexerstate = -1;
//  int indexerprevstate = -1;
bool anglerToggle = false;
bool expandToggle = false;
bool speedToggle = false;
bool deployExpansion = false;
int slowSpeed = 84;
int fastSpeed = 105;
bool rollerOn = false;

void opcontrol() {
  int time = 0;

	while (true) {
		// indexerDeltaPos = indexerTarget - INDEXER.get_position();
		// indexerDir = int(std::abs(indexerDeltaPos)/indexerDeltaPos);
		// indexerScaledDeltaPos = indexerDeltaPos/1.1;

    //displaying flywheel velocity and chassis motor temperatures
		int flywheelVelocity = (FLY.get_actual_velocity() + FLY1.get_actual_velocity())/2;
		double chasstempC = ((RF.get_temperature() + RB.get_temperature() + LF.get_temperature() + LB.get_temperature())/4);
		double chasstempF = chasstempC *(9/5) + 32;
		
    if (time % 100 == 0) con.clear();
		
    else if (time % 50 == 0) {
			cycle++;
			// if (cycle % 3 == 0) con.print(0, 0, "RPM: %d", flywheelVelocity);
      if (cycle % 3 == 0) con.print(0, 0, "Aut: %s", autstr); //autstr //%s
		  if ((cycle+1) % 3 == 0) con.print(1, 0, "FV: %d", flywheel_voltage);
		  if ((cycle+2) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}
    

		//chassis arcade drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)

		int turn = int(abs(RX) * RX / 75);
		int left = power + turn;
		int right = power - turn;

    // LF.move(left);
		// LB.move(left);
		// RF.move(right);
		// RB.move(right);

		// chassis tank drive 
		LF.move(con.get_analog(ANALOG_LEFT_Y));
		LB.move(con.get_analog(ANALOG_LEFT_Y));
		RF.move(con.get_analog(ANALOG_RIGHT_Y));
		RB.move(con.get_analog(ANALOG_RIGHT_Y));


    //auton selector
    if(selec.get_value() == true){
      atn ++;
      delay(350);
    }

    if (atn == 1){
      autstr = "Red Non-Roller";
    }
    else if(atn == 2){
      autstr = "Blue Non-Roller";
    }
    else if(atn == 3){
      autstr = "Red Roller";
    }
    else if(atn == 4){
      autstr = "Blue Roller";
    }
    else if(atn == 5){
      autstr = "Skip";
    }
    else if(atn == 6){
      autstr = "Skills";
    }

    //aim assist
    // if (con.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){ // brian was here
    //   // FLY.move_velocity(450);
    //   // FLY1.move_velocity(450);
    //   if(atn == 1){
    //     driveAim(215); //125
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127); 

    //     // FLY.move(105);
    //     // FLY1.move(105);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(120);
    //     INDEXER.move(-35);
    //     delay(100);
    //     INDEXER.move(0);
    //   }
    //   else if(atn == 2){
    //     driveAim(-145); //125
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127); 

    //     // FLY.move(105);
    //     // FLY1.move(105);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(100);
    //     INDEXER.move(-35);
    //     delay(100);
    //     INDEXER.move(0);
    //   }
    //   else if(atn == 3){
    //     driveAim(-10); //125
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127); 

    //     // FLY.move(105);
    //     // FLY1.move(105);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(100);
    //     INDEXER.move(-35);
    //     delay(100);
    //     INDEXER.move(0);

    //   }
    //   else if(atn == 4){
    //     driveAim(215); //125
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127); 

    //     // FLY.move(105);
    //     // FLY1.move(105);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(250);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(500);
    //     INDEXER.move(127);
    //     delay(300);
    //     INDEXER.move(-127);

    //     delay(100);
    //     INDEXER.move(-35);
    //     delay(100);
    //     INDEXER.move(0);
    //   }
    // }

    //three-shot
		if (con.get_digital(E_CONTROLLER_DIGITAL_UP)){
		  INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);

	    FLY.move(90); 
      FLY1.move(90);

      delay(250);
      INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);

	    delay(350);
      INDEXER.move(127);
      delay(300);
      INDEXER.move(-127);

	    delay(300);
	    INDEXER.move(127);
      delay(350);
      INDEXER.move(-40);

      delay(350);
      INDEXER.move(0);
		}

    //intake
		if (con.get_digital(E_CONTROLLER_DIGITAL_R1)){
			INTAKE.move(127);
		}
		else if(con.get_digital(E_CONTROLLER_DIGITAL_R2)){
			INTAKE.move(-127);
		}
		else {
			INTAKE.move(0);
		}

		//indexer
		if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){ // using prev state to determine next direction with current state turning motor either direction + off to reduce burnout
			indexerToggle = !indexerToggle;
			if (indexerToggle)
			{
			INDEXER.move_relative(197,200);
			}
			if (indexerToggle==false)
			{
			INDEXER.move_relative(-197,200);
			}
		}
		
		//flywheel
		if (con.get_digital(E_CONTROLLER_DIGITAL_L2)){
			FLY.move(flywheel_voltage);
			FLY1.move(flywheel_voltage);
		}
		else if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
			FLY.move(127); //good flywheel voltage for loader: 460-480 RPM
			FLY1.move(127);
		}
		else {
			FLY.move(0);
			FLY1.move(0);
		}
		
		//angler
		if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
			if (anglerToggle == false) {
				angler.set_value(false);
				anglerToggle = true;
			} else {
				angler.set_value(true);
				anglerToggle = false;
			}
		}

    //expansion
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			expand.set_value(true);
		}

		//flywheel speed changer
		if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
			con.rumble(".");
			speedToggle = !speedToggle;
			speedToggle == true ? flywheel_voltage = slowSpeed : flywheel_voltage = fastSpeed;
		}
		else if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
			speedToggle == true ? slowSpeed-- : fastSpeed--;
			speedToggle == true ? flywheel_voltage = slowSpeed : flywheel_voltage = fastSpeed;
		}
		else if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
			speedToggle == true ? slowSpeed++ : fastSpeed++;
			speedToggle == true ? flywheel_voltage = slowSpeed : flywheel_voltage = fastSpeed;
		}

    //reset all motor encoders
		if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {
			resetEncoders();
		}
		// if (con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		// 	deployExpansion = true;
		// }
		// if (deployExpansion == true) {
		// 	expand.set_value(false);
		// }

		time += 10;
		pros::delay(10);
	}
}