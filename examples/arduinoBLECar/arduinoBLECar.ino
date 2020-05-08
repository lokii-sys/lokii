/*
  arduinoBLECar

 [Prerequisite]  
 This program can be compiled in "Arduino Nano 33 BLE" board to demonstrate the control of the LOKII function by mobile apps.
 (BLE functions)

  [Function]                                                                                                                               
  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  LOKII BLE Service:   "FFD0"
  LOKII BLE Notify | Write Characteristics:  "FFD9"

  For the command string accepted by this demo, please check the function:  handleCmd(String cmd) { ... ...}

  For more more detail to duplicate this demo by building the the car, running the android app,
  please send request to "lokii@centek.com.hk"


  Written by Markuz Lee, Edward Chan
  7-2-2020
*/

#include <stdio.h>
#include <ArduinoBLE.h>

#include "SPI.h"


#include <lokii.h>

LOKII lokii;
int trackingCenterMode = 0;

// first car setting(blue car)
const uint8_t maxPosition[4] = {200, 200, 200, 180 };
const uint8_t minPosition[4] = {10, 10, 10, 70 };
const uint8_t centerPosition[4] = {100, 100, 100, 70 };


//const uint8_t maxPosition[4] = {200, 150, 200, 100 };
//const uint8_t minPosition[4] = {10, 10, 10, 180 };


// short arm(transparent)
//const uint8_t maxPosition[4] = {130, 150, 200, 100 };
//const uint8_t minPosition[4] = {50, 70, 10, 180 };
//const uint8_t centerPosition[4] = {100, 100, 100, 180 };


// long arm
//const uint8_t maxPosition[4] = {140, 180, 200, 1 };
//const uint8_t minPosition[4] = {20, 80, 10,  60};
//const uint8_t centerPosition[4] = {100, 100, 117, 60 };


const uint8_t moveSpeed[4] = {4, 4, 4, 0 };



//String vrList[]={"tell me a joke", "play me a song", "stop the music", "take a photo", "show me the photo", "track my face", "follow the ball", "record motor motion", "playback motor", "list commands"};

String vrList[] = {"OK I can tell you a joke, you are so handsome.",
                   "OK , Twinkle, Twinkle, Little Star. how I wonder where you are",
                   "OK, I shut up",
                   "are you ready. cheese",
                   "show me the photo",
                   "track my face",
                   "follow the ball",
                   "record motor motion",
                   "playback motor",
                   "list commands"
                  };


String colorList[] = {"NONE", "RED", "GREEN", "BLUE", "CUSTOM"};

void speechRecognizeSample() {
  int speechResult;

  lokii.startSpeechRecognize(L_KEYWORD_GROUP4);
  speechResult = lokii.waitForSpeechResult( );
  lokii.playTTS(  vrList[(int)(speechResult)]  , L_DEFAULT , 5 , 5 , E_NATURAL);
}



int currentPos;
int lastPos;
int varSpeed;

int lastMoved  = 0;
int clampAnimationState  = 0;
int RexistCount, BexistCount;
long lastRcenterSize, lastBcenterSize;
int greenNotFoundTimeCount;

void colorDetectionInit()
{
  lastMoved  = 0;
  clampAnimationState  = 0;
  RexistCount = 0;
  BexistCount = 0;
  lastRcenterSize = 0;
  lastBcenterSize = 0;
  greenNotFoundTimeCount = 0;

}

void colorDetectionSample() {


  int blobCount;
  int blobColor;
  int blobX;
  int blobY;
  int blobW;
  int blobH;

  int i, servoActionNeeded;
  int delta;

  int r, g, b;

  int tempcenterX, tempcenterY, tempcenterIndex;
  long tempcenterSize;
  int RcenterX, RcenterY, RcenterIndex;

  int BcenterX, BcenterY, BcenterIndex;
  long RcenterSize, BcenterSize;


  servoActionNeeded = 0;
  r = 0;
  g = 0;
  b = 0;
  RcenterSize = 0;
  BcenterSize = 0;

  blobCount = lokii.waitForBlobResult(false);
  //Serial.println(blobCount);
  if (blobCount > 0)
  {
    for (i = (0); i <= (blobCount - 1); i = i + (1))
    {
      // xy= lefttop coord, 320x240
      blobX = lokii.getBlobResult( i, L_XPOS);
      blobY = lokii.getBlobResult( i, L_YPOS);
      blobW = lokii.getBlobResult( i, L_WIDTH);
      blobH = lokii.getBlobResult( i, L_HEIGHT);
      blobColor = lokii.getBlobResult( i, L_COLOR);
      tempcenterX = blobX + blobW / 2;
      tempcenterY = blobY + blobH / 2;
      tempcenterSize = blobW * blobH;

      //Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  color =") + String(colorList[(int)((blobColor + 1) - 1)]))));
      //Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  x =") + String(String(blobX, DEC)))));
      //Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  y =") + String(String(blobY, DEC)))));
      //Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  width =") + String(String(blobW, DEC)))));
      //Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  height =") + String(String(blobH, DEC)))));

      if (blobColor == L_GREEN_COLOR)
      {
        servoActionNeeded = 1;
        currentPos = (blobX + blobW / 2) * 5 / 8;
        if (lastPos == 0 || currentPos > (lastPos + 10) || (currentPos + 10) < lastPos)
        {
          varSpeed = abs(currentPos - lastPos) / 11 + 3;


          //lokii.setRCServoAction(2 + 9, 4, 200-currentPos);
          delta = centerPosition[2] - (200 - currentPos);
          delta = delta * 40 / 100;
          //lokii.setRCServoAction(2 + 9, 4, 200-currentPos);
          if (clampAnimationState == 0)
              lokii.setRCServoAction(2 + 9, 2 , centerPosition[2] - delta);
          else
              servoActionNeeded = 0;
          lastPos = currentPos;
          //Serial.println(200-currentPos);
          lastMoved = 1;
        }
        else
        {
          if (lastMoved < 20) // ball found and stay still for some time
            lastMoved++;
        }
        g = 1;
        break; // green has highist priority
      }

      // area in center, size less than 70% of screen, and only count the largest red, width less than 80% max width, height less than 80% max height
      if (blobColor == L_RED_COLOR && tempcenterSize < (320 * 240 / 10 * 7) && tempcenterSize > (320 * 240 / 10 * 1) && blobW < 32 * 8 && blobH < 24 * 8
          && tempcenterX < 240 && tempcenterX > 80
          && tempcenterY < 180 && tempcenterX > 60
          && tempcenterSize > RcenterSize)
      {
        r = 1;
        RcenterSize = tempcenterSize;
        if (RexistCount < 3) // one frame time = 0.1s
          RexistCount++;
      }

      // area in center, size less than 70% of screen, and only countthe largeest blue
      if (blobColor == L_BLUE_COLOR && tempcenterSize < (320 * 240 / 10 * 7) && tempcenterSize > (320 * 240 / 10 * 1) && blobW < 32 * 8 && blobH < 24 * 8
          && tempcenterX < 240 && tempcenterX > 80
          && tempcenterY < 180 && tempcenterX > 60
          && tempcenterSize > BcenterSize)
    {
      b = 1;
      BcenterSize = tempcenterSize;
    }

  } // end for


  // similar size check with last frame's detection result
  if (r == 1 && RcenterSize * 10 < lastRcenterSize * 15 && RcenterSize * 10 > lastRcenterSize * 7)
    {
      if (RexistCount < 3)
        RexistCount++;
    }
    else
      RexistCount = 0;

    if (b == 1 && BcenterSize * 10 < lastBcenterSize * 15 && BcenterSize * 10 > lastBcenterSize * 7)
    {
      if (BexistCount < 3)
        BexistCount++;
    }
    else
      BexistCount = 0;
    lastRcenterSize = RcenterSize;
    lastBcenterSize = BcenterSize;

    if (g == 0)
    {
      // green ball found before and not doing clampanimation and not found green ball, go to center
      if (greenNotFoundTimeCount < 20)
        greenNotFoundTimeCount++;
      if (clampAnimationState == 0 && greenNotFoundTimeCount == 19)
      {
        servoActionNeeded = 1;
        lokii.setRCServoAction(2 + 9, moveSpeed[2], centerPosition[2]);
      }

      lastMoved = 0;
      if (r == 1 && RcenterSize > BcenterSize && RexistCount == 3)
      {
        servoActionNeeded = 1;
        setDC(0, 40);
        setDC(1, 40);
        setDC(2, 40);
        setDC(3, 40);
      }
      else if (b == 1 && BcenterSize > RcenterSize && BexistCount == 3)
      {
        servoActionNeeded = 1;
        setDC(0, 20);
        setDC(1, 20);
        setDC(2, 20);
        setDC(3, 20);
      }
    }
    else
    {
      greenNotFoundTimeCount = 0;
    }



  } // end if blob count



  if (lastMoved == 20)
  {
    if (clampAnimationState == 0)
      clampAnimationState = 1;
  }
  if (clampAnimationState == 1)
  {
    servoActionNeeded = 1;
    lokii.setRCServoAction(3 + 9, moveSpeed[3], maxPosition[3]); // close
    clampAnimationState++;
  }
  else if (clampAnimationState == 3)
  {
    servoActionNeeded = 1;
    lokii.setRCServoAction(3 + 9, moveSpeed[3], minPosition[3]); // open
    clampAnimationState++;
  }
  else if (clampAnimationState == 5)
  {
    servoActionNeeded = 1;
    lokii.setRCServoAction(3 + 9, moveSpeed[3], maxPosition[3]);  // close
    clampAnimationState++;
  }
  else if (clampAnimationState == 7)
  {
    servoActionNeeded = 1;
    lokii.setRCServoAction(3 + 9, moveSpeed[3], minPosition[3]);  // open
    clampAnimationState++;
  }
  else if (clampAnimationState == 22)
  {
    servoActionNeeded = 1;
    lokii.setRCServoAction(3 + 9, moveSpeed[3], maxPosition[3]);  // close
    clampAnimationState++;
  }
  else if (clampAnimationState == 37)
  {
    servoActionNeeded = 1;
    lokii.setRCServoAction(3 + 9, moveSpeed[3], minPosition[3]);  // open
    clampAnimationState = 0;
    lastMoved = 0;
  }
  else if (clampAnimationState > 0)
  {
    clampAnimationState++;
  }




  if (servoActionNeeded)
  {
    lokii.startMultiAction(false);
  }



}




// define the BLE packet size
#define BLE_PACKET_LEN 128

BLEService customService("FFD0");   //   ("19B10000-E8F2-537E-4F6C-D104768A1214"); // LOKII Service
BLEStringCharacteristic lokiiCharacteristic("FFD9",  BLEWriteWithoutResponse  | BLEWrite | BLENotify , BLE_PACKET_LEN);



const int ledPin = LED_BUILTIN; // pin to use for the LED


char mesgStr[20];
uint8_t byteList[BLE_PACKET_LEN];
String cmdStr = "";

uint8_t servoMode[4];


//forward/backward
//up/down
//left/right
// close/open

// robot wheel
int lastW1; // 31->0, 0-61
int lastW2;
int lastW3;
int lastW4;


void setRCServoMode(uint8_t index, uint8_t mode)
{
  if (servoMode[index] != mode || mode == 0)
  {
    if (mode == 0)
      lokii.setRCServoAction(index + 9, moveSpeed[index],  centerPosition[index]);
    else if (mode == 1) {
      if (index != 3)
        lokii.setRCServoActionStop(index + 9);
      else
        lokii.setRCServoAction(index + 9, moveSpeed[index], minPosition[index]);
    }
    else if (mode == 2)
      lokii.setRCServoAction(index + 9, moveSpeed[index], maxPosition[index]);
    else if (mode == 3)
      lokii.setRCServoAction(index + 9, moveSpeed[index], minPosition[index]);
    servoMode[index] = mode;
  }
}

int lastW[4];

void setDC(int index, int pwm)
{ 
  if (pwm >= 31)
  {
    if (lastW[index] >= 31)
      lokii.setDCMotorAction(index + 5, pwm - 0x1F, 0); // forward 0~31
    else
      lokii.setDCMotorAction(index + 5, 0, 0);
  }
  else
  {
    if (lastW[index] >= 31)
      lokii.setDCMotorAction(index + 5, 0, 0);
    else
      lokii.setDCMotorAction(index + 5, 0x1F - pwm, 1); // backward 0~31
  }
  lastW[index] = pwm;

}
// ---------------------------------------
void handleCmd(String cmd) {

  String cmdType = cmd.substring(0, 3);
  String cmdData = cmd.substring(3);

  Serial.println("Received cmd"  );
  Serial.println(cmd.length() );
  Serial.println(cmdType  );
  Serial.println(cmdData );

  if ( cmdType.compareTo("SPE") == 0) {
    if (trackingCenterMode != 0)
      lokii.setCameraMode(L_CAM_PREVIEW, false);
    trackingCenterMode = 0;

    Serial.println( "Speech demo for 10 commands");
    speechRecognizeSample();
  }
  else if ( cmdType.compareTo("TTS") == 0) {
    Serial.println( "Play TTS: " + cmdData);
    lokii.playTTS( cmdData , L_DEFAULT , 5 , 5 , E_NATURAL);
  }
  else if ( cmdType.compareTo("COL") == 0)  {
    Serial.println( "Color Tracking");
    colorDetectionInit();
    lokii.setCameraMode(L_CAM_RECOGNIZE_RGB, false);
    trackingCenterMode = 1;
  }
  else if ( cmdType.compareTo("FAC") == 0)  {
    Serial.println( "FAC Tracking");
    lokii.setCameraMode(L_CAM_FACE_DETECT, false);
    Serial.println( "FAC TrackingE");
    trackingCenterMode = 2;
  }
  else if ( cmdType.compareTo("MOV")  == 0) {

    if (trackingCenterMode != 0)
      lokii.setCameraMode(L_CAM_PREVIEW, false);
    trackingCenterMode = 0;

    // robot wheel //ble slider bar value = 0-61
    int w1 = cmdData.substring(0, 2).toInt(); // 31->0, 0-61
    int w2 = cmdData.substring(2, 4).toInt();
    int w3 = cmdData.substring(4, 6).toInt();
    int w4 = cmdData.substring(6, 8).toInt();

    setDC(0, w1);
    setDC(1, w2);
    setDC(2, w3);
    setDC(3, w4);

    // robot Arm //ble slider bar value = 0-100
    int a1 = cmdData.substring(8, 10).toInt();
    int a2 = cmdData.substring(10, 12).toInt();
    int a3 = cmdData.substring(12, 14).toInt();
    int a4 = cmdData.substring(14, 16).toInt();

    if (a1 == 50 && a2 == 50 && a3 == 50 && a4 == 50)
    {
      setRCServoMode( 0, 0);
      setRCServoMode( 1, 0);
      setRCServoMode( 2, 0);
      setRCServoMode( 3, 0);
    }
    else
    {
      if (a1 > 75)
        setRCServoMode( 0, 2);// forward
      else if (a1 < 25)
        setRCServoMode( 0, 3);// backward
      else
        setRCServoMode( 0, 1);

      if (a2 > 75)
        setRCServoMode( 1, 2); // up
      else if (a2 < 25)
        setRCServoMode( 1, 3);// down
      else
        setRCServoMode( 1, 1);

      if (a3 > 75)
        setRCServoMode( 2, 2); // left
      else if (a3 < 25)
        setRCServoMode( 2, 3); // right
      else
        setRCServoMode( 2, 1);

      if (a4 > 75)
        setRCServoMode( 3, 2);// close
      else if (a4 < 25)
        setRCServoMode( 3, 3); // open
      else
        setRCServoMode( 3, 1); // open

    }
    lokii.startMultiAction(false);

    Serial.println( "Car : " + String(w1) + " " + String(w2) + " " + String(w3) + " " + String(w4) );
    Serial.println( "Arm : " + String(a1) + " " + String(a2) + " " + String(a3) + " " + String(a4) );
  }

  /*
    else if ( cmdType.compareTo("MP3") == 0)  {
       Serial.println( "Play mp3 from a.mp3");
    }
    else if ( cmdType.compareTo("MIDI") == 0)  {
       Serial.println( "Play MIDI demo");
    }
    else if ( cmdType.compareTo("LED")  == 0){
       int r = cmdData.substring(0,3).toInt();
       int g = cmdData.substring(3,6).toInt();
       int b = cmdData.substring(6,9).toInt();
       Serial.println( "Set all the smart LED color to R:" + String(r) + " G:" + String(g) + " B:" + String(b) );
    }
    else if ( cmdType.compareTo("PHO") == 0) {
       Serial.println( "Take a photo");
    }
    else if ( cmdType.compareTo("DIS") == 0) {
       Serial.println( "Show the photo");
    }
    else if ( cmdType.compareTo("REC") == 0) {
       Serial.println( "Record movie for 10 seconds");
    }
    else if ( cmdType.compareTo("PLA") == 0) {
       Serial.println( "Playback movie");
    }
  */

}


// ---------------------------------------

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // LOKII TRAP FREE RUN


  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName("LOKII_CONTROL");
  BLE.setLocalName("LOKII_CONTROL");
  BLE.setAdvertisedService(customService);

  // add the characteristic to the service
  customService.addCharacteristic(lokiiCharacteristic);

  // add service
  BLE.addService(customService);

  // set the initial value for the characeristic:
  lokiiCharacteristic.writeValue("starting");

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");


  lokii.init();

}







int firstConnected;

void loop() {

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // LOKII TRAP FREE RUN
  firstConnected = 0;
  servoMode[0] = 0;
  servoMode[1] = 0;
  servoMode[2] = 0;
  servoMode[3] = 0;
  trackingCenterMode = 0;


  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());


    long currentMillis = millis();
    long previousMillis = currentMillis;



    // while the central is still connected to peripheral:
    while (central.connected()) {

      currentMillis = millis();
      if (firstConnected == 0 && currentMillis - previousMillis >= 1000)
      {

        if (lokii.init() == 0)
        {
          lokii.getSmartDeviceCount();
          Serial.println("starting LOKII!");

        }
        else
        {
          pinMode(13, OUTPUT);
          digitalWrite(13, LOW); // LOKII TRAP FREE RUN
        }
        firstConnected = 1;
      }


      if (lokiiCharacteristic.written()) {
        // Edward

        int len = 0;
        len = lokiiCharacteristic.valueLength();
        sprintf(mesgStr,  "packet len : %d  ", len);
        cmdStr = lokiiCharacteristic.value();
        handleCmd(cmdStr);


        lokiiCharacteristic.writeValue( cmdStr );
        /*
          if (lokiiCharacteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          } else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
          }
        */
      }
      // else {
      //   delay(1000);
      //  lokiiCharacteristic.writeValue( "Hello" );
      // }

      if (trackingCenterMode == 1)
      {
        //delay(100);
        colorDetectionSample();

      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
