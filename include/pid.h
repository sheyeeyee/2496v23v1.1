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
#define STRAIGHT_KP 15// 0.7
#define STRAIGHT_KI 0.1 // 0.17
#define STRAIGHT_KD 15 // 10

//tune straight integral-specific here: voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
#define STRAIGHT_INTEGRAL_KI 700
#define STRAIGHT_MAX_INTEGRAL 70


//tune turnt constants here: setConstants(TURN_KP, TURN_KI, TURN_KD);
#define TURN_KP 12 //150 //110 //90 gval:800 wth: 1800 REALLYGOOD: 1800 // 1640 ehh 1400 //1200 //////1800 // 1800
#define TURN_KI 0.5 // 80 //200 gval:20 wth: 20 REALLYGOOD:0.5 ehh 0.2 //0.45 //0.425 ////// 0.425 //ggs 0.1
#define TURN_KD 80 //850 gval:850 wth: 15000 REALLYGOOD:15000 ehh 17000 //10000 /////15000///185001

//tune turn integral-specific here: voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
#define TURN_INTEGRAL_KI 10
#define TURN_MAX_INTEGRAL 20

#endif