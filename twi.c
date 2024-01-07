#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#define TWI_STATUS_MASK		0xF8

void initTWI(void)
{
	TWBR = 0x02;		/*31KHz at 1MHz MCU and TWPS prescaler 1*/
}

void startTWI(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
}

void stopTWI(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	_delay_ms(10);
}

void transmitTWI(const uint8_t data)
{
	TWDR = data;
	
	TWCR = _BV(TWINT) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
}

uint8_t getStatusTWI(void)
{
	return TWSR & TWI_STATUS_MASK;
}