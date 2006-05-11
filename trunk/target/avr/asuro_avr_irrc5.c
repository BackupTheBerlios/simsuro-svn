/** @file 
 * 
 * AVR implementation of IR-RC5 decoding. Based on the c't-Bot version created 
 * by Benjamin Benz (bbe@heise.de).
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

#include "asuro.h"

#define AS_IR_SAMPLES_PER_BIT		8	///< 8 samples per bit
#define AS_IR_SAMPLES_PER_BIT_EARLY 6	///< edge not before the 6th sample
#define AS_IR_SAMPLES_PER_BIT_LATE 	10	///< edge after 10 samples at the latest

/** 
 * The start bit is only valid after 200 samples with unchanged edge. 
 * According to Benz, this should be 50x1.778ms, but since we have an 8-bit
 * counter for the samples, we are satisfied with about the half of it.
 */
#define AS_IR_PAUSE_SAMPLES			200 

#define AS_IR_PORT	PORTD	///< port D
#define AS_IR_DDR	DDRD	///< IO direction port D
#define AS_IR_PINR	PIND	///< input port D
#define AS_IR_PIN	PD0		///< IO pin on port D

volatile unsigned short	AS_ir_data = 0; ///< last completely read RC5 packet

/** @name private variables to the ISR */
//@{
char AS_ir_lastsample = 0; 			///< last read sample
unsigned char AS_ir_bittimer = 0;	///< call counter for AS_isr_irrc5()
unsigned short AS_ir_data_tmp = 0;	///< RC5 bit stream
char AS_ir_bitcount = 0;			///< number of read bits
//@}

/**
 * ISR for receiving IR-RC5 commands
 * 
 * called about every 222.2us
 */
void AS_isr_irrc5(void) {
	// read a sample
	char sample = 1;
	if (AS_IRRX_SAMPLE) sample = 0;

	// increase bittimer - the timer stops at 255
	if (AS_ir_bittimer < 255) AS_ir_bittimer++;

	if (AS_ir_lastsample != sample) {
		// edge detected
		// start bit?
		if (AS_ir_bitcount == 0) {
			if (sample && (AS_ir_bittimer > AS_IR_PAUSE_SAMPLES) ) {
				// save start bit
				AS_ir_data_tmp = 1;
				AS_ir_bitcount++;

			} else {
				// error
				AS_ir_data_tmp = 0;

			}

			// bittimer reset
			AS_ir_bittimer = 0;
			
		// bits 2..14: only consider edges within bits
		} else {
			if (AS_ir_bittimer >= AS_IR_SAMPLES_PER_BIT_EARLY) {
				if (AS_ir_bittimer <= AS_IR_SAMPLES_PER_BIT_LATE){
					// save bit
					AS_ir_data_tmp = (AS_ir_data_tmp << 1) | sample;
					AS_ir_bitcount++;

				} else {
					// too late, trop packet
					AS_ir_bitcount = 0;

				}
				
				// bittimer-reset
				AS_ir_bittimer = 0;
			}
		}
		
	} else {
		// no edge within bit time?
		if (AS_ir_bittimer > AS_IR_SAMPLES_PER_BIT_LATE) {
			// 14 bits read?
			if (AS_ir_bitcount == 14) {
				AS_ir_data = AS_ir_data_tmp;
			}
			
			// drop packet
			AS_ir_bitcount = 0;
		}
	}
	
	// save sample in sample buffer
	AS_ir_lastsample = sample;
}

/**
 * Read the last IR-RC5 code received. This will flush the input, thus
 * subsequent calls will return 0 or a new value.
 * 
 * @return Last IR RC5 code received
 */
inline unsigned short AS_Irrc5Read(void) {
	unsigned short rv = AS_ir_data;
	AS_ir_data = 0;
	return rv;
}
