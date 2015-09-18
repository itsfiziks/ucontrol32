/* 
 * File:   rtcc.c
 * Author: gvanhoy
 *
 * Created on September 17, 2015, 10:24 AM
 */

#include <proc/p32mx470f512l.h>


void initRTCC(){
    RTCCONbits.RTCWREN = 1;
    RTCCONbits.ON = 1;

    
    RTCDATEbits.YEAR10 = 0x1;
    RTCDATEbits.YEAR01 = 0x5;
    RTCDATEbits.MONTH10 = 0x0;
    RTCDATEbits.MONTH01 = 0x9;
    RTCDATEbits.WDAY01 = 0x4;
    RTCDATEbits.DAY10 = 0x1;
    RTCDATEbits.DAY01 = 0x7;
    
    RTCTIMEbits.HR10 = 0x1;
    RTCTIMEbits.HR01 = 0x0;
}