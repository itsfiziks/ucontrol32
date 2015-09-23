// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: This is the solution for part 1 of Lab 1. Just blinking LEDs with an external switch.
// This switch must be debounced.
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "interrupt.h"
#include "uart.h"
#include "timer.h"
#include "config.h"

// ******************************************************************************************* //

unsigned char receivedChar;

int main(void)
{
    initUART2();
    
    while(1)
    {
        U2TXREG = 0b01011010;
        
        if(IFS1bits.U2RXIF == 1){
            receivedChar = U2RXREG;
        }
        
        delayUs(500);
    }
    
    return 0;
}