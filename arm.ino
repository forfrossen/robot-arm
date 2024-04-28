#include <Wire.h>
enum DesiredPositions {REST, STRAIGHT, GREIFER_OPEN, GREIFER_CLOSE, TURN_AWAY_FROM_DESK, TURN_TO_DESK_ALIGNED, POS_1};
#include "RobotArm.h"


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  RobotArm arm;
  
  /*
  arm.SetDesiredPosition(REST);
  arm.DriveToDesiredPos();
  //delay(1000);
  
  arm.SetDesiredPosition(TURN_AWAY_FROM_DESK);
  arm.SetDesiredPosition(GREIFER_CLOSE);
  arm.SetDesiredPosition(STRAIGHT);
  arm.DriveToDesiredPos();

  delay(4000);

  arm.SetDesiredPosition(REST);
  arm.SetDesiredPosition(GREIFER_OPEN);
  arm.SetDesiredPosition(TURN_TO_DESK_ALIGNED);
  delay(200);
  arm.DriveToDesiredPos();
  
  delay(4000);
  */
  arm.SetDesiredPosition(POS_1);
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition(GREIFER_CLOSE);
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition(REST);
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition(TURN_AWAY_FROM_DESK);
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition(GREIFER_OPEN);
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition(TURN_TO_DESK_ALIGNED);
  arm.SetDesiredPosition(REST);
  arm.DriveToDesiredPos();
  //GrabCube();
  //restArm();
}

void loop() {
  /*
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);  
  */
}