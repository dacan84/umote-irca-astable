#include "irca.h"
#include "../adc/include/averaged_adc.h"
#include <delays.h>

static void Irca1InitIO(void);
//static void SampleAndHoldReset(void);

// Init sensor struct and hw associated
void IrcaInit(void) {
    AdcInit(); 
    Irca1InitIO();
}

void IrcaMeasure(IrcAData* data) {
    //SampleAndHoldReset();
    AdcConvert(IRCA1_SENSE_AN_CH, &data->out);
    AdcConvert(IRCA1_REF_AN_CH, &data->ref);
    AdcConvert(IRCA1_TMP_AN_CH, &data->tmp);
}

static void Irca1InitIO(void) {
    IRCA1_SENSE_CNF = 0;    // IRCA sense as analog pin
    IRCA1_SENSE_DDR = 1;    // IRCA sense analog in
    IRCA1_REF_CNF = 0;      // IRCA ref as analog pin
    IRCA1_REF_DDR = 1;      // IRCA ref analog in
    IRCA1_TMP_CNF = 0;      // IRCA temperature analog pin
    IRCA1_TMP_DDR = 1;      // IRCA temperature as input
    IRCA1_HOLD_DDR = 0;     // IRCA sample and hold
    IRCA1_HOLD = 0;         // Initally low
}

void SampleAndHoldIrcaReset(void) {
   IRCA1_HOLD = 1; 
     // The sample time that Daniel have in his project is 1KHz The dalay should be around this period.
     //  delay = 1/1000; = 0.001 i.e. 1us.
     __delay_us(2);
    IRCA1_HOLD = 0; 
     __delay_us(2);
}

//TODO: ajustar estos tiempos, medida mas o menos ok.


// TODO: Quiza cambiarlo por la habilitación de la alimentación del astable.
void IrcaEnableLamp(void) {
    T1CONbits.TMR1ON = 1;
}

void IrcaDisableLamp(void) {
    T1CONbits.TMR1ON = 0;
}
