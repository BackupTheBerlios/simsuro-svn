/** @file
 * 
 * General definitions for ASURO (eg pin assignments).
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

#ifndef ASURO_DEF_H_
#define ASURO_DEF_H_

#define TRUE		1	///< boolean TRUE
#define FALSE		0	///< boolean FALSE

#define AS_ON		1	///< general ON
#define AS_OFF		0	///< general OFF

#define AS_GREEN	1	///< status LED color green
#define AS_RED		2	///< status LED color red
#define AS_YELLOW	3	///< status LED color yellow

#define AS_LEFT		0	///< left motor
#define AS_RIGHT	1	///< right motor

/** @name LED ports */
//@{
#define AS_PB_LED_GREEN	(1 << PB0)	///< PB0: port for green status LED
#define AS_PD_LED_RED	(1 << PD2)	///< PD2: port for red status LED
#define AS_PD_LED_FRONT	(1 << PD6)	///< PD6: port for front LED
#define AS_PC_LED_LBACK	(1 << PC1)	///< PC1: port for left back LED
#define AS_PC_LED_RBACK	(1 << PC0)	///< PC0: port for right back LED
#define AS_PB_LED_IRTX	(1 << PB3)	///< PB3: port for IR transmitter LED
#define AS_PD_LED_ODO	(1 << PD7)	///< PD7: port for wheel IR-LEDs (for odometry)
//@}

/** @name Motor ports */
//@{
#define AS_DIR_FWD		(1 << PB5)					///< PB5/PD5: port for motor direction: rewind
#define AS_DIR_RWD		(1 << PB4)					///< PB4/PD4: port for motor direction: rewind
#define AS_DIR_FREE		(AS_DIR_FWD | AS_DIR_RWD)	///< no change to motor direction
#define AS_DIR_BREAK	0							///< stop motors
#define AS_PB_MTR_PWM	((1 << PB1) | (1 << PB2))	///< PB1, PB2: ports for pulse width modulation
//@}

/** @name LED control */
//@{
#define AS_LED_GREEN_ON		PORTB |=  AS_PB_LED_GREEN
#define AS_LED_GREEN_OFF	PORTB &= ~AS_PB_LED_GREEN
#define AS_LED_RED_ON		PORTD |=  AS_PD_LED_RED
#define AS_LED_RED_OFF		PORTD &= ~AS_PD_LED_RED
#define AS_LED_YELLOW_ON	{AS_LED_GREEN_ON; AS_LED_RED_ON;}
#define AS_LED_YELLOW_OFF	{AS_LED_GREEN_OFF; AS_LED_RED_OFF;}
#define AS_LED_FRONT_ON		PORTD |=  AS_PD_LED_FRONT
#define AS_LED_FRONT_OFF	PORTD &= ~AS_PD_LED_FRONT
#define AS_LED_RBACK_ON		PORTC |=  AS_PC_LED_RBACK	///< you have to be in AS_BACK_LED_MODE
#define AS_LED_RBACK_OFF	PORTC &= ~AS_PC_LED_RBACK	///< you have to be in AS_BACK_LED_MODE
#define AS_LED_LBACK_ON		PORTC |=  AS_PC_LED_LBACK	///< you have to be in AS_BACK_LED_MODE
#define AS_LED_LBACK_OFF	PORTC &= ~AS_PC_LED_LBACK	///< you have to be in AS_BACK_LED_MODE
#define AS_LED_ODO_ON		PORTD |=  AS_PD_LED_ODO		///< you have to be in AS_ODOMETRY_MODE
#define AS_LED_ODO_OFF		PORTD &= ~AS_PD_LED_ODO		///< you have to be in AS_ODOMETRY_MODE
//@}

/** @name Motors control */
//@{
#define AS_DIR_LEFT(dir)	PORTD = (PORTD & ~AS_DIR_FREE) | dir	///< set direction of left motor
#define AS_DIR_RIGHT(dir)	PORTB = (PORTB & ~AS_DIR_FREE) | dir	///< set direction of right motor
//@}

/** @name IO direction */
//@{
#define AS_BACK_LED_MODE	DDRC |= (AS_PC_LED_LBACK | AS_PC_LED_RBACK)		// output, no odometry
#define AS_ODOMETRY_MODE	DDRC &= ~(AS_PC_LED_LBACK | AS_PC_LED_RBACK)	// input, no back LEDs
//@}

/** @name Sensors */
//@{
#define AS_PD_SWITCHES	(1 << PD3)	///< PD3: port for switches
//@}

/** @name Sensor control */
//@{
#define AS_SENS_SWITCHES_MODE	DDRD |= AS_PD_SWITCHES		///< output, switches
#define AS_SENS_SWITCHES_ON		PORTD |= AS_PD_SWITCHES		///< switch sensor on
#define AS_SENS_SWITCHES_OFF	PORTD &= ~AS_PD_SWITCHES	///< switch sensor off
#define AS_SENS_SWITCH_1	(1 << 5)
#define AS_SENS_SWITCH_2	(1 << 4)
#define AS_SENS_SWITCH_3	(1 << 3)
#define AS_SENS_SWITCH_4	(1 << 2)
#define AS_SENS_SWITCH_5	(1 << 1)
#define AS_SENS_SWITCH_6	1
//@}

/** @name ADC ports for analogue sensors */
//@{
#define AS_MUX_SWITCHES		(1 << MUX2) 				///< ADC port for switches
#define AS_MUX_LINE_LEFT	((1 << MUX0) | (1 << MUX1))	///< ADC port for left line photo transistor
#define AS_MUX_LINE_RIGHT	(1 << MUX1)					///< ADC port for right line photo transistor
#define AS_MUX_ODO_LEFT		(1 << MUX0)					///< ADC port for left odometry IR photo transistor
#define AS_MUX_ODO_RIGHT	0							///< ADC port for right odometry IR photo transistor
//@}

/** @name A/D conversion control */
//@{
#define AS_ADC_START		ADCSRA |= (1 << ADSC)	///< start A/D conversion
#define AS_ADC_STOP			ADCSRA |= (1 << ADIF)	///< stop A/D conversion (clear finished flag)
#define AS_ADC_FINISHED		(ADCSRA & (1 << ADIF))	///< ADC finished
#define AS_ADC_VALUE		(ADCL + (ADCH << 8))	///< encoded analogue value
//@}

/** @name Others */
//@{
#define AS_PD_IRRX		(1 << PD0)			///< input port for IR receiver (IC2)
#define AS_IRRX_SAMPLE	(PIND & AS_PD_IRRX)	///< returns sample of current bit received by IC2
//@}

#endif /*ASURO_DEF_H_*/
