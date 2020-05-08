/*
  musicTone

  [Prerequisite]
  This program requires a speaker attached to LOKII Arduino Shield.

  [Function]
  A simple program demonstrate music tone playing by LOKII.

  Written by Markuz Lee
  3-1-2020

*/


#include <lokii.h>

LOKII lokii;

int TwinkleLittleStar[]={1,1,5,5,6,6,5,-1,4,4,3,3,2,2,1};

void setup(){
  lokii.connect();
}

void loop(){
  for (int i = (1); i <= (sizeof(TwinkleLittleStar)/sizeof(TwinkleLittleStar[0])); i = i + (1)) {
    lokii.playMIDI(TwinkleLittleStar[(int)(i - 1)]);
  }
  delay(10000);

}
