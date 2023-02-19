//constructors for everything electrical

#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pros/motors.h"

#define INDEXER_PORT 1
#define OPTICAL_PORT 4
#define IMU_PORT 2
#define LF_PORT 1
#define LM_PORT 9
#define LB_PORT 8
#define RF_PORT 10
#define RM_PORT 11
#define RB_PORT 12
#define GPS_PORT 16
#define CATA_PORT 17
#define INTAKE_PORT 18


pros::Motor LF (LF_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LM (LM_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor LB (LB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor RF (RF_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RM (RM_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor RB (RB_PORT, pros::E_MOTOR_GEARSET_06, false);
void resetEncoders() { //reset the chassis motors every time a target is reached
    LF.tare_position(); //or set_zero_position(0) or set_zero_position(LF.get_position()); (sets current encoder position to 0)
    LB.tare_position();
	RF.tare_position();
	RB.tare_position();
    RM.tare_position();
	LM.tare_position();
}
float encoderAvg() { return (LB.get_position() + RB.get_position()) / 2; }
void chasMove(int voltageLF, int voltageLB, int voltageLM, int voltageRF, int voltageRB, int voltageRM) {
    LM.move_voltage(voltageLB);
    LB.move_voltage(voltageLB);
    RF.move_voltage(voltageRF);
    RM.move_voltage(voltageRF);
    RB.move_voltage(voltageRB);
}

//intake
pros::Motor INTAKE (INTAKE_PORT, pros::E_MOTOR_GEARSET_18, true);

//cata
pros::Motor CATA (CATA_PORT, pros::E_MOTOR_GEARSET_06);

//angler for intake
pros::ADIDigitalOut angler ('B', false);

//cata limit switch
pros::ADIDigitalIn catalim ('H');

//expansion
pros::ADIDigitalOut expand ('G');

// extender
pros::ADIDigitalOut extender ('F');

//auton selector
pros::ADIDigitalIn selec ('A');

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