/*
  tts_red_little_riding_hood

  [Prerequisite]
  This program requires a speaker attached to LOKII shield board.

  [Function]
   This program demonstrate the english text-to-speech (TTS) function of LOKII system for storytelling purpose.
   The demo includes changing the TTS character, speed,  volumn, pitch and emotion to perform a multiple speaker function.


  Written by Edward Chan
  7-4-2020

*/


#include <lokii.h>

LOKII lokii;

void setup(){
  lokii.connect();
}

void loop(){
  // play the TTS function one sentence by one sentence
  lokii.playTTS(  (String) F("Red Little Red Riding Hood") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  delay(1000);
  lokii.playTTS(  (String) F("Once upon a time, a little girl named Little Red Riding Hood lived in a village near the forest.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("One day, Little Red Riding Hood's mother asked her to take a basket of fresh cakes to her sick Grandmother.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("Stay on the path through the forest and do no talk to strangers. Her mother warned.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("On the way, Little Red Riding Hood met a charming wolf.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("Where are you going, litte girl? asked the wolf.") , L_OLDMAN ,5 ,5 ,E_FRIENDLY);
  lokii.playTTS(  (String) F("To Grandmothers house.Little Red Riding Hood replied.  But I am not allowed to talk to strangers.") , L_YOUNGGIRL ,5 ,5 ,E_FRIENDLY);
  lokii.playTTS(  (String) F("The wolf smiled and went on his way, talking a short cut through the woods.") , L_DEFAULT ,5 ,5 ,E_FRIENDLY);
  lokii.playTTS(  (String) F("When the wolf arrived at Grandmother's house, she was sound asleep. He put her in the closet and closed the door.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("The he dressed in Grandmother's nightclothes and crawled into bed. He pulled the covers over his nose.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("After a long while, Little Red Riding Hood knocked at the door. She had followed a beautiful butterfly through the woods.") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.playTTS(  (String) F("Grandmother, I have brought you some flowers and cakes, said Little Red Ridding Hood.") , L_YOUNGGIRL ,5 ,5 ,E_FRIENDLY);
  lokii.playTTS(  (String) F("Come closer, my dear, the wolf beckoned in his softest voice.") , L_OLDMAN ,5 ,3 ,E_WHISPER);
  lokii.playTTS(  (String) F("Little Red Ridding Hood moved neared the bed. My Grandmother, what big ears you have. she said.") , L_YOUNGGIRL ,5 ,3 ,E_SURPRISED);
  lokii.playTTS(  (String) F("All the better to hear you with the wolf replied.") , L_OLDMAN ,5 ,3 ,E_WHISPER);
  lokii.playTTS(  (String) F("And what big eyes you have, Little Red Riding Hood said. ") , L_YOUNGGIRL ,5 ,3 ,E_SURPRISED);
  lokii.playTTS(  (String) F(" All the better to see you with, the wolf answered.") , L_OLDMAN ,5 ,3 ,E_WHISPER);
  lokii.playTTS(  (String) F("And what a big nose you have, Little Red Riding Hood said.") , L_YOUNGGIRL ,5 ,3 ,E_SURPRISED);
  lokii.playTTS(  (String) F(" All the better to smell you with, the wolf said with a big grin.") , L_OLDMAN ,5 ,3 ,E_WHISPER);
  lokii.playTTS(  (String) F("And my, what great big teeth you have! Little Red Riding Hood exclaimed.") , L_YOUNGGIRL ,5 ,3 ,E_SURPRISED);
  lokii.playTTS(  (String) F("All the better to eat you with! the wolf jumped out of the bed, snapping his sharp teeth.") , L_OLDMAN ,5 ,3 ,E_WHISPER);
  lokii.playTTS(  (String) F("A nearby woodcutter heard Little Red Riding Hood scream and saw her dash from the house. The woodcutter caught the wolf and took him far away.") , L_DEFAULT ,5 ,3 ,E_NATURAL);
  lokii.playTTS(  (String) F("He could never bother Little Red Riding Hood or her Grandmother again.") , L_DEFAULT ,5 ,3 ,E_NATURAL);
  while(true);

}
