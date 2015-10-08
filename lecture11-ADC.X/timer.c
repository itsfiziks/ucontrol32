/*
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

//Uses timer 2
void delayUs(unsigned int delay){
    TMR2 = 0;
    PR2 = 5*delay;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.TON = 0;
}