#include <Wire.h>
#include "RobotArm.h"

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  RobotArm arm;
  arm.SetDesiredPosition("REST");
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition("STRAIGHT");
  arm.DriveToDesiredPos();
  arm.SetDesiredPosition("REST");
  arm.DriveToDesiredPos();
  //GrabCube();
  //restArm();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
}