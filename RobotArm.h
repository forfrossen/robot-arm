#include "WString.h"
#include "Servo.h"

class RobotArm {
  private: 
    bool debug = true;
    int servoStepSize = 5;
    int servoWriteDelay = 30;
    Servo gelenk0 = Servo(1, 300, "Gelenk", 0);
    Servo gelenk1 = Servo(2, 200, "Gelenk", 1);
    Servo gelenk2 = Servo(3, 600, "Gelenk", 2);
    Servo dreher0 = Servo(0, 550, "Dreher", 0);
    Servo dreher1 = Servo(4, 490, "Dreher", 1);
    Servo greifer = Servo(5, 500, "Greifer", 0);

    void log(String Message){
      if(debug){
        Serial.println("[DEBUG] RobotArm: - " + Message);
      }
    }

  public:
    RobotArm(){
      Serial.println("\nHello world! This is a RobotArm!");
      // ====================================
      // GELENK   0
      // ====================================
      //Servo gelenk0(1, 300, "Gelenk", 0);
      //gelenk0.init(1, 300, "Gelenk", 0);
      gelenk0.SetMinPos(200);
      gelenk0.SetMaxPos(600);
      gelenk0.SetStraightPos(420);

      // ====================================
      // GELENK   1
      // ==================================== 
      //gelenk1.init(2, 200, "Gelenk", 1);
      gelenk1.SetStraightPos(430);
      gelenk1.SetMaxPos(600);
      gelenk1.SetMinPos(100);


      // ====================================
      // GELENK   2
      // ==================================== 
      //gelenk2.init(3, 600, "Gelenk", 2);
      gelenk2.SetStraightPos(380);
      gelenk2.SetMinPos(100);
      gelenk2.SetMaxPos(700);

      // ====================================
      // GREIFER
      // ====================================
      //greifer.init(5, 500, "Greifer", 0);
      greifer.SetMinPos(500);
      greifer.SetMaxPos(690);

      // ====================================
      // Dreher   0
      // ====================================
      //dreher0.init(0, 550, "Dreher", 0);
      dreher0.SetStraightPos(550);
      //dreher0.SetStraightPos(300);

      // ====================================
      // Dreher   1
      // ====================================
      //dreher1.init(4, 490, "Dreher", 1);
      dreher1.SetStraightPos(490);

      log(String("Gelenk0 currentPos: " + gelenk0.currentPos));
    }

    void GrabCube(){
      greifer.Up();
      gelenk2.add(40);
      gelenk0.add(40);
      delay(100);
      gelenk1.substract(20);
      delay(100);
      greifer.Down();
    }

    void restArm(){
      gelenk0.DriveToRest();
      gelenk1.DriveToRest();
      gelenk2.DriveToRest();
    }

    void SetDesiredPosition(String preset){
      if(preset == "REST"){
        log("Setting REST Position");
        gelenk0.desiredPos = gelenk0.restingPos;
        gelenk1.desiredPos = gelenk1.restingPos;
        gelenk2.desiredPos = gelenk2.restingPos;
        dreher0.desiredPos = dreher0.restingPos;
        dreher1.desiredPos = dreher1.restingPos;
      } else if ("STRAIGHT") {
        log("Setting STRAIGHT Position");
        gelenk0.desiredPos = gelenk0.straightServoPos;
        gelenk1.desiredPos = gelenk1.straightServoPos;
        gelenk2.desiredPos = gelenk2.straightServoPos;
        dreher0.desiredPos = dreher0.straightServoPos;
        dreher1.desiredPos = dreher1.straightServoPos;
      }
    }

    bool AreAnyDeiredPositionsLeft(){
      log("Checking if any positions are left to drive to");
      if(gelenk0.desiredPos == 0 && gelenk1.desiredPos == 0 && gelenk2.desiredPos == 0 && dreher0.desiredPos == 0 && dreher1.desiredPos == 0){
        log("No desired position is left.");
        return false;
      }
      log("Position found");
      return true;
    }

    void DriveToDesiredPos(){
      int servoAtDesiredPosCount = 0;

      do {
        
        if(gelenk0.desiredPos){
          gelenk0.DriveServoStep();
        } else { servoAtDesiredPosCount++; }

        if(gelenk1.desiredPos){
          gelenk1.DriveServoStep();
        } else { servoAtDesiredPosCount++; }

        if(gelenk2.desiredPos){
          gelenk2.DriveServoStep();
        } else { servoAtDesiredPosCount++; }

        if(dreher0.desiredPos){
          dreher0.DriveServoStep();
        } else { servoAtDesiredPosCount++; }

        if(dreher1.desiredPos){
          dreher1.DriveServoStep();
        } else { servoAtDesiredPosCount++; }

        if(servoAtDesiredPosCount == 5 ){
          log("servoAtDesiredPosCount == 5, breaking loop!");
          break;
        }

        delay(servoWriteDelay);

      } while (AreAnyDeiredPositionsLeft() == true);
    }

};