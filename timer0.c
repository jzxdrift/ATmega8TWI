#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "seg7_display.h"
#include "twi.h"

ISR(TIMER0_OVF_vect)
{
	extern uint8_t digits[];
	extern const uint8_t DIGITS_SIZE;
	
	fillHexDigits(digits, DIGITS_SIZE, getStatusTWI());
	
	static uint8_t index = 0;
	if(index >= DIGITS_SIZE)
		index = 0;
	
	switchDigits(index);
	switchSegments(digits, index);
	
	++index;
}

void initTimer(void)
{
	TCCR0 |= _BV(CS01);
	TIMSK |= _BV(TOIE0);
	
	sei();
}

void resetTimer(void)
{
	TCNT0 = 0x00;
}