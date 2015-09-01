/* 
 * File:   main.c
 * Author: gvanhoy
 *
 * Created on September 1, 2015, 8:05 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"


/*
 * 
 */
int main() {
    
    int i = 0;
    
    //Set TRD1 pin as an output
    TRISGbits.TRISG14 = 0;

    //set TRD2 as an input
    TRISGbits.TRISG12 = 1;
    
    TRISDbits.TRISD2 = 0;
    
    //Enable the internal pull=up resistor
    CNPUGbits.CNPUG12 = 1;
    
    //Enable Change notifications
    CNENGbits.CNIEG12 = 1;
    
    //Enable the change notification ISR
    IEC1bits.CNGIE = 1;
    
    //Put the flag down
    IFS1bits.CNGIF = 0;
    
    //Set interrupt priority
    
    //"send" a zero
    LATGbits.LATG14 = 0;
    
    LATDbits.LATD2 = 0;

    while(1){
        //Artificially change the pin value
        LATGbits.LATG14 = 0;
        LATGbits.LATG14 = 1;
        if(IFS1bits.CNGIF == 1){
            LATDbits.LATD2 = 1;
        }
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(){
    
}