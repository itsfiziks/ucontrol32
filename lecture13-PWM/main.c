
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"

int main(void){
    SYSTEMConfigPerformance(40000000);
    
    initTimer2();
    initPWM();
    initADC();
    enableInterrupts();
    
    while(1){   
        
    }
    
    return 0;
}

void __ISR(_ADC_VECTOR, IPL7SRS) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    OC2RS = ADC1BUF0;
}