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

/*
 * 
 */
int main() {

    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD6 = INPUT;
    CNPUDbits.CNPUD6 = 1;
    LATDbits.LATD0 = 1;
    
    while(1){
        if(PORTDbits.RD6 == 0){
            LATDbits.LATD0 = 1;
        }
        else{
            LATDbits.LATD0 = 0;
        }
    }
    
    return 0;
}

