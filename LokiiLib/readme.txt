This is lokii C++ library for Arduino. (V1.0.4)


Installation
--------------------------------------------------------------------------------

To install this library, launch "Arduino" in your PC.
In Arduino menu, select "Sketch" and click "Add File", open "lokii.zip" file location to import the LOKII library.


When installed, this library should be copied into following directory.
[Windows]
My Documents\Arduino\libraries\lokii\lokii.h
My Documents\Arduino\libraries\lokii\LokiMain.h

[Mac OSX]
~/Documents/Arduino/libraries/lokii/lokii.h
~/Documents/Arduino/libraries/lokii/LokiMain.h





Building
--------------------------------------------------------------------------------

After this library is installed,  you can include #include <lokii.h> in your sketch file  and create a 
LOKII instance to  start all the lokii shield board provided functions.

For example:

#include <lokii.h>

LOKII lokii;

void setup(){
  lokii.connect();
}

void loop(){
  lokii.playTTS(  (String) F("Hello, Welcome to LOKII system!") , L_DEFAULT ,5 ,5 ,E_NATURAL);
  while(true);

}