#include "seg7_display.h"
#include "twi.h"
#include "timer0.h"
#include "oled_display.h"

int main(void)
{
	initSeg7Display();
	initTWI();
	
	initTimer();
	resetTimer();
	
	initOLEDDisplay();
	sendDataOLEDDisplay("Hello World!");
	disconnectOLEDDisplay();
	
	connectOLEDDisplay();
	sendDataOLEDDisplay(" hi");
	disconnectOLEDDisplay();
	
	while(1)
	{
		
	}
}
