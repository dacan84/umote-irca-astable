/* 
 * File:   clkctrl.h
 * Author: Diego
 *
 * Created on 25 de septiembre de 2015, 10:24
 */

#ifndef CLKCTRL_H
#define	CLKCTRL_H

#include <stdint.h>
/******************************************************************************/
/* This function control the microcontoller  operation frequency while 
 * the device is run. The values change the OSCCON registister on this manner:
 * 
 *   F31Khz      0
 *   F125Khz     1
 *   F250Khz     2
 *   F500Khz     3
 *   F1Mhz       4
 *   F2Mhz       5
 *   F4Mhz       6
 *   F8Mhz       7
 */

#define     F31Khz      0
#define     F125Khz     1
#define     F250Khz     2
#define     F500Khz     3
#define     F1Mhz       4
#define     F2Mhz       5
#define     F4Mhz       6
#define     F8Mhz       7

void operationFrequencyIntOscCtrl (uint8_t frequency);


#endif	/* CLKCTRL_H */

