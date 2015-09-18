/* 
 * File:   keypad.h
 * Author: gvanhoy
 *
 * Created on September 17, 2015, 10:10 AM
 */

#include <proc/p32mx470f512l.h>


int keyPadScan(){

    int key = -1;
    
    LATDbits.LATD0 = 1;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;    
    LATDbits.LATD3 = 0;
    if(PORTGbits.RG0 == 0) key = 1;
    if(PORTGbits.RG1 == 0) key = 2;

    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 1;
    LATDbits.LATD2 = 0;    
    LATDbits.LATD3 = 0;
    if(PORTGbits.RG0 == 0) key = 4;
    if(PORTGbits.RG1 == 0) key = 5;
}