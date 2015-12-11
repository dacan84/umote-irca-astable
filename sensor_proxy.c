#include "sensor_proxy.h"
#include "sht/include/sht.h"
#include "adc/include/averaged_adc.h"
#include "co2-d1/include/co2-d1.h"
#include <delays.h>

static void PowerUpCO2Sensor(void);
static void PowerDownCO2Sensor(void);
static void PowerUpSHT11(void);
static void PowerDownSHT11(void);

static void MeasureSHT11(void);

static void MeasureCO2(void);
static void DisableCO2(void);

ShtData shtData;
Co2D1Data co2d1Data;

void SensorProxyInit(void) {
    Sht11Init();
    PowerUpCO2Sensor();
    Co2D1Init();
}

void MeasureSensors(void) {
    // SHT11 sequence
    PowerUpSHT11();
    Sht11Measure(&shtData);
    PowerDownSHT11();
    // CO2D1 sequence
    PowerUpCO2Sensor();
    Co2D1Measure(&co2d1Data);
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
