#include "api.h"
#include "main.h"
#include "robot.h"
#include "pid.h"
#include "okapi/api.hpp"
#include "pros/api_legacy.h"
#ifndef AUTONH
#define AUTONH

//robot starts in front of roller
extern void ezRed();
extern void ezBlue();

//robot starts not in front of roller
extern void red();
extern void blue();

//skills
extern void skills();

#endif