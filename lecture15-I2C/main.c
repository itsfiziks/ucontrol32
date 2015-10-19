

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "timer.h"
#include "i2c.h"
#include "accel.h"

#define SYS_CLK 10000000

int main(void){
    SYSTEMConfigPerformance(SYS_CLK);
    
    enableInterrupts();
    initI2C2();
    
    char* data;
    int i;
    while(1){
        data = i2cMultiByteRead(ACCEL_I2C_ADDRESS, ACCEL_DATAX0_REG, 6);
        for(i = 0; i < 100; i++) delayUs(1000);
    }
    
    return 0;
}