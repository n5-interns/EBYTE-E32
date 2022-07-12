/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/*
  The MIT License (MIT)
  Copyright (c) 2019 Kris Kasrpzak
  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  On a personal note, if you develop an application or product using this library 
  and make millions of dollars, I'm happy for you!
*/


#include "project.h"
#include <stdio.h>
#include <stdbool.h>


#ifndef EBYTEE32_h
    #define EBYTEE32_h 
    #define PIN_RECOVER 100

    #define USBUART_BUFFER_SIZE (64u)
    #define USB_TIMEOUT (50u)

    // modes NORMAL send and recieve for example
    #define MODE_NORMAL 0			// can send and recieve
    #define MODE_WAKEUP 1			// sends a preamble to waken receiver
    #define MODE_POWERDOWN 2		// can't transmit but receive works only in wake up mode
    #define MODE_PROGRAM 3			// for programming
    
    void writeUsb64(uint8_t *buffer, uint16 size);
    void sendUsb(char *buffer, unsigned int size);
    
    // options to save change permanently or temp (power down and restart will restore settings to last saved options
    #define PERMANENT 0xC0
    #define TEMPORARY 0xC2

    bool initRadio();
    	
    // methods to set modules working parameters NOTHING WILL BE SAVED UNLESS SaveParameters() is called
    void SetMode(uint8_t mode);
    void SetAddress(uint16_t val);
    void SetAddressH(uint8_t val);
    void SetAddressL(uint8_t val);
    void SetSpeed(uint8_t val);
    void SetChannel(uint8_t val);

    bool GetAux();

    bool available();
    // methods to get some operating parameters
    uint16_t GetAddress();

    // methods to get module data
    uint8_t GetModel();
    uint8_t GetVersion();
    uint8_t GetFeatures();

    uint8_t GetAddressH();
    uint8_t GetAddressL();
    uint8_t GetAirDataRate();
    uint8_t GetUARTBaudRate();
    uint8_t GetChannel();
    uint8_t GetParityBit();
    uint8_t GetTransmissionMode();
    uint8_t GetPullupMode();
    uint8_t GetWORTIming();
    uint8_t GetFECMode();
    uint8_t GetTransmitPower();


    uint8_t GetOptions();
    uint8_t GetSpeed();

    	
    // methods to get data from sending unit
    uint8_t GetByte();

    // method to send to data to receiving unit
    void SendByte(uint8_t TheByte);

    // mehod to print parameters
    void PrintParameters();

    // parameters are set above but NOT saved, here's how you save parameters
    // notion here is you can set several but save once as opposed to saving on each parameter change
    // you can save permanently (retained at start up, or temp which is ideal for dynamically changing the address or frequency
    void SaveParameters(uint8_t val);

    // MFG is not clear on what Reset does, but my testing indicates it clears buffer
    // I use this when needing to restart the EBYTE after programming while data is still streaming in
    // it does NOT return the ebyte back to factory defaults

    // function to read modules parameters
    bool ReadParameters();

    // method to let method know of module is busy doing something (timeout provided to avoid lockups)
    void CompleteTask(unsigned long timeout);

    // utility funciton to build the "speed byte" which is a collection of a few different parameters
    void BuildSpeedByte();

    // utility funciton to build the "options byte" which is a collection of a few different parameters

    void BuildOptionByte();
    bool ReadModelData();
    void ClearBuffer();
    

    typedef struct ebyte_t{
        // variable for the 6 bytes that are sent to the module to program it
    	// or bytes received to indicate modules programmed settings
    	uint8_t _Params[6];

    	// indicidual variables for each of the 6 bytes
    	// _Params could be used as the main variable storage, but since some bytes
    	// are a collection of several options, let's just make storage consistent
    	// also Param[1] is different data depending on the _Save variable
    	uint8_t _Save;
    	uint8_t _AddressHigh;
    	uint8_t _AddressLow;
    	uint8_t _Speed;
    	uint8_t _Channel;
    	uint8_t _Options;
    	uint8_t _Attempts;
    	
    	// individual variables for all the options
    	uint8_t _ParityBit;
    	uint8_t _UARTDataRate;
    	uint8_t _AirDataRate;
    	uint8_t _OptionTrans;
    	uint8_t _OptionPullup;
    	uint8_t _OptionWakeup;
    	uint8_t _OptionFEC;
    	uint8_t _OptionPower;
    	uint16_t _Address;
    	uint8_t _Model;
    	uint8_t _Version;
    	uint8_t _Features;
    	uint8_t _buf;
       
    } EBYTE;
    
    typedef struct data_t{
        //data sent and received
        uint8_t Count;
        uint8_t message1;
        uint8_t message2;
        uint8_t message3[6]; 
    } DATA;
    
    extern EBYTE Radio; 
#endif
/* [] END OF FILE */
