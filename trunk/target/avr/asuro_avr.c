/** @file 
 * 
 * AVR dependent part of interface to ASURO's devices
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
#include "asuro_irrc5.h"

/**
 * User ISR for INT1 (switches).
 */
volatile AS_UserIsr AS_UserIsrInterrupt1 = 0;

/**
 * Intermediate counter for system clock ticks. Don't read it directly, but 
 * use AS_GetClockTicks() or AS_GetSysTime() instead.
 */
volatile unsigned char AS_count36kHz = 0;

/**
 * Counter for system clock ticks. Don't read it directly, but use 
 * AS_GetClockTicks() or AS_GetSysTime() instead.
 */
volatile unsigned long AS_clockTicks = 0;

/**
 * Enable/disable IR-RC5 decoding in ISR. Will be disabled during read/write on
 * IR serial interface.
 */
volatile unsigned char AS_irrc5DecodeEnabled = 1;

/**
 * Set to true if the interrupt for switches is enabled. If it is not enabled,
 * you may activate it by using AS_SensSwitchesInterruptOn().
 */
volatile char AS_sensSwitchesOn = 0;

/**
 * Set to true, when one or more of the switches are pressed. Note that you
 * have to turn on the concerned interrupt using AS_SensSwitchesInterruptOn().
 */
volatile char AS_sensSwitched = 0;

/** @name Interrupt handlers **************************************************/
//@{

/**
 * ISR for timer2 overflow. timer2 is used as a 72kHz counter for IR 
 * communication. While the signal SIG_OUTPUT_COMPARE2 would be triggered every 
 * 1/72k seconds, this ISR is called only every 1/36k seconds.
 */
SIGNAL(SIG_OVERFLOW2)
{
	TCNT2 += 0x25; 	// next compare match in (0x91 - 0x25) = 0x6C 8MHz ticks
					// this causes the compare match to occur every 1/72kHz seconds
					// (needed for IR modulation)
	
	AS_count36kHz++;
	if (!AS_count36kHz) AS_clockTicks++; // count overflows
	
	if (AS_irrc5DecodeEnabled && !(AS_count36kHz % 8)) 
		AS_isr_irrc5(); // called about every 222.2us
	
}

/**
 * ISR for switches. The interrupt is disabled here, so you have to reactivate
 * it manually using AS_SensSwitchesInterruptOn().
 */
SIGNAL(SIG_INTERRUPT1)
{
	AS_sensSwitched = 1;
	AS_SensSwitchesInterruptOff();
	
	// call user ISR
	if (AS_UserIsrInterrupt1 != 0) AS_UserIsrInterrupt1();
}

//@}

/** @name Functions ***********************************************************/
//@{

/**
 * Halt execution for a given time of 36kHz ticks.
 * 
 * @param ticks	Time to sleep in 36kHz ticks (0..255)
 */
inline void AS_Avr_Sleep(unsigned char ticks)
{
	unsigned char tick = AS_count36kHz + ticks;
	while (tick != AS_count36kHz);
}

/**
 * Do some initialization stuff.
 */
inline void AS_Init()
{
	// serial interface programmed in boot routine and already running
	
	// prepare 72kHz oscillator for IR communication
	TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM20) | (1 << COM21) | (1 << CS20);
	OCR2  = 0x91; // (0xFF - 0x91) = 0x6E = 8MHz/72kHz (oscillator freq. divided by 2x IR modulation freq.)
	TIMSK |= (1 << TOIE2); // unmask timer2/overflow interrupt
	
	// set RS232 communication parameters
	UCSRA = 0x00;
	UCSRB = 0x00;
	UCSRC = 0x86; // no parity | 1 stop bit | 8 data bits
	UBRRL = 0xCF; // 2400bps @ 8.00MHz
	
	// set output ports
	DDRB = AS_DIR_FWD | AS_DIR_RWD | AS_PB_MTR_PWM | AS_PB_LED_IRTX | AS_PB_LED_GREEN;
	DDRD = AS_DIR_FWD | AS_DIR_RWD | AS_PD_LED_FRONT | AS_PD_LED_ODO | AS_PD_LED_RED;
	
	// for PWM (8-Bit PWM) on OC1A & OC1B
	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	// tmr1 running on MCU clock/8 
	TCCR1B = (1 << CS11);
	
	// A/D Conversion
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // clk/64 
	
	AS_BACK_LED_MODE;
	AS_LED_LBACK_ON; AS_LED_RBACK_ON;
	AS_LED_LBACK_OFF; AS_LED_RBACK_OFF;	
	AS_LED_ODO_OFF;
	AS_LED_FRONT_OFF;
	AS_LED_GREEN_OFF;
	AS_LED_RED_OFF;
	
	AS_MotorDir(AS_DIR_FWD, AS_DIR_FWD);
	AS_MotorSpeed(0,0);
	AS_LED_GREEN_ON;
	sei();
}

/**
 * Return the number of system clock ticks elapsed since system start. Remember
 * that it might overflow.
 * 
 * @return Number of system clock ticks
 */
inline unsigned long AS_GetClockTicks()
{
	return (AS_clockTicks<<8) + AS_count36kHz;
}

/**
 * Return the time in milliseconds elapsed since system start. Remember that it
 * might overflow.
 * 
 * @return System time in milliseconds
 */
inline unsigned long AS_GetSysTime()
{
	return ((AS_clockTicks/36)<<8) + AS_count36kHz/36;
}

/**
 * Halt execution for a given time. Note: a value of zero will not return 
 * immediately as you might expect. Instead, the execution is halted for
 * over a minute!
 * 
 * @param time	Time to sleep in milliseconds
 */
void AS_Sleep(unsigned int time)
{
	do {
		unsigned char tick = AS_count36kHz + 36;
		while (tick != AS_count36kHz);
		time--;
	} while (time);
}

/**
 * Set status LED to the specified color. Note that you can also call 
 * AS_LED_GREEN_ON, AS_LED_GREEN_OFF, AS_LED_RED_ON, AS_LED_RED_OFF, 
 * AS_LED_YELLOW_ON and AS_LED_YELLOW_OFF directly.
 * 
 * @params color	Color (possible values: AS_GREEN, AS_RED, AS_YELLOW)
 */
inline void AS_StatusLED(unsigned char color)
{
	if (color & AS_GREEN) AS_LED_GREEN_ON; else AS_LED_GREEN_OFF;
	if (color & AS_RED)   AS_LED_RED_ON;   else AS_LED_RED_OFF;
}

/**
 * Set front LED on or off. Note that you can also call AS_LED_FRONT_ON and 
 * AS_LED_FRONT_OFF directly.
 * 
 * @param status	AS_ON or AS_OFF
 */
inline void AS_FrontLED(unsigned char status)
{
	if (status) AS_LED_FRONT_ON; else AS_LED_FRONT_OFF;
}

/**
 * Set back LEDs on or off. Note that you can also call AS_LED_RBACK_ON, 
 * AS_LED_RBACK_OFF, AS_LED_LBACK_ON and AS_LED_LBACK_OFF directly, but you have
 * to switch to AS_BACK_LED_MODE before.
 * 
 * @params left		Status for left back LED (AS_ON or AS_OFF)
 * @params right	Status for right back LED (AS_ON or AS_OFF)
 */
inline void AS_BackLED(unsigned char left, unsigned char right)
{
	if (left || right) {
		AS_LED_ODO_OFF;
		AS_BACK_LED_MODE;
		
	}
	
	if (left)  AS_LED_LBACK_ON; else AS_LED_LBACK_OFF;
	if (right) AS_LED_RBACK_ON; else AS_LED_RBACK_OFF;
}

/**
 * Set speed of left and right motor. Use AS_MotorDir() before to specifiy the
 * direction.
 * 
 * @param left_speed	Speed of left motor (0..255)
 * @param right_speed	Speed of right motor (0..255)
 */
inline void AS_MotorSpeed(unsigned char left_speed, unsigned char right_speed)
{
	OCR1A = left_speed;
	OCR1B = right_speed;
}

/**
 * Set rotation direction of left and right motor. Possible values are
 * AS_DIR_FWD (forward), AS_DIR_RWD (backward), AS_DIR_BREAK (stop) and
 * AS_DIR_FREE (no change to direction).
 * 
 * @param left_dir	Direction for left motor.
 * @param right_dir	Direction for right motor.
 */
inline void AS_MotorDir(unsigned char left_dir, unsigned char right_dir)
{
	AS_DIR_LEFT(left_dir);
	AS_DIR_RIGHT(right_dir);
}

/**
 * Send data via IR serial interface. IR-RC5 decoding will be disabled during
 * write.
 * 
 * @param data		Pointer to data buffer to send.
 * @param length	Size of data in bytes.
 */
void AS_SerWrite(unsigned char *data, unsigned char length)
{
	unsigned char i = 0;
	unsigned char irrc5Decode = AS_irrc5DecodeEnabled;
	AS_irrc5DecodeEnabled = 0;
	
	UCSRB = 0x08; // enable transmitter
	while (length > 0) {
		if (UCSRA & 0x20) { // wait for empty transmit buffer
			UDR = data[i++];
			length --;
		}
	}
	while (!(UCSRA & 0x40)); 
	for (i = 0; i < 0xFE; i++)
		for(length = 0; length < 0xFE; length++);
		
	AS_irrc5DecodeEnabled = irrc5Decode;
}

/**
 * Turn on interrupt for activity on switches. The user ISR assigned to 
 * AS_UserIsrInterrupt1 will be called if any of the switches was pushed.
 */
void AS_SensSwitchesInterruptOn(void)
{
	AS_sensSwitched = 0;
	AS_SENS_SWITCHES_OFF;
	DDRD &= ~AS_PD_SWITCHES; // switches as input
	MCUCR &= ~((1 << ISC11) | (1 << ISC10)); // low level interrupt generation
	GICR |= (1 << INT1); // enable external interrupt 1
}

/**
 * Disable interrupt for activity on switches.
 */
inline void AS_SensSwitchesInterruptOff(void)
{
	GICR &= ~(1 << INT1); // disable external interrupt 1
}

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
unsigned char AS_SensSwitchesRead(void)
{
	unsigned int value;
	
	AS_SENS_SWITCHES_MODE;	// output for switches
	AS_SENS_SWITCHES_ON;	// output 'high' for measurement
	
	ADMUX = (1 << REFS0) | AS_MUX_SWITCHES;	// AVCC reference with external capacitor
	AS_Avr_Sleep(10);
	
	AS_ADC_START;				// start A/D conversion
	while (!AS_ADC_FINISHED);	// wait for ADC to finish
	AS_ADC_STOP;				// stop A/D conversion (clear finished flag)
	value = AS_ADC_VALUE;
	
	AS_SENS_SWITCHES_OFF;
	
	// if no switch is pressed, the ADC value will be around 1024, and if all 
	// are pressed it is around 512
	return (char) (((1024000000UL/((unsigned long) value) - 1000000UL)*63UL + 500000UL) / 1000000UL);
}

//@}
