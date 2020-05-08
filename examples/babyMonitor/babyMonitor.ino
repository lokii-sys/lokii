/*
  babyMonitor

  [Prerequisite]
   No

  [Function]
  This program keep doing face detection and it will speak out "Alert! Baby not found!" if there are more than 3 seconds
  LOKII report no frontal face detected.
 

  Written by Edward Chan
  27-3-2020

*/



#include <lokii.h>

volatile int faceChecked;
volatile int count;

LOKII lokii;

void setup(){
  lokii.connect();
  faceChecked = 0;
  count = 0;
  lokii.playTTS(  (String) F("Baby Monitor Demo ") , L_YOUNGGIRL ,5 ,5 ,E_NATURAL);
  lokii.setCameraMode(L_CAM_FACE_DETECT);
}

void loop(){
  if (lokii.waitForFaceResult(L_OFF) > 0) {
    faceChecked = 1;
  }
  if (count >= 3) {
    if (faceChecked == 0) {
      lokii.playTTS(  (String) F("Alert! Baby not found!") , L_DEFAULT ,5 ,5 ,E_SURPRISED);

    }
    faceChecked = 0;
    count = 0;
  } else {
    count = count + 1;
  }
  delay(1000);
}
