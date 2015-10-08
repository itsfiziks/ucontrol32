
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"

volatile unsigned int val = 0;

int main(void){
    SYSTEMConfigPerformance(40000000);
    int i;
    
    enableInterrupts();
    initADC();
    TRISDbits.TRISD0 = 0;
    
    while(1){
//        if(IFS0bits.AD1IF == 1){
//            val = ADC1BUF0;
//            IFS0bits.AD1IF = 0;
//        }
        for(i = 0; i < (int) (1000*val)/1023; i++) delayUs(10);
        LATDbits.LATD0 = 1;
        for(i = 0; i < (int) (1000*(1023 - val))/1023; i++) delayUs(10);
        LATDbits.LATD0 = 0;
    }
    
    return 0;
}


void __ISR(_ADC_VECTOR, IPL7AUTO) _ADCInterrupt(void){
    IFS0bits.AD1IF = 0;
    val = ADC1BUF0;
}