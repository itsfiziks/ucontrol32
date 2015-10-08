/* 
 * File:   interrupt.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:32 PM
 */

#include <xc.h>
#include "interrupt.h"

void enableInterrupts(){
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    unsigned int status = 0;
    asm volatile("ei    %0" : "=r"(status));
}

void disableInterrupts(){
    unsigned int status = 0;
    asm volatile("di    %0" : "=r"(status));
}

extern unsigned int SYSTEMConfigPerformance(unsigned int sys_clock)
{
    // set up the wait states
    unsigned int pb_clk;
#ifdef _PCACHE
    unsigned int cache_status;
#endif
    unsigned int int_status;

    pb_clk = SYSTEMConfigWaitStatesAndPB(sys_clock);

    int_status=INTDisableInterrupts();

    mBMXDisableDRMWaitState();

#ifdef _PCACHE
    cache_status = mCheGetCon();
    cache_status |= CHE_CONF_PF_ALL;
    mCheConfigure(cache_status);
    CheKseg0CacheOn();
#endif

    INTRestoreInterrupts(int_status);

    return pb_clk;

}

extern unsigned int SYSTEMConfigWaitStatesAndPB(unsigned int sys_clock)
{
#ifdef _PCACHE
    unsigned int wait_states;
#endif
    unsigned int pb_clock;
    unsigned int int_status;

    pb_clock = SYSTEMConfigPB(sys_clock);


    // set the flash wait states based on 1 wait state
    // for every 20 MHz
#ifdef _PCACHE
    wait_states = 0;

    while(sys_clock > FLASH_SPEED_HZ)
    {
        wait_states++;
        sys_clock -= FLASH_SPEED_HZ;
    }

    int_status=INTDisableInterrupts();
    mCheConfigure(wait_states);
    INTRestoreInterrupts(int_status);

#endif

    return pb_clock;
}

unsigned int __attribute__((nomips16))  INTEnableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("ei    %0" : "=r"(status));

    return status;
}

unsigned int __attribute__((nomips16)) INTDisableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("di    %0" : "=r"(status));

    return status;
}

extern  unsigned int SYSTEMConfigPB(unsigned int sys_clock)
{
    unsigned int pb_div;
    unsigned int pb_clock;

    pb_clock = sys_clock;

    if(sys_clock > PB_BUS_MAX_FREQ_HZ)
    {
        pb_div=OSC_PB_DIV_2;
        pb_clock >>= 1;
    }
    else
    {
        pb_div=OSC_PB_DIV_1;
    }

    OSCSetPBDIV(pb_div);

    return pb_clock;
}

void __attribute__((nomips16))  INTRestoreInterrupts(unsigned int status)
{
    if(status & 0x00000001){
        asm volatile("ei");
    }
    else {
        asm volatile("di");
        }
}

extern void  OSCSetPBDIV(unsigned int oscPbDiv)
{
    unsigned int dma_status;
    unsigned int int_status;
    __OSCCONbits_t oscBits;

    mSYSTEMUnlock(int_status, dma_status);

    oscBits.w=OSCCON;       // read to be in sync. flush any pending write
    oscBits.PBDIV=0;
    oscBits.w|=oscPbDiv;
    OSCCON=oscBits.w;       // write back
    oscBits.w=OSCCON;       // make sure the write occurred before returning from this function

    mSYSTEMLock(int_status, dma_status);
}

extern int DmaSuspend(void)
    {
        int suspSt;
        if(!(suspSt=DMACONbits.SUSPEND))
        {
            DMACONSET=_DMACON_SUSPEND_MASK;     // suspend
            while(!(DMACONbits.SUSPEND));   // wait to be actually suspended
        }
        return suspSt;
    }

extern void DmaResume(int susp)
{
	if(susp)
	{
		DmaSuspend();
	}
	else
	{
		DMACONCLR=_DMACON_SUSPEND_MASK;     // resume DMA activity
	}
}

void __attribute__ ((nomips16)) CheKseg0CacheOn()
{
	register unsigned long tmp;
	asm("mfc0 %0,$16,0" :  "=r"(tmp));
	tmp = (tmp & ~7) | 3;
	asm("mtc0 %0,$16,0" :: "r" (tmp));
}