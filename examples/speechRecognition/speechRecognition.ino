/*
  speechRecognition 

  [Prerequisite]
  This program requires a speaker attached to LOKII shield board.

  [Function]
  This program demonstrate the built-in speech recongition  function of LOKII system.
  The demo will recognize the keywords from the microphone and speak out the recognized keywords throught Text-To-Speech Functions.
  User can set the keyboards group by the defined constant: 
      L_KEYWORD_GROUP1
      L_KEYWORD_GROUP2
      L_KEYWORD_GROUP3
      L_KEYWORD_GROUP4

  Written by Markuz Lee
  7-4-2020

*/



#include <lokii.h>

volatile int speechResult;

// Below are  four  LOKII preseted speech recognition keyword groups


// L_KEYWORD_GROUP1
String numberList[]={"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

// L_KEYWORD_GROUP2
String actionList[]={"Action", "Move", "Turn", "Run", "Look", "Attack", "Stop", "Hello"};

// L_KEYWORD_GROUP3
String movementList[]={"Turn Left", "Turn Right", "Move Up", "Move Down",  "Go Forward","Go Backward"};

// L_KEYWORD_GROUP4
String functionList[]={"tell me a joke", "play me a song", "stop the music", "take a photo", "show me the photo", "track my face", "follow the ball", "record motor motion", "playback motor", "list commands"};



LOKII lokii;

void speechRecognizeSample() {

  // We set LOKII to recognize L_KEYWORD_GROUP3
  //  "Movement group" ==>   [ "Turn Left", "Turn Right", "Move Up", "Move Down",  "Go Forward",  "Go Backward"]
  lokii.startSpeechRecognize(L_KEYWORD_GROUP3);

  // wait util LOKII detect the result
  speechResult = lokii.waitForSpeechResult( );
  Serial.println(String(movementList[(int)((speechResult + 1) - 1)]) + String(" detected "));
  lokii.startSpeechRecognize(L_KEYWORD_STOP);
}

void setup(){
  speechResult = 0;
  pinMode(A1, INPUT_PULLUP);
  lokii.connect();
  Serial.begin(9600);
}

void loop(){
  while (true) {
    speechRecognizeSample();
    lokii.playTTS(  (String)  String(movementList[(int)((speechResult + 1) - 1)]) + String("")  , L_DEFAULT ,5 ,5 ,E_NATURAL);
  }

}
