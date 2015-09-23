/*
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

#define ONE_HUNDREDTH_SECOND 1561

void initTimer1(){
    // Clear Timer value (i.e. current timer value) to 0
    TMR1 = 0;
    PR1 = ONE_HUNDREDTH_SECOND;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    IPC1bits.T1IP = 7;
    T1CONbits.TCKPS = 3;
    T1CONbits.TON = 1;
}


//Uses timer 2
void delayUs(unsigned int delay){
    TMR2 = 0;
    PR2 = 10*delay;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.TON = 0;
}