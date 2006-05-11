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
 
#include "asuro_unix.h"
#include "asuro_unix_decode.h"
#include "asuro_defs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

volatile int AS_unix_alarmCount = 0;
volatile double AS_unix_simTime = 0.0;
volatile int AS_unix_ioLock = 0;

/**
 * Call SIG_OUTPUT_COMPARE2 ISR and evaulate IO vector.
 */
void AS_unix_sh_SIGALRM(int signo, siginfo_t *info, void *context) 
{
	if (signo == SIGALRM) {
		int i;
		for (i = 0; i < 255; i++) {
			SIG_OUTPUT_COMPARE2();
			
		}
		
		AS_unix_alarmCount++;
		if (AS_unix_alarmCount >= 28) {
			AS_unix_simTime += 0.003556*28;
			AS_unix_alarmCount = 0;
			
			AS_unix_decode();
			
		}
	
	}
	
}

/**
 * This function is called just before any read or write access to the IO 
 * vector. Any reactions on IO requests have to be handled here.
 * 
 * At the moment, the following is handled here:
 *  - Writes to the serial interface.
 * 
 * @param io_addr	IO vector offset that is being accessed.
 * 
 * @return Always io_addr
 */
int AS_unix_prepareIo(int io_addr)
{
	// avoid endless recursive calls (this is not thread/signal safe)
	if (AS_unix_ioLock) return io_addr;
	AS_unix_ioLock = 1;
	
	switch (io_addr) {
		// UCSRB
		case 0x0A: {
			UDR = '\0'; // clear UDR
			UCSRA |= 0x20 | 0x40; // write-ready and TX complete
			UCSRA &= ~0x80; // not read-ready
			break;
		}
		
		// UDR
		case 0x0C: {
			if (UCSRB == 0x08) {
				// TX mode
				printf("%c", UDR); // push previous character out
				fflush(stdout);
				
			} else if (UCSRB == 0x10) {
				// RX mode (TODO)
				
			}
			break;
		}
		
		default: {}
	}
	
	AS_unix_ioLock = 0;
	return io_addr;
}

/**
 * Initialization for simsuro
 */
inline void AS_Init(void) 
{
	fprintf(stderr, "AS_Init()\n");
	
	// clear IO vector
	memset(AS_unix_ioVector, 0, sizeof(AS_unix_ioVector));
	
	// set signal action
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = AS_unix_sh_SIGALRM;
	sigaction(SIGALRM, &act, NULL);
	
	// set timer
	struct itimerval itimer;
	memset(&itimer, 0, sizeof(itimer));
	itimer.it_interval.tv_usec = 7000;
	itimer.it_value.tv_usec = 7000;
	setitimer(ITIMER_REAL, &itimer, NULL);
	
	// low priority (uses busy waiting on UNIX!)
	setpriority(PRIO_PROCESS, getpid(), 5);
	
}
