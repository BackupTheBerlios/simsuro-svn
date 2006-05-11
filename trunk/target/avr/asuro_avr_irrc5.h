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

#ifndef ASURO_AVR_IRRC5_H_
#define ASURO_AVR_IRRC5_H_

/**
 * Read the last IR-RC5 code received. This will flush the input, thus
 * subsequent calls will return 0 or a new value.
 * 
 * @return Last IR RC5 code received
 */
void AS_isr_irrc5(void);

#endif /*ASURO_AVR_IRRC5_H_*/
