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

int atn;
string autstr;

void competition_initialize() {
    while(true){
      if(selec.get_value() == true){
        atn ++;
        delay(350);
      }
    
      if (atn == 1){
        autstr = "Red Non-Roller";
        con.print(0, 0, "Aut 1: %s", autstr);
      }
      else if(atn == 2){
        autstr = "Blue Non-Roller";
        con.print(0, 0, "Aut 2: %s", autstr);
      }
      else if(atn == 3){
        autstr = "Red Roller";
        con.print(0, 0, "Aut 3: %s", autstr);
      }
      else if(atn == 4){
        autstr = "Blue Roller";
        con.print(0, 0, "Aut 4: %s", autstr);
      }
      else if(atn == 5){
        autstr = "AWP";
        con.print(0, 0, "Aut 5: %s", autstr);
      }
      else if(atn == 6){
        autstr = "Skills";
        con.print(0, 0, "Aut 6: %s", autstr);
      }
      con.clear();
      // con.print(0, 0, "Aut: %s", autstr);
    }
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

int cycle = 0;
int wait = 900;
int wait2 = 250;

bool anglerToggle = false;
bool expandToggle = false;
bool deployExpansion = false;

bool rollerOn = false;

void opcontrol() {
  int time = 0;
  bool arcToggle = false;
  bool tankToggle = true;

	while (true) {
    //printing stuff
		double chasstempC = ((RF.get_temperature() + RB.get_temperature() + LF.get_temperature() + LB.get_temperature())/4);
		double chasstempF = chasstempC *(9/5) + 32;
		
    if (time % 100 == 0) con.clear();
		
    else if (time % 50 == 0) {
			cycle++;
      // if (cycle % 3 == 0) con.print(0, 0, "Aut: %s", ); //autstr //%s
      if ((cycle+1) % 3 == 0) con.print(0, 0, "ERROR: %f", error ); //autstr //%s
		  if ((cycle+2) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}

		//chassis arcade drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)

		int turn = int(abs(RX) * RX / 75);
		int left = power + turn;
		int right = power - turn;

    if (con.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      arcToggle = !arcToggle;
      tankToggle = !tankToggle;
    }
    if (tankToggle) {
      LF.move(con.get_analog(ANALOG_LEFT_Y));
      LM.move(con.get_analog(ANALOG_LEFT_Y));
      LB.move(con.get_analog(ANALOG_LEFT_Y));
      RF.move(con.get_analog(ANALOG_RIGHT_Y));
      RM.move(con.get_analog(ANALOG_RIGHT_Y));
      RB.move(con.get_analog(ANALOG_RIGHT_Y));
    }
    if (arcToggle) {
      LF.move(left);
      LM.move(left);
      LB.move(left);
      RF.move(right);
      RM.move(right);
      RB.move(right);
    }


    //auton selector
    if(selec.get_value() == true){ // brain was here
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

    //intake
		if (con.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			INTAKE.move(127);
		}
		else if (con.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			INTAKE.move(-127);
		}
		else {
			INTAKE.move(0);
		}

    //cata
    if ((con.get_digital(E_CONTROLLER_DIGITAL_L1) == true) || (catalim.get_value() == false)) {
			CATA.move(-127);
		}
    else {
      CATA.move(0);
    }
    //pid helper
		if (con.get_digital(E_CONTROLLER_DIGITAL_X)) {
      driveStraight(1000);
			// driveTurn(90);
		}
		// angler (might use for v2)
		if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
			if (anglerToggle == false) {
				angler.set_value(false);
				anglerToggle = true;
			}
      else {
				angler.set_value(true);
				anglerToggle = false;
			}
		}

    //expansion
    if (con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			expand.set_value(true);
		}

    //reset all motor encoders
		if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {
			resetEncoders();
		}

		time += 10;
		pros::delay(10);
	}
}