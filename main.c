#include "bsp.h"
#include "interrupts.h"
#include "sensor_proxy.h"
#include "xbee/../digi_api.h"
#include "clock/include/clkctrl.h"
#include "opController.h"
#include "power.h"
static void Idle(void);

int main() {
    
//    if (DEEP_SLEEP_WAKE_UP){
//        
//    }

    BspInit();
    ClearInterrupts();
    DisableInterrupts();
    EnableDeelSleepInterrupt();
   
    XBeeInit();
    // XBeeJoin(); //ESTE AHI QUE SACARLO DEL xbee INIT PARA TRABAJAR EN DEEP SLEEP pongo el Join solo con el associate a ver si asi no consume tanto
    SensorProxyInit();

    //    EnableInterrupts();
    while (1) {
 
    #if SLEEP_MODE == DEEP_SLEEP
        if (XBEE_ON_DS_AWAKE) {
            OnWakeUp();
        } else if (ON_DS_MCLR) {
            OnMclr();
        } else if (ON_DS_WDT) {
            OnDsWdtWakeUp();
        } else if (ON_DS_ULP){
            WDTCONbits.DS = 0;// quiza desierta por este modo y hay q 
            // configurarlo en como salida antes de ponerlo a dormir.
        } else if (ON_DS_RTC_ALARM){
            WDTCONbits.DS = 0;
        } else if (POWER_UP){
            OnPowerUp();
        } else if (DS_FAULT){
            WDTCONbits.DS = 0;
            DSWAKELbits.DSFLT=0; 
            while(1); //TODO: REVisar que pinta este while(1) aqui
        }
        PowerDeepSleep();
    #endif 

        //        operationFrequencyIntOscCtrl(F31Khz);
        //        Idle();
    }
    return 0;
}

/**
 * In RC_IDLE mode, the CPU is disabled but the peripherals continue to be
 * clocked from the internal oscillator block.
 * This mode allows for controllable power conservation during Idle periods.
 * From RC_RUN, this mode is entered by setting the IDLEN bit and executing
 * a SLEEP instruction.
 * If the device is in another Run mode, first set IDLEN, then clear the SCS
 * bits and execute SLEEP.
 * When the clock source is switched to the INTOSC block, the primary oscillator
 * is shutdown and the OSTS bit is cleared.
 * When a wake event occurs, the peripherals continue to be clocked from the
 * internal oscillator block.
 * After a wake event, the CPU begins executing code being clocked by the INTRC.
 * The IDLEN and SCS bits are not affected by the wake-up.
 * The INTRC source will continue to run if either the WDT or the FSCM is enabled.
 */
static void Idle(void) {
    // FIXME ¿Should check for timer 1 status?
    OSCCONbits.IDLEN = 1;
    //    // If RC_RUN is not enabled(SCS = '11') then set SCS = 0x11
    //    if (OSCCONbits.SCS != 3) {
    //        OSCCONbits.SCS = 3;
    //    }
    Sleep();
    Nop();
}
