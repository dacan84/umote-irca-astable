#include <pic18f26j50.h>
#include "clkctrl.h"

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

/******************************************************************************/

void operationFrequencyIntOscCtrl(uint8_t frequency) {

    // INTOSC drives clock directly
    if (frequency == F31Khz) {
        OSCTUNEbits.INTSRC = 1;
    }
    OSCCONbits.IRCF = frequency;
}