/*
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
#include "interrupt.h"

void initTimer2(){
    TMR2 = 0;
    PR2 = 1023;
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    T2CONbits.ON = 1;
}

//Uses timer 2
void delayUs(unsigned int delay){
    TMR1 = 0;
    PR1 = 5*delay;
    IFS0bits.T2IF = 0;
    T1CONbits.TCKPS = 1;
    disableInterrupts();
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0);
    T1CONbits.TON = 0;
    enableInterrupts();
}