#include "api.h"
#include "main.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

//header guards?
#ifndef PIDH
#define PIDH

extern void resetEncoders();
extern void tarePos();
void driveStraight(int target, double timeout, double minTarget, double vKp, double vKi, double vKd, double slew, double maxIntegral, double integralStart);
extern void driveTurn(int target, double timeout, double minTarget, double vKp, double vKi, double vKd, double slew);

//tune straight constants here: setConstants(STRAIGHT_KP, STRAIGHT_KI, STRAIGHT_KD);
#define STRAIGHT_KP 0
#define STRAIGHT_KI 0
#define STRAIGHT_KD 0

//tune straight integral-specific here: voltage = calcPID(target, encoderAvg, STRAIGHT_INTEGRAL_KI, STRAIGHT_MAX_INTEGRAL);
#define STRAIGHT_INTEGRAL_KI 55
#define STRAIGHT_MAX_INTEGRAL 14.4


//tune turnt constants here: setConstants(TURN_KP, TURN_KI, TURN_KD);
#define TURN_KP 0
#define TURN_KI 0
#define TURN_KD 0

//tune turn integral-specific here: voltage = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL);
#define TURN_INTEGRAL_KI 0
#define TURN_MAX_INTEGRAL 0

#endif