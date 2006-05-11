#include "asuro.h"
#include "stdio.h"

int main(void)
{
	int i = 0;
	int toggle = 0;
	
	Init();
	
	while(1) {
		toggle = !toggle;
		FrontLED(toggle);
		for (i = 0; i < 1000; i++) {
			Sleep(36);
			
		}
		
	}
	return 0;
}
