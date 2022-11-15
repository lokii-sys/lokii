#include <lokii.h>

#define BLOCKING 1
#define NOBLOCKING 0

   
LOKII lokii;


// WIFI
uint8_t wifiStatus[2] = {0, 0};

void readWifiStatus(int prtAnyway)
{
    uint8_t router, cloud;
      
    lokii.getWIFI(&router, &cloud);
    if ( prtAnyway == 1 || wifiStatus[0] != router || wifiStatus[1] != cloud)
    {
        wifiStatus[0] = router;
        wifiStatus[1] = cloud;
        Serial.printf("\nwifi status : %d  %d \n", wifiStatus[0], wifiStatus[1]);
    }
}

void setup(){
  
  Serial.begin(9600);
  //while(!Serial);  

  lokii.connect();  
}

void loop(){

  lokii.playTTS("audio streaming Demo" , L_DEFAULT ,5 ,5 ,E_NATURAL);
  lokii.setCameraMode(L_CAM_A_STREAM); // 10 seconds

  lokii.setWIFI(1, 1);
  Serial.println("Connecting WIFI and Cloud");
  while ( wifiStatus[0] != 1)
  {
      readWifiStatus(0);
  }
  Serial.printf("\nwifi status : %d  %d \n", wifiStatus[0], wifiStatus[1]);

  delay(60000);

  lokii.setCameraMode(L_CAM_A_STREAM_STOP);
  lokii.playTTS("audio streaming stop" , L_DEFAULT ,5 ,5 ,E_NATURAL);

  
  while (1)
      delay(1000);
}
