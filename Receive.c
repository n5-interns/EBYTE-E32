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
    DATA MyData;
    
    for(;;)
    {
        /* Place your application code here. */
        if (available()){
            CyDelay(50);
            MyData.Count = EBYTE_GetByte();
            MyData.message1 = EBYTE_GetByte();
            MyData.message2 = EBYTE_GetByte();
            MyData.message3[0] = EBYTE_GetByte();
            MyData.message3[1] = EBYTE_GetByte();
            MyData.message3[2] = EBYTE_GetByte();
            MyData.message3[3] = EBYTE_GetByte(); 
            MyData.message3[4] = EBYTE_GetByte(); 
            MyData.message3[5] = EBYTE_GetByte();  
            
                
            
            sprintf(usbmessage,"count: %d\nMessage1: %x\nMessage2: %x\nMessage3: %s\n", MyData.Count, MyData.message1,MyData.message2, MyData.message3);
            sendUsb((void *)usbmessage, strlen(usbmessage));
        }
        
        else{
            sprintf(usbmessage,"Searching: \n");
            sendUsb((void *)usbmessage, strlen(usbmessage));
        
        }
        CyDelay(1000);
    }
}

/* [] END OF FILE */
