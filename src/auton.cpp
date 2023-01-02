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
  INTAKE.move(127);
  delay(300);
  int i = 0;
  while (i <= 2){
    delay (1500);
    CATA.move(-127);
    delay(190);
    while(catalim.get_value() == false){
      	CATA.move(-127);
    }
    CATA.move(0);
    i++;
  }
  CATA.move(0);
  driveStraight(-600);
  driveTurn(35);
  angler.set_value(true);
  driveStraight(1670);
  angler.set_value(false);
  delay(600);
  driveTurn(-24);
  driveStraight(1100);
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
        INTAKE.move_relative(1100, 600);
        delay(800);
      driveStraight(-820);
      driveTurn(-85);
      driveStraight(600);
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
      INTAKE.move_relative(1100, 600);
      delay(800);
       driveStraight(-700);


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
//     //set flywheel voltage
//     FLY.move(108);
//     FLY1.move(108);

//     //outtake to prevent disc jam
//     INTAKE.move(127);
//     driveStraight(1000);
//     // delay(1000);
//     // driveStraight(-400);
//     // delay(200);
//     // driveStraight(400);
//     // delay(200);
//     driveTurn(48);

//     //shoot disc 1
//     INDEXER.move(127);
//     delay(250);
//     INDEXER.move(-127);

//     //speed up flywheel from 100
//     FLY.move(102);
//     FLY1.move(102);

//     //shoot disc 2
//     delay(2000);
//     INDEXER.move(127);
//     delay(250);
//     INDEXER.move(-127);

//     //shoot disc 3
//     delay(2000);
//     INDEXER.move(127);
//     delay(250);
//     INDEXER.move(-127);

//     // //shoot disc 4
//     // delay(750);
//     // INDEXER.move(127);

//     delay(200);
//     INDEXER.move(0);

//     //turn towards roller
//     driveTurn(74);
//     driveStraight(1985);
//     driveTurn(57);
//     delay(100);
//     INTAKE.move(0);

//     // INTAKE.move(-127);
//     // delay(350);
//     INTAKE.move(-110);
//     LF.move(40);
//     LB.move(40);
//     RF.move(40);
//     RB.move(40);
//     delay(900);

//     //drive backwards immediately after spinning roller
//     // driveStraight(-300);

//     // move forward more??
//     LF.move(5);
//     LB.move(5);
//     RF.move(5);
//     RB.move(5);

//     delay(100);

//     LF.move(5);
//     LB.move(5);
//     RF.move(5);
//     RB.move(5);
//     delay(500);    

//     //spin roller to red
//     while(true){
//       while (optical.get_hue() < 20) {
//       INTAKE.move(-80);
//       con.print(0, 0, "Going");
//       }

//       if (optical.get_hue() > 200) {
//         INTAKE.move(40);
//         delay(180);
//         INTAKE.move(0);
//         con.print(0, 2, "Done");
//         break;
//       }
//     }
    
//     // INDEXER.move(-127);
//     // delay(750);
//     // INDEXER.move(127); // should it be indexerToggle?
//     // delay(250);
//     // INDEXER.move(0);
//   }

// //22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

//   //BLUE NON-ROLLER
//   else if(atn == 2){
//     //set flywheel voltage
//     FLY.move(110);
//     FLY1.move(110);

//     //intake singular disc (not sure if disc gets jammed or not)
//     INTAKE.move(127);
//     driveStraight(1000);
//     // delay(1000);
//     // driveStraight(-400);
//     // delay(200);
//     // driveStraight(400);
//     // delay(200);
//     driveTurn(49);
//     delay(500);
//     //shoot disc 1
//     INDEXER.move(127);
//     delay(250);
//     INDEXER.move(-127);

//     //speed up flywheel from 100
//     // FLY.move(114);
//     // FLY1.move(114);

//     //shoot disc 2
//     delay(750);
//     INDEXER.move(127);
//     delay(250);
//     INDEXER.move(-127);

//     //shoot disc 3
//     delay(500);
//     INDEXER.move(127);
//     delay(250);
//     INDEXER.move(-127);

//     // //shoot disc 4
//     // delay(750);
//     // INDEXER.move(127);
//     // delay(250);
//     // INDEXER.move(0);

//     // INDEXER.move(127);
//     // delay(250);
//     // INDEXER.move(-127);
//     // delay(250);

//     // INDEXER.move(127);
    
//     // FLY.move(115);
//     // FLY1.move(115);
    
//     // delay(250);
//     // INDEXER.move(-127);
//     // delay(250);
//     // INDEXER.move(127);

//     // delay(250);
//     // INDEXER.move(-127);
//     // delay(250);
//     // INDEXER.move(127);

//     // delay(250);
//     // INDEXER.move(0);

//     //turn towards roller
//     driveTurn(76);
//     driveStraight(1985);
//     driveTurn(57);
//     delay(100);
//     INTAKE.move(0);
    
//     LF.move(40);
//     LB.move(40);
//     RF.move(40);
//     RB.move(40);
//     delay(500);

//     // move forward more??
//     LF.move(6);
//     LB.move(6);
//     RF.move(6);
//     RB.move(6);

//     delay(100);

//     LF.move(5);
//     LB.move(5);
//     RF.move(5);
//     RB.move(5);
//     delay(500);    

//     //spin roller to blue
//      while(true){
//       while (optical.get_hue() > 200) {
//       INTAKE.move(-110);
//       con.print(0, 0, "Going");
//       }

//       if (optical.get_hue() < 20) {
//         INTAKE.move(110);
//         delay(180);
//         INTAKE.move(0);
//         con.print(0, 2, "Done");
//         break;
//       }
//     }
    
//     // INDEXER.move(-127);
//     // delay(750);
//     // INDEXER.move(127); // should it be indexerToggle?
//     // delay(250);
//     // INDEXER.move(0);
//   }

//   //3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333
  
//   //RED ROLLER
//   else if(atn == 3){
//     bool Global = false;
    
//       FLY.move(109);
//       FLY1.move(109);
      
//       // FLY.move_velocity(480);
//       // FLY1.move_velocity(480);

//       INTAKE.move(127);
//       delay(350);
      
//       LF.move(40);
//       LB.move(40);
//       RF.move(40);
//       RB.move(40);
//       delay(500);

//       // move forward more??
//       LF.move(5);
//       LB.move(5);
//       RF.move(5);
//       RB.move(5);

//       delay(100);

//       LF.move(5);
//       LB.move(5);
//       RF.move(5);
//       RB.move(5);
//       delay(500);    

//       //spin roller to red
//       // while(true){
//       //   while (optical.get_hue() < 20) {
//       //   INTAKE.move(-10);
//       //   con.print(0, 0, "Going");
//       //   }

//       //   if (optical.get_hue() > 200) {
//       //     INTAKE.move(40);
//       //     delay(180);
//       //     INTAKE.move(0);
//       //     con.print(0, 2, "Done");
//       //     break;
//       //   }
//       // }
//       INTAKE.move(-40);
//       delay(2000);
//       // // move forward to contact roller
//       // LF.move(40);
//       // LB.move(40);
//       // RF.move(40);
//       // RB.move(40);
//       // delay(180);

//       // // move forward more??
//       // LF.move(10);
//       // LB.move(10);
//       // RF.move(10);
//       // RB.move(10);

//       driveStraight(-320);
//       driveTurn(-126);
//       INTAKE.move(127);
//       driveStraight(1380);
//       driveTurn(-48);
//       delay(250);
//       // driveStraight(750);
//       // driveTurn(-110);
//       // driveStraight(-700);
//       INDEXER.move(127);
            
//       //shoot discs  
//       delay(250);
//       INDEXER.move(-127); 
//       delay(2500);
//       INDEXER.move(127);

//       delay(250);
//       INDEXER.move(-127);
//       delay(2500);//delay
//       INDEXER.move(127);

//       delay(250);
//       INDEXER.move(-127);
//       delay(2500);
//       INDEXER.move(127);

//       delay(250);
//       INDEXER.move(0);
//       delay(1050);
//   }

// //444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444

//   //BLUE ROLLER
//   else if(atn == 4){
//     bool Global = false;
    
//       FLY.move(106);
//       FLY1.move(106);
//       // FLY.move_velocity(480);
//       // FLY1.move_velocity(480);

//       INTAKE.move(127);
//       delay(350);

//       LF.move(30);
//       LB.move(30);
//       RF.move(30);
//       RB.move(30);
//       delay(2000);

//       // move forward more??
//       LF.move(5);
//       LB.move(5);
//       RF.move(5);
//       RB.move(5);

//       delay(100);

//       LF.move(0);
//       LB.move(0);
//       RF.move(0);
//       RB.move(0);
//       // delay(500);

//       INTAKE.move(0);

//       //spin roller to blue
//       while(true){
//         while (optical.get_hue() > 200) {
//         INTAKE.move(-127);
//         con.print(0, 0, "Going");
//         }

//         if (optical.get_hue() < 20) {
//           INTAKE.move(127);
//           delay(150);
//           INTAKE.move(0);
//           con.print(0, 2, "Done");
//           break;
//         }
//       }

//       driveStraight(-390);
//       driveTurn(-125);
//       INTAKE.move(127);
//       driveStraight(1400);
//       driveTurn(-48);

//       // driveStraight(750);
//       // driveTurn(-110);
//       // driveStraight(-700);

//       INDEXER.move(127);
              
//       delay(250);
//       INDEXER.move(-127); 
//       delay(3000);
//       INDEXER.move(127);

//       delay(250);
//       INDEXER.move(-127);
//       delay(3000);
//       INDEXER.move(127);

//       delay(250);
//       INDEXER.move(-127);
//       delay(3000);
//       INDEXER.move(127);

//       delay(250);
//       INDEXER.move(0);
//       delay(1050);
//   }

// //55555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555

//   else if (atn == 5) {

//   }

// //666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666

//   //SKILLS
//   else if(atn == 6){
//     FLY.move(84);
//     FLY1.move(84);
//     angler.set_value(false);
    
//     //shoot disc 1
//     delay(2500);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 2
//     delay(2500);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 3
//     delay(2500);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 4
//     delay(2500);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 5
//     delay(2500);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 6
//     delay(3000);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 7
//     delay(3000);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 8
//     delay(3000);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 9
//     delay(3000);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);

//     //shoot disc 10
//     delay(3000);
//     INDEXER.move(127);
//     delay(240);
//     INDEXER.move(-127);
//     delay(250);

//     //first roller
//     driveStraight(-2600);
//     driveTurn(75);
//     driveStraight(380); //390?
//     INTAKE.move(127);
    
//     // delay(350);
      
//     LF.move(50);
//     LB.move(50);
//     RF.move(50);
//     RB.move(50);
//     delay(1000);

//     // move forward more??
//     LF.move(5);
//     LB.move(5);
//     RF.move(5);
//     RB.move(5);

//     delay(100);

//     LF.move(0);
//     LB.move(0);
//     RF.move(0);
//     RB.move(0);
//     // delay(500);
//     //spin roller to red
//     while(true){
//       while (optical.get_hue() > 200) {
//       INTAKE.move(100);
//       con.print(0, 0, "Going");
//       }

//       if (optical.get_hue() < 20) {
//         INTAKE.move(-100);
//         delay(130);
//         INTAKE.move(0);
//         con.print(0, 2, "Done");
//         break;
//       }
//     }

//     delay(250);
//     FLY.move(0);
//     FLY1.move(0);
    
//     //spin roller to red
//     // while(true){
//     //   while (optical.get_hue() < 20) {
//     //   INTAKE.move(-90);
//     //   con.print(0, 0, "Going");
//     //   }

//     //   if (optical.get_hue() > 200) {
//     //     INTAKE.move(90);
//     //     delay(180);
//     //     INTAKE.move(0);
//     //     con.print(0, 2, "Done");
//     //     break;
//     //   }
//     // }

//     //second roller
//     driveStraight(-1125);
//     driveTurn(90);
//     INTAKE.move(127);

//     driveStraight(720);
//     driveStraight(-400);
//     driveStraight(750);
//     // INTAKE.move(127);

//     delay(1000);
//     // INTAKE.move(-127);

//     // delay(1000);

//     // INTAKE.move(127);

//     // delay(2000);

//     LF.move(100);
//     LB.move(100);
//     RF.move(100);
//     RB.move(100);
//     delay(250);

//     // move forward more
//     LF.move(5);
//     LB.move(5);
//     RF.move(5);
//     RB.move(5);
//     while(true){
//         while (optical.get_hue() > 200) {
//         INTAKE.move(100);
//         con.print(0, 0, "Going");
//         }

//         if (optical.get_hue() < 20) {
//           INTAKE.move(-100);
//           delay(130);
//           INTAKE.move(0);
//           con.print(0, 2, "Done");
//           break;
//         }
//     }
//     delay(500);

//     // LF.move(-50);
//     // LB.move(-50);
//     // RF.move(-50);
//     // RB.move(-50);



//     // //spin roller to red
//     // while(true){
//     //   while (optical.get_hue() > 200) {
//     //   INTAKE.move(80);
//     //   con.print(0, 0, "Going");
//     //   }

//     //   if (optical.get_hue() < 20) {
//     //     INTAKE.move(-70);
//     //     delay(120);
//     //     INTAKE.move(0);
//     //     con.print(0, 2, "Done");
//     //     break;
//     //   }
//     // }

    
//     // INTAKE.move(-127);
//     // delay(250);
    
//     // while(true){
//     //   while (optical.get_hue() > 200) {
//     //   INTAKE.move(-127);
//     //   con.print(0, 0, "Going");
//     //   }

//     //   if (optical.get_hue() < 20) {
//     //     INTAKE.move(127);
//     //     delay(150);
//     //     INTAKE.move(0);
//     //     con.print(0, 2, "Done");
//     //     break;
//     //   }
//     // }

//     //move to get to expansion spot
//     delay(400);
//     driveStraight(-1000);
//     driveTurn(-60);
//     driveStraight(600);
//     INTAKE.move(0);
    
//     //expansion
//     expand.set_value(true);
//     delay(1500);

//     //turn to get 4 tiles from chassis
//     driveTurn(45);
//     driveStraight(-70);
//   }
}