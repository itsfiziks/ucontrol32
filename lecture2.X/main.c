/* 
 * File:   main.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>

#define OUTPUT 0
#define INPUT 1

typedef enum stateTypeEnum{
    led_on, led_off
} stateType;
/*
 * 
 */
int main() {

    stateType state = led_on;
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD6 = INPUT;
    CNPUDbits.CNPUD6 = 1;
    LATDbits.LATD0 = 1;
    
    while(1){
        switch(state){
            case led_on:
                LATDbits.LATD0 = 1;
                if(PORTDbits.RD6 == 0) state = led_off;
                break;
            case led_off:
                LATDbits.LATD0 = 0;
                if(PORTDbits.RD6 == 1) state = led_on;
                break;
        }
    }
    
    return 0;
}

