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
    //AUTON 5: EMPTY
    //AUTON 6: EMPTY

  //RED NON-ROLLER
  if (atn == 1){
    FLY.move(103);
    FLY1.move(103);

    INTAKE.move(127);
    driveStraight(1000);
    driveTurn(46);

    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    FLY.move(112);
    FLY1.move(112);

    delay(500);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(0);

    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);
    // delay(250);

    // INDEXER.move(127);
    // FLY.move(115);
    // FLY1.move(115);
    // delay(250);

    // INDEXER.move(-127);
    // delay(250);
    // INDEXER.move(127);
    // delay(250);

    // INDEXER.move(-127);
    // delay(250);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(0);

    driveTurn(79);
    driveStraight(2050);
    driveTurn(55);
    INTAKE.move(0);

    delay(1000);
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(250);

    // move forward more??
    LF.move(5);
    LB.move(5);
    RF.move(5);
    RB.move(5);

    delay(500);

    LF.move(0);
    LB.move(0);
    RF.move(0);
    RB.move(0);

    // spin roller
     while(true){
      while (optical.get_hue() < 20) {
      INTAKE.move(-100);
      con.print(0, 0, "Going");
      }

      if (optical.get_hue() > 200) {
        INTAKE.move(70);
        delay(250);
        INTAKE.move(0);
        con.print(0, 2, "Done");
        break;
      }
    }

    INDEXER.move(-127);
    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(0);
  }

//22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

  //BLUE NON-ROLLER
  else if(atn == 2){
    //set flywheel voltage
    FLY.move(100);
    FLY1.move(100);

    //intake discs
    INTAKE.move(127);
    driveStraight(1000);
    driveTurn(48);

    //shoot disc 1
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    //speed up flywheel from 100
    FLY.move(114);
    FLY1.move(114);

    //shoot disc 2
    delay(500);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    //shoot disc 3
    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    //shoot disc 4
    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(0);

    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);
    // delay(250);

    // INDEXER.move(127);
    
    // FLY.move(115);
    // FLY1.move(115);
    
    // delay(250);
    // INDEXER.move(-127);
    // delay(250);
    // INDEXER.move(127);

    // delay(250);
    // INDEXER.move(-127);
    // delay(250);
    // INDEXER.move(127);

    // delay(250);
    // INDEXER.move(0);

    //turn towards roller
    driveTurn(78);
    driveStraight(1950);
    driveTurn(56);
    INTAKE.move(0);

    //move intricately towards roller for proper contact
    delay(1000);
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(800);

    //move forward even more intricately for proper contact
    LF.move(5);
    LB.move(5);
    RF.move(5);
    RB.move(5);
    delay(500);
    LF.move(2);
    LB.move(2);
    RF.move(2);
    RB.move(2);

    //spin roller
    while(true){
      while (optical.get_hue() > 200) {
      INTAKE.move(-90);
      con.print(0, 0, "Going");
      }

      if (optical.get_hue() < 20) {
        INTAKE.move(70);
        delay(250);
        INTAKE.move(0);
        con.print(0, 2, "Done");
        break;
      }
    }

    // INDEXER.move(-127);
    // delay(750);
    // INDEXER.move(127); // should it be indexerToggle?
    // delay(250);
    // INDEXER.move(0);
  }

  //3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
  
  //RED ROLLER
  else if(atn == 3){
    bool Global = false;
    
      FLY.move(104);
      FLY1.move(104);
      
      // FLY.move_velocity(480);
      // FLY1.move_velocity(480);

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

      //spin roller
      while (optical.get_hue() < 20) {
        INTAKE.move(90);
      }

      if (optical.get_hue() > 200) {
        INTAKE.move(0);
      }

      driveStraight(-320);
      driveTurn(-125);
      INTAKE.move(127);
      driveStraight(1400);
      driveTurn(-47);
      delay(180);
      // driveStraight(750);
      // driveTurn(-110);
      // driveStraight(-700);
      INDEXER.move(127);
            
      //shoot discs  
      delay(250);
      INDEXER.move(-127); 
      delay(2500);
      INDEXER.move(127);

      delay(250);
      INDEXER.move(-127);
      delay(2500);//delay
      INDEXER.move(127);

      delay(250);
      INDEXER.move(-127);
      delay(2500);
      INDEXER.move(127);

      delay(250);
      INDEXER.move(0);
      delay(1050);
  }

//444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

  //BLUE ROLLER
  else if(atn == 4){
    bool Global = false;
    
      FLY.move(106);
      FLY1.move(106);
      // FLY.move_velocity(480);
      // FLY1.move_velocity(480);

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
        
      while(true){
        while (optical.get_hue() > 200) {
          INTAKE.move(-90);

          con.print(0, 0, "Going");
        }

        if (optical.get_hue() < 20) {
          INTAKE.move(70);
          delay(200);
          INTAKE.move(0);

          con.print(0, 2, "Done");
          break;
        }
      }

      driveStraight(-390);
      driveTurn(-125);
      INTAKE.move(127);
      driveStraight(1400);
      driveTurn(-48);

      // driveStraight(750);
      // driveTurn(-110);
      // driveStraight(-700);

      INDEXER.move(127);
              
      delay(250);
      INDEXER.move(-127); 
      delay(3000);
      INDEXER.move(127);

      delay(250);
      INDEXER.move(-127);
      delay(3000);
      INDEXER.move(127);

      delay(250);
      INDEXER.move(-127);
      delay(3000);
      INDEXER.move(127);

      delay(250);
      INDEXER.move(0);
      delay(1050);
  }

//55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

  //SKILLS (based on blue non-roller)
  else if(atn == 5){
    //set flywheel voltage
    FLY.move(100);
    FLY1.move(100);

    //intake discs
    INTAKE.move(127);
    driveStraight(1000);
    driveTurn(48);

    //shoot disc 1
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    //speed up flywheel from 100
    FLY.move(114);
    FLY1.move(114);

    //shoot disc 2
    delay(500);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    //shoot disc 3
    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    //shoot disc 4
    delay(750);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(0);

    //turn towards roller
    driveTurn(78);
    driveStraight(1950);
    driveTurn(56);
    INTAKE.move(0);

    //move intricately towards roller for proper contact
    delay(1000);
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(800);

    //move forward even more intricately for proper contact
    LF.move(5);
    LB.move(5);
    RF.move(5);
    RB.move(5);
    delay(500);
    LF.move(2);
    LB.move(2);
    RF.move(2);
    RB.move(2);

    //spin roller
    while(true){
      while (optical.get_hue() > 200) {
      INTAKE.move(-90);
      con.print(0, 0, "Going");
      }

      if (optical.get_hue() < 20) {
        INTAKE.move(70);
        delay(250);
        INTAKE.move(0);
        con.print(0, 2, "Done");
        break;
      }
    }

    //back and turn away from roller, face corner disc
    driveStraight(-100);
    driveTurn(-90);

    //intake disc
    INTAKE.move(127);
    driveStraight(100);
    delay(1000);

    //turn around to intake more discs
    driveTurn(-45);
  }

//6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666

  //yet to have auton 6
  else if(atn == 6){


    FLY.move(87);
    FLY1.move(87);
    angler.set_value(false);
    
    delay(2500);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    delay(2500);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    delay(2500);
    INDEXER.move(127);
    delay(250);
    INDEXER.move(-127);

    // delay(2500);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    // delay(2500);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    // delay(3000);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    // delay(3000);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    // delay(3000);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    // delay(3000);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    // delay(3000);
    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);

    driveStraight(-2600);
    driveTurn(72);
    driveStraight(900);
      
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(250);

    // move forward more??
    LF.move(5);
    LB.move(5);
    RF.move(5);
    RB.move(5);

    delay(500);

    LF.move(0);
    LB.move(0);
    RF.move(0);
    RB.move(0);

    INTAKE.move(-90);
    delay(200);
    INTAKE.move(0);


    while(true){
    while (optical.get_hue() < 20) {
    INTAKE.move(-100);
    con.print(0, 0, "Going");
    }

      if (optical.get_hue() > 200) {
        INTAKE.move(70);
        delay(250);
        INTAKE.move(0);
        con.print(0, 2, "Done");
        break;
      }
    }

    driveStraight(-950);
    driveTurn(-90);
    driveStraight(300);

    
    LF.move(100);
    LB.move(100);
    RF.move(100);
    RB.move(100);
    delay(250);

    // move forward more??
    LF.move(5);
    LB.move(5);
    RF.move(5);
    RB.move(5);

    delay(500);

    LF.move(0);
    LB.move(0);
    RF.move(0);
    RB.move(0);

    while(true){
    while (optical.get_hue() < 20) {
    INTAKE.move(-100);
    con.print(0, 0, "Going");
    }

      if (optical.get_hue() > 200) {
        INTAKE.move(70);
        delay(250);
        INTAKE.move(0);
        con.print(0, 2, "Done");
        break;
      }
    }


    



  }
}


//Red attmpt full op too slow
  // bool Global = false;
    // FLY.move(102);
    // FLY1.move(102);

	  // FLY.move_velocity(480);
    // FLY1.move_velocity(480);
		
    // // move forward to contact roller
    // LF.move(40);
    // LB.move(40);
    // RF.move(40);
    // RB.move(40);
    // delay(180);

    // // move forward more??
    // LF.move(10);
    // LB.move(10);
    // RF.move(10);
    // RB.move(10);

    // while (optical.get_hue() < 20) {
    //   INTAKE.move(90);
    // }

    // if (optical.get_hue() > 200) {
    //   INTAKE.move(0);
    // }


    // driveStraight(-390); //prev -390
    // driveTurn(-125);
    // INTAKE.move(127);

    // driveStraight(3200);
    // driveTurn(-70);

    // driveStraight(750);
    // driveTurn(-110);

    // driveStraight(-700);

    // INDEXER.move(127);
    // delay(250);
    // INDEXER.move(-127);
    // delay(600);

    // INDEXER.move(127);

    // FLY.move(108);
    // FLY1.move(108);

    // delay(250);
    // INDEXER.move(-127);
    // delay(600);
    // INDEXER.move(127);

    // delay(250);
    // INDEXER.move(-127);
    // delay(600);
    // INDEXER.move(127);

    // delay(250);
    // INDEXER.move(0);

    // delay(400);

    // driveTurn(56);
    // driveStraight(3300);