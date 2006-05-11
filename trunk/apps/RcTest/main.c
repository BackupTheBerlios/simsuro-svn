
#include "asuro.h"
#include "asuro_irrc5.h"
#include "asuro_irrc5_commands.h"

#include <stdio.h>

/**
 * User ISR (switches)
 */
void isrInterrupt1(void)
{
	if (AS_sensSwitched) {
		AS_MotorDir(AS_DIR_BREAK, AS_DIR_BREAK);
		AS_MotorSpeed(0, 0);
		AS_LED_YELLOW_ON;
	}
}

int main(void) 
{
	AS_Init();
	
	AS_UserIsrInterrupt1 = isrInterrupt1;
	
	char msg[128];
	char* action = "";
	char statusToggle = 1;
	char frontToggle = 0;
	char lbackToggle = 0;
	char rbackToggle = 0;
	
	unsigned short lastRc5Cmd = 0;
	
	int l;
	
	AS_SerWrite("Asuro here.\r", 12);
	AS_MotorDir(AS_DIR_FWD, AS_DIR_FWD);
	
	for (;;) {
		
		unsigned short rc5_cmd = AS_Irrc5Read();
		// ignore repeated commands (note that the rc5 code is different when a 
		// button is pressed twice due to the rc5 toggle bit!)
		if (rc5_cmd && (rc5_cmd != lastRc5Cmd)) {
			lastRc5Cmd = rc5_cmd;
			
			switch (rc5_cmd & AS_RC5_COMMAND_MASK) {
				case AS_RC5_CC_STOP: {
					AS_MotorDir(AS_DIR_BREAK, AS_DIR_BREAK);
					AS_MotorSpeed(0, 0);
					action = "STOP";
					break;
					
				}
				case AS_RC5_CC_FWD: {
					AS_MotorDir(AS_DIR_FWD, AS_DIR_FWD);
					AS_MotorSpeed(120, 120);
					if (!AS_sensSwitchesOn) AS_SensSwitchesInterruptOn();
					action = "FWD";
					break;
					
				}
				case AS_RC5_CC_RWD: {
					AS_MotorDir(AS_DIR_RWD, AS_DIR_RWD);
					AS_MotorSpeed(120, 120);
					// no need for collision switches if we are going backward...
					action = "RWD";
					break;
					
				}
				case AS_RC5_CC_RIGHT: {
					AS_MotorSpeed(150, 100);
					if (!AS_sensSwitchesOn) AS_SensSwitchesInterruptOn();
					action = "RIGHT";
					break;
					
				}
				case AS_RC5_CC_LEFT: {
					AS_MotorSpeed(100, 150);
					if (!AS_sensSwitchesOn) AS_SensSwitchesInterruptOn();
					action = "LEFT";
					break;
					
				}
				case AS_RC5_CC_STATUS_LED: {
					statusToggle = (statusToggle+1) % 4;
					if (statusToggle & 1) AS_LED_GREEN_ON; else AS_LED_GREEN_OFF;
					if (statusToggle & 2) AS_LED_RED_ON; else AS_LED_RED_OFF;
					action = "STATUS LED";
					break;
					
				}
				case AS_RC5_CC_FRONT_LED: {
					frontToggle = !frontToggle;
					if (frontToggle) AS_LED_FRONT_ON; else AS_LED_FRONT_OFF;
					action = "FRONT LED";
					break;
					
				}
				case AS_RC5_CC_LBACK_LED: {
					lbackToggle = !lbackToggle;
					if (lbackToggle) AS_LED_LBACK_ON; else AS_LED_LBACK_OFF;
					action = "LEFT BACK LED";
					break;
					
				}
				case AS_RC5_CC_RBACK_LED: {
					rbackToggle = !rbackToggle;
					if (rbackToggle) AS_LED_RBACK_ON; else AS_LED_RBACK_OFF;
					action = "RIGHT BACK LED";
					break;
					
				}
				default: {
					action = "none";
					break;
				}
			}
			
			l = sprintf(msg, "RC5: %04x (%04x): %s\r", rc5_cmd, rc5_cmd & AS_RC5_COMMAND_MASK, action);
			AS_SerWrite(msg, l);
			
		}
			
	} // for (;;)
	
	return 0;
}
