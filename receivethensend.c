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
#include <string.h>


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char usbmessage[256];
    CyDelay(5000);
    initRadio();
    DATA MyData, MyData2;
    
    for(;;)
    {
        /* Place your application code here. */
        
        
        
        if (available()){
           
            MyData.Count = EBYTE_GetByte();
            MyData.message1 = EBYTE_GetByte();
            MyData.message2 = EBYTE_GetByte();
            MyData.message3[0] = EBYTE_GetByte();
            MyData.message3[1] = EBYTE_GetByte();
            MyData.message3[2] = EBYTE_GetByte();
            MyData.message3[3] = EBYTE_GetByte(); 
            MyData.message3[4] = EBYTE_GetByte(); 
            MyData.message3[5] = EBYTE_GetByte();  
            
                
            
            sprintf(usbmessage,"count: %x\nMessage1: %x\nMessage2: %x\nMessage3: %s\n", MyData.Count, MyData.message1,MyData.message2, MyData.message3);
            sendUsb((void *)usbmessage, strlen(usbmessage));
            
        }
        
        else{
            sprintf(usbmessage,"Searching: \n");
            sendUsb((void *)usbmessage, strlen(usbmessage));
            
            
        }
    
        ClearBuffer();
        
        
        
        
        
        //process data 
        int i;
        MyData2.Count= MyData.Count +20;
        MyData2.message1 = MyData.message1 +20;
        MyData2.message2 = MyData.message2 + 20;
        for (i=0;i<6;i++){
            MyData2.message3[i] = MyData.message3[i] - 32 ;
           
        }
        
        CyDelay(500);
        
        if (!UART_1_GetRxBufferSize()){
            
            sprintf(usbmessage,"Sending: %x\n", MyData2.Count);
            sendUsb((void *)usbmessage, strlen(usbmessage));
            // send processed data
            EBYTE_SendByte(MyData2.Count);
            EBYTE_SendByte(MyData2.message1);
            EBYTE_SendByte(MyData2.message2);
//            EBYTE_SendByte(MyData2.message3[0]);
//            EBYTE_SendByte(MyData2.message3[1]);
//            EBYTE_SendByte(MyData2.message3[2]);
//            EBYTE_SendByte(MyData2.message3[3]);
//            EBYTE_SendByte(MyData2.message3[4]);
//            EBYTE_SendByte(MyData2.message3[5]);            
            UART_1_PutArray((void *)MyData2.message3, 6);
            

            
        }
        CyDelay(3000);
        
    }
}
