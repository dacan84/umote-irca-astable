#include "sensor_proxy.h"
#include "sht/include/sht.h"
#include "adc/include/averaged_adc.h"
#include "co2-d1/include/co2-d1.h"
#include "irca/include/irca.h"
#include <delays.h>

static void PowerUpCO2Sensor(void);
static void PowerDownCO2Sensor(void);
static void PowerUpSHT11(void);
static void PowerDownSHT11(void);

ShtData shtData;
IrcAData ircAData;

void SensorProxyInit(void) {
    Sht11Init();
    IrcaInit();
}

void MeasureSensors(void) {
    SampleAndHoldIrcaReset();
    // SHT11 sequence
    PowerUpSHT11();
    Sht11Measure(&shtData);
    PowerDownSHT11();
    // IRCA1 sequence
    PowerUpCO2Sensor(); //TODO; esto igual sobra
    IrcaMeasure(&ircAData);
    //PowerDownCO2Sensor();
}

static void PowerUpCO2Sensor(void) {
    TRISBbits.TRISB2 = 0;
    PORTBbits.RB2 = 1;
}

static void PowerDownCO2Sensor(void) {
    PORTBbits.RB2 = 0;
}

static void PowerUpSHT11(void) {
    TRISAbits.TRISA5 = 0;
    PORTAbits.RA5 = 1;
}

static void PowerDownSHT11(void) {
    PORTAbits.RA5 = 0;
}
