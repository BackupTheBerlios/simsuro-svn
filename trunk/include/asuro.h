/**@file 
 * 
 * Interface to ASURO's devices. The implentations of these are target-specific.
 * 
 * @author Denis Martin
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details. You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef ASURO_H_
#define ASURO_H_

#ifdef UNIX
#include "asuro_unix.h"
#endif

#ifdef AVR
#include "asuro_avr.h"
#endif

#include "asuro_defs.h"

/** @name Type definitions */
//@{
/**
 * User ISRs have to have this signature.
 */
typedef void (*AS_UserIsr)(void);
//@}

/** @name Global variables */
//@{
/**
 * Set to true, when one or more of the switches are pressed. Note that you
 * have to turn on the concerned interrupt using AS_SensSwitchesInterruptOn()
 */
extern volatile char AS_sensSwitched;

/**
 * Set to true if the interrupt for switches is enabled. If it is not enabled,
 * you may activate it by using AS_SensSwitchesInterruptOn().
 */
extern volatile char AS_sensSwitchesOn;

/**
 * User defined ISR for INT1 (switches). Assign a function to this global 
 * variable to get your own ISR called.
 */
extern volatile AS_UserIsr AS_UserIsrInterrupt1;
//@}

/** @name Main functions */
//@{
/**
 * Do some initialization stuff
 */
inline void AS_Init(void);

/**
 * Return the number of system clock ticks elapsed since system start. Remember
 * that it might overflow.
 * 
 * @return Number of system clock ticks
 */
inline unsigned long AS_GetClockTicks(void);

/**
 * Return the time in milliseconds elapsed since system start. Remember that it
 * might overflow.
 * 
 * @return System time in milliseconds
 */
inline unsigned long AS_GetSysTime(void);

/**
 * Halt execution for a given time in milliseconds. Note: a value of zero will
 * not return immediately as you might expect. Instead, the execution is halted
 * for over a minute!
 * 
 * @param time	Time in milliseconds to sleep
 */
void AS_Sleep(unsigned int time);

/**
 * Set status LED to the specified color. Note that you can also call 
 * AS_LED_GREEN_ON, AS_LED_GREEN_OFF, AS_LED_RED_ON, AS_LED_RED_OFF, 
 * AS_LED_YELLOW_ON and AS_LED_YELLOW_OFF directly.
 * 
 * @param color	Color (possible values: AS_GREEN, AS_RED, AS_YELLOW)
 */
inline void AS_StatusLED(unsigned char color);

/**
 * Set front LED on or off. Note that you can also call AS_LED_FRONT_ON and 
 * AS_LED_FRONT_OFF directly.
 * 
 * @param status	AS_ON or AS_OFF
 */
inline void AS_FrontLED(unsigned char status);

/**
 * Set back LEDs on or off. Note that you can also call AS_LED_RBACK_ON, 
 * AS_LED_RBACK_OFF, AS_LED_LBACK_ON and AS_LED_LBACK_OFF directly, but you have
 * to switch to AS_BACK_LED_MODE before.
 * 
 * @param left		Status for left back LED (AS_ON or AS_OFF)
 * @param right	Status for right back LED (AS_ON or AS_OFF)
 */
inline void AS_BackLED(unsigned char left, unsigned char right);

/**
 * Set speed of left and right motor. AS_MotorDir() before to specifiy the
 * direction.
 * 
 * @param left_speed	Speed of left motor (0..255)
 * @param right_speed	Speed of right motor (0..255)
 */
inline void AS_MotorSpeed(unsigned char left_speed, unsigned char right_speed);

/**
 * Set rotation direction of left and right motor. Possible values are
 * AS_DIR_FWD (forward), AS_DIR_RWD (backward), AS_DIR_BREAK (stop) and
 * AS_DIR_FREE (no change to direction).
 * 
 * @param left_dir	Direction for left motor.
 * @param right_dir	Direction for right motor.
 */
inline void AS_MotorDir(unsigned char left_dir, unsigned char right_dir);

/**
 * Send data via IR serial interface.
 * 
 * @param data		Pointer to data buffer to send.
 * @param length	Size of data in bytes.
 */
void AS_SerWrite(unsigned char *data, unsigned char length);

/**
 * Turn on interrupt for activity on switches. The user ISR assigned to 
 * AS_UserIsrInterrupt1 will be called if any of the switches was pushed.
 */
void AS_SensSwitchesInterruptOn(void);

/**
 * Disable interrupt for activity on switches.
 */
inline void AS_SensSwitchesInterruptOff(void);

/**
 * Read status of switches. The bits of the returned value represent the 
 * switches currently pressed. The mapping is the following:
 * 
 * bit0 = K6,
 * bit1 = K5,
 * bit2 = K4,
 * bit3 = K3,
 * bit4 = K2,
 * bit5 = K1
 * 
 * @return 	A value whose bits represent the switches currently pressed (see 
 * 			above)
 */
unsigned char AS_SensSwitchesRead(void);

//@}

#endif /*ASURO_H_*/
