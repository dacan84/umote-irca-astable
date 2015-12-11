#ifndef BSP_H
#define	BSP_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <GenericTypeDefs.h>

#define NO_MOBILE   0
#define MOBILE      1

#define SHT_ID      'S'
#define IRCA_ID     'I'
#define CO2D1_ID    'C'
#define BMP085      'B'

/* DEEP SLEEP WAKE UP SOURCES */
#define ON_MCLR         RCONbits.TO && !RCONbits.PD
#define ON_DS_MCLR      WDTCONbits.DS && DSWAKELbits.DSMCLR
#define ON_DS_WDT       WDTCONbits.DS && DSWAKELbits.DSWDT
#define ON_DS_ULP       WDTCONbits.DS && DSWAKELbits.DSULP 
#define ON_DS_RTC_ALARM WDTCONbits.DS && DSWAKELbits.DSRTC
#define POWER_UP        !WDTCONbits.DS
#define DS_FAULT        DSWAKELbits.DSFLT

#define DEEP_SLEEP_WAKE_UP WDTCONbits.Ds == 1


// Defines based on previous selection
#define XBEE_ON_SLEEP_FLAG          INTCONbits.INT0IF
#define XBEE_ON_SLEEP_CLEAR_FLAG()  XBEE_ON_SLEEP_FLAG = 0
#define XBEE_ON_DS_AWAKE	    WDTCONbits.DS && DSWAKEHbits.DSINT0

void BspInit(void);
void UnUsedPeriphericalDisable (void);
void DeepSleep(void);

#endif	/* BSP_H */

