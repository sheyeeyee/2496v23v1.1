//externing to make sure that these electrical component declarations are defined (the names can't be used more than once) and will be used multiple times in multiple files
//extern: external linkage

#include "main.h"
#include "pros/motors.h"

#ifndef ROBOTH
#define ROBOTH

extern pros::Motor LF;
extern pros::Motor LB;
extern pros::Motor RF;
extern pros::Motor RB;

//intake
extern pros::Motor INTAKE;

//flywheel
extern pros::Motor FLY;
extern pros::Motor FLY1;

//controller
extern pros::Controller con;


//sensors
extern pros::ADIEncoder encLeft;
extern pros::ADIEncoder encRight;
extern pros::ADIEncoder encMid;

//imu
extern pros::Imu imu;

//indexer
extern pros::Motor INDEXER;

//angler
extern pros::ADIDigitalOut angler;

//gps
extern pros::Gps gps1;
extern pros::c::gps_status_s_t gpsData;

//expansion
extern pros::ADIDigitalOut expand;

//optical
extern pros::Optical optical;
#endif