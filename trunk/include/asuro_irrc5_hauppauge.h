/** @file
 * 
 * Special RC5 codes for the Hauppauge WinTV remote control.
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

#ifndef ASURO_IRRC5_HAUPPAUGE_H_
#define ASURO_IRRC5_HAUPPAUGE_H_

#include "asuro_irrc5.h"

#define AS_RC5_RCMASK_HAUPPAUGE	0x2000

#define AS_RC5_CODE_HAUPPAUGE_TV			AS_RC5_CODE_DISPLAY
#define AS_RC5_CODE_HAUPPAUGE_RADIO			AS_RC5_CODE_POWER
#define AS_RC5_CODE_HAUPPAUGE_FULLSCREEN	AS_RC5_CODE_GREEN
#define AS_RC5_CODE_HAUPPAUGE_SOURCE		AS_RC5_CODE_SELECT
#define AS_RC5_CODE_HAUPPAUGE_RESERVED		0x101e
#define AS_RC5_CODE_HAUPPAUGE_MINIMIZE		0x1026

#endif /*ASURO_IRRC5_HAUPPAUGE_H_*/
