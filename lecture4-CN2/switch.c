/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on September 3, 2015, 10:15 AM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

void initSW1(){
    TRISDbits.TRISD6 = INPUT;           // Configure switch as input
    CNCONDbits.ON = 1;                  // Enable overall interrupt
    CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
    CNPUDbits.CNPUD6 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNDIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 2;                  // Configure interrupt priority
    IPC8bits.CNIS = 3;                  // Configure the interrupt sub-priority
    IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
}