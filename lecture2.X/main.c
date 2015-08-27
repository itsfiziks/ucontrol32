/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: Using a finite state machine (FSM) implementation, use SW1 to 
 * turn LED1 on and off.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//Define states of the state machine
typedef enum stateTypeEnum{
    led_on, led_off
} stateType;

/*
 * 
 */
int main() {

    //Define an initial state
    stateType state = led_on;
    //Configure LED1 as an output
    TRISDbits.TRISD0 = OUTPUT;
    //Have the LED1 be one by default
    LATDbits.LATD0 = 1;
    //Configure the switch as an input
    TRISDbits.TRISD6 = INPUT;
    //Configure the internal pull-up resistor for the switch
    CNPUDbits.CNPUD6 = 1;

    
    while(1){
        switch(state){
            case led_on:
                //Turn the LED ON
                LATDbits.LATD0 = 1;
                //If the switch is pressed, switch states
                if(PORTDbits.RD6 == 0) state = led_off;
                break;
            case led_off:
                //Turn the LED OFF
                LATDbits.LATD0 = 0;
                //If the switch is released, switch states
                if(PORTDbits.RD6 == 1) state = led_on;
                break;
        }
    }
    
    return 0;
}

