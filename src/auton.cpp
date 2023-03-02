#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pid.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  //INDEX
    //AUTON 1: ROLLER
    //AUTON 2: NON-ROLLER
    //AUTON 3: SKILLS
    //AUTON 4: 
    //AUTON 5: 
    //AUTON 6: 

//111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

  //ROLLER
  if (atn == 1) {
    //
  }

//22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

  //NON-ROLLER
  else if (atn == 2) {
    //
  }

//44444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

//   else if(atn == 4){
//   }

//55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

//   else if (atn == 5) {
//   }

//66666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666

//   else if(atn == 6) {
//   }
}