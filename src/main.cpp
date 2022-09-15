// basically run all of the code here (PID, auton, etc.)

#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "robot.h"
#include "pros/colors.h"
#include "pros/misc.h"
#include "pros/screen.hpp"
#include "pros/vision.h"
#include <type_traits>

using namespace std;
using namespace pros;


float indexerTarget = 0;
float indexerDeltaPos = 0;
int indexerDir = 0;
int indexerScaledDeltaPos = 0;
int voltageMacro = 0;

void resetSensors() {
	encLeft.reset();
	encRight.reset();
	encMid.reset();
	con.rumble(".");
}

void printBrainScreen() {
	screen::set_pen(COLOR_WHITE);
	while(true) {
		gpsData = gps1.get_status();
		screen::erase();
		// screen::print(TEXT_MEDIUM, 0, "encL: %d", encLeft.get_value());
		// screen::print(TEXT_MEDIUM, 1, "encR: %d", encRight.get_value());
		// screen::print(TEXT_MEDIUM, 2, "encM: %d", encMid.get_value());
		screen::print(TEXT_MEDIUM, 3, "X Position: %3f", gpsData.x);
		screen::print(TEXT_MEDIUM, 4, "Y Position: %3f", gpsData.y);
		screen::print(TEXT_MEDIUM, 5, "Pitch: %3f", gpsData.pitch);
		screen::print(TEXT_MEDIUM, 6, "Roll: %3f", gpsData.roll);
		screen::print(TEXT_MEDIUM, 7, "Yaw: %3f", gpsData.yaw);
		delay(20);
		pros::screen::erase();
		// pros::screen::print(TEXT_MEDIUM, 0, "encL: %d", encLeft.get_value());
		// pros::screen::print(TEXT_MEDIUM, 1, "encR: %d", encRight.get_value());
		// pros::screen::print(TEXT_MEDIUM, 2, "encM: %d", encMid.get_value());
		// pros::screen::print(TEXT_MEDIUM, 0, "indexerPos: %f", INDEXER.get_position());
		// pros::screen::print(TEXT_MEDIUM, 1, "indexerTarget: %f", indexerTarget);
		// pros::screen::print(TEXT_MEDIUM, 2, "indexerDeltaPos: %f", indexerDeltaPos);
		// pros::screen::print(TEXT_MEDIUM, 3, "indexerDir: %d", indexerDir);
		// pros::screen::print(TEXT_MEDIUM, 3, "indexerScaledDeltaPos: %d", indexerScaledDeltaPos);
		pros::delay(20);
	}
}

void moveIndexer() { //move motor to a certain position and then back
	while(true) {
		INDEXER.move(indexerScaledDeltaPos);
		pros::delay(20);
	}
}

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
	expand.set_value(true);
	angler.set_value(false);
	optical.set_led_pwm(100);
	resetSensors();
	resetEncoders();
	//Task Indexer_move(moveIndexer);
	Task printValues(printBrainScreen);
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
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

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

int max_flywheel_speed = 480;
int flywheel_voltage = 105;
int cycle = 0;
bool indexerToggle = false;
//int indexerstate = -1;
// int indexerprevstate = -1;
bool anglerToggle = false; 
bool expandToggle = false;
bool speedToggle = false;
bool deployExpansion = false;
int slowSpeed = 80;
int fastSpeed = 105;
void opcontrol() {
	int time = 0;

	while (true) {
		// indexerDeltaPos = indexerTarget - INDEXER.get_position();
		// indexerDir = int(std::abs(indexerDeltaPos)/indexerDeltaPos);
		// indexerScaledDeltaPos = indexerDeltaPos/1.1;
		int flywheelVelocity = (FLY.get_actual_velocity() + FLY1.get_actual_velocity())/2;
		double chasstempC = ((RF.get_temperature() + RB.get_temperature() + LF.get_temperature() + LB.get_temperature())/4);
		double chasstempF = chasstempC *(9/5) + 32;
		if (time % 100 == 0) con.clear();
		else if (time % 50 == 0) {
			cycle++;
			if (cycle % 3 == 0) con.print(0, 0, "RPM: %d", flywheelVelocity);
			if ((cycle+1) % 3 == 0) con.print(1, 0, "FV: %d", flywheel_voltage);
			if ((cycle+2) % 3 == 0) con.print(2, 0, "Temp: %f", chasstempC);
		}
		
		//chassis arcade drive
		int power = con.get_analog(ANALOG_LEFT_Y); //power is defined as forward or backward
		int RX = con.get_analog(ANALOG_RIGHT_X); //turn is defined as left (positive) or right (negative)
		int turn = int(abs(RX) * RX / 75);
		
		int left = power + turn;
		int right = power - turn;

		LF.move(left);
		LB.move(left);
		RF.move(right);
		RB.move(right);

		// chassis tank drive 
		// LF.move(con.get_analog(ANALOG_LEFT_Y));
		// LB.move(con.get_analog(ANALOG_LEFT_Y));
		// RF.move(con.get_analog(ANALOG_RIGHT_Y));
		// RB.move(con.get_analog(ANALOG_RIGHT_Y));

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

		//expansion
		if (con.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			deployExpansion = true;
		}
		if (deployExpansion == true) {
			expand.set_value(false);
		}

		// //blue roller
		// if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)) {
		// 	while (optical.get_hue() > 200) { //optical reads blue, aka scored red
        // 	INTAKE.move(-90); //we want to it to score blue
      	// 	}

      	// 	if (optical.get_hue() < 20) {
        // 	INTAKE.move(0);
      	// 	}
		// }

		// //red roller
		// if (con.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)) {
		// 	while (optical.get_hue() < 20) { //optical reads red, aka scored blue
        // 	INTAKE.move(90);
      	// 	}

      	// 	if (optical.get_hue() > 200) {
        // 	INTAKE.move(0);
      	// 	}
		// }

		time += 10;
		pros::delay(10);
	}
}