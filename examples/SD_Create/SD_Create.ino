#include <lokii.h>

volatile int SD_index;
volatile int numKeywords;
volatile int result;

LOKII lokii;


String numberList[] = {  "zero",  "one",  "two",  "three",  "four",  "five",  "six",  "seven",  "eight",  "nine",  "ten"};


void setup(){
  Serial.begin(9600);
  
  lokii.connect();

  SD_index = 11;
  numKeywords = 3;
  result = 0;
}

void loop(){
  
  int speechResult;

  // create speaker depentent group
  lokii.createSDGroup(SD_index, numKeywords);
  for (int i = (0); i <= (numKeywords - 1); i = i + (1)) {

      lokii.playTTS(  (String) "Said Your word" + (String) " " , L_DEFAULT ,5 ,5 ,E_NATURAL);
      Serial.println(String("Train speech index") + String(String(i, DEC)));
      //delay(500);
      result = lokii.trainSDkeyword(SD_index,i);
      Serial.println(String(" result = ") + String(String(result, DEC)));
  }
  result = lokii.checkSDComplete(SD_index);
  if (result == 0) {
    Serial.println("Create SD group success!");

  } else {
    Serial.println("Create SD group Fail!");
  }

  
  // start recognize speaker depentent group
  while (1)
  {
      lokii.startSpeechRecognize(SD_index);    
      speechResult = lokii.waitForSpeechResult();
      lokii.playTTS(  numberList[speechResult] , L_DEFAULT ,5 ,5 ,E_NATURAL);      
  }

}
