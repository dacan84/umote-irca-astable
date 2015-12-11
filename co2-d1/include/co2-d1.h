#ifndef CO2_D1_H
#define	CO2_D1_H

#include "../../bsp.h"

#define CO2D1_SENSE_AN_CH   10
#define CO2D1_REF_AN_CH     9

// Offset del sensor necesario para el cálculo
const uint16_t CO2OFFSET = 52; // DEPENDE DEL CADA SENSOR. 

typedef struct {
    uint16_t co2ref;
    uint16_t co2sense;
} Co2D1Data;

void Co2D1Init(void);

void Co2D1Measure(Co2D1Data* data);

#endif	/* CO2_D1_H */

