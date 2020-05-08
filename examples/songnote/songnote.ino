/*
  songnote

  [Prerequisite]
  This program requires a speaker attached to LOKII Arduino Shield.

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

int TwinkleLittleStar[] =
{
  BEAT_1, NOTE_1, NOTE_1, NOTE_5, NOTE_5, NOTE_6, NOTE_6, BEAT_2, NOTE_5,
  BEAT_1, NOTE_4, NOTE_4, NOTE_3, NOTE_3, NOTE_2, NOTE_2, BEAT_2, NOTE_1,
  BEAT_1, NOTE_5, NOTE_5, NOTE_4, NOTE_4, NOTE_3, NOTE_3, BEAT_2, NOTE_2,
  BEAT_1, NOTE_5, NOTE_5, NOTE_4, NOTE_4, NOTE_3, NOTE_3, BEAT_2, NOTE_2,
  BEAT_1, NOTE_1, NOTE_1, NOTE_5, NOTE_5, NOTE_6, NOTE_6, BEAT_2, NOTE_5,
  BEAT_1, NOTE_4, NOTE_4, NOTE_3, NOTE_3, NOTE_2, NOTE_2, BEAT_2, NOTE_1,
};




int openMos[] =
{ BEAT_1, NOTE_1, NOTE_2, NOTE_3, NOTE_1, NOTE_1, NOTE_2, NOTE_3, NOTE_1, NOTE_3, NOTE_4, BEAT_2, NOTE_5,
  BEAT_1, NOTE_3, NOTE_4, BEAT_2, NOTE_5,
  BEAT_0_5, NOTE_5, NOTE_6, NOTE_5, NOTE_4, BEAT_1, NOTE_3, NOTE_1,
  BEAT_0_5, NOTE_5, NOTE_6, NOTE_5, NOTE_4, BEAT_1, NOTE_3, NOTE_1,
  BEAT_1, NOTE_2, NOTE_5L, BEAT_2, NOTE_1,
  BEAT_1, NOTE_2, NOTE_5L, BEAT_2, NOTE_1,
};


int smallWorld[] =
{

  BEAT_1, NOTE_3L, NOTE_4L, BEAT_2, NOTE_5L, NOTE_3, NOTE_1,
  BEAT_1, NOTE_2, NOTE_1, BEAT_2, NOTE_1, NOTE_7L, NOTE_7L,
  BEAT_1, NOTE_2L, NOTE_3L, BEAT_2, NOTE_4L, NOTE_2, NOTE_7L,
  BEAT_1, NOTE_1, NOTE_7L, BEAT_2, NOTE_6L, NOTE_5L, NOTE_5L,
  BEAT_1, NOTE_3L, NOTE_4L, BEAT_2, NOTE_5L, BEAT_1, NOTE_1, NOTE_2, BEAT_2, NOTE_3,
  BEAT_1, NOTE_2, NOTE_1, BEAT_2, NOTE_6L, BEAT_1, NOTE_2, NOTE_3, BEAT_2, NOTE_4,
  BEAT_1, NOTE_3, NOTE_2, BEAT_2, NOTE_5L, NOTE_4, NOTE_3, NOTE_2, BEAT_4, NOTE_1,

  BEAT_4, NOTE_P,

  BEAT_1, NOTE_1, NOTE_P, NOTE_P, NOTE_1, BEAT_2, NOTE_3, NOTE_1, NOTE_2, BEAT_1, NOTE_P, NOTE_2, BEAT_4, NOTE_2,
  BEAT_1, NOTE_2, NOTE_P, NOTE_P, NOTE_2, BEAT_2, NOTE_4, NOTE_2, NOTE_3, BEAT_1, NOTE_P, NOTE_3, BEAT_4, NOTE_3,
  BEAT_1, NOTE_3, NOTE_P, NOTE_P, NOTE_3, BEAT_2, NOTE_5, NOTE_3, NOTE_4, BEAT_1, NOTE_P, NOTE_4, BEAT_2, NOTE_4,
  BEAT_1, NOTE_3, NOTE_2, BEAT_4, NOTE_5L, NOTE_7L, NOTE_1

} ;



// 1 = C // Do // C4?
// 2 = D // Re
// 3 = E // Mi
// 4 = F
// 5 = G
// 6 = A
// 7 = B


void setup() {

  Serial.begin(9600);
  while (!Serial);

  lokii.connect();
  Serial.println("starting E!");

}

void loop() {

  // beat per minute
  //lokii.setMIDIBPM(90);

  // play single note Middle Major C for 1 beat
  // lokii.playMIDI(BEAT_1);
  // lokii.playMIDI(NOTE_C);


  // set LOKII to 90 beat per minute
  lokii.setMIDIBPM(90);

  // play "Twinkle Twinkle Little Star"
  for (unsigned int i = (1); i <= (sizeof(TwinkleLittleStar) / sizeof(TwinkleLittleStar[0])); i = i + (1)) {
    lokii.playMIDI(TwinkleLittleStar[(int)(i - 1)]);
  }

 
  // set LOKII to 300 beat per minute 
  lokii.setMIDIBPM(300);
  // play "It's a Small World"
  for (int i = (1); i <= (sizeof(smallWorld)/sizeof(smallWorld[0])); i = i + (1)) {
    lokii.playMIDI(smallWorld[(int)(i - 1)]);
  }

 
  // set LOKII to 100 beat per minute 
  lokii.setMIDIBPM(100);
  // play "Open Mos"
  for (int i = (1); i <= (sizeof( openMos   )/sizeof(openMos[0])); i = i + (1)) {
     lokii.playMIDI( openMos[(int)(i - 1)]);
  }

  delay(10000);

}
