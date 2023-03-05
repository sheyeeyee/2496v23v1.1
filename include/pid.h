 #include "api.h"
#include "main.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

//header guards?
#ifndef PIDH
#define PIDH

// extern void setConstants(float kp, float ki, float kd);
extern void resetEncoders();
// extern void chasMove(int voltageLF, int voltageLB, int voltageRF, int voltageRB);
// extern float calcPID(int target, float input, int integralKi, int maxI);

extern void driveStraight(int target);
extern void driveTurn(int target);
extern void driveAim(int target);
extern void driveSlow(int target);
extern void driveSmall(int target);
extern void driveShoot(int target);
extern float error;
extern float viewvol;

//tune straight constants here: setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
#define STRAIGHT_KP 0.68 * 1 // 0.7 0.18
#define STRAIGHT_KI 0.4 // 0.17 0.1 0
#define STRAIGHT_KD 9 * 1 // 10 8 0.4

//tune straight integral-specific here: voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
#define STRAIGHT_INTEGRAL_KI 40
#define STRAIGHT_MAX_INTEGRAL 14.5


//tune turn constants here: setConstants(TURN_KP, TURN_KI, TURN_KD);
#define TURN_KP 21.5 * 0.68 //12 23
#define TURN_KI 0.34 //0,05 0.07 // 0.34
#define TURN_KD 197 * 0.65 //80

//tune turn integral-specific here: voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
#define TURN_INTEGRAL_KI 15
#define TURN_MAX_INTEGRAL 25

#endif