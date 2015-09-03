/* 
 * File:   main.c
 * Author: gvanhoy
 *
 * Created on September 1, 2015, 8:05 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "led.h"
#include "switch.h"

// Define states
typedef enum stateTypeEnum{
    waitPush, waitRelease
} stateType;

volatile stateType state = waitPush;
        
int main() {
    
    initLEDs();
    initSW1();
    
    while(1){
        switch(state){
            case waitPush:
                if(IFS1bits.CNDIF == 1){
                    state = waitRelease;
                }
                break;
            case waitRelease:
                if(IFS1bits.CNDIF == 1){
                    turnOnLED(1);
                    state = waitPush;
                }
                break;
        }
    }
    
    return 0;
}