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
    delay(180);
      INTAKE.move(0);
      LF.move(20);
      LM.move(20);
      LB.move(20);
      RF.move(20);
      RM.move(20);
      RB.move(20);
      delay(450);

      INTAKE.move_relative(-500, -600);
      delay(800);
        
      //back out from roller
      driveStraight(-400);
      driveTurn(50);

      //back toward center field
      driveStraight(-2150);
      driveTurn(-95);

      //shoot 1st disc
      CATA.move(-127);
      delay(200);
      while(catalim.get_value() == false) CATA.move(-127);
      CATA.move(0);

      //intake 2nd disc
      INTAKE.move(127);
      delay(800);

      //shoot 2nd disc
      CATA.move(-127);
      delay(200);
      while(catalim.get_value() == false) CATA.move(-127);
      CATA.move(0);

      //release bands
      extender.set_value(true);
      delay(180);
      extender.set_value(false);
  }

//22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

  //NON-ROLLER
  else if (atn == 2) {
    //back toward center field
    driveStraight(-2000);
    
    //outtake-ish 2nd disc
    INTAKE.move_relative(-500, -600);

    driveTurn(44);
    
    //shoot 1st disc
    CATA.move(-127);
    delay(200);
    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);

    //intake 2nd disc
    INTAKE.move(127);
    delay(600);

    //shoot 2nd disc
    CATA.move(-127);
    delay(200);
    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);

    //release bands
    extender.set_value(true);
    delay(180);
    extender.set_value(false);

    //turn toward 2 discs and intake
    driveTurn(-91);
    driveStraight(2500);

    //toward roller
    driveTurn(45);
    driveStraight(150);

    //spin roller
    delay(180);
    INTAKE.move(0);
    LF.move(20);
    LM.move(20);
    LB.move(20);
    RF.move(20);
    RM.move(20);
    RB.move(20);
    delay(800);

    INTAKE.move_relative(-500, -600);
    delay(1000);

    driveStraight(-200);
  }

//3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
  
  //SKILLS
  else if (atn == 3) {
    //run intake to ensure discs fall into the right place
    INTAKE.move(127);
    delay(300);
      
    //shoot three cycles
    int i = 0;
    while (i <= 2) {
      while(catalim.get_value() == false) CATA.move(-127);
      CATA.move(0);
      delay(1500);
      CATA.move(-127);
      delay(400);
      
      CATA.move(0);
      i++;
    }
    CATA.move(0);


    //reposition by going backwards for enough space to turn towards next spot
    driveStraight(-600);
    driveTurn(36);
    //intake up for 3-stack
    angler.set_value(true);
    driveStraight(1670); //1670
    angler.set_value(false);
    delay(600);

    //turn toward roller
    driveTurn(-28);
    driveStraight(1000);
    INTAKE.move(0);

    //move forward to far (first) roller
    INTAKE.move(0);
    LF.move(60);
    LM.move(60);
    LB.move(60);
    RF.move(60);
    RM.move(60);
    RB.move(60);
    delay(450);

    //less voltage toward roller to prevent too much friction
    LF.move(10);
    LM.move(10);
    LB.move(10);
    RF.move(10);
    RM.move(10);
    RB.move(10);

    //spin the intake a certain amount
    // INTAKE.move(127);
    INTAKE.move_relative(1100, 600);
    delay(800);
    INTAKE.move(127);
      
    //back out from roller
    driveStraight(-780); // -820
    //turn toward other roller
    driveTurn(-88);
    //move to roller
    driveStraight(600);
      
    //move forward to second roller
    INTAKE.move(0);
    LF.move(60);
    LM.move(60);
    LB.move(60);
    RF.move(60);
    RM.move(60);
    RB.move(60);
    delay(450);
    
    LF.move(10);
    LM.move(10);
    LB.move(10);
    RF.move(10);
    RM.move(10);
    RB.move(10);
    //spin the intake a certain amount for second roller
    INTAKE.move_relative(1100, 600);
    delay(800);
    driveStraight(-700);
    //turn right to position for expansion
    driveTurn(-15);
    driveStraight(-1800);
    driveTurn(19);
      
    CATA.move(-127);
    delay(190);
    driveTurn(-14);

    driveStraight(1000);//950
    driveTurn(-124);
    INTAKE.move(127);
    driveSlow(2000);
    driveTurn(85);
    // driveSmall(-200);
    CATA.move(-127);
    delay(190);

    while(catalim.get_value() == false) {
      CATA.move(-127);
    }
    CATA.move(0);

    // driveSmall(150);

    driveTurn(-87); //86
    angler.set_value(true);
    driveStraight(950); //1670
    angler.set_value(false);
    delay(600);
    driveTurn(86);
    driveStraight(-500);
    driveTurn(-25);
    CATA.move(-127);
    delay(190);

  // while(catalim.get_value() == false) {
  //     CATA.move(-127);
  // }
  // CATA.move(0);

        
    driveTurn(-25);
    driveStraight(1600);
    driveTurn(-86);
    driveStraight(380);
    INTAKE.move(0);
    LF.move(60);
    LM.move(60);
    LB.move(60);
    RF.move(60);
    RM.move(60);
    RB.move(60);
    delay(450);

    //less voltage toward roller to prevent too much friction
    LF.move(10);
    LM.move(10);
    LB.move(10);
    RF.move(10);
    RM.move(10);
    RB.move(10);

    //spin the intake a certain amount
    // INTAKE.move(127);
    INTAKE.move_relative(1100, 600);
    delay(800);
    INTAKE.move(127);
        
    //back out from roller
    driveStraight(-820);

    //turn toward other roller
    driveTurn(88);

    //move to roller
    driveStraight(550);
     
    //move forward to second roller
    INTAKE.move(0);
    LF.move(60);
    LM.move(60);
    LB.move(60);
    RF.move(60);
    RM.move(60);
    RB.move(60);
    delay(450);
    
    LF.move(10);
    LM.move(10);
    LB.move(10);
    RF.move(10);
    RM.move(10);
    RB.move(10);
  
    //spin the intake a certain amount for second roller
    INTAKE.move_relative(1100, 600);
    delay(800);

    driveStraight(-760);
    driveTurn(-44);
    driveStraight(500);

    //expansion
    expand.set_value(true);
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