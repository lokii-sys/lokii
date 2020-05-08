#include <lokii.h>

volatile int faceX;
volatile int faceY;
volatile int faceW;
volatile int faceH;

LOKII lokii;

void FaceDetectSample() {
  lokii.setCameraMode(L_CAM_FACE_DETECT);
  if (lokii.waitForFaceResult(L_ON) > 0) {
    faceX = lokii.getFaceResult( L_XPOS);
    faceY = lokii.getFaceResult( L_YPOS);
    faceW = lokii.getFaceResult( L_WIDTH);
    faceH = lokii.getFaceResult( L_HEIGHT);
    Serial.println(String("There is a face at:") + String(String(String(faceX, DEC)) + String(String(" , ") + String(String(faceY, DEC)))));

  }
}

void setup(){
  lokii.connect();
  faceX = 0;
  faceY = 0;
  faceW = 0;
  faceH = 0;
  Serial.begin(9600);
}

void loop(){
  FaceDetectSample();

}
