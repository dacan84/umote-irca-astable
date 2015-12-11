#include "opController.h"
#include  <xc.h>
#include "power.h"
#include "bsp.h"
#include "xbee/include/digi_api.h"
#include "xbee/include/digi_serial.h"
#include "network_proxy.h"
#include "sensor_proxy.h"
#include "interrupts.h"

/*...........................................................................*/
void OnPowerUp(void) {
    XBeeJoin();
    UnUsedPeriphericalDisable();
}

/*...........................................................................*/

/* On reset push, join xbee */
void OnMclr(void) {
    ClearMclrFlags();
    Delay10KTCYx(10);
    XBeeJoin();
}

/*...........................................................................*/

void OnWakeUp(void) {
    // Clear wake up flags
    ClearDSWakeUpFlags();
    // Clear network interrupt
    ClearNetworkInterrupt();
    // Gather measurements
    MeasureSensors();
    // Send measurements
    SendMeasures();
    //    // Ejecuta la interrupción que ha despertado al sistema
    //    XBeeInterrupt_handleBottomHalve();
}

/*...........................................................................*/

/**
 * Entering this method could mean that the transceiver is malfunctioning.
 * Xbee may be down or may have lost sync with his neighbor.
 * So, try to send a reset message to the transceiver and rejoin the mote.
 * A 100 ms delay is necessary to perform a full reset before send any command.
 */
void OnDsWdtWakeUp(void) {
    WDTCONbits.DS = 0;
    XBeeReset();
    Delay100TCYx(100);
    XBeeJoin();
}

/*...........................................................................*/
void ClearMclrFlags(void) {
    WDTCONbits.DS = 0;
    DSWAKELbits.DSMCLR = 0;
    DSCONLbits.RELEASE = 0;
}

void ClearDSWakeUpFlags(void) {
    WDTCONbits.DS = 0;
    DSWAKEHbits.DSINT0 = 0;
    DSCONLbits.RELEASE = 0; // permite reconfigurar los IO pins despues de despertar de un deepSleep
}

/*...........................................................................*/
void SleepModeOn(void) {
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    PowerSleep();
}

