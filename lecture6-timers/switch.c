/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1 
#define DISABLED 0

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;
    CNPUDbits.CNPUD6 = ENABLED;
}