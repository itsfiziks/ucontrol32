/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//Define states of the state machine
typedef enum stateTypeEnum{
    led
} stateType;


int main() {
    enableInterrupts();
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
    while(1){

    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0;
}

