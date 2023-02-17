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
    //AUTON 1: RED NON-ROLLER
    //AUTON 2: BLUE NON-ROLLER
    //AUTON 3: RED ROLLER
    //AUTON 4: BLUE ROLLER
    //AUTON 5: FULL AWP
    //AUTON 6: SKILLS

// //11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

//   //RED NON-ROLLER
//   if (atn == 1){
//   }

// //22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

//   //BLUE NON-ROLLER
//   else if(atn == 2){
//   }

//   //3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
  
//   //RED ROLLER
//   else if(atn == 3){
//   }

// //444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

//   //BLUE ROLLER
//   else if(atn == 4){
//   }

// //55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

//   else if (atn == 5) {
//   }

// //666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666

  //SKILLS + HALF AWP
//   else if(atn == 6){

  ///////////////START HALF AWP/////////////////////////////////////////////////////////////////////////////////////

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
      driveStraight(-2100);
      driveTurn(-95);
      CATA.move(-127);
      delay(200);
      while(catalim.get_value() == false) CATA.move(-127);
      CATA.move(0);
      INTAKE.move(127);
      delay(600);
      CATA.move(-127);
      delay(200);
      while(catalim.get_value() == false) CATA.move(-127);
      CATA.move(0);
      extender.set_value(true);
      delay(180);
      extender.set_value(false);

      delay(99999999);


      //////END HALF AWP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // driveTurn(-85);
      // driveStraight(2100);
      // driveTurn(50);
      // driveStraight(400);
      // INTAKE.move(0);

      // LF.move(20);
      // LM.move(20);
      // LB.move(20);
      // RF.move(20);
      // RM.move(20);
      // RB.move(20);
      // delay(450);


      //spin the intake a certain amount
      // INTAKE.move(127);

      // INTAKE.move_relative(-500, -600);
      // delay(800);



//////start skills////////////////////////////////////////////////////////////////////////////
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

      ////////////////////

      // while(catalim.get_value() == false) {
      //     CATA.move(-127);
      // }
      // CATA.move(0);
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
  // }



  ////////////////////////////////////end//////
      
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
//   // }
}