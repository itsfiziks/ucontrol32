/* 
 * File:   interrupt.h
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:32 PM
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#define FLASH_SPEED_HZ              30000000 //Max Flash speed
#define PB_BUS_MAX_FREQ_HZ          80000000 //Max Peripheral bus speed
#define SYS_CFG_WAIT_STATES         0x00000001 //SYSTEMConfig wait states
#define SYS_CFG_PB_BUS              0x00000002 //SYSTEMConfig pb bus
#define SYS_CFG_PCACHE              0x00000004 //SYSTEMConfig cache
#define SYS_CFG_ALL                 0xFFFFFFFF //SYSTEMConfig All

#define mBMXDisableDRMWaitState()   (BMXCONCLR = _BMXCON_BMXWSDRM_MASK)
#define mCheGetCon()                CHECON
#define CHE_CONF_PF_ALL             (3 << _CHECON_PREFEN_POSITION)
#define mCheConfigure(val)          (CHECON = (val))
#define OSC_PB_DIV_8                (3 << _OSCCON_PBDIV_POSITION)
#define OSC_PB_DIV_4                (2 << _OSCCON_PBDIV_POSITION)
#define OSC_PB_DIV_2                (1 << _OSCCON_PBDIV_POSITION)
#define OSC_PB_DIV_1                (0 << _OSCCON_PBDIV_POSITION)
#define mSYSTEMUnlock(intStat, dmaSusp) do{intStat=INTDisableInterrupts(); dmaSusp=DmaSuspend(); \
                    SYSKEY = 0, SYSKEY = 0xAA996655, SYSKEY = 0x556699AA;}while(0)
#define mSYSTEMLock(intStat, dmaSusp)   do{SYSKEY = 0x33333333; DmaResume(dmaSusp); INTRestoreInterrupts(intStat);}while(0)

void enableInterrupts();
void disableInterrupts();
extern unsigned int SYSTEMConfigWaitStatesAndPB(unsigned int sys_clock);
extern unsigned int SYSTEMConfigPerformance(unsigned int sys_clock);
extern unsigned int SYSTEMConfigPB(unsigned int sys_clock);
int DmaSuspend(void);
void DmaResume(int susp);
extern void OSCSetPBDIV(unsigned int oscPbDiv);
void __attribute__((nomips16))  INTRestoreInterrupts(unsigned int status);
unsigned int __attribute__((nomips16))  INTEnableInterrupts(void);
unsigned int __attribute__((nomips16)) INTDisableInterrupts(void);
void __attribute__ ((nomips16)) CheKseg0CacheOn();

#endif	/* INTERRUPT_H */

