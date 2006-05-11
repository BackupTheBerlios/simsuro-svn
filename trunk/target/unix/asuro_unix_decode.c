/**@file 
 * 
 * Decode simulated IO vector.
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
 
#include "asuro_defs.h"
#include "asuro_unix.h"
#include "asuro_unix_decode.h"

#include "stdio.h"

extern volatile double AS_unix_simTime;

/**
 * Evaluate state of IO vector
 */
void AS_unix_decode() {
	char leds[8];
	
	// status LED
	if (PORTB & AS_PB_LED_GREEN) {
		if (PORTD & AS_PD_LED_RED) {
			leds[0] = 'Y'; // yellow
			
		} else {
			leds[0] = 'G'; // green
			
		}
		
	} else if (PORTD & AS_PD_LED_RED) {
		leds[0] = 'R'; // red
		
	} else {
		leds[0] = '0'; // off
		
	}
	
	// front and back LEDs
	leds[1] = PORTD & AS_PD_LED_FRONT ? '1' : '0';
	leds[2] = PORTC & AS_PC_LED_LBACK ? '1' : '0';
	leds[3] = PORTC & AS_PC_LED_RBACK ? '1' : '0';
	leds[4] = '-';
	
	// odometry and IR LEDs
	leds[5] = PORTD & AS_PD_LED_ODO ? '1' : '0';
	leds[6] = PORTB & AS_PB_LED_IRTX ? '1' : '0';
	
	leds[7] = '\0';
	
	fprintf(stderr, "%6.2f LD %s\r", AS_unix_simTime, leds);
	
}
