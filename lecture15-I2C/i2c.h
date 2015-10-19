/* 
 * File:   i2c.h
 * Author: gvanhoy
 *
 * Created on October 15, 2015, 8:18 AM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

void initI2C2();
char i2cRead(char i2cAddress, char data);
char i2cWrite(char i2cAddress, char data);
char* i2cMultiByteRead(char i2cAddress, char regAddress, int numAddress);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

