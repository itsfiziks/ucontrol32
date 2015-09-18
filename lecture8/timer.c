/*
 * File:   initTimer.c
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

#define PRESCALAR 256
#define FOSC 625000
#define LOWER_16_BITS_MASK 0x0000FFFF

//Uses timer 2
void initTimer2(){
    TMR2 = 0;
    T2CONbits.TCKPS = 7; //prescalar of 256
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T1IE = 1;
    IPC1bits.T1IP = 3; // Interrupt priority
    IPC1bits.T1IS = 3; // Interupt sub-priority
}

void delayMs(unsigned int delay){
    TMR2 = 0;
    PR2 = delay*39*8;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    IEC1bits.CNGIE = 0;
    while(IFS0bits.T2IF == 0);
    IEC1bits.CNGIE = 1;
    T2CONbits.ON = 0;
}


/* 
 * Initialize timers 4 and 5 in 32-bit mode.
 */
void init32BitTimer(){
    T4CONbits.T32 = 1;
    T4CONbits.TCKPS = 0;
    T4CONbits.TCS = 0;
    T4CONbits.TGATE = 0;
//    IEC0bits.T5IE = 1;
    IFS0bits.T5IF = 0;
//    IPC5bits.T5IP = 3;
//    IPC5bits.T5IS = 3;
}
/* 
 * Use timers 4 and 5 in 32 bit mode to create a delay that is an arbitrary amount
 * of seconds long.
 */
void delayS(float seconds){
    TMR4 = 0;
    TMR5 = 0;
    int prValue = (int) ((seconds*FOSC)/PRESCALAR - 1);
    PR4 = prValue & LOWER_16_BITS_MASK;
    PR5 = prValue >> 16;
    T4CONbits.ON = 1;
    while(IFS0bits.T5IF == 0);
    IFS0bits.T5IF = 1;
    T4CONbits.ON = 0;
}