/* 
 * File:   main.c
 * Author: gvanhoy
 *
 * Created on September 1, 2015, 8:05 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "interrupt.h"
#include "config.h"
#include "led.h"
#include "switch.h"

// Define states
typedef enum stateTypeEnum{
    waitPush, waitRelease
} stateType;

volatile stateType state = waitPush;
unsigned int dummyVariable = 0;

int main() {
    
    initLEDs();
    initSW1();
    
    enableInterrupts();
    
    while(1){
        switch(state){
            case waitPush:
                break;
            case waitRelease:
                break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SRS) _CNInterrupt( void ){
    dummyVariable = PORTDbits.RD6 = 1;
    IFS1bits.CNDIF = 0;
    if(state == waitPush) state = waitRelease;
    else if(state == waitRelease){
        state = waitPush;
        LED1 = !LED1;
    }
}