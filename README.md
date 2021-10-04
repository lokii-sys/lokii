# lokii
LOKII Arduino Shield Library (Support for 1st Generation LOKII boards and the upcoming  2nd Generation LOKII-CE boards) <p>
1) LokiiLib1.0.4.zip is the latest library for LOKII boards <p>
2) LokiiLib1.0.5.zip is the latest library for LOKII-CE boards which support following new features:
  - sound direction detection
  - BLE connection for sensors reading 
  - WIFI connection

# Preparation
First, user need to install the Arduino IDE on their window or MAC computer.

After the Arduino IDE installation, user can download the “LokiiLib1.0.x.zip”
and “lokii_sd.zip” from github.

User should unzip “lokii_sd.zip” into a FAT32 format TF card and insert the
TF card into the LOKII Arduino Shield boards before power up.

# Arduino Library Installation
With the above preparation, user can open the Arduino IDE, and locate the
“LokiiLib1.0.x.zip” by clicking “Sketch” —> “Include Library” —>Add .ZIP
Library.

In the file browser, select the “LokiiLib1.0.x.zip” to install the LOKII Arduino
library.

# Arduino Test

LOKII Hello world Programming<p>
After LOKII library installation, user can select  “Examples” from Arduino IDE "Files" menu and locate “LOKII”
for a simple demo program called “tts_red_litte_riding_hood”.

Once the example is loaded, user can compile and upload the example to
test the LOKII functions. If everything ok, you will hear the Text-To-Speech
voice playback form the LOKII attached speaker.

# LOKII Examples
You can always download the examples from examples folder to taste all LOKII functions.


