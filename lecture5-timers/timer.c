/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on September 8, 2015, 10:19 AM
 */

#include <proc/p32mx470f512l.h>


void initTimer1(){
    TMR1 = 0;// clear TMR1
    PR1 = 1221*2;// Initialize PR1
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator
    IEC0bits.T1IE = 1;// Enable the interrupt
    IFS0bits.T1IF = 0;// Put the flag down
    IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    T1CONbits.TON = 1;// Turn the timer on
}
