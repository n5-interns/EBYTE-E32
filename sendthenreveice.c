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
#include "project.h"
#include <stdio.h>
#include <stdbool.h>
#include "EBYTEE32.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char usbmessage[256];
    CyDelay(5000);
    initRadio();
    DATA MyData, MyData2;
    MyData.Count = 0x01;
    for(;;)
    {
        /* Place your application code here. */
       
        
        MyData.message1 = 0xBA;
        MyData.message2 = 0x15;
        MyData.message3[0] = 'h';MyData.message3[1] = 'e'; MyData.message3[2] = 'l';
        MyData.message3[3] = 'l'; MyData.message3[4] = 'o'; MyData.message3[5] = '\0';   
    
        
        
            
        EBYTE_SendByte(MyData.Count);
        EBYTE_SendByte(MyData.message1);
        EBYTE_SendByte(MyData.message2);
//        EBYTE_SendByte(MyData.message3[0]);
//        EBYTE_SendByte(MyData.message3[1]);
//        EBYTE_SendByte(MyData.message3[2]);
//        EBYTE_SendByte(MyData.message3[3]);
//        EBYTE_SendByte(MyData.message3[4]);
//        EBYTE_SendByte(MyData.message3[5]);
        UART_1_PutArray((void *)MyData.message3, 6);
        
        
        sprintf(usbmessage,"Sending: %x\n", MyData.Count);
        sendUsb((void *)usbmessage, strlen(usbmessage));
        MyData.Count++;
            
        
       
        CyDelay(1000);
                    
        if (available()){
           
            MyData2.Count = EBYTE_GetByte();
            MyData2.message1 = EBYTE_GetByte();
            MyData2.message2 = EBYTE_GetByte();
            MyData2.message3[0] = EBYTE_GetByte();
            MyData2.message3[1] = EBYTE_GetByte();
            MyData2.message3[2] = EBYTE_GetByte();
            MyData2.message3[3] = EBYTE_GetByte(); 
            MyData2.message3[4] = EBYTE_GetByte(); 
            MyData2.message3[5] = EBYTE_GetByte();
            
            
            sprintf(usbmessage,"count: %x\nMessage1: %x\nMessage2: %x\nMessage3: %s\n", MyData2.Count, MyData2.message1,MyData2.message2, MyData2.message3);
            sendUsb((void *)usbmessage, strlen(usbmessage));
        }
        
        else{
            sprintf(usbmessage,"Searching: \n");
            sendUsb((void *)usbmessage, strlen(usbmessage));
        
        }
        
        CyDelay(3000);
        
      
    }
}

/* [] END OF FILE */
