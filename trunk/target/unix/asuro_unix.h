/**@file 
 * 
 * This part attempts to simulate the ATmega8 pin port interface under UNIX.
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

#ifndef ASURO_UNIX_H_
#define ASURO_UNIX_H_

unsigned char AS_unix_ioVector[256];

int AS_unix_prepareIo(int io_addr);

#define sei()	{}
#define cli()	{}

#define SIGNAL(signame) \
	void signame (void)

// the following part comes from avr-gcc package

#define _VECTOR(N) __vector_ ## N

// a little tricky...
#define _SFR_IO8(io_addr)	AS_unix_ioVector[AS_unix_prepareIo(io_addr)]
#define _SFR_IO16(io_addr)	AS_unix_ioVector[AS_unix_prepareIo(io_addr)]

/* I/O registers */

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define TWBR	_SFR_IO8(0x00)
#define TWSR	_SFR_IO8(0x01)
#define TWAR	_SFR_IO8(0x02)
#define TWDR	_SFR_IO8(0x03)

/* ADC */
#define ADCW	_SFR_IO16(0x04)
#define ADC		_SFR_IO16(0x04)
#define ADCL	_SFR_IO8(0x04)
#define ADCH	_SFR_IO8(0x05)
#define ADCSR	_SFR_IO8(0x06)
#define ADCSRA	_SFR_IO8(0x06)  /* Changed in 2486H-AVR-09/02 */
#define ADMUX	_SFR_IO8(0x07)

/* analog comparator */
#define ACSR	_SFR_IO8(0x08)

/* USART */
#define UBRRL	_SFR_IO8(0x09)
#define UCSRB	_SFR_IO8(0x0A)
#define UCSRA	_SFR_IO8(0x0B)
#define UDR		_SFR_IO8(0x0C)

/* SPI */
#define SPCR	_SFR_IO8(0x0D)
#define SPSR	_SFR_IO8(0x0E)
#define SPDR	_SFR_IO8(0x0F)

/* Port D */
#define PIND	_SFR_IO8(0x10)
#define DDRD	_SFR_IO8(0x11)
#define PORTD	_SFR_IO8(0x12)

/* Port C */
#define PINC	_SFR_IO8(0x13)
#define DDRC	_SFR_IO8(0x14)
#define PORTC	_SFR_IO8(0x15)

/* Port B */
#define PINB	_SFR_IO8(0x16)
#define DDRB	_SFR_IO8(0x17)
#define PORTB	_SFR_IO8(0x18)

/* 0x1C..0x1F EEPROM */

#define UCSRC	_SFR_IO8(0x20)
#define UBRRH	_SFR_IO8(0x20)

#define WDTCR	_SFR_IO8(0x21)
#define ASSR	_SFR_IO8(0x22)

/* Timer 2 */
#define OCR2	_SFR_IO8(0x23)
#define TCNT2	_SFR_IO8(0x24)
#define TCCR2	_SFR_IO8(0x25)

/* Timer 1 */
#define ICR1	_SFR_IO16(0x26)
#define ICR1L	_SFR_IO8(0x26)
#define ICR1H	_SFR_IO8(0x27)
#define OCR1B	_SFR_IO16(0x28)
#define OCR1BL	_SFR_IO8(0x28)
#define OCR1BH	_SFR_IO8(0x29)
#define OCR1A	_SFR_IO16(0x2A)
#define OCR1AL	_SFR_IO8(0x2A)
#define OCR1AH	_SFR_IO8(0x2B)
#define TCNT1	_SFR_IO16(0x2C)
#define TCNT1L	_SFR_IO8(0x2C)
#define TCNT1H	_SFR_IO8(0x2D)
#define TCCR1B	_SFR_IO8(0x2E)
#define TCCR1A	_SFR_IO8(0x2F)

#define SFIOR	_SFR_IO8(0x30)

#define OSCCAL	_SFR_IO8(0x31)

/* Timer 0 */
#define TCNT0	_SFR_IO8(0x32)
#define TCCR0	_SFR_IO8(0x33)

#define MCUCSR	_SFR_IO8(0x34)
#define MCUCR	_SFR_IO8(0x35)

#define TWCR	_SFR_IO8(0x36)

#define SPMCR	_SFR_IO8(0x37)

#define TIFR	_SFR_IO8(0x38)
#define TIMSK	_SFR_IO8(0x39)

#define GIFR	_SFR_IO8(0x3A)
#define GIMSK	_SFR_IO8(0x3B)
#define GICR	_SFR_IO8(0x3B)   /* Changed in 2486H-AVR-09/02 */

/* 0x3C reserved (OCR0?) */

/* 0x3D..0x3E SP */

/* 0x3F SREG */

/* Interrupt vectors */

#define SIG_INTERRUPT0		_VECTOR(1)
#define SIG_INTERRUPT1		_VECTOR(2)
#define SIG_OUTPUT_COMPARE2	_VECTOR(3)
#define SIG_OVERFLOW2		_VECTOR(4)
#define SIG_INPUT_CAPTURE1	_VECTOR(5)
#define SIG_OUTPUT_COMPARE1A	_VECTOR(6)
#define SIG_OUTPUT_COMPARE1B	_VECTOR(7)
#define SIG_OVERFLOW1		_VECTOR(8)
#define SIG_OVERFLOW0		_VECTOR(9)
#define SIG_SPI			_VECTOR(10)
#define SIG_UART_RECV		_VECTOR(11)
#define SIG_UART_DATA		_VECTOR(12)
#define SIG_UART_TRANS		_VECTOR(13)
#define SIG_ADC			_VECTOR(14)
#define SIG_EEPROM_READY	_VECTOR(15)
#define SIG_COMPARATOR		_VECTOR(16)
#define SIG_2WIRE_SERIAL	_VECTOR(17)
#define SIG_SPM_READY		_VECTOR(18)

#define _VECTORS_SIZE 38

/* Bit numbers */

/* GIMSK / GICR */
#define INT1	7
#define INT0	6
#define IVSEL	1
#define IVCE	0

/* GIFR */
#define INTF1	7
#define INTF0	6

/* TIMSK */
#define OCIE2	7
#define TOIE2	6
#define TICIE1	5
#define OCIE1A	4
#define OCIE1B	3
#define TOIE1	2
/* bit 1 reserved (OCIE0?) */
#define TOIE0	0

/* TIFR */
#define OCF2	7
#define TOV2	6
#define ICF1	5
#define OCF1A	4
#define OCF1B	3
#define TOV1	2
/* bit 1 reserved (OCF0?) */
#define TOV0	0

/* SPMCR */
#define SPMIE	7
#define RWWSB	6
/* bit 5 reserved */
#define RWWSRE	4
#define BLBSET	3
#define PGWRT	2
#define PGERS	1
#define SPMEN	0

/* TWCR */
#define TWINT	7
#define TWEA	6
#define TWSTA	5
#define TWSTO	4
#define TWWC	3
#define TWEN	2
/* bit 1 reserved (TWI_TST?) */
#define TWIE	0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE	0

/* TWSR */
#define TWS7	7
#define TWS6	6
#define TWS5	5
#define TWS4	4
#define TWS3	3
/* bit 2 reserved */
#define TWPS1	1
#define TWPS0	0

/* MCUCR */
#define SE	7
#define SM2	6
#define SM1	5
#define SM0	4
#define ISC11	3
#define ISC10	2
#define ISC01	1
#define ISC00	0

/* MCUCSR */
/* bits 7-4 reserved */
#define WDRF	3
#define BORF	2
#define EXTRF	1
#define PORF	0

/* SFIOR */
/* bits 7-5 reserved */
#define ADHSM	4
#define ACME	3
#define PUD	2
#define PSR2	1
#define PSR10	0

/* TCCR0 */
/* bits 7-3 reserved */
#define CS02	2
#define CS01	1
#define CS00	0

/* TCCR2 */
#define FOC2	7
#define WGM20	6
#define COM21	5
#define COM20	4
#define WGM21	3
#define CS22	2
#define CS21	1
#define CS20	0

/* ASSR */
/* bits 7-4 reserved */
#define AS2	3
#define TCN2UB	2
#define OCR2UB	1
#define TCR2UB	0

/* TCCR1A */
#define COM1A1	7
#define COM1A0	6
#define COM1B1	5
#define COM1B0	4
#define FOC1A	3
#define FOC1B	2
#define WGM11	1
#define WGM10	0

/* TCCR1B */
#define ICNC1	7
#define ICES1	6
/* bit 5 reserved */
#define WGM13	4
#define WGM12	3
#define CS12	2
#define CS11	1
#define CS10	0

/* WDTCR */
/* bits 7-5 reserved */
#define WDCE	4
#define WDE	3
#define WDP2	2
#define WDP1	1
#define WDP0	0

/* UBRRH */
#define URSEL	7

/* UCSRC */
#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0

/* PORTB */
#define PB7	7
#define PB6	6
#define PB5	5
#define PB4	4
#define PB3	3
#define PB2	2
#define PB1	1
#define PB0	0

/* DDRB */
#define DDB7	7
#define DDB6	6
#define DDB5	5
#define DDB4	4
#define DDB3	3
#define DDB2	2
#define DDB1	1
#define DDB0	0

/* PINB */
#define PINB7	7
#define PINB6	6
#define PINB5	5
#define PINB4	4
#define PINB3	3
#define PINB2	2
#define PINB1	1
#define PINB0	0

/* PORTC */
#define PC6	 6
#define PC5	 5
#define PC4	 4
#define PC3	 3
#define PC2	 2
#define PC1	 1
#define PC0	 0

/* DDRC */
#define DDC6	6
#define DDC5	5
#define DDC4	4
#define DDC3	3
#define DDC2	2
#define DDC1	1
#define DDC0	0

/* PINC */
#define PINC6	6
#define PINC5	5
#define PINC4	4
#define PINC3	3
#define PINC2	2
#define PINC1	1
#define PINC0	0

/* PORTD */
#define PD7	 7
#define PD6	 6
#define PD5	 5
#define PD4	 4
#define PD3	 3
#define PD2	 2
#define PD1	 1
#define PD0	 0

/* DDRD */
#define DDD7	7
#define DDD6	6
#define DDD5	5
#define DDD4	4
#define DDD3	3
#define DDD2	2
#define DDD1	1
#define DDD0	0

/* PIND */
#define PIND7	7
#define PIND6	6
#define PIND5	5
#define PIND4	4
#define PIND3	3
#define PIND2	2
#define PIND1	1
#define PIND0	0

/* SPSR */
#define SPIF	7
#define WCOL	6
#define SPI2X	0

/* SPCR */
#define SPIE	7
#define SPE	6
#define DORD	5
#define MSTR	4
#define CPOL	3
#define CPHA	2
#define SPR1	1
#define SPR0	0

/* UCSRA */
#define RXC	7
#define TXC	6
#define UDRE	5
#define FE	4
#define DOR	3
#define PE	2
#define U2X	1
#define MPCM	0

/* UCSRB */
#define RXCIE	7
#define TXCIE	6
#define UDRIE	5
#define RXEN	4
#define	TXEN	3
#define UCSZ2	2
#define RXB8	1
#define TXB8	0

/* ACSR */
#define ACD	7
#define ACBG	6
#define ACO	5
#define ACI	4
#define ACIE	3
#define ACIC	2
#define ACIS1	1
#define ACIS0	0

/* ADCSR / ADCSRA */
#define ADEN	7
#define ADSC	6
#define ADFR	5
#define ADIF	4
#define ADIE	3
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

/* ADMUX */
#define REFS1	7
#define REFS0	6
#define ADLAR	5
/* bit 4 reserved */
#define MUX3	3
#define MUX2	2
#define MUX1	1
#define MUX0	0

/* Constants */
#define SPM_PAGESIZE 64
#define RAMEND		0x45F
#define XRAMEND		0x45F
#define E2END		0x1FF
#define FLASHEND	0x1FFF


#endif /*ASURO_UNIX_H_*/
