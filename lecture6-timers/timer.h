/* 
 * File:   timer.h
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

void initTimer1();
void initTimer2();
void delayMs(int delay);
void resetTimer1();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

