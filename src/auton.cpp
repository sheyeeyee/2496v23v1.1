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

if (atn == 1){
  //red non-roller side
  FLY.move(100);
      FLY1.move(100);
      INTAKE.move(127);
      driveStraight(1000);
      driveTurn(40);

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
	  INDEXER.move(127); // should it be indexerToggle?
      delay(250);
      INDEXER.move(0);


    //   INDEXER.move(127);
    //   delay(250);
    //   INDEXER.move(-127);
    //   delay(250);
    //   INDEXER.move(127);
    //        FLY.move(115);
    //   FLY1.move(115);
    //   delay(250);
    //   INDEXER.move(-127);
	  // delay(250);
    // INDEXER.move(127);
    //   delay(250);
    //   INDEXER.move(-127);
	  // delay(250);
	  // INDEXER.move(127); // should it be indexerToggle?
    //   delay(250);
    //   INDEXER.move(0);
      driveTurn(84);
      driveStraight(1950);
      driveTurn(56);
INTAKE.move(0);

delay(1000);
       LF.move(100);
      LB.move(100);
      RF.move(100);
      RB.move(100);
      delay(800);

      // move forward more??
      LF.move(5);
      LB.move(5);
      RF.move(5);
      RB.move(5);
delay(500);
            LF.move(2);
      LB.move(2);
      RF.move(2);
      RB.move(2);



      while(true){
         while (optical.get_hue() < 20) {
        INTAKE.move(-40);
         con.print(0, 0, "Going");
      }

     

      if (optical.get_hue() > 200) {
        INTAKE.move(0);
                 con.print(0, 2, "Done");
                 break;
      }

      }

     
            INDEXER.move(-127);
	  delay(750);
	  INDEXER.move(127); // should it be indexerToggle?
      delay(250);
      INDEXER.move(0);
}
else if(atn == 2){
  
//   //blue non-roller side
  FLY.move(110);
      FLY1.move(110);
      INTAKE.move(127);
      driveStraight(1000);
      driveTurn(38);

       INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
        FLY.move(117);
      FLY1.move(117);
      delay(500);
      INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
	  delay(750);
    INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
	  delay(750);
	  INDEXER.move(127); // should it be indexerToggle?
      delay(250);
      INDEXER.move(0);


    //   INDEXER.move(127);
    //   delay(250);
    //   INDEXER.move(-127);
    //   delay(250);
    //   INDEXER.move(127);
    //        FLY.move(115);
    //   FLY1.move(115);
    //   delay(250);
    //   INDEXER.move(-127);
	  // delay(250);
    // INDEXER.move(127);
    //   delay(250);
    //   INDEXER.move(-127);
	  // delay(250);
	  // INDEXER.move(127); // should it be indexerToggle?
    //   delay(250);
    //   INDEXER.move(0);
      driveTurn(80);
      driveStraight(1950);
      driveTurn(56);
INTAKE.move(0);

delay(1000);
       LF.move(100);
      LB.move(100);
      RF.move(100);
      RB.move(100);
      delay(800);

      // move forward more??
      LF.move(5);
      LB.move(5);
      RF.move(5);
      RB.move(5);
delay(500);
            LF.move(2);
      LB.move(2);
      RF.move(2);
      RB.move(2);


      
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


     
    //         INDEXER.move(-127);
	  // delay(750);
	  // INDEXER.move(127); // should it be indexerToggle?
    //   delay(250);
    //   INDEXER.move(0);


}
else if(atn == 3){

//roller side red half good
 bool Global = false;
     FLY.move(102);
      FLY1.move(102);
		  //    FLY.move_velocity(480);
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

      while (optical.get_hue() < 20) {
        INTAKE.move(90);
      }

      if (optical.get_hue() > 200) {
        INTAKE.move(0);
      }


            driveStraight(-390);
            driveTurn(-125);
            INTAKE.move(127);
            driveStraight(1400);
            driveTurn(-49);
            // driveStraight(750);
            // driveTurn(-110);
            // driveStraight(-700);
             INDEXER.move(127);
             
      delay(250);
      INDEXER.move(-127);
      delay(600);
      INDEXER.move(127);
           FLY.move(108);
      FLY1.move(108);
      delay(250);
      INDEXER.move(-127);
	  delay(600);
    INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
	  delay(600);
	  INDEXER.move(127); // should it be indexerToggle?
      delay(250);
      INDEXER.move(0);
      delay(700);
      delay(350);

}
else if(atn == 4){
  
//roller side blue half good
 bool Global = false;
     FLY.move(115);
      FLY1.move(115);
		  //    FLY.move_velocity(480);
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
        delay(250);
        INTAKE.move(0);

                 con.print(0, 2, "Done");
                 break;
      }

      }

            driveStraight(-390);
            driveTurn(-125);
            INTAKE.move(127);
            driveStraight(1400);
            driveTurn(-60);
            // driveStraight(750);
            // driveTurn(-110);
            // driveStraight(-700);
             INDEXER.move(127);
             
      delay(250);
      INDEXER.move(-127); 
      delay(3000);//delay
      INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
	  delay(3000);//delay
    INDEXER.move(127);
      delay(250);
      INDEXER.move(-127);
	  delay(3000); //delay
	  INDEXER.move(127); // should it be indexerToggle?
      delay(250);
      INDEXER.move(0);
      delay(700);
      delay(350);

}
else if(atn == 5){

}
else if(atn == 6){

}



}




//Red attmpt full op too slow


  
  // bool Global = false;
  //    FLY.move(102);
  //     FLY1.move(102);
	// 	  //    FLY.move_velocity(480);
  //     // FLY1.move_velocity(480);
		

  //     // move forward to contact roller
  //     LF.move(40);
  //     LB.move(40);
  //     RF.move(40);
  //     RB.move(40);
  //     delay(180);

  //     // move forward more??
  //     LF.move(10);
  //     LB.move(10);
  //     RF.move(10);
  //     RB.move(10);

  //     while (optical.get_hue() < 20) {
  //       INTAKE.move(90);
  //     }

  //     if (optical.get_hue() > 200) {
  //       INTAKE.move(0);
  //     }


  //           driveStraight(-390); //prev -390
  //           driveTurn(-125);
  //           INTAKE.move(127);
  //           driveStraight(1900);
  //           driveStraight(1300);
  //           driveTurn(-70);
  //           // driveStraight(750);
  //           // driveTurn(-110);
  //           // driveStraight(-700);
  //            INDEXER.move(127);
             
  //     delay(250);
  //     INDEXER.move(-127);
  //     delay(600);
  //     INDEXER.move(127);
  //          FLY.move(108);
  //     FLY1.move(108);
  //     delay(250);
  //     INDEXER.move(-127);
	//   delay(600);
  //   INDEXER.move(127);
  //     delay(250);
  //     INDEXER.move(-127);
	//   delay(600);
	//   // INDEXER.move(127); // should it be indexerToggle?
  //   //   delay(250);
  //   //   INDEXER.move(0);
  //   //   delay(400);
  //     driveTurn(56);
  //     driveStraight(3300);


    