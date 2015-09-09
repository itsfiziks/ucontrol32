/* 
 * File:   main.c
 * Author: gvanhoy
 *
 * Created on September 1, 2015, 8:05 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "led.h"
#include "switch.h"
#include "timer.h"
        
int main() {
    
    enableInterrupts();
    initLEDs();
    initSW1();
    initTimer1();
    
    while(1){
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt(){
    IFS0bits.T1IF = 0;
    LATDbits.LATD0 = !LATDbits.LATD0;
}