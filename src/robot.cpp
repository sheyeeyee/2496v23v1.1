//constructors for everything electrical

#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pros/motors.h"

pros::Motor LF (7, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LB (8, pros::E_MOTOR_GEARSET_06, true);
pros::Motor RF (9, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RB (10, pros::E_MOTOR_GEARSET_06, false);

//intake
pros::Motor INTAKE (18, pros::E_MOTOR_GEARSET_18, true);

//flywheel
pros::Motor FLY (17, pros::E_MOTOR_GEARSET_06);
pros::Motor FLY1 (20, pros::E_MOTOR_GEARSET_06);

//indexer
pros::Motor INDEXER (1, pros::E_MOTOR_GEARSET_18, true);

//angler
pros::ADIDigitalOut angler ('B', true);

//expansion
pros::ADIDigitalOut expand ('A', false);

//sensors
pros::ADIEncoder encLeft ({{1, 1, 2}, false});
pros::ADIEncoder encRight ({{1, 3, 4}, false});
pros::ADIEncoder encMid ({{1, 5, 6}, false});

pros::Imu imu (4);

//controller
pros::Controller con (pros::E_CONTROLLER_MASTER);

//gps
#define GPS_PORT 16
#define X_OFFSET .225
#define Y_OFFSET .223
#define X_INITIAL 1.54
#define Y_INITIAL 1.14
#define HEADING_INITIAL 90
pros::Gps gps1(GPS_PORT, X_INITIAL, Y_INITIAL, HEADING_INITIAL, X_OFFSET, Y_OFFSET);
pros::c::gps_status_s_t gpsData;