// protocol.

#ifndef _LOKIMAIN_H
#define _LOKIMAIN_H

// uncomment to turn on debug prints to console
//#define LOKI_DEBUG_ON
#define TURNON_CMD8BIT


//#define PRINT_VR_RESULT




// CMD FORMAT : SyncHeader(2byte) + CMD(1byte) + DataLength(1byte) + Data
#define L_BUFFERSIZE                         0x0120
#define WITH_CHECKSUM_HEADER                 0xc1af
#define WITHOUT_CHECKSUM_HEADER              0xc1ae
#define L_SEND_HEADER_SIZE                        4






// SPI<->LOKI Command List
// must less than 0x80
#define L_VERSION                        0x40
#define L_PLAY_TTS                       0x44
#define L_RECOGNIZE_GROUP                0x45
#define L_COLOR_REGISTER_CUSTOM_PREVIEW  0x46
#define L_COLOR_REGISTER_CUSTOM_GENERATE 0x47
#define L_COLOR_RECOGNIZE_CUSTOM         0x48
#define L_COLOR_RECOGNIZE_RGB            0x49
#define L_FACE_DETECTION                 0x43
#define L_TAKE_PHOTO                     0x4A
#define L_DISPLAY_PHOTO                  0x4B

#define L_REQUEST_RECOGNITION_RESULT     0x4C

#define L_MOVE_MOTOR                     0x4D
#define L_READ_MOTOR                     0x4E

#define L_PLAYBACK_MOTOR_SEQUENCE        0x4F
#define L_RECORD_MOTOR_SEQUENCE          0x50
#define L_RECORD_MOTOR_END               0x3F

#define L_SET_RGB_LED                    0x51


#define L_CHECK_AUDIO_STATUS             0x52


#define L_SET_SMART_ID                   0x53
#define L_GET_SMART_COUNT                0x54
#define L_SCAN_SMART_BUS                 0x55

#define L_PLAYFILE                 0x56
#define L_STOPFILE                 0x57
#define L_PLAYNOTE                0x58

#define L_CREATE_SD               0x59
#define L_TRAIN_KEYWORD           0x60
#define L_SAVE_SD                 0x61

#define L_SET_GET_MIC             0x62

#define L_TAKEPHOTO                 0x63
#define L_SHOWPHOTO                0x64

#define L_MOVE_MULTI_MOTOR           0x65
#define L_MULTI_ACTION  0x66

#define L_REC_PLAY_VIDEO        0x67
#define L_STOP_REC_PLAY_VIDEO   0x68

#define L_REC_AUDIO_FILE                  0x69
#define L_STOP_REC_AUDIO_FILE             0x70

#define L_MOVE_RC_SERVO 0x71
#define L_MOVE_DC_MOTOR 0x72


#define L_SEND_STRING 0x73
#define L_GET_STRING  0x74









#define LOKI_REPLY_OK                      0
#define LOKI_REPLY_FAIL                   -1
#define LOKI_RESULT_BUSY                  -2
#define LOKI_RESULT_CHECKSUM_ERROR        -3
#define LOKI_RESULT_RETURN_ERROR          -6

#define RESULT_TYPE_OBJECT_DETECTION  0
#define RESULT_TYPE_VOICE_RECOGNITION 1

#define OBJECT_FACE                  0x0F
#define OBJECT_BLACK                 0
#define OBJECT_R                     1
#define OBJECT_G                     2
#define OBJECT_B                     3
#define OBJECT_CUSTOM                4



















// blob color definition
#define L_BLACK_COLOR   0
#define L_RED_COLOR     1
#define L_GREEN_COLOR   2
#define L_BLUE_COLOR    3
#define L_CUSTOM_COLOR  4

// LOKII camera states
#define L_CAM_PREVIEW           0 
#define L_CAM_RECOGNIZE_CUSTOM  1
#define L_CAM_RECOGNIZE_RGB     3
#define L_CAM_FACE_DETECT       4


// blob atributeType 
#define  L_XPOS                 0
#define  L_YPOS                 1
#define  L_WIDTH                2
#define  L_HEIGHT               3
#define  L_COLOR                4

// wordgroupIndex
#define  L_KEYWORD_STOP         0
#define  L_KEYWORD_GROUP1       1
#define  L_KEYWORD_GROUP2       2
#define  L_KEYWORD_GROUP3       3
#define  L_KEYWORD_GROUP4       5

// voice type
#define  L_DEFAULT     0
#define  L_MAN         1
#define  L_OLDMAN      2
#define  L_OLDWOMAN    3
#define  L_BOY         4
#define  L_YOUNGGIRL   5
#define  L_ROBOT       6
#define  L_GIANT       7
#define  L_DWARF       8
#define  L_ALIENT      9



#define  E_NATURAL     0
#define  E_FRIENDLY    1
#define  E_ANGRY       2
#define  E_FURIOUS     3
#define  E_DRILL       4
#define  E_SCARED      5
#define  E_EMOTIONAL   6
#define  E_WEEPY       7
#define  E_EXCITED     8
#define  E_SURPRISED   9
#define  E_SAD        10
#define  E_DISGUSTED  11
#define  E_WHISPER    12



 
#define L_ON    1
#define L_OFF   0



#define NON_BLOCKING 0
#define BLOCKING     1



#define mod_servo		0
#define mod_led_rgb		1
#define mod_rc_servo	2
#define mod_dc_mot		3


enum CameraRecognitionMode {
  PREVIEW_MODE,
  CUSTOM_OBJECT_RECOGNIZE_MODE_AND_REGISTER_CENTER,
  CUSTOM_OBJECT_RECOGNIZE_MODE,
  RGB_COLOR_RECOGNIZE_MODE,
  FACE_RECOGNIZE_MODE,
  CAPTURE_PHOTO,
  SHOW_PHOTO
};

struct Version
{  
  uint8_t hardware;
  uint8_t firmwareMajor;
  uint8_t firmwareMinor;
  uint8_t firmwareBuild;
  //char firmwareType[10];   
};


struct BlockObject 
{
  // print block structure!
  void print()
  {
    //char buf[128];
    //sprintf(buf, "object type: %d x: %d y: %d width: %d height: %d ", m_type, m_x, m_y, m_width, m_height);   
    //Serial.println(buf); 
  }
  
  uint16_t m_type;
  uint16_t m_x;
  uint16_t m_y;
  uint16_t m_width;
  uint16_t m_height;
};


template <class LinkType> class LokiMain
{
public:
  LokiMain();
  ~LokiMain(); 

  int8_t init();

  int8_t getVersion();
  void   printVersion();

  // with return
  //int8_t setFaceDetection(bool onOff);
  int8_t playTextToSpeech(String textString, uint8_t volume=7, uint8_t frequency=5, uint8_t pitch=5, uint8_t emotion=0, uint8_t character=0);
  //int8_t playTextToSpeech(char *textString, uint8_t volume, uint8_t frequency, uint8_t pitch, uint8_t emotion, uint8_t character);
  int8_t setVoiceRegonizeGroup(uint8_t groupNumber);
  int8_t setCameraRecognitionMode(CameraRecognitionMode mode, bool isBlocking);
  int8_t getResult(void);

  int8_t setSmartID(int id);
  int8_t setSmartLED(int motorid,  int r, int g, int b);    
  int8_t getSmartCount(void);
  int8_t scanSmartBus(void);
  
  void setMotorPower(int motorid, int state);



  Version version;

  LinkType m_link;
  

  uint8_t vrGroup;
  uint8_t vrResult;

  uint8_t numObjects;
  BlockObject objects[20];



//*************************************//
// MIXLY INTERFACE
//*************************************//
// ------------------------------------------------------------------------------------
//   Edward: Change in the function are summerized here
// --------------------------------------------------------------------------------------


    // Same syntax.  Add print out for successfully set the smart device address
    void setSmartDeviceAdress(int id);


    // return number of smart device in the bus
    // if there is any errror (such as conflicted address ) ,return -1;
    int getSmartDeviceCount(void);
    int getSmartMotorCount(void);
    int getSmartLEDCount(void);

    int setgetMicrophone(int micSource);
    void setMicrophone(int source);
    int getMicrophone(void);

    // return 0x01 for success, other for error
    int takePhoto(String filename);

    // return 0x01 for success, other for error
    int displayPhoto(String filename);


    // play the midi note number util it finish.
    // if the value is negative,  block the function for 1 seconds to simulate a silence note
    int playMIDI(int note);
    void setMIDIBPM(int bpmIn);

    // ---------------------------------------------------------
    // Create Speaker Dependent  keyword group
    // groupIndex = 11 -20 inclusively
    // numKeyworkds = 1 -5 inclusively
    // return 1 success
    //        0 fail  
    // ---------------------------------------------------------
    int createSDGroup(int groupIndex, int numKeywords);


    // ---------------------------------------------------------
    // Train Speaker Dependent  keyword group
    // groupIndex = 11 -20 inclusively
    // numKeyworkds = 1 -5 inclusively
    // return 1 success
    //        0 fail  
    // ---------------------------------------------------------
    int trainSDkeyword(int groupIndex, int keywordsIndex);

  // ---------------------------------------------------------
    // Check Speaker Dependent  keyword group completeness
    // groupIndex = 11 -20 inclusively
    // return 1 success  (If all keywords are trained )
    //        0 fail     
    // ---------------------------------------------------------    
    int checkSDComplete(int groupIndex);

    //Init LOKII here
    void connect();

    // LOKII camera states
    void setCameraMode( int cameraState, bool isBlocking=true );
    // register custom color
    void registerColor();

    int getFaceResult(int atributeType );
    int waitForFaceResult(int faceState);

    int getBlobCount( );
    int getBlobResult( int blobIndex, int atributeType );
    int waitForBlobResult(bool isBlocking=true);

    void startSpeechRecognize( int wordgroupIndex);
    int getSpeechResult( );
    int waitForSpeechResult();


    int sendString(char* textString, int num, bool isBlocking=false);
    int8_t getString(char *str);


    // Speech and sound methods
    void setVolume(int vol);
    void playTTS( String text,  int voiceType, int speed, int pitch , int emotion);
    void playSoundFile( String filename, bool isBlocking);
    void stopSound();

    int checkAudioStatus( );

    // Motor functions , position = 0xFFFF for endless movement
    void moveMotor( int motorid, int speed, int  position , int direction );
    int  readMotorPosition(int motorid); 
    void moveMultiMotor( int motorid, int speed, int  position , int direction );
    void moveMultiMotorStart(void);



    void playbackMotor();
    void recordMotor(int numSeconds);

    void setRGB(int motorid,  int r, int g, int b);    


    void prepareSetRCServoBuffer(int motorid, int speed, int  position, int type);
    int readRCServoPosition( int motorid);
    int8_t setRCServo(int motorid, int speed, int  position);
    int8_t setRCServoUp(int motorid);
    int8_t setRCServoDown(int motorid);
    int8_t setRCServoStop(int motorid);
    void setRCServoAction(int motorid, int speed, int  position);
    void setRCServoActionUp(int motorid);
    void setRCServoActionDown(int motorid);
    void setRCServoActionStop(int motorid);


    void setRGBAction(int motorid,  int r, int g, int b);
    void moveMotorAction( int motorid, int speed, int  position , int direction);
    void startMultiAction(bool isBlocking=true);


//*************************************//
// MIXLY INTERFACE
//*************************************//
  int stopRecordMotor(void);

  void prepareSetDCMotor(int motorid, int speed, int  direction);
  int8_t setDCMotor(int motorid, int speed, int  direction);
  void setDCMotorAction(int motorid, int speed, int  direction);

  int recordVideo(String filename);
  int playVideo(String filename);
  int stopRecordVideo(String filename);
  int stopPlayVideo(String filename);

  int recAudio(String filename);
  int stopRecAudio(void);


private:
  int16_t getSync();
  int16_t recvPacket();
  int16_t sendPacket(bool checksum=false);
  void prepareSetSmartLEDBuffer(int motorid,  int r, int g, int b);

  void toActionBuffer(void);


  int processVideo(String filename, int para);
  int stopProcessVideo(int para);

  uint8_t *m_buf;
  uint8_t *m_bufPayload;
  uint8_t m_type;
  uint8_t m_length;
  bool m_cs;

  uint8_t sndVolume;

  uint8_t needReadAgain;

  uint8_t cmd8bit;
  uint8_t cmdCount;

  uint8_t *motorCmdBuf;
  uint8_t motorCmdNum;



  uint8_t *actionsCmdBuf;
  uint8_t actionsCmdLength;



  uint8_t smartCount;
  uint8_t motorCount;
  uint8_t ledCount;
  uint8_t rcServoCount;
  uint8_t dcMotorCount;
  uint8_t unknownCount;


  // midi
  int bpm;
  int duration;
};










///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////Function Start
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

template <class LinkType> LokiMain<LinkType>::LokiMain()// : ccc(this), line(this)
{
  m_buf = (uint8_t *)malloc(L_BUFFERSIZE);
  m_bufPayload = m_buf + L_SEND_HEADER_SIZE;


  version.hardware = 0;
  version.firmwareMajor = 0;
  version.firmwareMinor = 0;
  version.firmwareBuild = 0;


  sndVolume = 7;
  numObjects = 0;
  vrGroup = 0;
  needReadAgain = 1;
  cmd8bit = 0;

  motorCmdBuf = m_buf;
  motorCmdNum = 0;


  actionsCmdBuf = m_buf;
  actionsCmdLength = 0;

  bpm = 90;
  duration = 1000/bpm * 60;
}

template <class LinkType> LokiMain<LinkType>::~LokiMain()
{
  m_link.close();
  free(m_buf);
}


template <class LinkType> int8_t LokiMain<LinkType>::init(void)
{
  uint32_t t0;
  int8_t res;
  
  res = m_link.open();
  if (res<0)
    return res;

  for(t0 = millis(); millis() - t0 < 5000; )
  {
    //if (getVersion() == LOKI_REPLY_OK) // check device ready
    if (scanSmartBus() == LOKI_REPLY_OK)
	{
      Serial.println("SPI OK") ;
      return LOKI_REPLY_OK;
    }	  
    //return LOKI_REPLY_FAIL;
    delayMicroseconds(5000); // delay for sync
  }

  m_link.close();
  Serial.println("SPI Fail") ;
  //while (1);

  // timeout
  return LOKI_REPLY_FAIL;

}

template <class LinkType> void LokiMain<LinkType>::connect(void)
{
    init();
}

template <class LinkType> int16_t LokiMain<LinkType>::getSync()
{
  uint8_t i, j, c, cprev;
  int16_t res;
  uint16_t start;

#ifdef LOKI_DEBUG_ON  
uint8_t k;
uint8_t rcvBytes[32];
k = 0;
#endif


res = 0;
c = 0;
cprev = 0;
start = 0;



#ifdef LOKI_DEBUG_ON
  Serial.println('S') ;
#endif


  // parse bytes until we find sync
  for(i=j=0, cprev=0; true; i++)
  {
#ifdef LOKI_DEBUG_ON
    k++;
#endif

    res = m_link.recv(&c, 1);
    if (res>=LOKI_REPLY_OK)
    {

#ifdef LOKI_DEBUG_ON
      rcvBytes[k]=c;
      Serial.print(c, HEX);
      Serial.print(' ') ;
#endif

      // since we're using little endian, previous byte is least significant byte
      start = cprev;
      // current byte is most significant byte
      start |= c << 8;
      cprev = c;
      if (start==WITH_CHECKSUM_HEADER)
      {
	    m_cs = true;
	    return LOKI_REPLY_OK;
      }
      if (start==WITHOUT_CHECKSUM_HEADER)
      {
	    m_cs = false;
        return LOKI_REPLY_OK;
      }
    }

    
    if (i>=4*2)//*(1+ m_length/20))
    {
      //if (j>=4)
      //{     
//for(i=0; i < 32; i++)
//{
//    Serial.print(rcvBytes[i], HEX) ;//gives "4E"
//    Serial.print(' ') ;//gives "4E"
//}

#ifdef LOKI_DEBUG_ON
        Serial.println("\nerror: no response");
#endif		  
        return LOKI_REPLY_FAIL;
      //}
      //j++;
      //i = 0;
    }

    if (c == 0)
        delay(20 * (1+ m_length/50) );
    else
        delay(1);
  }


}


template <class LinkType> int16_t LokiMain<LinkType>::recvPacket()
{
  //uint8_t i;

  uint16_t csCalc, csSerial;
  int16_t res;

  res = getSync();
  if (res<0)
  {
    m_link.csDisable();
    return res;
  }

  if (m_cs)
  {
    m_buf[0] = WITH_CHECKSUM_HEADER&0xff;
    m_buf[1] = WITH_CHECKSUM_HEADER>>8;
    csSerial = m_buf[0] + m_buf[1];

    res = m_link.recv(m_buf, 2);
    if (res<0)
    {
      m_link.csDisable();
      return res;
    }

#ifdef LOKI_DEBUG_ON
      Serial.print(m_buf[0], HEX);
      Serial.print(' ') ;
      Serial.print(m_buf[1], HEX);
      Serial.print(' ') ;
#endif

    m_type = m_buf[0];
    m_length = m_buf[1];
    csSerial += m_buf[0] + m_buf[1];

    res = m_link.recv(m_buf, m_length, &csCalc);
    if (res<0)
    {
      m_link.csDisable();
      return res;
    }

#ifdef LOKI_DEBUG_ON
      Serial.print(m_buf[0], HEX);
      Serial.print(' ') ;
      Serial.print(m_buf[1], HEX);
      Serial.print(' ') ;
      Serial.print(m_buf[2], HEX);
      Serial.print(' ') ;

#endif

    csSerial += (csCalc - m_buf[m_length-2] - m_buf[m_length-1]);

    csCalc = m_buf[m_length-2] * 256 + m_buf[m_length-1];

    if (csSerial!=csCalc)
    {
#ifdef LOKI_DEBUG_ON
      //Serial.print(m_length, HEX);
      //Serial.print(' ');
      //Serial.print(csSerial, HEX);
      //Serial.print(m_buf[m_length-4], HEX);
      //Serial.print(' ');
      //Serial.print(m_buf[m_length-3], HEX);
      //Serial.print(' ');
      //Serial.print(m_buf[m_length-2], HEX);
      //Serial.print(' ');
      //Serial.print(m_buf[m_length-1], HEX);
      Serial.print(" error: checksum ");
      //Serial.println(csCalc, HEX);
#endif
      m_link.csDisable();
      return LOKI_RESULT_CHECKSUM_ERROR;
    }
  }
  else
  {   
    res = m_link.recv(m_buf, 2);
    if (res<0)
    {
      m_link.csDisable();
      return res;
    }

    m_buf[0] = (m_buf[0] & 0x7F);// return the result without cmd8bit
    m_type = m_buf[0];
    m_length = m_buf[1];

    res = m_link.recv(m_buf, m_length);
    if (res<0)
    {
      m_link.csDisable();
      return res;
    }
  }

  // if successfully get response , xor the 8bit,
  // so the mcu side know if this is the retry command or new command
#ifdef TURNON_CMD8BIT
  cmd8bit = (cmd8bit ^ 0x80); 
#endif

  m_link.csDisable();

  return LOKI_REPLY_OK;
}


template <class LinkType> int16_t LokiMain<LinkType>::sendPacket(bool checksum)
{
  // write header info at beginnig of buffer
  uint16_t csCalc, i;
  m_link.csEnable();

  m_buf[2] = m_type | cmd8bit;
  m_buf[3] = m_length;
  if (checksum == false)
  {
    m_buf[0] = WITHOUT_CHECKSUM_HEADER&0xff;
    m_buf[1] = WITHOUT_CHECKSUM_HEADER>>8;
  }
  else
  {
    m_buf[0] = WITH_CHECKSUM_HEADER&0xff;
    m_buf[1] = WITH_CHECKSUM_HEADER>>8;
    csCalc = 0;
    for (i = 0; i < (m_length+L_SEND_HEADER_SIZE-2); i++)
    {
      csCalc += m_buf[i];
    }
    m_bufPayload[m_length-2] = (csCalc)>>8;
    m_bufPayload[m_length-1] = (csCalc)&0xFF;
  }

  // send whole thing -- header and data in one call
  return m_link.send(m_buf, m_length+L_SEND_HEADER_SIZE);
}


template <class LinkType> int8_t LokiMain<LinkType>::getVersion()
{
  m_type = L_VERSION;
  m_length = 2;
  sendPacket(true);
  if (recvPacket()==0)
  {   
    if (m_type == L_VERSION)
    {
      version.hardware = m_buf[0];
      version.firmwareMajor = m_buf[1];
      version.firmwareMinor = m_buf[2];
      version.firmwareBuild = m_buf[3];

      return LOKI_REPLY_OK;
    }
  }
  
  return LOKI_REPLY_FAIL;  // some kind of bitstream error
}

template <class LinkType> void LokiMain<LinkType>::printVersion()
{
    char buf[64];

    sprintf(buf, "hardware ver: 0x%x firmware ver: %d.%d.%d", version.hardware, version.firmwareMajor, 
                   version.firmwareMinor, version.firmwareBuild);

    Serial.println(buf);

}

/*
template <class LinkType> int8_t LokiMain<LinkType>::setFaceDetection(bool onOff)
{
 
 
  m_type = L_FACE_DETECTION;
  m_length = 3;
  m_bufPayload[0] = onOff;
  sendPacket(true);
  if (recvPacket()==0 && m_type==L_FACE_DETECTION)
  {
      if (m_buf[0] == 1)
          return LOKI_REPLY_OK;	
      else // 0xFF
          return LOKI_RESULT_RETURN_ERROR;
  }
  else
      return LOKI_REPLY_FAIL;  // some kind of bitstream error
}
*/

#if 1
template <class LinkType> int8_t LokiMain<LinkType>::playTextToSpeech(String textString, uint8_t volume, uint8_t frequency, uint8_t pitch, uint8_t emotion, uint8_t character)
{
  int textLength;
  int retry;


  String localString;
  localString = textString + ' ';

  m_type = L_PLAY_TTS;
  m_length = 5 + localString.length() + 2;

  m_bufPayload[0] = volume;
  m_bufPayload[1] = frequency;
  m_bufPayload[2] = pitch;
  m_bufPayload[3] = emotion;
  m_bufPayload[4] = character;

  textLength = localString.length();

  //Serial.println(textString);
  //Serial.println(textLength);

  localString.toCharArray((char*)(m_bufPayload + 5), textLength ); // not include the string end char '0x00'

  //Serial.println(m_bufPayload[5 + textLength-3], HEX);
  //Serial.println(m_bufPayload[5 + textLength-2], HEX);
  //Serial.println(m_bufPayload[5 + textLength-1], HEX);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_PLAY_TTS)
  {
    
    textLength = LOKI_REPLY_FAIL;
    retry = 0;

    // wait until the audio status(TTS finish) is silence
    while (textLength != 0)
    {
        delay(50);
        textLength = checkAudioStatus(); // 1 = playing , 0 = idle, -1 = no reply

//delay(2000);
//textLength = 0;
        if (textLength == LOKI_REPLY_FAIL)
            retry += 1;
        else 
            retry = 0;
        ///if (retry > 10)
        //    return LOKI_RESULT_RETURN_ERROR;
    }

    //Serial.println(localString);

    //if (m_buf[0] == 1)
        return LOKI_REPLY_OK;	
    //else // 0xFF
    //    return LOKI_RESULT_RETURN_ERROR;
  }
  else
  {
      return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  }
}
#endif


template <class LinkType> int LokiMain<LinkType>::sendString(char *textString, int num, bool isBlocking)
{
  int textLength;
  int retry;
  int i;

  uint8_t repeat;

  repeat = 1;
while(repeat == 1)
{

  //String localString;
  //localString = textString;// + ' ';

  m_type = L_SEND_STRING;
  m_length = num+2;//localString.length() + 2;

  textLength = num;//localString.length();

  //Serial.println(textString);
  //Serial.println(textLength);
  
  for (i = 0; i < textLength; i++)	  
  {
     m_bufPayload[i] = textString[i];
     //Serial.println(textString[i], HEX); 
  }
  //textString.toCharArray((char*)(m_bufPayload), textLength ); // not include the string end char '0x00'

  //Serial.println(m_bufPayload[textLength-3], HEX);
  //Serial.println(m_bufPayload[textLength-2], HEX);
  //Serial.println(m_bufPayload[textLength-1], HEX);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_SEND_STRING)
  {
        return LOKI_REPLY_OK;	
  }
  else
  {
      delay(50);//return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  }

  if (isBlocking != true)
    repeat = 0;
}

}


template <class LinkType> int8_t LokiMain<LinkType>::getString(char *str)
{
  uint8_t readLength;
  int result;
  uint8_t repeatLast;
  int i;

  numObjects = 0;
  vrGroup = 0;

  repeatLast = cmd8bit;
  m_type = L_GET_STRING;
  m_length = 2;
  sendPacket(true);
  result = recvPacket();
  if (result == 0 && m_type == L_GET_STRING)
  {
      i = 0;
      readLength  = 2;
      while (readLength < m_length)
      {
          str[i] = m_buf[i];
          //Serial.println(str[i], HEX);
          readLength++;
          i++;
      }

      if (readLength != 2)
      {
          //Serial.println(m_length);
          return m_length-2;//LOKI_REPLY_OK;
      }
      else
      {
          return 0;//LOKI_REPLY_FAIL;
      }
  }
  else
  {
      //Serial.println('F');
      //Serial.println(m_type);
      cmd8bit = repeatLast;
      if (result == 0) // it's last command's reply, not current command
          return 0;//LOKI_REPLY_FAIL; 
      else
          return 0;//result;
  }
}




template <class LinkType> void LokiMain<LinkType>::setVolume(int volume)
{
    if (volume >= 0 && volume < 11)
        sndVolume = volume;
    else
        sndVolume = 10;
    //playTextToSpeech(" ", sndVolume, 3,4,1,1);
    //delay(1000);
}


// Constant String need F() marco to store at Flash instead of RAM
template <class LinkType> void LokiMain<LinkType>::playTTS( String text,  int voiceType, int speed, int pitch , int emotion)
{

  int charDot;
  //int charComma;
  int charOther;
  int targetEnd;
  int searchFrom;
  String tailStr;
  String headStr;


  searchFrom = 0;
  //strcpy(tailStr, text);
  //tailStr.reserve(text.length());
  tailStr = String(text);
   

     // Serial.println(tailStr);  
  // TTS SPI Command too long will have problem, need to parse
#if 1

  while (tailStr.length() > 80)
  {


    charDot = tailStr.indexOf('.', searchFrom);
    //charComma = tailStr.indexOf(',', searchFrom);
    charOther = tailStr.indexOf("  ");

    targetEnd = -1;
    // take the min length
    if (targetEnd == -1 || charDot != -1)
      targetEnd = charDot;
    //if (targetEnd == -1 || (charComma != -1 && charComma < targetEnd))
    //  targetEnd = charComma;
    if (targetEnd == -1 || (charOther != -1 && charOther < targetEnd) )
      targetEnd = charOther;


    //Serial.println(targetEnd);

    if (targetEnd != -1 && targetEnd < 80)
    {
      headStr = tailStr.substring(0, targetEnd);
      tailStr = tailStr.substring(targetEnd+1);

      //Serial.println(targetEnd);      
      //Serial.println(headStr);

      if (targetEnd != 0 ) // speak non empty string
        while (playTextToSpeech(headStr, sndVolume, speed, pitch, emotion, voiceType) == LOKI_REPLY_FAIL)
        {
          delay(50);
        }
    }
    else
    {
        if (targetEnd == -1)
        {
            //Serial.println(tailStr.length());
            //Serial.println(tailStr);
            //Serial.println("line too long and can't parse");
            return;    
        }
        else
        {
            headStr = tailStr.substring(0, targetEnd);
            tailStr = tailStr.substring(targetEnd+1);

            //Serial.println(targetEnd);
            //Serial.println(headStr);
            //Serial.println("line too long and parse next line");
        }
    }

  }
#endif

  //Serial.println(tailStr);
  while (playTextToSpeech(tailStr, sndVolume, speed, pitch, emotion, voiceType) == LOKI_REPLY_FAIL)
  {
      delay(50);
  }

}

template <class LinkType> int8_t LokiMain<LinkType>::setVoiceRegonizeGroup(uint8_t groupNumber)
{
  //uint8_t localGroupNum;

  //if (localGroupNum > 3)
  //    localGroupNum = 3;

  m_type = L_RECOGNIZE_GROUP;
  m_length = 3;
  m_bufPayload[0] = groupNumber;
  sendPacket(true);
  if (recvPacket()==0 && m_type==L_RECOGNIZE_GROUP)
  {
      if (m_buf[0] != 0xFF)
          return LOKI_REPLY_OK;	
      else // 0xFF
          return LOKI_RESULT_RETURN_ERROR;
  }
  else
      return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  
}

template <class LinkType> void LokiMain<LinkType>::startSpeechRecognize(int wordgroupIndex)
{
    while (setVoiceRegonizeGroup(wordgroupIndex) == LOKI_REPLY_FAIL)
    {
        delay(100);
    }
}

template <class LinkType> int8_t LokiMain<LinkType>::setCameraRecognitionMode(CameraRecognitionMode mode, bool isBlocking)
{
  uint8_t inType;
  uint8_t repeat;

  repeat = 1;
while(repeat == 1)
{
  if (mode == CUSTOM_OBJECT_RECOGNIZE_MODE_AND_REGISTER_CENTER)
      inType = L_COLOR_REGISTER_CUSTOM_GENERATE;
  else if (mode == CUSTOM_OBJECT_RECOGNIZE_MODE)
      inType = L_COLOR_RECOGNIZE_CUSTOM;
  else if (mode == RGB_COLOR_RECOGNIZE_MODE)
      inType = L_COLOR_RECOGNIZE_RGB;
  else if (mode == FACE_RECOGNIZE_MODE)
      inType = L_FACE_DETECTION;
  else if (mode == CAPTURE_PHOTO)
      inType = L_TAKE_PHOTO;
  else if (mode == SHOW_PHOTO)
      inType = L_DISPLAY_PHOTO;
  else
      inType = L_COLOR_REGISTER_CUSTOM_PREVIEW;

  m_type = inType;
  m_length = 2;
  sendPacket(true);
  if (recvPacket()==0 && m_type==inType)
  {
      //if (m_buf[0] == 1)
          return LOKI_REPLY_OK;	
      //else // 0xFF
      //    return LOKI_RESULT_RETURN_ERROR;
  }
  else
  {
      //return LOKI_REPLY_FAIL;  // some kind of bitstream error
      delay(50);
  }

  if (isBlocking != true)
      repeat = 0;
}

return LOKI_REPLY_FAIL;

}

template <class LinkType> void LokiMain<LinkType>::setCameraMode(int cameraState, bool isBlocking)
{
    if (cameraState == L_CAM_RECOGNIZE_RGB)
        setCameraRecognitionMode(RGB_COLOR_RECOGNIZE_MODE, isBlocking);
    else if (cameraState == L_CAM_RECOGNIZE_CUSTOM)
        setCameraRecognitionMode(CUSTOM_OBJECT_RECOGNIZE_MODE_AND_REGISTER_CENTER, isBlocking);
    else if (cameraState == L_CAM_FACE_DETECT)
        setCameraRecognitionMode(FACE_RECOGNIZE_MODE, isBlocking);
    else
        setCameraRecognitionMode(PREVIEW_MODE, isBlocking);
}

template <class LinkType> void LokiMain<LinkType>::registerColor()
{
    setCameraRecognitionMode(CUSTOM_OBJECT_RECOGNIZE_MODE_AND_REGISTER_CENTER);
}

template <class LinkType> int8_t LokiMain<LinkType>::getResult(void)
{
  uint8_t readLength;
  uint8_t *indexBufPtr;
  int result;
  uint8_t  repeatLast;


  numObjects = 0;
  vrGroup = 0;

  repeatLast = cmd8bit; 

  m_type = L_REQUEST_RECOGNITION_RESULT;
  m_length = 2;
  sendPacket(true);
  result = recvPacket();
  if (result ==0 && m_type==L_REQUEST_RECOGNITION_RESULT)
  {
      readLength = 2; // ignore two byte checksum
      indexBufPtr = m_buf;
      while (readLength < m_length)
      {
          if (indexBufPtr[0] == RESULT_TYPE_OBJECT_DETECTION)
          {
              objects[numObjects].m_type = indexBufPtr[1];
              objects[numObjects].m_x = indexBufPtr[2] + indexBufPtr[3] * 256;
              objects[numObjects].m_y = indexBufPtr[4] + indexBufPtr[5] * 256;
              objects[numObjects].m_width = indexBufPtr[6 ] + indexBufPtr[7] * 256;
              objects[numObjects].m_width = objects[numObjects].m_width - objects[numObjects].m_x;
              objects[numObjects].m_height = indexBufPtr[8] + indexBufPtr[9] * 256;
              objects[numObjects].m_height = objects[numObjects].m_height - objects[numObjects].m_y;

              numObjects++;
             
              indexBufPtr += 10;
              readLength += 10;               
          }
          else if (indexBufPtr[0] == RESULT_TYPE_VOICE_RECOGNITION)
          {
              vrGroup = indexBufPtr[1];
              vrResult = indexBufPtr[2];

              indexBufPtr += 3;
              readLength += 3;   
          }
      }
      return LOKI_REPLY_OK;	
  }
  else
  {
      cmd8bit = repeatLast;
      return result;
      //return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  }
}

//nonblocking
template <class LinkType> int LokiMain<LinkType>::getSpeechResult(void)
{
    int result;
    //int waitTimes;

    //waitTimes = 0;
    vrGroup = 0 ;
    //while (waitTimes < 400)
    //while (1)//vrGroup == 0)
    {
        result = getResult();
        //Serial.print(String(" result : ") + result + " \n");
                    
        if (result >= 0)
        {
            if (vrGroup > 0)
            {
#ifdef PRINT_VR_RESULT
                Serial.print("  VR Group : ");
                Serial.print(vrGroup);
                Serial.print(" Result ");
                Serial.println(vrResult);
#endif
                return vrResult;            
            }
            //waitTimes += 10;
        }
        delay(1);
    }

    return LOKI_REPLY_FAIL;
}

//blocking
template <class LinkType> int LokiMain<LinkType>::waitForSpeechResult(void)
{
    int result;
   // int waitTimes;

   // waitTimes = 0;
    vrGroup = 0 ;
    //while (waitTimes < 100)
    while (1)//vrGroup == 0)
    {
        result = getResult();
        //Serial.print(String(" result : ") + result + " \n");
                    
        if (result >= 0)
        {
            if (vrGroup > 0)
            {
#ifdef PRINT_VR_RESULT
                Serial.print("  VR Group : ");
                Serial.print(vrGroup);
                Serial.print(" Result ");
                Serial.println(vrResult);
#endif
                return vrResult;            
            }
    //        waitTimes = 0; 
        }
        else
        {
            // if loki no response for 5 second, assume it's system error then quit
            //waitTimes += 1;
        }
        delay(50);
    }

    return -1;
}


template <class LinkType> int LokiMain<LinkType>::getFaceResult(int attributeType )
{
    int result;
       
    if (attributeType == L_XPOS)
    {   
        if (needReadAgain == 1) // read again until user get the result from L_YPOS or L_WIDTH or L_HEIGHT
        { 
            result = getResult();
            delay(20);
        }
        else
        {
            result = 0;//
        }
        if (result < 0 || numObjects == 0 || objects[0].m_type != OBJECT_FACE)
        {
            objects[0].m_x = 0;
            objects[0].m_y = 0;
            objects[0].m_width = 0;
            objects[0].m_height = 0;
        }
        if (numObjects > 0)
        {
            //if (needReadAgain == 1)
            //    objects[0].print();
            needReadAgain = 0;
        }
        return objects[0].m_x;
    }
    else if (attributeType == L_YPOS)
    {   
        needReadAgain = 1;
        return objects[0].m_y;
    }
    else if (attributeType == L_WIDTH)
    {   
        needReadAgain = 1;
        return objects[0].m_width;
    }
    else if (attributeType == L_HEIGHT)
    {   
        needReadAgain = 1;
        return objects[0].m_height;
    }

}

template <class LinkType> int LokiMain<LinkType>::waitForFaceResult(int faceState)
{
    int result;
    int waitTimes;

    waitTimes = 0;
    //while (waitTimes < 100)
    while (1)
    {
        result = getResult();
        //Serial.print(String(" result : ") + result + " \n");
                    
        if (result >= 0)
        {
            //if (faceState == L_ON)
            //{
                if (numObjects > 0 && objects[0].m_type == OBJECT_FACE)
                {
                    return objects[0].m_width * objects[0].m_height/ 32 /24;
                }
            //}
            //else
            //{
            //    if (numObjects == 0)
            //    {
            //        return 0;
            //    }
            //}

      //      waitTimes = 0; 
        }
        else
        {
            // if loki no response for 5 second, assume it's system error then quit
            //waitTimes += 1;
        }
        //delay(50);
	if (faceState == 0)
	    break;
    }

    return 0;//-1;

}



template <class LinkType> int LokiMain<LinkType>::getBlobCount( )
{
   int result, i;

        result = getResult();      
        if (result < 0 || numObjects == 0 || objects[0].m_type == OBJECT_FACE)
        {
            numObjects = 0;
            delay(20);
        }
        else
        {
            // print the result
            //for (i = 0; i < numObjects; i++)
            //    objects[i].print();
            delay(20);
        }
        return numObjects;
}

template <class LinkType> int LokiMain<LinkType>::waitForBlobResult(bool isBlocking)
{
    int result;
    //int waitTimes;

    //waitTimes = 0;
    //while (waitTimes < 100)
    while (1)// || waitTimes < 2)//vrGroup == 0)
    {
        result = getResult();
        //Serial.print(String(" result : ") + result + " \n");

        if (result >= 0)
        {
            if (numObjects > 0 && objects[0].m_type != OBJECT_FACE)
            {
                return numObjects;
            }
           // waitTimes = 0;
        }
        else
        {
            // if loki no response for 5 second, assume it's system error then quit
           // waitTimes += 1;
        }

        if (isBlocking == true)
           delay(50);
        else
           break;
    }

    return -1;

}

template <class LinkType> int LokiMain<LinkType>::getBlobResult( int blobIndex, int attributeType )
{
    if (numObjects <= blobIndex)
        return 0;

    if (attributeType == L_XPOS)
    {   
        return objects[blobIndex].m_x;
    }
    else if (attributeType == L_YPOS)
    {   
        return objects[blobIndex].m_y;
    }
    else if (attributeType == L_WIDTH)
    {   
        return objects[blobIndex].m_width;
    }
    else if (attributeType == L_HEIGHT)
    {   
        return objects[blobIndex].m_height;
    }
    else if (attributeType == L_COLOR)
        return objects[blobIndex].m_type;
    return 0;
}

template <class LinkType> void LokiMain<LinkType>::moveMotor( int motorid, int speed, int  position , int direction)
{
  int localMotorId, localSpeed, localPosition;

while (1)
{
  m_type = L_MOVE_MOTOR;
  m_length = 5 + 2;

  localMotorId = motorid;

  localSpeed = speed;
  if (localSpeed < 100)
      localSpeed = 100;
  else if (localSpeed > 2000)
      localSpeed = 2000;

  localPosition = position; // 0 = release motor
  if (localPosition > 100)
      localPosition = 100;
  if (localPosition == 0 )
      localPosition = 1;


  m_bufPayload[0] = localMotorId;
  m_bufPayload[1] = ((localSpeed/10) &0xFF00)>>8; //GP side : 100 = 1 second
  m_bufPayload[2] = ((localSpeed/10) &0xFF); //GP side : 100 = 1 second
  m_bufPayload[3] = localPosition; // GP side : 1-100
  m_bufPayload[4] = 0;//3 = release,4 = move to current position
  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_MOTOR)
  {
    delay(1); // avoid sending command too fast
    //if (m_buf[0] == 1)
    //    return LOKI_REPLY_OK;	
    //else // 0xFF
    //    return LOKI_RESULT_RETURN_ERROR;
    return;
  }
  else
  {
     //Serial.println("FFF");
  //    return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  }

   delay(50);
}

}

template <class LinkType> void LokiMain<LinkType>::moveMultiMotor( int motorid, int speed, int  position , int direction)
{
  int localMotorId, localSpeed, localPosition;

  localMotorId = motorid;

  localSpeed = speed;
  if (localSpeed < 100)
      localSpeed = 100;
  else if (localSpeed > 2000)
      localSpeed = 2000;

  localPosition = position; // 0 = release motor
  if (localPosition > 100)
      localPosition = 100;

  motorCmdNum++;
  motorCmdBuf[L_BUFFERSIZE - 5*motorCmdNum + 0] = localMotorId;
  motorCmdBuf[L_BUFFERSIZE - 5*motorCmdNum + 1] = ((localSpeed/10) &0xFF00)>>8; //GP side : 100 = 1 second
  motorCmdBuf[L_BUFFERSIZE - 5*motorCmdNum + 2] = ((localSpeed/10) &0xFF); //GP side : 100 = 1 second
  motorCmdBuf[L_BUFFERSIZE - 5*motorCmdNum + 3] = localPosition; // GP side : 1-100
  motorCmdBuf[L_BUFFERSIZE - 5*motorCmdNum + 4] = 0; //3 = release,4 = move to current position

}

template <class LinkType> void LokiMain<LinkType>::moveMultiMotorStart(void)
{
    int i,j;

while (1)
{
  m_type = L_MOVE_MULTI_MOTOR;
  m_length = 5*motorCmdNum + 2;

  for (j = 0; j < motorCmdNum*5; j++)
  {
      m_bufPayload[j] = motorCmdBuf[L_BUFFERSIZE - 5*motorCmdNum + j];
  }

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_MULTI_MOTOR)
  {
    delay(1); // avoid sending command too fast
    //if (m_buf[0] == 1)
    //    return LOKI_REPLY_OK;	
    //else // 0xFF
    //    return LOKI_RESULT_RETURN_ERROR;
    motorCmdNum = 0;
    return;
  }
  else
  {
     //Serial.println("FFF");
  //    return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  }

   delay(50);
}

}



/*
template <class LinkType> void LokiMain<LinkType>::moveMotorAction( int motorid, int speed, int  position , int direction)
{
  int localMotorId, localSpeed, localPosition;

  localMotorId = motorid;

  localSpeed = speed;
  if (localSpeed < 100)
      localSpeed = 100;
  else if (localSpeed > 2000)
      localSpeed = 2000;

  localPosition = position; // 0 = release motor
  if (localPosition > 100)
      localPosition = 100;

  actionsCmdLength += 7;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 6] = L_MOVE_MOTOR;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 5] = 5;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 4] = localMotorId;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 3] = ((localSpeed/10) &0xFF00)>>8; //GP side : 100 = 1 second
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 2] = ((localSpeed/10) &0xFF); //GP side : 100 = 1 second
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 1] = localPosition; // GP side : 1-100
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 0] = 0; //3 = release,4 = move to current position

}
*/
template <class LinkType> void LokiMain<LinkType>::moveMotorAction( int motorid, int speed, int  position , int direction)
{
  int localMotorId, localSpeed, localPosition;

  localMotorId = motorid;

  localSpeed = speed;
  if (localSpeed < 100)
      localSpeed = 100;
  else if (localSpeed > 2000)
      localSpeed = 2000;

  localPosition = position; // 0 = release motor
  if (localPosition > 100)
      localPosition = 100;

  actionsCmdLength += 7;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 6] = L_MOVE_MOTOR;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 5] = 5;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 4] = localMotorId;
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 3] = ((localSpeed/10) &0xFF00)>>8; //GP side : 100 = 1 second
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 2] = ((localSpeed/10) &0xFF); //GP side : 100 = 1 second
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 1] = localPosition; // GP side : 1-100
  actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + 0] = 0; //3 = release,4 = move to current position

}

template <class LinkType> void LokiMain<LinkType>::startMultiAction(bool isBlocking)
{
    //int i;
    int j;

//  uint8_t *actionsCmdBuf;
//  uint8_t actionsCmdLength;

  uint8_t mType;
  uint8_t mLen;

  mType = L_MULTI_ACTION;
  mLen = actionsCmdLength + 2;

do
{
  m_type = mType;
  m_length = mLen;

  for (j = 0; j < actionsCmdLength; j++)
  {
      m_bufPayload[j] = actionsCmdBuf[L_BUFFERSIZE -1 - j];
  }

  actionsCmdLength = 3;;// 3 byte payload return, so need to recover 3 byte in next retrys

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MULTI_ACTION)
  {
    delay(1); // avoid sending command too fast
    //if (m_buf[0] == 1)
    //    return LOKI_REPLY_OK;	
    //else // 0xFF
    //    return LOKI_RESULT_RETURN_ERROR;
    actionsCmdLength = 0;
    return;
  }
  else
  {
     //Serial.println("FFF");
  //    return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  }

   delay(50);
} while (isBlocking == true);

  actionsCmdLength = 0;
}





template <class LinkType> void LokiMain<LinkType>::setMotorPower(int motorid, int state)
{
    if (state == 0)//release
        moveMotor(motorid, 0, 0, 3);
    else// set to current position
        moveMotor(motorid, 0, 0, 4);
}

template <class LinkType> int LokiMain<LinkType>::readMotorPosition( int motorid)
{
  int localMotorId;


while (1)
{
  m_type = L_READ_MOTOR;
  m_length = 1 + 2;

  localMotorId = motorid;

  m_bufPayload[0] = localMotorId;
  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_READ_MOTOR)
      return m_buf[0];	
  //else
  //    return LOKI_REPLY_FAIL;  // some kind of bitstream error

  delay(50);

}

}

template <class LinkType> void LokiMain<LinkType>::playbackMotor(void)
{
while (1)
{

  m_type = L_PLAYBACK_MOTOR_SEQUENCE;
  m_length = 2;

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_PLAYBACK_MOTOR_SEQUENCE)
  {
      //return m_buf[0];
      return;
  }
  //else
  //    return LOKI_REPLY_FAIL;  // some kind of bitstream error
  delay(50);

}

}

template <class LinkType> int LokiMain<LinkType>::stopRecordMotor(void)
{
while (1)
{

  m_type = L_RECORD_MOTOR_END;
  m_length = 2;

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_RECORD_MOTOR_END)
  {
      return LOKI_REPLY_OK;	
  }
  //else
  //    return LOKI_REPLY_FAIL;  // some kind of bitstream error	
  delay(50);

}

}

template <class LinkType> void LokiMain<LinkType>::recordMotor(int numSeconds)
{
  int localSeconds;
  int retry;

while (1)
{

  m_type = L_RECORD_MOTOR_SEQUENCE;
  m_length = 1 + 2;

  localSeconds = numSeconds;
  if (localSeconds > 10)
    localSeconds = 10;

  m_bufPayload[0] = localSeconds;
  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_RECORD_MOTOR_SEQUENCE)
  {

      delay(localSeconds*1000);
      localSeconds = LOKI_REPLY_FAIL;
      while (localSeconds != LOKI_REPLY_OK)
      {
          delay(50);
          localSeconds = stopRecordMotor();
          if (localSeconds == LOKI_REPLY_FAIL)
              retry += 1;
          else 
              retry = 0;
      //    ///if (retry > 10)
      //    //    return LOKI_RESULT_RETURN_ERROR;
      }
      return;
  }
  //else
   //   return LOKI_REPLY_FAIL;  // some kind of bitstream error
  delay(50);

}

}


template <class LinkType> void LokiMain<LinkType>::toActionBuffer(void)
{
    int i;
      
    actionsCmdLength += (m_length);
    
    actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + (m_length-1)] = m_type;
    actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + (m_length-2)] = (m_length-2);
  
    for (i = 0; i < (m_length-2); i++)
    {
      actionsCmdBuf[L_BUFFERSIZE - actionsCmdLength + (m_length-3-i)] = m_bufPayload[i];
    }
}



template <class LinkType> void LokiMain<LinkType>::prepareSetRCServoBuffer(int motorid, int speed, int  position, int type)
{
  int localMotorId, localSpeed, localPosition;

  m_type = L_MOVE_RC_SERVO;
  m_length = 5 + 2;

  localMotorId = motorid;

  localSpeed = speed; //0-20 (0-immediately, 1 slowest, 20 fastest)
  if (localSpeed > 20)
      localSpeed = 20;

  localPosition = position; // 0 = release motor , pos = 1-200
  if (localPosition > 200)
      localPosition = 200;

  m_bufPayload[0] = localMotorId;
  m_bufPayload[1] = ((localSpeed) &0xFF00)>>8; //GP side : 1000 = 1 second
  m_bufPayload[2] = ((localSpeed) &0xFF); //GP side : 1000 = 1 second
  m_bufPayload[3] = localPosition; // GP side : 1-200
  m_bufPayload[4] = type; // 0 = absolution position, 1 = stop, 2=read

}


template <class LinkType> int LokiMain<LinkType>::readRCServoPosition( int motorid)
{

while (1)
{

  prepareSetRCServoBuffer(motorid, 0, 0, 2);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_RC_SERVO)
      return m_buf[0];	
  
    delay(50);

}

}

template <class LinkType> int8_t LokiMain<LinkType>::setRCServo(int motorid, int speed, int  position)
{

  prepareSetRCServoBuffer(motorid, speed, position,0);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_RC_SERVO)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL;

}

template <class LinkType> int8_t LokiMain<LinkType>::setRCServoUp(int motorid)
{

  prepareSetRCServoBuffer(motorid, 3, 200, 0);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_RC_SERVO)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL;

}

template <class LinkType> int8_t LokiMain<LinkType>::setRCServoDown(int motorid)
{

  prepareSetRCServoBuffer(motorid, 3, 1, 0);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_RC_SERVO)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL;
}

template <class LinkType> int8_t LokiMain<LinkType>::setRCServoStop(int motorid)
{

  prepareSetRCServoBuffer(motorid, 0, 0, 1);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_RC_SERVO)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL;
}

template <class LinkType> void LokiMain<LinkType>::setRCServoAction(int motorid, int speed, int  position)
{

  prepareSetRCServoBuffer(motorid, speed, position,0);

  toActionBuffer();

}

template <class LinkType> void LokiMain<LinkType>::setRCServoActionUp(int motorid)
{

  prepareSetRCServoBuffer(motorid, 3, 200, 0);

  toActionBuffer();

}

template <class LinkType> void LokiMain<LinkType>::setRCServoActionDown(int motorid)
{

  prepareSetRCServoBuffer(motorid, 3, 1, 0);

  toActionBuffer();

}

template <class LinkType> void LokiMain<LinkType>::setRCServoActionStop(int motorid)
{

  prepareSetRCServoBuffer(motorid, 0, 0, 1);

  toActionBuffer();

}


template <class LinkType> void LokiMain<LinkType>::prepareSetSmartLEDBuffer(int motorid,  int r, int g, int b)
{
  // prepare m_type/m_length/m_bufPayload

  int localMotorId, localR,localG,localB;


  m_type = L_SET_RGB_LED;
  m_length = 5 + 2;

  localMotorId = motorid;
  localR = r;
  if (localR < 0)
      localR = 0;
  else if (localR > 255)
      localR = 255;

  localG = g;
  if (localG < 0)
      localG = 0;
  else if (localG > 255)
      localG = 255;

  localB = b;
  if (localB < 0)
      localB = 0;
  else if (localB > 255)
      localB = 255;

  localR = localR*0x1F/255;
  localG = localG*0x1F/255;
  localB = localB*0x1F/255;

  m_bufPayload[0] = localMotorId;
  m_bufPayload[1] = localR;
  m_bufPayload[2] = localG;
  m_bufPayload[3] = localB;
  m_bufPayload[4] = 0;

}

template <class LinkType> int8_t LokiMain<LinkType>::setSmartLED(int motorid,  int r, int g, int b)
{

  prepareSetSmartLEDBuffer(motorid, r, g, b);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_SET_RGB_LED)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL;

}

template <class LinkType> void LokiMain<LinkType>::setRGBAction(int motorid,  int r, int g, int b)
{
    int i;

    prepareSetSmartLEDBuffer(motorid, r, g, b);

    toActionBuffer();

}

template <class LinkType> void LokiMain<LinkType>::setRGB(int motorid,  int r, int g, int b)
{
    while (setSmartLED(motorid, r, g, b) == LOKI_REPLY_FAIL)
    {
        delay(50);
    }
}

template <class LinkType> int8_t LokiMain<LinkType>::setSmartID(int id)
{
  m_type = L_SET_SMART_ID;
  m_length = 1 + 2;

  m_bufPayload[0] = id;
  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_SET_SMART_ID)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL; 
}
template <class LinkType> void LokiMain<LinkType>::setSmartDeviceAdress(int id)
{
    while (setSmartID(id) == LOKI_REPLY_FAIL)
    {
        delay(50);
    }
}


template <class LinkType> int8_t LokiMain<LinkType>::getSmartCount(void)
{

  scanSmartBus();

  m_type = L_GET_SMART_COUNT;
  m_length = 2;

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_GET_SMART_COUNT)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL; 
}

template <class LinkType> int LokiMain<LinkType>::getSmartDeviceCount(void)
{
    int i;

    while (getSmartCount() == LOKI_REPLY_FAIL)
    {
        delay(50);
    }

    smartCount = m_length/2 - 1;
    motorCount = 0;
    ledCount = 0;
    rcServoCount = 0;
    dcMotorCount = 0;
    unknownCount = 0;

    //Serial.print("Smart Count: ");
    //Serial.println(smartCount);

    for (i = 0; i < m_length-2; i += 2)
    {
        if (m_buf[i] == mod_servo)
            motorCount++;
        else if (m_buf[i] == mod_led_rgb)
            ledCount++;
        else if (m_buf[i] == mod_rc_servo)
            rcServoCount++;
        else if (m_buf[i] == mod_dc_mot)
            dcMotorCount++;
        else
            unknownCount++;

      //Serial.print(m_buf[i]);
      //Serial.print(' ');
      //Serial.println(m_buf[i+1]);

    }

    return motorCount;
}

template <class LinkType> int LokiMain<LinkType>::getSmartMotorCount(void)
{
    return motorCount;
}

template <class LinkType> int LokiMain<LinkType>::getSmartLEDCount(void)
{
    return ledCount;
}


template <class LinkType> int8_t LokiMain<LinkType>::scanSmartBus(void)
{
  //while (1) 
  //{
      m_type = L_SCAN_SMART_BUS;
      m_length = 2;
      
      cmd8bit = 0; // special case // avoid twice scan smart bus
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_SCAN_SMART_BUS && m_buf[0] == 1)
          return LOKI_REPLY_OK;	
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  //}
  return LOKI_REPLY_FAIL; 
}





template <class LinkType> void LokiMain<LinkType>::playSoundFile( String filename, bool isBlocking)
{
  String localString;
  int textLength;

  localString = filename + ' ';

  while (1) 
  {
      m_type = L_PLAYFILE;
      m_length = 0 + localString.length() + 2;

      textLength = localString.length();

      //Serial.println(localString);
      //Serial.println(textLength);

      localString.toCharArray((char*)(m_bufPayload + 0), textLength );

      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_PLAYFILE)
      {
          if (isBlocking == NON_BLOCKING)
          {
              return ;//LOKI_REPLY_OK;
          }
          else
          {
              // wait until the audio status is silence
              while (textLength != 0)
              {
                  delay(50);
                  textLength = checkAudioStatus(); // 1 = playing , 0 = idle, -1 = no reply
              }
              return;
          }
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }
}

template <class LinkType> void LokiMain<LinkType>::stopSound(void)
{

  while (1) 
  {
      m_type = L_STOPFILE;
      m_length = 0 + 2;


      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_STOPFILE)
      {
          return ;//LOKI_REPLY_OK;
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }


}

template <class LinkType> int LokiMain<LinkType>::checkAudioStatus(void) // 1 = playing , 0 = idle
{

  m_type = L_CHECK_AUDIO_STATUS;
  m_length = 0 + 2;

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_CHECK_AUDIO_STATUS)
  {
      return m_buf[0];
  }

  return LOKI_REPLY_FAIL;
}



#define NOTE_C1		  0
#define NOTE_C1S      1
#define NOTE_D1       2
#define NOTE_E1b      3
#define NOTE_E1       4
#define NOTE_F1       5
#define NOTE_F1S      6
#define NOTE_G1       7
#define NOTE_G1S      8
#define NOTE_A2		  9
#define NOTE_B2b     10
#define NOTE_B2      11

#define NOTE_C2      12
#define NOTE_C2S     13
#define NOTE_D2      14
#define NOTE_E2b     15
#define NOTE_E2      16
#define NOTE_F2      17
#define NOTE_F2S     18
#define NOTE_G2      19
#define NOTE_G2S     20
#define NOTE_A3		 21
#define NOTE_B3b     22
#define NOTE_B3      23

#define NOTE_C3      24
#define NOTE_C3S     25
#define NOTE_D3      26
#define NOTE_E3b     27
#define NOTE_E3      28
#define NOTE_F3      29
#define NOTE_F3S     30
#define NOTE_G3      31
#define NOTE_G3S     32
#define NOTE_A4		 33
#define NOTE_B4b     34
#define NOTE_B4      35

#define NOTE_C4      36
#define NOTE_C4S     37
#define NOTE_D4      38
#define NOTE_E4b     39
#define NOTE_E4      40
#define NOTE_F4      41
#define NOTE_F4S     42
#define NOTE_G4      43
#define NOTE_G4S     44
#define NOTE_A5		 45
#define NOTE_B5b     46
#define NOTE_B5      47

#define NOTE_C5      48
#define NOTE_C5S     49
#define NOTE_D5      50
#define NOTE_E5b     51
#define NOTE_E5      52
#define NOTE_F5      53
#define NOTE_F5S     54
#define NOTE_G5      55
#define NOTE_G5S     56
#define NOTE_A6		 57
#define NOTE_B6b     58
#define NOTE_B6      59



// Major Note
#define NOTE_1L   NOTE_C3
#define NOTE_2L   NOTE_D3
#define NOTE_3L   NOTE_E3
#define NOTE_4L   NOTE_F3
#define NOTE_5L   NOTE_G3
#define NOTE_6L   NOTE_A4
#define NOTE_7L   NOTE_B4

#define NOTE_1   NOTE_C4
#define NOTE_2   NOTE_D4
#define NOTE_3   NOTE_E4
#define NOTE_4   NOTE_F4
#define NOTE_5   NOTE_G4
#define NOTE_6   NOTE_A5
#define NOTE_7   NOTE_B5

#define NOTE_1H   NOTE_C5
#define NOTE_2H   NOTE_D5
#define NOTE_3H   NOTE_E5
#define NOTE_4H   NOTE_F5
#define NOTE_5H   NOTE_G5
#define NOTE_6H   NOTE_A6
#define NOTE_7H   NOTE_B6

#define NOTE_CL NOTE_1L
#define NOTE_DL NOTE_2L
#define NOTE_EL NOTE_3L
#define NOTE_FL NOTE_4L
#define NOTE_GL NOTE_5L
#define NOTE_AL NOTE_6L
#define NOTE_BL NOTE_7L

#define NOTE_C NOTE_1
#define NOTE_D NOTE_2
#define NOTE_E NOTE_3
#define NOTE_F NOTE_4
#define NOTE_G NOTE_5
#define NOTE_A NOTE_6
#define NOTE_B NOTE_7

#define NOTE_CH NOTE_1H
#define NOTE_DH NOTE_2H
#define NOTE_EH NOTE_3H
#define NOTE_FH NOTE_4H
#define NOTE_GH NOTE_5H
#define NOTE_AH NOTE_6H
#define NOTE_BH NOTE_7H


// note pause , less than 127
#define NOTE_P   100

#define BEAT_0_125 (1+NOTE_P)
#define BEAT_0_25  (2+NOTE_P)
#define BEAT_0_5   (3+NOTE_P)
#define BEAT_1     (4+NOTE_P)
#define BEAT_2     (5+NOTE_P)
#define BEAT_3     (6+NOTE_P)
#define BEAT_4     (7+NOTE_P)

// 1 = C // Do // C4
// 2 = D // Re
// 3 = E // Mi
// 4 = F
// 5 = G
// 6 = A
// 7 = B

// 1 with under point = Low C = C3
// 1 with upper point = High C = C5

const int NoteMajor[] = {
NOTE_C1, NOTE_D1, NOTE_E1, NOTE_F1, NOTE_G1, NOTE_A2, NOTE_B2,
NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A3, NOTE_B3,
NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A4, NOTE_B4,
NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A5, NOTE_B5,
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A6, NOTE_B6,
};

const int NoteLowMajor[] = {NOTE_P, NOTE_CL, NOTE_DL, NOTE_EL, NOTE_FL, NOTE_GL, NOTE_AL, NOTE_BL};
const int NoteMiddleMajor[] = {NOTE_P, NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G, NOTE_A, NOTE_B};
const int NoteHighMajor[] = {NOTE_P, NOTE_CH, NOTE_DH, NOTE_EH, NOTE_FH, NOTE_GH, NOTE_AH, NOTE_BH};






const int beatTimeTable[] = {7,15,30, 60, 120, 180, 240};

template <class LinkType> void LokiMain<LinkType>::setMIDIBPM(int bpmIn) 
{
    bpm = bpmIn;
    //if (bpm < 30)
    //    bpm = 30;
    //if (bpm > 120)
    //    bpm = 120;
}

template <class LinkType> int LokiMain<LinkType>::playMIDI(int note)
{
  int timeCountHost;

  //if (note == -1)
  //{
  //    delay(1000); 
  //    return;
  //}
  

  //0=whole note, -1= half note, -2= quarter note, fixed bpm=60???
  if (note > 0 && note > NOTE_P)
  {
      // assume fixed  ?/4 , means QUARTER_NOTE = 1 beat
      duration = 1000 /bpm * beatTimeTable[(note-NOTE_P-1)];
      return LOKI_REPLY_OK;
  }

  if (NOTE_B6 < note || note < NOTE_C1)
      return LOKI_REPLY_FAIL;

  // 1=need wait finish and time delay count in MCU
  // 0=no need wait finish and time delay count in ARDUINO
  timeCountHost = 0;

  while (1) 
  {
      m_type = L_PLAYNOTE;
      m_length = 5 +  2;
      
      m_bufPayload[0] = note;
      //m_bufPayload[1] = 1; // 1=need wait finish and delay count in MCU
      m_bufPayload[1] = timeCountHost; // 0=no need wait finish and delay(duration) count in ARDUINO
      m_bufPayload[2] = (duration&0xFF00)>>8;
      m_bufPayload[3] = (duration&0xFF);
      m_bufPayload[4] = cmdCount;
      cmd8bit = 0; // special case // avoid twice action
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_PLAYNOTE && m_buf[0] == 1)
      {
          cmdCount++;// make change to the command , so even the same note can run
          if (timeCountHost == 0)
            delay(duration); 

          return LOKI_REPLY_OK;
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(10);   
  }

}


    // ---------------------------------------------------------
    // Create Speaker Dependent  keyword group
    // groupIndex = 11 -20 inclusively
    // numKeyworkds = 1 -5 inclusively
    // return 1 success
    //        0 fail  
    // ---------------------------------------------------------
template <class LinkType> int LokiMain<LinkType>::createSDGroup(int groupIndex, int numKeywords)
{
  while (1) 
  {
      m_type = L_CREATE_SD;
      m_length = 2 +  2;
      
      m_bufPayload[0] = groupIndex;
      m_bufPayload[1] = numKeywords;
      cmd8bit = 0; // special case // avoid twice action
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_CREATE_SD)
      {
          //delay(100);
          if (m_buf[0] != 2) // 2= cmd sent and still running
              return m_buf[0];
      }
      //else
      //   return 0; 
      delay(50);   
  }

  return 0;
}


    // ---------------------------------------------------------
    // Train Speaker Dependent  keyword group
    // groupIndex = 11 -20 inclusively
    // numKeyworkds = 1 -5 inclusively
    // return 1 success
    //        0 fail  
    // ---------------------------------------------------------
template <class LinkType> int LokiMain<LinkType>::trainSDkeyword(int groupIndex, int keywordsIndex)
{
  while (1) 
  {
      m_type = L_TRAIN_KEYWORD;
      m_length = 1 +  2;
      
      m_bufPayload[0] = keywordsIndex;
      cmd8bit = 0; // special case // avoid twice action
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_TRAIN_KEYWORD)
      {
          //delay(100);
          if (m_buf[0] != 2) // 2= cmd sent and still running
              return m_buf[0];
      }
      //else
      //   return 0; 
      delay(50);   
  }
}



  // ---------------------------------------------------------
    // Check Speaker Dependent  keyword group completeness
    // groupIndex = 11 -20 inclusively
    // return 1 success  (If all keywords are trained )
    //        0 fail     
    // ---------------------------------------------------------    
    
template <class LinkType> int LokiMain<LinkType>::checkSDComplete(int groupIndex)
{
  while (1) 
  {
      m_type = L_SAVE_SD;
      m_length = 0 +  2;
      
      cmd8bit = 0; // special case // avoid twice action
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_SAVE_SD)
      {
          //delay(100);
          if (m_buf[0] != 2) // 2= cmd sent and still running
              return m_buf[0];
      }
      //else
      //   return 0; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::setgetMicrophone(int micSource)
{
  while (1) 
  {
      m_type = L_SET_GET_MIC;
      m_length = 1 +  2;
      
      m_bufPayload[0] = micSource; // 1 = bulite in 2 = i2s , other = not set read only
   
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_SET_GET_MIC)
      {
          return m_buf[0];
      }
      //else
      //   return 0; 
      delay(50);   
  }
}

template <class LinkType> void LokiMain<LinkType>::setMicrophone(int micSource)
{
    setgetMicrophone(micSource);
}

template <class LinkType> int LokiMain<LinkType>::getMicrophone(void)
{
    return setgetMicrophone(0);
}


template <class LinkType> int LokiMain<LinkType>::recAudio(String filename)
{
  String localString;
  int textLength;

  localString = filename + ' ';

  while (1) 
  {
      m_type = L_REC_AUDIO_FILE;
      m_length = 0 + localString.length() + 2;

      textLength = localString.length();

      localString.toCharArray((char*)(m_bufPayload + 0), textLength );

      cmd8bit = 0; // special case // avoid twice scan smart bus
      sendPacket(true);
      // two byte = still starting, three byte = started(fail or success)
      if (recvPacket() == 0 && m_type == L_REC_AUDIO_FILE && m_length == 3)
      {
          return m_buf[0];
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::stopRecAudio(void)
{
  while (1) 
  {
      m_type = L_STOP_REC_AUDIO_FILE;
      m_length = 0 +  2;
   
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_STOP_REC_AUDIO_FILE)
      {
          return LOKI_REPLY_OK;
      }
      //else
      //   return 0; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::takePhoto(String filename)
{
  String localString;
  int textLength;

  localString = filename + ' ';

  while (1) 
  {
      m_type = L_TAKEPHOTO;
      m_length = 0 + localString.length() + 2;

      textLength = localString.length();

      localString.toCharArray((char*)(m_bufPayload + 0), textLength );

      cmd8bit = 0; // special case // avoid twice scan smart bus
      sendPacket(true);
      // two byte = still starting, three byte = started(fail or success)
      if (recvPacket() == 0 && m_type == L_TAKEPHOTO && m_length == 3)
      {
          return m_buf[0];
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::displayPhoto(String filename)
{
  String localString;
  int textLength;

  localString = filename + ' ';

  while (1) 
  {
      m_type = L_SHOWPHOTO;
      m_length = 0 + localString.length() + 2;

      textLength = localString.length();

      localString.toCharArray((char*)(m_bufPayload + 0), textLength );

      cmd8bit = 0; // special case // avoid twice scan smart bus
      sendPacket(true);
      if (recvPacket() == 0 && m_type == L_SHOWPHOTO && m_length == 3)
      {
          return m_buf[0];
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::processVideo(String filename, int para)
{
  String localString;
  int textLength;

  localString = filename + ' ';

  while (1) 
  {
      m_type = L_REC_PLAY_VIDEO;
      m_length = 1 + localString.length() + 2;

      textLength = localString.length();

      m_bufPayload[0] = para;
      localString.toCharArray((char*)(m_bufPayload + 1), textLength );

      cmd8bit = 0; // special case // avoid twice scan smart bus
      sendPacket(true);
      // two byte = still starting, three byte = started(fail or success)
      if (recvPacket() == 0 && m_type == L_REC_PLAY_VIDEO && m_length == 3)
      {
          return m_buf[0];
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::recordVideo(String filename)
{
    return processVideo(filename, 0);
}

template <class LinkType> int LokiMain<LinkType>::playVideo(String filename)
{
    return processVideo(filename, 1);
}


template <class LinkType> int LokiMain<LinkType>::stopProcessVideo(int para)
{

  while (1) 
  {
      m_type = L_STOP_REC_PLAY_VIDEO;
      m_length = 1 + 2;

      m_bufPayload[0] = para;

      cmd8bit = 0; // special case // avoid twice scan smart bus
      sendPacket(true);
      // two byte = still starting, three byte = started(fail or success)
      if (recvPacket() == 0 && m_type == L_STOP_REC_PLAY_VIDEO && m_length == 3)
      {
          return m_buf[0];
      }
      //else
      //   return LOKI_REPLY_FAIL; 
      delay(50);   
  }
}

template <class LinkType> int LokiMain<LinkType>::stopRecordVideo(String filename)
{
    return stopProcessVideo(0);
}

template <class LinkType> int LokiMain<LinkType>::stopPlayVideo(String filename)
{
    return stopProcessVideo(1);
}



template <class LinkType> void LokiMain<LinkType>::prepareSetDCMotor(int motorid, int speed, int  direction)
{
  int localMotorId, localSpeed, localDirection;

  m_type = L_MOVE_DC_MOTOR;
  m_length = 3 + 2;

  localMotorId = motorid;

  localSpeed = speed;     // 0 = release motor
  if (localSpeed > 0x1F)
      localSpeed = 0x1F;

  localDirection = direction&1; 

  m_bufPayload[0] = localMotorId;
  m_bufPayload[1] = localSpeed;
  m_bufPayload[2] = localDirection; 

}


template <class LinkType> int8_t LokiMain<LinkType>::setDCMotor(int motorid, int speed, int  direction)
{

  prepareSetDCMotor(motorid, speed, direction);

  sendPacket(true);
  if (recvPacket() == 0 && m_type == L_MOVE_DC_MOTOR)
      return LOKI_REPLY_OK;	
  else
      return LOKI_REPLY_FAIL;

}

template <class LinkType> void LokiMain<LinkType>::setDCMotorAction(int motorid, int speed, int  direction)
{

  prepareSetDCMotor(motorid, speed, direction);

  toActionBuffer();

}

#endif
