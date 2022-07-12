# EBYTE-E32
Library for EBYTE-E32 (LoRa radio)


The Radios do not need to use pull-up resistors or voltage dividers with the chemnode boards since UART logic works at 3.3V. It is only a matter of connecting the radio to the chemnode. 
The top design includes two digital outputs (M0 and M1) that are used to set the mode of the radio (Normal or Programming mode). When it is in Normal Mode, the radio can send or receive data.
The top design also includes a digital input pin (AUX) which is read to determine if the radio is busy. 
The only other component was the UART component at 9600 Baud rate and a buffer size of 256 Bytes. 


![image](https://user-images.githubusercontent.com/105006862/178507525-22b48567-c0e8-481b-897e-d86f30b7848f.png)
