/* 
 * File:   led.h
 * Author: gvanhoy
 *
 * Created on September 3, 2015, 10:09 AM
 */

#ifndef LED_H
#define	LED_H

#define LED1 LATDbits.LATD0

void initLEDs();
void turnOnLED(int led);

#endif	/* LED_H */

