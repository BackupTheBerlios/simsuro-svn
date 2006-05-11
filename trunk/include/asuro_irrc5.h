/** @file
 * 
 * General RC5 codes for remote controls.
 * 
 * For an explanation on how RC5 works, you may have a look on
 * http://www.sprut.de/electronic/ir/rc5.htm (in german, though).
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

#ifndef ASURO_IRRC5_H_
#define ASURO_IRRC5_H_

#ifdef AVR
#include "asuro_avr_irrc5.h"
#endif

#define AS_RC5_START_MASK	0x2000
#define AS_RC5_TOGGLE_MASK	0x0800
#define AS_RC5_ADDRESS_MASK	0x07c0
#define AS_RC5_COMMAND_MASK	0x103f

/** @name Common remote control button codes */
//@{
#define AS_RC5_CODE_0		0x1000
#define AS_RC5_CODE_1		0x1001
#define AS_RC5_CODE_2		0x1002
#define AS_RC5_CODE_3		0x1003
#define AS_RC5_CODE_4		0x1004
#define AS_RC5_CODE_5		0x1005
#define AS_RC5_CODE_6		0x1006
#define AS_RC5_CODE_7		0x1007
#define AS_RC5_CODE_8		0x1008
#define AS_RC5_CODE_9		0x1009

#define AS_RC5_CODE_POWER	0x100c
#define AS_RC5_CODE_MUTE	0x100d
#define AS_RC5_CODE_GREEN	0x102e
#define AS_RC5_CODE_YELLOW	0x1038
#define AS_RC5_CODE_BLUE	0x1029
#define AS_RC5_CODE_DISPLAY	0x100f

#define AS_RC5_CODE_VOLUP	0x1010	///< volume +
#define AS_RC5_CODE_VOLDOWN	0x1011	///< volume -
#define AS_RC5_CODE_CHUP	0x1020	///< channel +
#define AS_RC5_CODE_CHDOWN	0x1021	///< channel -
#define AS_RC5_CODE_SELECT	0x1022	///< source selection
//@}

/**
 * Read the last RC5 code that was successfully received. Note that the value is
 * reset upon reading and that subsequent calls may return 0 or other values.
 * 
 * @return The last valid RC5 code.
 */
inline unsigned short AS_Irrc5Read(void);

#endif /*ASURO_IRRC5_H_*/
