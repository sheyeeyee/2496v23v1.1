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
    //AUTON 0: SKILLS
    //AUTON 1: ROLLER
    //AUTON 2: NON-ROLLER
    //AUTON 3: ELIMS ROLLER
    //AUTON 4: ELIMS NON-ROLLER
    //AUTON 5: 

//111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

  //ROLLER (MIGHT BE SOLO AWP, SHOOTS TWICE)
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
    delay(250);
    CATA.move(0);

    //release bands
    extender.set_value(true);
    delay(500);
    extender.set_value(false);
    delay(500);

    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);


    /* below is testing for solo AWP */

    //turn to other roller
    driveTurn(-90);

    //drive toward roller
    driveStraight(2150);
    driveTurn(45);

    //spin 2nd roller
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
    delay(250);
    CATA.move(0);

    //release bands
    extender.set_value(true);
    delay(500);
    extender.set_value(false);
    delay(500);

    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);

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
  }

//3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333

  //ELIMS ROLLER (starts next to low goal)
  else if (atn == 3) {
    INTAKE.move(127);
    
    driveStraight(1600); //1670 //950 //850
    driveTurn(133);

    driveStraight(-75);
    
    CATA.move(-127);
    delay(250);
    CATA.move(0);

    //release bands
    extender.set_value(true);
    delay(500);
    extender.set_value(false);
    delay(500);

    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);
    
    driveStraight(375);
    driveTurn(94);
    
    driveStraight(2500);
    driveTurn(-45);
    
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
  }

//44444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

  //ELIMS NON-ROLLER
  else if (atn == 4) {
    //drive toward center field
    INTAKE.move(127);
    driveStraight(1675); //1600

    //huge turn toward high goal
    driveTurn(-136);//138
    delay(300);
    
    //shoot 2-3 discs
    CATA.move(-127);
    delay(250);
    CATA.move(0);

    //release bands
    extender.set_value(true);
    delay(500);
    extender.set_value(false);
    delay(500);

    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);

    //turn toward 2 discs and intake
    driveTurn(-91);//89
    driveStraight(2400);

    //toward roller
    driveTurn(45);
    // driveStraight(150);
    INTAKE.move(0);
    LF.move(50);
    LM.move(50);
    LB.move(50);
    RF.move(50);
    RM.move(50);
    RB.move(50);
    //spin roller
    delay(280);
    INTAKE.move(0);
    LF.move(10);
    LM.move(10);
    LB.move(10);
    RF.move(10);
    RM.move(10);
    RB.move(10);
    delay(800);

    INTAKE.move_relative(-800, -600);
    delay(1000);
    // driveShoot(-150);
    driveStraight(-150);
    // driveTurn(10);
  }

//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
  
  //SKILLS
  else if (atn == 0) {
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
    driveStraight(-603);
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
    INTAKE.move_relative(1000, 600);
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
    INTAKE.move_relative(1000, 600);
    delay(800);
    driveStraight(-700);

    //turn toward low goal shot
    driveTurn(-15);

    //back to low goal shot
    driveStraight(-1800);

    //turn to aim
    driveTurn(18); //19 //17
    
    //shoot
    CATA.move(-127);
    delay(190);

    //turn to go forward away from low goal
    driveTurn(-15); //14 //16

    //forward out of low goal shot position
    driveStraight(1075); //950 //1000

    //turn to face 3 discs in row
    driveTurn(-123); //124
    INTAKE.move(127);
    driveSlow(2000);

    //turn to shoot at low goal corner
    driveTurn(90); //85
    // driveSmall(-200);
    delay(200);
    CATA.move(-127);
    delay(190);

    while(catalim.get_value() == false) {
      CATA.move(-127);
    }
    CATA.move(0);

    // driveSmall(150);

    //turn to 3-stack
    driveTurn(-84); //86 //-82 //83
    angler.set_value(true);
    driveStraight(1000); //1670 //950 //850
    angler.set_value(false);
    delay(800);

    //turn to aim second low goal shot
    driveTurn(86);
    delay(350);
    driveStraight(-570); //500
    driveTurn(-34); //25 //28 //32
    CATA.move(-127);
    delay(190);
        
    //turn away from second low goal shot
    driveTurn(-19); //25 //-22 //-21

    //drive to roller
    driveStraight(1500);//1600
    driveTurn(-85); //-86
    driveStraight(320);
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
    INTAKE.move_relative(1000, 600);
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
    INTAKE.move_relative(1000, 600);
    delay(800);

    driveStraight(-760);
    driveTurn(-44);
    driveStraight(500);

    //expansion
    expand.set_value(true);
  }

//55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

  //SOLO AWP (ONLY SHOOTS ONCE)
  else if(atn == 5) {
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
    driveTurn(-135);

    //back toward center field
    angler.set_value(true);
    INTAKE.move(127);
    driveStraight(2150 / 2);
    
    delay(350);
    angler.set_value(false);
    INTAKE.move(0);

    driveStraight(2150 / 2);
    driveTurn(-95);
    driveStraight(-100);

    //shoot 3 discs
    CATA.move(-127);
    delay(200);
    while(catalim.get_value() == false) CATA.move(-127);
    CATA.move(0);

    //release bands
    extender.set_value(true);
    delay(180);
    extender.set_value(false);

    //turn to other roller
    driveTurn(-90);

    //intake 3 discs in a row while driving to other roller
    INTAKE.move(127);
    driveStraight(2150);
    driveTurn(45);

    //spin 2nd roller
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
  }

//////////////////////////////ARCHIVE/////////////////////////////////////////////////////////////////////////////////////////////////////////
//OLD SKILLS (TRIED TO GET TO OTHER MATCH LOADER)
//       //back out from second roller
//       driveStraight(-1250);

//       //turn right to position for run across the field
//       driveTurn(46);

//       //backward across field to push discs out of the way
//       driveStraight(-4200);

//       //forward to reposition for next match loader
//       driveStraight(400);

//       //turn a lot to back into match loader
//       driveTurn(-115);

//       //start intake to make sure discs fall into place again
//       INTAKE.move(127);

//       //drive back toward second match loader
//       driveStraight(-1450);

//       //turn to adjust to second match loader
//       driveTurn(-35);

//       //forward to adjust more to second match loader
//       driveStraight(250);
//       // delay(300);
      
//       //shoot three cycles at second match loader
//       i = 0;
//       while (i <= 2) {
//         delay (1500);
//         CATA.move(-127);
//         delay(190);

//         while(catalim.get_value() == false) {
//             CATA.move(-127);
//         }
//         CATA.move(0);
//         i++;
//       }

//       //reposition by going backwards for enough space to turn towards next spot (expansion)
//       driveStraight(-600);
//       driveTurn(36);

//       //intake up for 3-stack
//       angler.set_value(true);
//       driveStraight(1690); //1670
//       angler.set_value(false);
//       delay(600);

//       //turn toward roller
//       driveTurn(-24);
//       driveStraight(1100);

//       //second set of rollers
//       //move forward to far (first) roller
//       INTAKE.move(0);
//         LF.move(60);
//         LM.move(60);
//         LB.move(60);
//         RF.move(60);
//         RM.move(60);
//         RB.move(60);
//         delay(450);

//         //less voltage toward roller to prevent too much friction
//         LF.move(10);
//         LM.move(10);
//         LB.move(10);
//         RF.move(10);
//         RM.move(10);
//         RB.move(10);

//         //spin the intake a certain amount
//         INTAKE.move_relative(1100, 600);
//         delay(800);
        
//       //back out from roller
//       driveStraight(-820);

//       //turn toward other roller
//       driveTurn(-85);

//       //move to roller
//       driveStraight(600);
      
//       //move forward to second roller
//       INTAKE.move(0);
//         LF.move(60);
//         LM.move(60);
//         LB.move(60);
//         RF.move(60);
//         RM.move(60);
//         RB.move(60);
//         delay(450);
      
//         LF.move(10);
//         LM.move(10);
//         LB.move(10);
//         RF.move(10);
//         RM.move(10);
//         RB.move(10);

//         //spin the intake a certain amount for second roller
//         INTAKE.move_relative(1100, 600);
//         delay(800);
      
//       //back out from second roller
//       driveStraight(-500);

//       //turn right to position for expansion
//       driveTurn(5);
//       driveStraight(-500);
//        i = 0;
//       while (i <= 0) {
//         delay (1500);
//         CATA.move(-127);
//         delay(190);

//         while(catalim.get_value() == false) {
//             CATA.move(-127);
//         }
//         CATA.move(0);
//         i++;
//       }

//       //expansion
//       expand.set_value(true);
}