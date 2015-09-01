/* 
 * File:   main.c
 * Author: gvanhoy
 *
 * Created on September 1, 2015, 8:05 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

int main() {
    
    TRISDbits.TRISD2 = 0;       //Initialize LED 2
    LATDbits.LATD2 = 0;         // Default OFF

    TRISGbits.TRISG14 = 0;      //Set TRD1 pin as an output
    TRISGbits.TRISG12 = 1;      //set TRD2 as an input

    CNCONGbits.ON = 1;          //Turn ON change notifications
    CNPUGbits.CNPUG12 = 1;      //Enable the internal pull-up resistor
    CNENGbits.CNIEG12 = 1;      //Enable Change notifications

    LATGbits.LATG14 = 0;        //start a zero
    
    while(1){
        //Artificially change the pin value (like a pulse))
        LATGbits.LATG14 = 1;
        LATGbits.LATG14 = 0;
        
        //Check if a CN has been triggered
        if(IFS1bits.CNGIF == 1){
            LATDbits.LATD2 = 1;
        }
    }
    
    return 0;
}