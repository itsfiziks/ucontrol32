/*
* File:   leds.c
* Author: Garrett Vanhoy
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"

#define TRIS_RUN TRISGbits.TRISG12
#define TRIS_STOP TRISGbits.TRISG14
#define ODC_RUN ODCGbits.ODCG12
#define ODC_STOP ODCGbits.ODCG14
#define RUN_LED LATGbits.LATG12 // TRD1
#define STOP_LED LATGbits.LATG14 // TRD2

#define ON 1
#define OFF 0

#define INPUT 1
#define OUTPUT 0

typedef enum ledStateTypeEnum{
    run, stop
} ledStateType;

ledStateType ledState = run;

void initLEDs(){
    TRIS_RUN = OUTPUT;
    TRIS_STOP = OUTPUT;

    ODC_RUN = 1;
    ODC_STOP = 1;
    
    RUN_LED = ON;
    STOP_LED = OFF;
}

void runLED(){
    RUN_LED = ON;
    STOP_LED = OFF;
}

void stopLED(){
    RUN_LED = OFF;
    STOP_LED = ON;
}

void toggleLED(){
    switch(ledState){
        case run:
            ledState = stop;
            stopLED();
            break;
        case stop:
            ledState = run;
            runLED();
            break;
    }
}

void initTestLEDs(){
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}