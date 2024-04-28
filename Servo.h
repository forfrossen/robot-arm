#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

class Servo {
  private:
    //void log(String Message);
    void log(String Message){
      if(debug){
        Serial.println("[DEBUG] " + type + number + " - " + Message);
      }
    }

  public:
    Adafruit_PWMServoDriver myServos;
    int servonum = 0;
    int minServoPos = 100;
    int maxServoPos = 600;
    int straightServoPos = 0;
    int servoStepSize = 5;
    int servoWriteDelay = 20;
    int restingPos = 0;
    int pin = 0;
    int currentPos = 0;
    bool debug = true;
    int desiredPos = 0;
    String type;
    int number;
    bool invalidDesiredPosition = false;
    
    Servo(int pin, int restingPos, String type, int number){
      myServos = Adafruit_PWMServoDriver();
      myServos.begin();
      myServos.setPWMFreq(60);

      this->servonum = pin;
      this->number = number;
      this->type = type;

      log(String("Init"));
      SetRestingPosition(restingPos);
      Rest();
    }

    void SetMinPos(int pos){
      this->minServoPos = pos;
    }

    void SetMaxPos(int pos){
      this->maxServoPos = pos;
    }

    void SetStraightPos(int pos){
      this->straightServoPos = pos;
    }

    void SetRestingPosition(int restingPos){
      this->restingPos = restingPos;      
    }

    void DriveToStraight(){
      DriveServo(straightServoPos);
    }

    void DriveToRest(){
      DriveServo(restingPos);
    }

    void Rest(){
      //DriveServo(restingPos);
      myServos.setPWM(servonum, 0, restingPos);
      delay(200);
      this->currentPos = restingPos;
      log(String("Resting at: " + this->currentPos));
    }

    void Straight(){
      if(straightServoPos){
        DriveServo(straightServoPos);
      }
    }

    void Up() {
      log(String("Opening Greifer"));
      DriveServo(minServoPos);
    }

    void Down(){
      log(String("Closing Greifer"));
      DriveServo(maxServoPos);
    }

    void add(int value){
      int _desiredPos = currentPos + value;
      DriveServo(_desiredPos);
    }

    void substract(int value){
      int _desiredPos = currentPos - value;
      DriveServo(_desiredPos);
    }

    bool isPosAllowed(int pos){
      bool returnValue;
      if(minServoPos && pos < minServoPos){
        invalidDesiredPosition = true;
        log(String("isPosAllowed - Have to return false! Pos: " + String(pos) + " minServoPos: " + String(minServoPos) + " currentPos: " + String(currentPos)));
        return false;       
      }
      if(maxServoPos && pos > maxServoPos){
        invalidDesiredPosition = true;
        log(String("isPosAllowed - Have to return false! Pos: " + String(pos) + " maxServoPos: " + String(maxServoPos) + " currentPos: " + String(currentPos)));
        return false;
      }
      return true;
    }

    void DriveServoStep(){
      int nextStep = 0;
      if(desiredPos == 0){
        log(String("Nowhere to go ..."));
        return;
      }

      if (desiredPos == currentPos) {
        log("Desired position has been reached: " + String(desiredPos) + " CurrentPos: " + String(currentPos));
        desiredPos = 0;
        return;
      }
      
       

      if(desiredPos > currentPos){
        if((desiredPos - currentPos) <= servoStepSize){
          nextStep = desiredPos;
        } else {
          nextStep = currentPos + (desiredPos < currentPos ? -servoStepSize : servoStepSize);
        }
      } else {
        if((currentPos - desiredPos) <= servoStepSize){
          nextStep = desiredPos;
        } else { 
          nextStep = currentPos + (desiredPos < currentPos ? -servoStepSize : servoStepSize); 
        }
      }

      log(String("Next step is: " + String(nextStep)));

      if (!isPosAllowed(nextStep)) {
        log(String("Position not allowed: " + String(desiredPos)));
        desiredPos = 0;
      }

      myServos.setPWM(servonum, 0, nextStep);
      currentPos = nextStep;
    }

    void DriveServo(int pos){
      if(currentPos >= pos){
        log(String("Driving Servo up"));
        DriveServoUp(pos);
      } else {
        log(String("Driving Servo down"));
        DriveServoDown(pos);
      }
    }

    void DriveServoNoDelay(int pos){
      myServos.setPWM(servonum, 0, pos);
      currentPos = pos;
    }

    void DriveServoUp(int desiredPos){
      log(String("Driving Gelenk servo to position: " + char(desiredPos)));
      for (int pos = currentPos; pos >= desiredPos; pos -= servoStepSize) {
        log(String("moving Greifer to Pos: " + char(pos)));
        myServos.setPWM(servonum, 0, pos);
        currentPos = pos;
        delay(servoWriteDelay);
      }
    }

    void DriveServoDown(int desiredPos){
      log(String("Driving Gelenk servo to position: " + char(desiredPos)));
      for (int pos = currentPos; pos <= desiredPos; pos += servoStepSize) { 
          log(String("moving Greifer to Pos: " + char(pos)));
          myServos.setPWM(servonum, 0, pos);
          currentPos = pos;
          delay(servoWriteDelay);
      }
    }

/*
    void init(int pin, int restingPos, String type, int Number);

    void SetMinPos(int pos);

    void SetMaxPos(int pos);

    void SetStraightPos(int pos);
    
    void SetRestingPosition(int restingPos);

    void DriveToStraight();
    
    void DriveToRest();

    void Rest();

    void Straight();

    void Up();

    void Down();

    void add(int value);

    void substract(int value);

    bool isPosAllowed(int pos);

    void DriveServoStep();

    void DriveServo(int pos);

    void DriveServoNoDelay(int pos);

    void DriveServoUp(int desiredPos);

    void DriveServoDown(int desiredPos);
*/
};
