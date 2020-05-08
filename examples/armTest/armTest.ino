/*
  armTest 

  [Prerequisite]
  This program requires:
    1) servo motors linked hardware robotic arm attached to LOKII shield
    2) a 6V DC  power supply to the robotic arm
    3) a Window PC program  "RobotArm.exe" to control the robotic arm
    
  [Function]
  This program works as a motor control proxy to allow PC motor  commmand transfer to LOKII system through standard Arduino COM port interface (Serial port)


  Written by Markuz Lee
  5-4-2020

*/



#include <lokii.h>

// init the lokii resource
LOKII lokii;


// the setup routine runs once when you press reset
void setup() {
  // initialize serial communication at 9600 bits per second
}

void loop() {

  char a[64];
  char strBuf[40];
  int numBytes;
  size_t ret;

  Serial.begin(115200);
  lokii.connect();
  Serial.setTimeout(50);

  // print out the value you read
  while (1)
  {
    numBytes = Serial.available();
    // read the Serial data from Arduino COM port (read from PC)
    if (numBytes > 0) {
      // set the Serial data to LOKII system as a String command 
      ret = Serial.readBytes(a, numBytes);//a=Serial.readString(); // read the incoming data as string
      lokii.sendString(a, numBytes);
    }

    // read the string response from LOKII system
    numBytes = lokii.getString(strBuf);
    if (  numBytes > 0)
    {
      // send it back to Arduino COM port  (send back to PC)
      Serial.write(strBuf, numBytes);
    }

  }
}
