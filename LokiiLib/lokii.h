// Arduino  class 

#ifndef _LOKII_H
#define _LOKII_H

#include "Internal\LokiMain.h"
#include "pins_arduino.h"

#include "SPI.h"

// more than 200k , error rate higher in uno
#define SPI_CLOCKRATE      2000000
#define CLOCK_HOLD         (500000/SPI_CLOCKRATE)

//#define SPI_DEBUG_ON

class LokiSPI
{
private:


int clockPin;
int dataOutMOSIPin;
int dataInMISOPin;
int csPin;

int num_digitals;
int num_analogs;

int use_softSPI;
int board_type;
public:


  int8_t open(int spi_soft=0)
  {
     int clockDiv;

     clockDiv = 1;
     num_digitals = 0;
     num_analogs = 0;

#ifdef NUM_DIGITAL_PINS
     num_digitals = NUM_DIGITAL_PINS;
#endif

#ifdef NUM_ANALOG_INPUTS
     num_analogs = NUM_ANALOG_INPUTS;
#endif

    //spi_soft = 1; // 1 = force soft spi
    board_type = 0;

    if ((num_digitals == 20 && num_analogs == 6) //uno
        || (num_digitals == 31 && num_analogs == 12) // yun
        || (num_digitals == 19 && num_analogs == 5) // zero
       )// noraml size board
    {

        board_type = 1;

        csPin = 10;

        if (num_digitals == 31 && num_analogs == 12) // yun
            spi_soft = 1;



        if (spi_soft == 0)
        {
            use_softSPI = 0;
        }
        else
        {
            use_softSPI = 1;
        }
        dataInMISOPin = 12;
        dataOutMOSIPin = 11;
        clockPin = 13;
    }
    else if (// small board
             (num_digitals == 15 && num_analogs == 7)
             || (num_digitals == 22 && num_analogs == 7) // mkr 1000
             )
    {
        board_type = 2;
        csPin = 1;
        if (spi_soft == 0)          
        {
            use_softSPI = 0;
        }
        else
        {
            use_softSPI = 1;
        }

        dataInMISOPin = 10;
        dataOutMOSIPin = 8;
        clockPin = 9;
        
    }    
    else // all other boards use soft spi
    {
        board_type = 3;
        use_softSPI = 1;
        csPin = 10;
        dataInMISOPin = 12;
        dataOutMOSIPin = 11;
        clockPin = 13;
    }


#ifdef BOARD_NAME
    String name = BOARD_NAME;
    if ( name.equals("Nano 33 BLE") )
    {
        spi_soft = 1; 

        board_type = 4;
        if (spi_soft == 0)
        {
            use_softSPI = 0;
        }
        else
        {
            use_softSPI = 1;
        }

        csPin = 10; // D10
        dataInMISOPin = 12; // D12
        dataOutMOSIPin = 11; // D11
        clockPin = 13; // D13

        clockDiv = 1;

    }
#endif


#ifdef SPI_DEBUG_ON
Serial.print("Board Type : ");
Serial.println(board_type) ;
Serial.println(num_digitals) ;
Serial.println(num_analogs) ;

#endif

    // CLK PIN = LOKII TRAP PIN
    delay(500);


    if (use_softSPI == 0)
    {
        pinMode(csPin, OUTPUT);
        digitalWrite(csPin, HIGH);

        SPI.begin();
        SPI.beginTransaction(SPISettings(SPI_CLOCKRATE/clockDiv, MSBFIRST, SPI_MODE0));
    }
    else
    {

        pinMode(csPin, OUTPUT);
        digitalWrite(csPin, HIGH);
    
        pinMode(clockPin, OUTPUT);
        pinMode(dataOutMOSIPin, OUTPUT);

        //digitalWrite(clockPin, HIGH); // CPOL = 1
        digitalWrite(clockPin, LOW);  // CPOL = 0
        digitalWrite(dataOutMOSIPin, LOW);

        pinMode(dataInMISOPin, INPUT);

    }

    return 0;
  }

  void csEnable()
  {
        digitalWrite(csPin, LOW);
        delayMicroseconds(10);
  }

  void csDisable()
  {
        digitalWrite(csPin, HIGH);
        delayMicroseconds(10);
  }

  
  void close()
  {
    if (use_softSPI == 0)
        SPI.endTransaction();
    
    digitalWrite(csPin, HIGH);
  }
    
  int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs=NULL)
  {
    uint8_t i;
    if (cs)
      *cs = 0;

    if (use_softSPI == 0)
    {
      for (i=0; i<len; i++)
      {
        buf[i] = SPI.transfer(0x00);
        if (cs)
          *cs += buf[i];
        //delayMicroseconds(2000);
        delayMicroseconds(50);
      }
    }
    else
    {
      for (i=0; i<len; i++)
      {
        buf[i] = myShiftIn(dataInMISOPin, clockPin, MSBFIRST);
    
        if (cs)
          *cs += buf[i];
        //delayMicroseconds(2000);
        delayMicroseconds(50);
      }
    }

    return len;
  }
    
  int16_t send(uint8_t *buf, uint8_t len)
  {
    uint8_t i;
    if (use_softSPI == 0)
    {
      for (i=0; i<len; i++)
      {
        SPI.transfer(buf[i]);
        //delayMicroseconds(25);
        //delay(1);
        delayMicroseconds(1);
      }
    }
    else
    {
      for (i=0; i<len; i++)
      {
        //delayMicroseconds(25);
        myShiftOut(dataOutMOSIPin, clockPin, MSBFIRST, buf[i]);
        digitalWrite(dataOutMOSIPin, LOW);
        //delay(1);
        delayMicroseconds(1);
      }      
    }

    return len;
  }

    //SPI MODE 0
    uint32_t myShiftIn( uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder )
    {
        uint8_t value = 0 ;
        uint8_t i ;

        delayMicroseconds(CLOCK_HOLD);

        for ( i=0 ; i < 8 ; ++i )
        {

            digitalWrite( ulClockPin, LOW ) ;
            //delay(1);
            delayMicroseconds(CLOCK_HOLD);

            digitalWrite( ulClockPin, HIGH ) ;
            //delay(1);
            delayMicroseconds(CLOCK_HOLD);
            if ( ulBitOrder == LSBFIRST )
            {
                value |= digitalRead( ulDataPin ) << i ;
            }
            else
            {
                value |= digitalRead( ulDataPin ) << (7 - i) ;
            }    
        }

        return value ;
    }

   // delay too long may trigger LOKII's SPI timeout
   void myShiftOut( uint32_t ulDataPin, uint32_t ulClockPin, uint32_t ulBitOrder, uint32_t ulVal )
   {
        uint8_t i ;

        delayMicroseconds(CLOCK_HOLD);

        for ( i=0 ; i < 8 ; i++ )
        {

            digitalWrite( ulClockPin, LOW ) ;
            //delay(1);  
            delayMicroseconds(CLOCK_HOLD);

            if ( ulBitOrder == LSBFIRST )
            {
               digitalWrite( ulDataPin, !!(ulVal & (1 << i)) ) ;
            }
            else    
            {
                digitalWrite( ulDataPin, !!(ulVal & (1 << (7 - i))) ) ;
            }

            digitalWrite( ulClockPin, HIGH ) ;
            //delay(1);
            delayMicroseconds(CLOCK_HOLD);

        }
    }

};

typedef LokiMain<LokiSPI> LOKII;

#endif
