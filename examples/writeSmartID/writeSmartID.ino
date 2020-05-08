/*
  WriteSmartID

  [Prerequisite]
  This program requires a hardware LOKII smart device to work with.

  [Function]
  Set a smart ID to the serial device attached in LOKII Arduino Shield.
  (Make sure only one smart device is attached)
  User shall enter a smart ID number [ 1-99] to the serial monitor connected in Arduino
  when prompt to set the smart ID.


  Written by Markuz Lee
  10-1-2020

*/



#include <lokii.h>

LOKII lokii;

void setup(){

  Serial.begin(9600);
}

void loop(){
  
  char charArray[2];
  int deviceID;
  charArray[0] = 0;  
  charArray[1] = 0;
  
   

    // Ask user to inpu the smart deivce ID in the Arduino serial monitor
    Serial.println("input target device ID");
    lokii.playTTS(  (String) "input target device ID" , L_ROBOT ,5 ,5 ,E_NATURAL);    
    while(!Serial.available()){};
    
    Serial.readBytes(charArray,2);

    // convert the number string into integer
    if (charArray[1] < '0' || charArray[1] > '9')
        deviceID = charArray[0] - '0';
    else
        deviceID = charArray[1] - '0' + (charArray[0] - '0') * 10;    

    //Serial.println(charArray[0]);
    //Serial.println(charArray[1]);       
    Serial.println(deviceID);

    // Set the smart ID into the attached smart device
    lokii.setSmartDeviceAdress(deviceID);
    lokii.playTTS(  (String) ("Set device to address") + String(deviceID) + String("success!"), L_ROBOT ,5 ,5 ,E_NATURAL);

    delay(100);
    while (Serial.available() >0 ) // flush
    {
       Serial.read();
       //Serial.println("i");
    }


  // We are done here
  while(true);

}
