/*
Slightly modified version of U8g2 library that allows you to define which
i2c bus you are using.
For example:
#define Wire Wire1
means that we are using bus 1 instead of bus 0 as default.

I am using this on a teensy 4 - remember that you will need to pull up SDA1 and SCL 1 to 3.3v using a 2.2k resistor if you want to use them. (this is included on the board for SDA0 and SCL0)

This gets rid of unpredictable behaviour when combining the Teensy Audio Shield with MPR121 sensors.

based on the version posted on this thread https://forums.adafruit.com/viewtopic.php?f=19&t=68139

www.gawainhewitt.co.uk
https://github.com/gawainhewitt

*/

/*

  bus1_U8g2lib.cpp
  
  Arduino specific functions


  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/


#include "bus1_U8g2lib.h"
#define Wire Wire1 // use this to specify a different i2c bus - For example: #define Wire Wire1 means that we are using bus 1 instead of bus 0 as default.

#ifdef ARDUINO
static Print *u8g2_print_for_screenshot;

void u8g2_print_callback(const char *s)
{ 
  yield(); 
  u8g2_print_for_screenshot->print(s); 
}

void U8G2::writeBufferPBM(Print &p)
{
  u8g2_print_for_screenshot = &p;
  u8g2_WriteBufferPBM(getU8g2(), u8g2_print_callback);
}

void U8G2::writeBufferXBM(Print &p)
{
  u8g2_print_for_screenshot = &p;
  u8g2_WriteBufferXBM(getU8g2(), u8g2_print_callback);
}

void U8G2::writeBufferPBM2(Print &p)
{
  u8g2_print_for_screenshot = &p;
  u8g2_WriteBufferPBM2(getU8g2(), u8g2_print_callback);
}

void U8G2::writeBufferXBM2(Print &p)
{
  u8g2_print_for_screenshot = &p;
  u8g2_WriteBufferXBM2(getU8g2(), u8g2_print_callback);
}
#endif


