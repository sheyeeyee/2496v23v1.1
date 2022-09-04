#include "api.h"
#include "main.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"

#ifndef PIDH
#define PIDH

extern float vKp;
extern float vKi;
extern float vKd;

extern float error; //amount from target
extern float prevError; //how is this specified/calculated??

extern int integral;

extern float power; //voltage provided to motors at any given time to reach the target

extern void setConstants(float kp, float ki, float kd);
extern void resetEncoders();
extern void chasMove(int voltageLF, int voltageLB, int voltageRF, int voltageRB);
extern float calcPID(int target, float input, int integralKi, int maxI);

extern void driveStraight(int target);
extern void driveTurn(int target);

#endif