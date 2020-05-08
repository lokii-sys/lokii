/*
  Text-To-Speech

  [Prerequisite]
  This program requires a speaker attached to LOKII shield board.

  [Function]
   This program demonstrate the english text-to-speech (TTS) function of LOKII system.
 


  Written by Markuz Lee
  7-2-2020

*/


#include <lokii.h>

LOKII lokii;

void setup(){
  lokii.connect();
}

void loop(){
  lokii.playTTS(  (String) F(" Hello, Welcome to Lokii system!") , L_YOUNGGIRL ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("How are you today?") , L_BOY ,5 ,5 ,E_NATURAL);
  while(true);

}
