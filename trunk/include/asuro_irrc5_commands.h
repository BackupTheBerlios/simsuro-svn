/** @file
 * 
 * Assignments between RC5 codes and ASURO control commands.
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

#ifndef ASURO_IRRC5_COMMANDS_H_
#define ASURO_IRRC5_COMMANDS_H_

#include "asuro_irrc5.h"


// which remote control to use?
#define AS_RC5_HAUPPAUGE


#ifdef AS_RC5_HAUPPAUGE
/** @name RC5 code/command mappings for Hauppauge WinTV remote control */
//@{
#include "asuro_irrc5_hauppauge.h"

#define AS_RC5_RCMASK			AS_RC5_RCMASK_HAUPPAUGE				///< RC dependend mask

#define AS_RC5_CC_STOP			AS_RC5_CODE_HAUPPAUGE_FULLSCREEN	///< emergency stop
#define AS_RC5_CC_FWD			AS_RC5_CODE_CHUP					///< go forward
#define AS_RC5_CC_RWD			AS_RC5_CODE_CHDOWN					///< go backward
#define AS_RC5_CC_RIGHT			AS_RC5_CODE_VOLUP					///< turn right
#define AS_RC5_CC_LEFT			AS_RC5_CODE_VOLDOWN					///< turn left
#define AS_RC5_CC_STATUS_LED	AS_RC5_CODE_HAUPPAUGE_TV			///< toggle status LED
#define AS_RC5_CC_FRONT_LED		AS_RC5_CODE_1						///< toggle front LED
#define AS_RC5_CC_LBACK_LED		AS_RC5_CODE_2						///< toggle left back LED
#define AS_RC5_CC_RBACK_LED		AS_RC5_CODE_3						///< toggle right back LED
//@}
#endif // AS_RC5_HAUPPAUGE


#endif /*ASURO_IRRC5_COMMANDS_H_*/
