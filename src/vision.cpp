
#include "main.h"
#include "api.h"
#include "auton.h"
#include "pid.h"
#include "robot.h"

using namespace pros;
using namespace std;


//goes in main 

//end of main code

void aim(int color = 2){
    int move = 0;
    int x = 0;
    pros::vision_object_s_t goal = vision.get_by_sig(0, color);
    x = goal.left_coord;
    // move = calcPID(target, position, TURN_INTEGRAL_KI, TURN_MAX_INTEGRAL, false);

}