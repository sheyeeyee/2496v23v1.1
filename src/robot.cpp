//constructors for everything electrical

#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pros/motors.h"

#define INDEXER_PORT 1
#define OPTICAL_PORT 4
#define IMU_PORT 6
#define LF_PORT 7
#define LB_PORT 8
#define RF_PORT 9
#define RB_PORT 10
#define GPS_PORT 16
#define FLY_PORT 17
#define INTAKE_PORT 18
#define FLY1_PORT 20

pros::Motor LF (LF_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LB (LB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor RF (RF_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RB (RB_PORT, pros::E_MOTOR_GEARSET_06, false);

//intake
pros::Motor INTAKE (INTAKE_PORT, pros::E_MOTOR_GEARSET_18, true);

//flywheel
pros::Motor FLY (FLY_PORT, pros::E_MOTOR_GEARSET_06);
pros::Motor FLY1 (FLY1_PORT, pros::E_MOTOR_GEARSET_06);

//indexer
pros::Motor INDEXER (INDEXER_PORT, pros::E_MOTOR_GEARSET_18, true);

//angler
pros::ADIDigitalOut angler ('B', true);

//expansion
pros::ADIDigitalOut expand ('A', false);

//sensors
pros::ADIEncoder encLeft ({{1, 1, 2}, false});
pros::ADIEncoder encRight ({{1, 3, 4}, false});
pros::ADIEncoder encMid ({{1, 5, 6}, false});

pros::Imu imu (IMU_PORT);

//controller
pros::Controller con (pros::E_CONTROLLER_MASTER);

//gps
#define X_OFFSET .225
#define Y_OFFSET .223
#define X_INITIAL 1.54
#define Y_INITIAL 1.14
#define HEADING_INITIAL 90
pros::Gps gps1(GPS_PORT, X_INITIAL, Y_INITIAL, HEADING_INITIAL, X_OFFSET, Y_OFFSET);
pros::c::gps_status_s_t gpsData;

//optical
pros::Optical optical(OPTICAL_PORT);