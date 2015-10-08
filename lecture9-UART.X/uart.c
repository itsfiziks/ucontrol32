/* 
 * File:   uart.c
 * Author: gvanhoy
 *
 * Created on September 22, 2015, 8:55 AM
 */

#include <xc.h>

void initUART2(){
    RPD3Rbits.RPD3R = 1;    //Maps U2TX to pin 18
//    U2RXRbits.U2RXR = 0;    //Mapping U2RX to pin 17, J11
    U2BRG = 10;             //Set the baud rate
    U2MODEbits.PDSEL = 2;   //Parity select (depends on device) (8-N-1)
    U2MODEbits.STSEL = 0;   //One stop bit
    U2MODEbits.UEN = 0;
    U2MODEbits.BRGH = 0;
//    U2STAbits.URXEN = 1;    //Enable the receive pin (TRIS not needed)
    U2STAbits.UTXEN = 1;    //Enable the transmit pin (TRIS not needed)
    U2MODEbits.ON = 1;      //Enable the UART
}