#include "averaged_adc.h"
#include "include/co2-d1.h"

static void Co2D1InitIO(void);

void Co2D1Init() {
    AdcInit();
    Co2D1InitIO();
}

void Co2D1Measure(Co2D1Data* data) {
    AdcConvert(CO2D1_SENSE_AN_CH, &data->co2sense);
    AdcConvert(CO2D1_REF_AN_CH, &data->co2ref);
}

static void Co2D1InitIO(void) {
    ANCON1bits.PCFG10 = 0;
    TRISBbits.TRISB1 = 1;
    ANCON1bits.PCFG9 = 0;
    TRISBbits.TRISB3 = 1;
}