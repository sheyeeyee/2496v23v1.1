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
     FLY.move(100);
      FLY1.move(100);
		
      // move forward to contact roller
      LF.move(40);
      LB.move(40);
      RF.move(40);
      RB.move(40);
      delay(180);

      // move forward more??
      LF.move(10);
      LB.move(10);
      RF.move(10);
      RB.move(10);

      while (optical.get_hue() > 200) {
        INTAKE.move(90);
      }

      if (optical.get_hue() < 20) {
        INTAKE.move(0);
      }


            driveStraight(-390);
            driveTurn(-125);
            INTAKE.move(127);
            driveStraight(1400);
            driveTurn(55);
            driveStraight(800);
            driveTurn(-110);
            driveStraight(-670);
             INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
      delay(250);
      INDEXER.move(127);
           FLY.move(115);
      FLY1.move(115);
      delay(250);
      INDEXER.move(-127);
	  delay(250);
    INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
	  delay(250);
	  INDEXER.move(127); // should it be indexerToggle?
      delay(250);
      INDEXER.move(0);
      delay(700);
      delay(350);


    
}