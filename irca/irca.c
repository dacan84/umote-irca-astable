#include "irca.h"
#include "../adc/include/averaged_adc.h"
#include <delays.h>

static void Irca1InitIO(void);
static void SampleAndHoldInit(void);
static void SampleAndHoldReset(void);

// Init sensor struct and hw associated
void IrcaInit(void) {
    AdcInit(); //TODO: mirar si tengo que sacar esta función de aquí.
    Irca1InitIO();
}

void IrcaMeasure(IrcAData* data) {
    SampleAndHoldReset();
    AdcConvert(IRCA1_SENSE_AN_CH, &data->out);
    AdcConvert(IRCA1_REF_AN_CH, &data->ref);
    AdcConvert(IRCA1_TMP_AN_CH, &data->tmp);
}

static void Irca1InitIO(void) {
    IRCA1_SENSE_CNF = 0; // IRCA sense as analog pin
    IRCA1_SENSE_DDR = 1; // IRCA sense analog in
    IRCA1_REF_CNF = 0; // IRCA ref as analog pin
    IRCA1_REF_DDR = 1; // IRCA ref analog in
    IRCA1_TMP_CNF = 0; // IRCA temperature analog pin
    IRCA1_TMP_DDR = 1; // IRCA temperature as input
    IRCA1_HOLD_DDR_DDR = 0; // IRCA sample and hold
    IRCA1_HOLD = 0; // Initally low
}

static void SampleAndHoldInit(void) {
    //TODo: inicializar pin para el circuito de muestreo y retención

}

static void ResetSampleAndHold(void) {
     IRCA1_HOLD = 1; // Initally low
    //TODO : INSERTAR DELAY
     IRCA1_HOLD = 0; // Initally low
}


// TODO: Quiza cambiarlo por la habilitación de la alimentación del astable.
void IrcaEnableLamp(void) {
    T1CONbits.TMR1ON = 1;
}

void IrcaDisableLamp(void) {
    T1CONbits.TMR1ON = 0;
}
