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
    DATA MyData;
    MyData.Count = 0x01;
//    MyData.message1 = 0xBA;
//    MyData.message2 = 0x15;
//    MyData.message3[0] = 'H';MyData.message3[1] = 'e'; MyData.message3[2] = 'l';
//    MyData.message3[3] = 'l'; MyData.message3[4] = 'o'; MyData.message3[5] = '\0';   
    
    for(;;)
    {
        /* Place your application code here. */
        
        MyData.message1 = 0xBA;
        MyData.message2 = 0x15;
        MyData.message3[0] = 'H';MyData.message3[1] = 'e'; MyData.message3[2] = 'l';
        MyData.message3[3] = 'l'; MyData.message3[4] = 'o'; MyData.message3[5] = '\0';   
    
        CyDelay(50);
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
        
        
        sprintf(usbmessage,"Sending: %d\n", MyData.Count);
        sendUsb((void *)usbmessage, strlen(usbmessage));
        MyData.Count++;
        CyDelay(1000);
    }
}

/* [] END OF FILE */
