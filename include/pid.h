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
extern float error;
extern float viewvol;


//tune straight constants here: setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
#define STRAIGHT_KP 61 //80 9.5 77 15 // 1519 70 71 70 //////20 ///// 70 20 working val: 220 nval 110 
#define STRAIGHT_KI 0.48//0.2 0.2 0.25 0.4 // 0.8 0.5 0.5 0.9 ////0.7 //// 0.5 0.7//3 working val: 0.2 nval 0.2
#define STRAIGHT_KD 878//1488 25 50 57////800 1000 working val: 1000 nval 1100

//tune straight integral-specific here: voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
#define STRAIGHT_INTEGRAL_KI 430
#define STRAIGHT_MAX_INTEGRAL 2000


//tune turnt constants here: setConstants(TURN_KP, TURN_KI, TURN_KD);
#define TURN_KP 180 //150
#define TURN_KI 160
#define TURN_KD 700

//tune turn integral-specific here: voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
#define TURN_INTEGRAL_KI 10
#define TURN_MAX_INTEGRAL 10

#endif