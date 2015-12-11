#include "bsp.h"

void BspInit(void) {
    if (DSCONLbits.RELEASE) {
         DSCONLbits.RELEASE = 0;
    }
    // All analog inputs to ADC are by default digital
    ANCON0 = 0xFF;
    ANCON1 = 0xFF;
    // INTOSC drives clock directly
    OSCCONbits.IRCF = 7;
}

void DeepSleep(void){
       /* prepare to enter deep sleep */
    INTCONbits.GIEH = 0; /* disable interrupts */
    WDTCONbits.SWDTEN = 0; /* turn on the watch dog timer */
    DSCONLbits.ULPWDIS = 1; /* disable ULP wake up */
    DSCONLbits.DSBOR = 1; /* disable Brownout wake up */
    DSCONHbits.DSULPEN = 0; /* disable ULP pull up */
    DSCONHbits.RTCWDIS = 1; /* disable RTCC wake up */
    WDTCONbits.REGSLP = 1; /* turn off core regulator for deep sleep */
    OSCCONbits.IDLEN = 0; /* enter sleep mode, not idle */

    /* Check the generated code, the SLEEP instruction
     ** must be the next instruction after the DSEN bit
     ** is set in the DSCONH register.
     ** If not you must use inline assembly or call
     ** an assembly function to enter deep sleep
     */
    /* go to deep sleep, DSWDT or reset is the only way out in this demo */
    DSCONHbits.DSEN = 1;
    Sleep();
}

void UnUsedPeriphericalDisable (void){
    UCONbits.USBEN = 0; //USB circuit disable.
    RTCCFGbits.RTCOE = 0; //RTC output clock disable.
    RTCCFGbits.RTCEN = 0; //RTC circuit disable.
    
}