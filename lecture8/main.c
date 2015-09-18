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
#include "timer.h"
#include "leds.h"
#include "config.h"

// ******************************************************************************************* //

int main(void)
{
    disableInterrupts();
    TRISDbits.TRISD0 = 0;
    enableInterrupts();
    initTestLEDs();
    
    while(1)
    {
        
    }
    
    return 0;
}