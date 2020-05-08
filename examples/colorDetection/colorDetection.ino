/*
  colorDetection 

  [Prerequisite]
  You need to have some "RED", "GREEN", "BLUE" color objects place in front of the LOKII camera.
  To have a better accuracy, it is better to have a still background color environment in either white or gray background.
  

  [Function]
  This program detect all the red, green , blue object found on the LOKII camera and list out their center coordinates and width, height information
  according to a 320x240 resolution coordinates system.
 

  Written by Markuz Lee
  5-4-2020

*/




#include <lokii.h>

volatile int blobCount;
volatile int blobColor;
volatile int blobX;
volatile int blobY;
volatile int blobW;
volatile int blobH;

String colorList[]={"NONE","RED","GREEN","BLUE","CUSTOM"};

LOKII lokii;

void colorDetectionSample() {
  lokii.setCameraMode(L_CAM_RECOGNIZE_RGB);
  blobCount = lokii.waitForBlobResult( );
  for (int i = (0); i <= (blobCount - 1); i = i + (1)) {
    blobX = lokii.getBlobResult( i,L_XPOS);
    blobY = lokii.getBlobResult( i,L_YPOS);
    blobW = lokii.getBlobResult( i,L_WIDTH);
    blobH = lokii.getBlobResult( i,L_HEIGHT);
    blobColor = lokii.getBlobResult( i,L_COLOR);
    Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  color =") + String(colorList[(int)((blobColor + 1) - 1)]))));
    Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  x =") + String(String(blobX, DEC)))));
    Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  y =") + String(String(blobY, DEC)))));
    Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  width =") + String(String(blobW, DEC)))));
    Serial.println(String("Object[") + String(String(String(i, DEC)) + String(String(" ]  height =") + String(String(blobH, DEC)))));
    Serial.println("");
  }
}

void setup(){
  blobCount = 0;
  blobColor = 0;
  blobX = 0;
  blobY = 0;
  blobW = 0;
  blobH = 0;
  pinMode(A4, INPUT_PULLUP);
  lokii.connect();
  Serial.begin(9600);
}

void loop(){
  while (true) {
    colorDetectionSample();
  }

}
