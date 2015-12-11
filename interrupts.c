#include "bsp.h"
#include "interrupts.h"
#include "sensor_proxy.h"
#include "network_proxy.h"
#include "clock/include/clkctrl.h"

static volatile uint8_t count = 0;

void EnableInterrupts(void) {
    // Clear peripheral priorities
    IPR1 = 0x00;
    IPR2 = 0x00;
    IPR3 = 0x00;
    // Clear interrupt flags
    PIR1 = 0x00;
    PIR2 = 0x00;
    PIR3 = 0x00;
    // Configure interrupts
    RCONbits.IPEN = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIEH = 1; /* Enable interrupts*/
    INTCONbits.GIEL = 1; /* Enable interrupts*/
}
// Clear o DisableInterrups
void ClearInterrupts(void){
    // Clear peripheral priorities
    IPR1 = 0x00;
    IPR2 = 0x00;
    IPR3 = 0x00;
    // Clear interrupt flags
    PIR1 = 0x00;
    PIR2 = 0x00;
    PIR3 = 0x00;
}

//TODO: probando si hay que habilitar las ISR para que funcione todo adecuadamente.
void EnableDeepSleepInterrupt (void) {
    RCONbits.IPEN = 1;
    INTCONbits.PEIE = 1;
}

void DisableInterrupts (void){
    INTCON = 0x00;
}

// Interrupt handler

//void interrupt HandleInterrupt(void) {
//    if (NetworkAwake()) {
//        //Operation Frequency increment.
//        operationFrequencyIntOscCtrl(F8Mhz);
//        // Clear network interrupt
//        ClearNetworkInterrupt();
//        // Gather measurements
//        MeasureSensors();
//        // Send measurements
//        SendMeasures();
//    }
//}
