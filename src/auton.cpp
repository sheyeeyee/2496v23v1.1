#include "api.h"
#include "auton.h"
#include "main.h"
#include "robot.h"
#include "pid.h"

using namespace pros;

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
int currAuton = 0;

void competition_initialize() {
  bool selected = true;
  int totAuton = 5; //total number of autons we have
  int time = 0; //for controller refresh (refresh rate = 50 ms)

  con.clear();

  while (true) {
    if (lSwitch.get_value() == 0) {
      if (selected) { //it is default true, so when the limit switch is pressed, the auton will be switched to the next one
        currAuton++;
        
        if (currAuton == totAuton + 1) { //special case: if the last auton is currently selected, then go back to the first one
          currAuton = 1;
        }
      }
    }

    if (time % 5 == 0) { //the mod is to create a delay so the controller isn't overloaded, each time the loop runs, there's a 10ms delay so total is 50ms delay between each loop
      switch (currAuton) {
        case 1:
          con.print(0, 0, "%d EZ Red", currAuton); //the %d is referring to the currAuton variable so it displays what number auton it is
          break;
        case 2:
          con.print(0, 0, "%d EZ Blue", currAuton);
          break;
        case 3:
          con.print(0, 0, "%d Red", currAuton);
          break;
        case 4:
          con.print(0, 0, "%d Blue", currAuton);
          break;
        case 5:
          con.print(0, 0, "%d Skills", currAuton)
      }
      delay(10);
    }
    time++;
  }
}

//AUTONS
bool Global = false;

  void ezRed() {
    //rev flywheel
    FLY.move(100);
    FLY1.move(100);
	
    //move forward to contact roller constantly
    LF.move(40);
    LB.move(40);
    RF.move(40);
    RB.move(40);
    delay(180);

    //decrease motor power so chassis doesn't burn out while spinning roller
    LF.move(10);
    LB.move(10);
    RF.move(10);
    RB.move(10);

    //spin to red
    while (optical.get_hue() > 200) { //hue > 200 is red
      INTAKE.move(90);
    }
    if (optical.get_hue() < 20) {
      INTAKE.move(0);
    }

    //go backwards
    driveStraight(-390);
    driveTurn(-125);

    //run intake for a bit
    INTAKE.move(127);

    //go towards disc still
    driveStraight(1400);
    driveTurn(55);

    //still disc
    driveStraight(800);
    driveTurn(-110);

    //still disc
    driveStraight(-670);

    //shoot disc 1
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
    delay(250);

    //shoot disc 2
    INDEXER.move(127);

    //flywheel faster?
    FLY.move(115);
    FLY1.move(115);
    delay(250);

    INDEXER.move(-127);
	  delay(250);

    //shoot disc 3
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(250);

    //shoot disc 4 (just in case)
	  INDEXER.move(127);
    delay(250);

    INDEXER.move(0);
    delay(1050);
  }


  void ezBlue() {
    //rev flywheel
    FLY.move(100);
    FLY1.move(100);
	
    //move forward to contact roller constantly
    LF.move(40);
    LB.move(40);
    RF.move(40);
    RB.move(40);
    delay(180);

    //decrease motor power so chassis doesn't burn out while spinning roller
    LF.move(10);
    LB.move(10);
    RF.move(10);
    RB.move(10);

    //spin to blue
    while (optical.get_hue() < 20) { //hue < 20 is blue
      INTAKE.move(90);
    }
    if (optical.get_hue() > 200) {
      INTAKE.move(0);
    }

    //go backwards
    driveStraight(-390);
    driveTurn(-125);

    //run intake for a bit
    INTAKE.move(127);

    //go towards disc still
    driveStraight(1400);
    driveTurn(55);

    //still disc
    driveStraight(800);
    driveTurn(-110);

    //still disc
    driveStraight(-670);

    //shoot disc 1
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
    delay(250);

    //shoot disc 2
    INDEXER.move(127);

    //flywheel faster?
    FLY.move(115);
    FLY1.move(115);
    delay(250);

    INDEXER.move(-127);
	  delay(250);

    //shoot disc 3
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(250);

    //shoot disc 4 (just in case)
	  INDEXER.move(127);
    delay(250);

    INDEXER.move(0);
    delay(1050);
  }


  void red() {
    //rev flywheel
    FLY.move(97);
    FLY1.move(97);

    //intake disc
    INTAKE.move(127);
    driveStraight(1000);
    driveTurn(46.5);

    //shoot disc 1
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
    delay(500);

    //shoot disc 2
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(750);

    //shoot disc 3
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(750);

    //shoot disc 4
	  INDEXER.move(127);
    delay(250);
    INDEXER.move(0);


    //INDEXER.move(127); //wait what is happening
    //delay(250);
    INDEXER.move(-127);
    delay(250);

    //shoot disc 5
    INDEXER.move(127);

    //increase flywheel voltage from 97
    FLY.move(115);
    FLY1.move(115);

    delay(250);
    INDEXER.move(-127);
	  delay(250);

    //shoot disc 6??
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(250);

    //shoot disc 7???
	  INDEXER.move(127);
    delay(250);
    INDEXER.move(0);

    //move to roller
    driveTurn(77.5);
    driveStraight(1950);
    driveTurn(56);

    //stop intake
    INTAKE.move(0);

    //constant forward movement for constant contact with rollers
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(250);

    //decrease motor power so chassis doesn't burn out
    LF.move(4);
    LB.move(4);
    RF.move(4);
    RB.move(4);

    //spin to red
    while (optical.get_hue() > 200) {
      INTAKE.move(90);
    }
    if (optical.get_hue() < 20) {
      INTAKE.move(0);
    }
}


void blue() {
    //rev flywheel
    FLY.move(97);
    FLY1.move(97);

    //intake disc
    INTAKE.move(127);
    driveStraight(1000);
    driveTurn(46.5);

    //shoot disc 1
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
    delay(500);

    //shoot disc 2
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(750);

    //shoot disc 3
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(750);

    //shoot disc 4
	  INDEXER.move(127);
    delay(250);
    INDEXER.move(0);


    //INDEXER.move(127); //wait what is happening
    //delay(250);
    INDEXER.move(-127);
    delay(250);

    //shoot disc 5
    INDEXER.move(127);

    //increase flywheel voltage from 97
    FLY.move(115);
    FLY1.move(115);

    delay(250);
    INDEXER.move(-127);
	  delay(250);

    //shoot disc 6??
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);
	  delay(250);

    //shoot disc 7???
	  INDEXER.move(127);
    delay(250);
    INDEXER.move(0);

    //move to roller
    driveTurn(77.5);
    driveStraight(1950);
    driveTurn(56);

    //stop intake
    INTAKE.move(0);

    //constant forward movement for constant contact with rollers
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(250);

    //decrease motor power so chassis doesn't burn out
    LF.move(4);
    LB.move(4);
    RF.move(4);
    RB.move(4);

    //spin to blue
    while (optical.get_hue() < 20) {
      INTAKE.move(90);
    }
    if (optical.get_hue() > 200) {
      INTAKE.move(0);
    }
}


void skills() {

}

  void autonomous() { //this is what runs the autons
  if (currAuton == 1) ezRed();
  else if (currAuton == 2) ezBlue();
  else if (currAuton == 3) red();
  else if (currAuton == 4) blue();
  else if (currAuton == 5) skills();
}