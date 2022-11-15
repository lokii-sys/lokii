#include <lokii.h>

// BLE IOT CONTROL TEST

LOKII lokii;

// BLOCKY IOT ID from 1, 
// ARDUINO IOT ID from 0

// BLE
#define MAX_BLE_DEVICES 8

uint8_t bleStatus = 0; // BLE power on/off
uint8_t bleConnectedNum = 0;
int connectedBLE[MAX_BLE_DEVICES+1] = {0, 0, 0, 0, 0, 0, 0, 0, 999}; // 1 extra byte for packet index
uint16_t connectedBLEUpdateRate[MAX_BLE_DEVICES] = {0, 0};
char param[256];

char scriptString[3][200] = 
{
"let hu;\r\nsetLCDText('Humindity',0,0);\r\nhu=readHum();\r\nsetLCDText_i(hu,12,0);\r\nif(hu>79) {\r\n    playBuzzer(1000, 3000, 0);\r\n    taskDelay(3000);\r\n}",

"let te;\n\r\nsetLCDText('Temp.     ',0,0);\n\rte=readTemp();\n\rsetLCDText_i(te, 12, 0);\n\rif(te>40)\n\rsetLCDText('Alert',0,1);\n\r else \n\r setLCDText('     ',0,1);",

"let te,by;\n\r\nsetLCDText('Gravity    ',0,0);\n\rte=readGravity();\n\rsetLCDText_i(te, 12,0);\n\rby=isDataRecording();\n\rif((te>5)&&(by===0))\n\rstartDataRec(10);"

};



float qToFloat(int16_t fixedPointValue, uint8_t qPoint)
{
    double qFloat = fixedPointValue;
    qFloat *= pow(2, qPoint * -1);
    return (qFloat);
}

void readRecordedSensorData(uint8_t id)
{
    int j, result;
  
    String sensorTypeString[]={"temperature", "humidity", "co2", "tvoc",  "lux","distance", "soundLevel", "accel", "gyro", "mag", "quaternion"}; // group 3

    uint32_t dataRecordSize;
    uint32_t dataRecordStartTime;
    uint32_t dataRecordEndTime;

    uint16_t sensorType;

    uint16_t sensorData16[3];
    
    // read recorded sensor data
    Serial.printf("ble device %d : read recorded data \n", id); 
    if (lokii.readIOTSensors(id, 1, param, &result) == LOKI_REPLY_OK) // 0=readsensor value, 1= read recorded "sensor data" header 2= read recorded "sensor data" content
    {        
        if (result == 0)
        {
            Serial.printf("no recorded sensor data");
            return;
        }

        // print raw for debug
        //for (j =0; j < result; j++)
        //    printf("%x ", param[j]);
        //printf("\n");
        dataRecordSize =      param[0] + (param[1]<<8) + (param[2]<<16) + (param[3]<<24);
        dataRecordStartTime = param[4] + (param[5]<<8) + (param[6]<<16) + (param[7]<<24);
        dataRecordEndTime =   param[8] + (param[9]<<8) + (param[10]<<16) + (param[11]<<24);
        Serial.printf("Record size: %d StartTime: %d EndTime %d\n", dataRecordSize, dataRecordStartTime, dataRecordEndTime);

        // print raw data for debug
        //while (lokii.readIOTSensors(id, 2, param, &result) == LOKI_REPLY_OK && result > 0)
        //{        
        //    for (j =0; j < result; j++)
        //        printf("%x ", param[j]);
        //    printf("\n");
        //}   
        result = 0;
        while (lokii.readIOTSensors(id, 2, param, &result) == LOKI_REPLY_OK && result > 0)
        {  
             dataRecordStartTime = param[1] + (param[2]<<8) + (param[3]<<16) + (param[4]<<24);
             sensorType = param[5] + (param[6]<<8);
             if (sensorType == 1) 
             {                             
                 Serial.printf("Record Time: %d, temperature: %d.%d Degree\n", dataRecordStartTime, param[7], param[8]);
             }
             else if (sensorType == 2) 
             {                             
                 Serial.printf("Record Time: %d, humidity: %d% \n", dataRecordStartTime, param[7]);
             }             
             else if (sensorType == 3) 
             {                             
                 sensorData16[0] = param[7] + (param[8]<<8);
                 sensorData16[1] = param[9] + (param[10]<<8);
                 Serial.printf("Record Time: %d, co2: %d%, tvoc: %d\n", dataRecordStartTime, sensorData16[0], sensorData16[1]);
             }               
             else if (sensorType == 4) 
             {                             
                 sensorData16[0] = param[7] + (param[8]<<8);
                 sensorData16[1] = param[10] + (param[11]<<8);
                 Serial.printf("Record Time: %d, lux: %d%, distance: %dmm, soundLevel: %d\n", dataRecordStartTime, sensorData16[0], param[9], sensorData16[1]);
             }      
             else if (sensorType == 7) 
             {                             
                 sensorData16[0] = param[7] + (param[8]<<8);
                 sensorData16[1] = param[9] + (param[10]<<8);
                 sensorData16[2] = param[11] + (param[12]<<8);                 
                 Serial.printf("Record Time: %d, accel: %f %f %f m^2/s\n", dataRecordStartTime, qToFloat(sensorData16[0], 8), qToFloat(sensorData16[1], 8), qToFloat(sensorData16[2], 8));

                 sensorData16[0] = param[13] + (param[14]<<8);
                 sensorData16[1] = param[15] + (param[16]<<8);
                 sensorData16[2] = param[17] + (param[18]<<8);                 
                 Serial.printf("Record Time: %d, gyro: %f %f %f rad/second \n", dataRecordStartTime, qToFloat(sensorData16[0], 9), qToFloat(sensorData16[1], 9), qToFloat(sensorData16[2], 9));

                 sensorData16[0] = param[19] + (param[20]<<8);
                 sensorData16[1] = param[21] + (param[22]<<8);
                 sensorData16[2] = param[23] + (param[24]<<8);                 
                 Serial.printf("Record Time: %d, mag: %f %f %f uTesla \n", dataRecordStartTime, qToFloat(sensorData16[0], 4), qToFloat(sensorData16[1], 4), qToFloat(sensorData16[2], 4));

             } 
        }                            
    }
    else
    {
        printf("header: fail\n");            
    }
}


void readConnectionStatus(void)
{
    int number2, readStrLength;
    int number, i, j, oldIndex;
    String readStr = "LONG STRING LONG STRINGLONG STRINGLONG STRINGLONG STRING";
    int result;


        
    // last byte is packet index
    // any ble connected/disconnected event happen packet index will change
    oldIndex = connectedBLE[MAX_BLE_DEVICES];
    
    // Update Connection Status : read connection status to array connectedBLE
    number = lokii.connectIOT(MAX_BLE_DEVICES, connectedBLE);

    //Serial.printf("\nble device current total connected: %d \n", number);
        
    // Update Config : if connection status change , then read the config again
    if (bleConnectedNum != number || (number > 0 && connectedBLE[MAX_BLE_DEVICES] != oldIndex))
    {
        bleConnectedNum = number;

        // print connected device
        Serial.printf("\nble device total connected: %d \n", number);
        for (i = 0,j = 0;i < MAX_BLE_DEVICES; i++)
        {
            if (connectedBLE[i]) // connected
            {
                Serial.printf("\nble device %d : %s \n", i+1, "Connected");
            }
            else
            {
                //Serial.printf("\nble device %d : %s \n\n", i+1, "Disconnected");
            }
        }        
    }

    if (Serial.available() > 0) 
    {
        // read string
        ///////////////////////////////////////////////////////////
        for (i = 0;i < 12; i++)
            readStr[i] = 0;
        i = 0;            
        readStr[i++] = Serial.read(); // "readstring" command the last byte is not 0x00 so use "read" instead
        while (readStr[i-1] >= ' ' && readStr[i-1] <= 'z') // if non ascii , then it's end
        {
            //Serial.println(readStr[i-1], HEX);          
            readStr[i++] = Serial.read();
        }   
        readStr[i-1] = 0;
        readStrLength = i-1;
        Serial.println(&(readStr[0])); // not stop with 0x00, print full string

        // parse the read string into parameraters
        j = 0;
        result = 0;
        number = 0;
        number2 = 0;
        for (i = 0; i <= readStrLength; i++)
        {
            if (readStr[i] == ' ' || readStr[i] == 0) // seperate char found
            {
                if (j == 0)
                {
                    readStr[i] = 0;
                    result = i;                
                    Serial.print("cmd : \"");                 
                    Serial.print(&(readStr[0]));
                    Serial.print("\"");
                }
                else if (j == 1) 
                {
                    number = readStr.substring(result+1).toInt();
                    Serial.print(" param : ");
                    Serial.print(number);

                    //ttsStart = result+1;
                    result = i;
                    
                }
                else if (j == 2) 
                {
                    number2 = readStr.substring(result+1).toInt();
                    Serial.print(" ");
                    Serial.print(number2);                           
                }
                j++;
            }           
        }        
        Serial.println("");  
        ///////////////////////////////////////////////////////////        
        

        if (readStr.equals("send")) // send recorded sensor data to smartshield
        { 
            Serial.println("IOT send recorded data to smartShield");           
            result = 0;
            for (i = 0; i < MAX_BLE_DEVICES; i++)
            {
                if (connectedBLE[i])
                {                  
                  param[0] = 2; // type
                  param[1] = 0;             

                    if (lokii.commandIOT(i, (char*)(param), 2) != LOKI_REPLY_OK) // may fail because of disconnected
                    {
                        Serial.printf("ble device %d command write FAIL\n", i+1);
                    }
                    else
                    {
                        Serial.printf("ble device %d command write SUCCESS\n", i+1);
                        result = 1;
                    }
                }
            } 

            if (result == 1)
               delay(300);// config take effect need time? avoid repeat writing config   
        }
        else if (readStr.equals("read")) // read recorded sensor data in smartshield
        {          
            // R1 IDLE
            // R2 preparing
            // R3 recording
            // R4 sending            
            Serial.println("read recorded data stored in smartShield");             
            for (i = 0;i < MAX_BLE_DEVICES; i++)
            { 
                if (connectedBLE[i] != 0)// && connectedBLEConfig[i].humidity_interval_ms != 0) 
                {
                    // read recorded sensor data
                    readRecordedSensorData(i);       
                }
            }
        }        
        else if (readStr.equals("script"))
        {
            Serial.println("send script");           
            // send script
            number--;            
            j = number2;
            
            if (connectedBLE[number])
            {
                Serial.printf("ble device %d , Script : %s \n", number+1, scriptString[j]);
                lokii.setSmartIOTAction(number, scriptString[j], strlen(scriptString[j])+1);
                j++;
            }
        }
    }
}


void setup(){
  
  Serial.begin(9600);
  while(!Serial);
            
  lokii.connect();
}

void loop(){
  
    Serial.printf("BLE IOT Control Demo\n");  
    lokii.playTTS("I O T, Control Demo" , L_DEFAULT ,5 ,5 ,E_NATURAL);

    Serial.printf("Turn On BLE\n");                  
    lokii.startBLE();
    //Serial.printf("Turn Off BLE\n");
    //lokii.closeBLE();
          
    bleStatus = lokii.getBLE();    
    if (bleStatus == 1)    // should be OFF
        Serial.printf("BLE:OFF %d\n", bleStatus);
    else if (bleStatus == 2)       
        Serial.printf("BLE:ON %d\n", bleStatus);
    else
        Serial.printf("BLE:UNKNOWN %d\n", bleStatus);    

                 
    while (true) {  
        readConnectionStatus();
        delay(1000);
    }
  
}
