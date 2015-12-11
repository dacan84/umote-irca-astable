/* 
 * File:   opController.h
 * Author: Diegol
 *
 * Created on 5 de octubre de 2015, 11:25
 */

#ifndef OPCONTROLLER_H
#define	OPCONTROLLER_H

/*...........................................................................*/
void OnPowerUp(void); 
/*...........................................................................*/

/* On reset push, join xbee */
void OnMclr(void);
/*...........................................................................*/
void OnWakeUp(void);
void OnDsWdtWakeUp(void);
/*...........................................................................*/
void ClearMclrFlags(void);
void ClearDSWakeUpFlags(void);
/*...........................................................................*/
void SleepModeOn(void);

#endif	/* OPCONTROLLER_H */

