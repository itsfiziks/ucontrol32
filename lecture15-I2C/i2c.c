/* 
 * File:   i2c.c
 * Author: gvanhoy
 *
 * Created on October 15, 2015, 8:18 AM
 */

#include <xc.h>

#define I2C_WRITE 0
#define I2C_READ 1

void initI2C2(){
    I2C2CONbits.ON = 1;
//    I2C2BRG = 100*0x030;
    I2C2BRG = 4096/2 - 1;
    TRISDbits.TRISD0 = 0;
}

void i2cWrite(char i2cAddress, char data){
// Start condition
    I2C2CONbits.SEN = 1;                    // Start condition
    while(I2C2CONbits.SEN);
    
    // Send I2C Address and wait for ACK
    IFS1bits.I2C2MIF = 0;
    I2C2TRN = i2cAddress << 1 | I2C_WRITE;   // Send data
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(IFS1bits.I2C2MIF == 0);           // Wait until its transmitted
    if(!I2C2STATbits.ACKSTAT){
        LATDbits.LATD0 = 1;   
    }
    else{
        LATDbits.LATD0 = 0;
//        return;
    }    

    // Send data register address and wait for acknowledge
    IFS1bits.I2C2MIF = 0;
    I2C2TRN = data;               // Send Register
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(IFS1bits.I2C2MIF == 0);           // Wait until its transmitted
    if(!I2C2STATbits.ACKSTAT){
        LATDbits.LATD0 = 1;   
    }
    else{
        LATDbits.LATD0 = 0;
//        return;
    }
    
    // Start-restart condition
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);           // Wait until its transmitted
}

char i2cRead(char i2cAddress, char regAddress){
    char data;
    
    // Start condition
    I2C2CONbits.SEN = 1;                    // Start condition
    while(I2C2CONbits.SEN);
    
    // Send I2C Address and wait for ACK
    IFS1bits.I2C2MIF = 0;
    I2C2TRN = i2cAddress << 1 | I2C_WRITE;   // Send data
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(IFS1bits.I2C2MIF == 0);           // Wait until its transmitted
    if(!I2C2STATbits.ACKSTAT){
        LATDbits.LATD0 = 1;   
    }
    else{
        LATDbits.LATD0 = 0;
//        return;
    }    

    // Send data register address and wait for acknowledge
    IFS1bits.I2C2MIF = 0;
    I2C2TRN = regAddress;               // Send Register
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(IFS1bits.I2C2MIF == 0);           // Wait until its transmitted
    if(!I2C2STATbits.ACKSTAT){
        LATDbits.LATD0 = 1;   
    }
    else{
        LATDbits.LATD0 = 0;
//        return;
    }
    
    // Start-restart condition
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);           // Wait until its transmitted
    
    delayUs(10);
    
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);           // Wait until its transmitted
    
    // Send I2C and READ
    I2C2TRN = i2cAddress << 1 | I2C_READ;   // Send data
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(I2C2STATbits.TRSTAT);           // Wait until its transmitted
    
//    if(I2C2STATbits.ACKSTAT);
    
    // Receive Data
    I2C2CONbits.RCEN = 1;
    while(I2C2CONbits.RCEN);           // Wait until its transmitted
    data = I2C2RCV;
    
    // Not Acknowledge
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
    while(I2C2CONbits.ACKEN);           // Wait until its transmitted
    
    // Stop condition
    I2C2CONbits.PEN = 1;                    // Create a stop condition
    while(I2C2CONbits.PEN);
    
    return data;
}

char* i2cMultiByteRead(char i2cAddress, char regAddress, int numAddresses){
    char data[6];
    
    // Start condition
    I2C2CONbits.SEN = 1;                    // Start condition
    while(I2C2CONbits.SEN);
    
    // Send I2C Address and wait for ACK
    IFS1bits.I2C2MIF = 0;
    I2C2TRN = i2cAddress << 1 | I2C_WRITE;   // Send data
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(IFS1bits.I2C2MIF == 0);           // Wait until its transmitted
    if(!I2C2STATbits.ACKSTAT){
        LATDbits.LATD0 = 1;   
    }
    else{
        LATDbits.LATD0 = 0;
    }    

    // Send data register address and wait for acknowledge
    IFS1bits.I2C2MIF = 0;
    I2C2TRN = regAddress;               // Send Register
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(IFS1bits.I2C2MIF == 0);           // Wait until its transmitted
    if(!I2C2STATbits.ACKSTAT){
        LATDbits.LATD0 = 1;   
    }
    else{
        LATDbits.LATD0 = 0;
    }
    
    // Start-restart condition
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);           // Wait until its transmitted
    
    delayUs(10);
    
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);           // Wait until its transmitted
    
    // Send I2C and READ
    I2C2TRN = i2cAddress << 1 | I2C_READ;   // Send data
    if(I2C2STATbits.IWCOL == 1){
        I2C2STATbits.IWCOL = 0;
    }
    while(I2C2STATbits.TRSTAT);           // Wait until its transmitted
    

    int k;
    for(k = 0; k <= numAddresses; k++){
        I2C2CONbits.RCEN = 1;
        while(I2C2CONbits.RCEN);           // Wait until its transmitted
        data[k] = I2C2RCV;

        // Not Acknowledge
        if(k < numAddresses){
            I2C2CONbits.ACKDT = 0;
        }
        else{
            I2C2CONbits.ACKDT = 1;
        }
        I2C2CONbits.ACKEN = 1;
        while(I2C2CONbits.ACKEN);           // Wait until its transmitted
    }
    // Receive Data

    
    // Stop condition
    I2C2CONbits.PEN = 1;                    // Create a stop condition
    while(I2C2CONbits.PEN);
    
    return data;
}