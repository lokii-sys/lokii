/*
  smartDeviceTest 

  [Prerequisite]
  This program requires four smart LEDs and four smart motors attached to LOKII Shield board.
  The smart motors should be set to smart IDs: 1, 2, 3, 4
  The smart LEDs should be set to smart IDs:   5, 6, 7, 8   by  "writeSmartID.ino"   program
  

  [Function]
  This program controls 8 smarts devices attached to LOKII Shield board at the same time.
 

  Written by Markuz Lee
  5-4-2020

*/




#include <lokii.h>

volatile int motorCount;
volatile int motorPos;
volatile int motorFlag;
volatile int motorStatus;
volatile int ledStep;

LOKII lokii;

void testMotor() {
  if ((motorFlag&1) == 0) {
    lokii.moveMotor(1,500,100 ,L_DEFAULT);
    lokii.moveMotor(2,1000,100 ,L_DEFAULT);
    lokii.moveMotor(3,1500,100 ,L_DEFAULT);
    lokii.moveMotor(4,2000,100 ,L_DEFAULT);

  } else {
    lokii.moveMotor(1,500,0,L_DEFAULT);
    lokii.moveMotor(2,1000,0,L_DEFAULT);
    lokii.moveMotor(3,1500,0,L_DEFAULT);
    lokii.moveMotor(4,2000,0,L_DEFAULT);

  }
}

void testLED() {
  ledStep = (long) (motorFlag) % (long) (4);
  if (ledStep == 0) {
    lokii.setRGB(6,255, 0, 0);
    lokii.setRGB(7,255, 102, 0);
    lokii.setRGB(8,255, 255, 0);
    lokii.setRGB(9,51, 255, 51);

  } else if (ledStep == 1) {
    lokii.setRGB(6,255, 102, 0);
    lokii.setRGB(7,255, 255, 0);
    lokii.setRGB(8,51, 255, 51);
    lokii.setRGB(9,0, 204, 204);
  } else if (ledStep == 2) {
    lokii.setRGB(6,255, 255, 0);
    lokii.setRGB(7,51, 255, 51);
    lokii.setRGB(8,0, 204, 204);
    lokii.setRGB(9,204, 51, 204);
  } else {
    lokii.setRGB(6,51, 255, 51);
    lokii.setRGB(7,51, 153, 153);
    lokii.setRGB(8,204, 51, 204);
    lokii.setRGB(9,255, 0, 0);

  }
}

void printMotor() {
  for (int i = (1); i <= (motorCount); i = i + (1)) {
    motorPos = lokii.readMotorPosition(i);
    motorStatus = 0;
    Serial.println(String(String("Motor ") + String(String(i).toInt())) + String(String(String(" pos:") + String(String(motorPos).toInt())) + String(String(" status:") + String(String(motorStatus).toInt()))));
  }
}

void setup(){
  lokii.connect();
  motorCount = 0;
  motorPos = 0;
  motorFlag = 0;
  motorStatus = 0;
  ledStep = 0;
  motorCount = lokii.getSmartDeviceCount( );
  Serial.begin(9600);
}

void loop(){
  motorFlag = motorFlag + 1;
  testMotor();
  testLED();
  delay(2000);
  printMotor();

}
