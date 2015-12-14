#ifndef IRCA_H
#define	IRCA_H

#include "../bsp.h"

#define IRCA1_SENSE_AN_CH         10
#define IRCA1_SENSE_CNF           ANCON1bits.PCFG10   /* AN10 config*/
#define IRCA1_SENSE_DDR           TRISBbits.TRISB1    /* AN10, PINB1 as input */

#define IRCA1_TMP_AN_CH         11
#define IRCA1_TMP_CNF           ANCON1bits.PCFG11   /* AN11 config */
#define IRCA1_TMP_DDR           TRISCbits.TRISC2    /* AN11, PINC2 as input */

//TODO: mirar cual es el pin al que se conecta la medida del ref.
#define IRCA1_REF_AN_CH         10
#define IRCA1_REF_CNF           ANCON1bits.PCFG10   /* AN10 config*/
#define IRCA1_REF_DDR           TRISBbits.TRISB1    /* LMP91051 output */

/* PWM OUTPUT CONFIGURATION FOR VPULSE */
#define IRCA1_HOLD_DDR         TRISCbits.TRISC0    /* Sample & Hold reset */
#define IRCA1_HOLD             LATCbits.LATC0      /* Sample & Hold reset */


/*...........................................................................*/
/* Class IrcA1Data sensor data */
typedef struct IrcAData IrcAData;

struct IrcAData {
    uint16_t out;
    uint16_t tmp;
    uint16_t ref;
};

void IrcaInit(void);

void IrcaMeasure(IrcAData* data);

void IrcaDisableLamp(void);

void IrcaEnableLamp(void);

#endif	/* IRCA_H */

