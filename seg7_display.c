#include <avr/io.h>
#include <stdint.h>

#define SEG_CC_DDR		DDRD
#define SEG_CC_PORT		PORTD

#define DIG_DDR			DDRB
#define DIG_PORT		PORTB

#define DIG_1			1
#define DIG_2			2

#define HEX_A			10
#define HEX_B			11
#define HEX_C			12
#define HEX_D			13
#define HEX_E			14
#define HEX_F			15
#define HEX_BASE		16

typedef enum
{
	ZER0  = 0x3F,
	ONE	  = 0x06,
	TWO	  = 0x5B,
	THREE = 0x4F,
	FOUR  = 0x66,
	FIVE  = 0x6D,
	SIX	  = 0x7D,
	SEVEN = 0x07,
	EIGHT = 0x7F,
	NINE  = 0x6F,
	A	  = 0x77,
	B	  = 0x7C,
	C	  = 0x39,
	D	  = 0x5E,
	E	  = 0x79,
	F	  = 0x71
} Segments;

uint8_t digits[] = { 0, 0 };
const uint8_t DIGITS_SIZE = sizeof digits / sizeof digits[0];

void initSeg7Display(void)
{
	SEG_CC_DDR  = 0xFF;
	
	DIG_DDR |= _BV(DIG_2) | _BV(DIG_1);
	DIG_PORT |= _BV(DIG_2) | _BV(DIG_1);
}

void fillHexDigits(uint8_t dgts[], const uint8_t sz, uint8_t num)
{
	for(int8_t i = sz - 1; i >= 0; --i)
	{
		dgts[i] = num % HEX_BASE;
		num /= HEX_BASE;
	}
}

void switchDigits(const uint8_t idx)
{
	DIG_PORT |= _BV(DIG_2) | _BV(DIG_1);
	DIG_PORT &= ~_BV(idx + 1);
}

void switchSegments(const uint8_t dgts[], const uint8_t idx)
{
	static const Segments SEGMENTS[] = { ZER0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D, E, F };
	
	switch(dgts[idx])
	{
		case HEX_A:
			SEG_CC_PORT = SEGMENTS[HEX_A];
			break;
		case HEX_B:
			SEG_CC_PORT = SEGMENTS[HEX_B];
			break;
		case HEX_C:
			SEG_CC_PORT = SEGMENTS[HEX_C];
			break;
		case HEX_D:
			SEG_CC_PORT = SEGMENTS[HEX_D];
			break;
		case HEX_E:
			SEG_CC_PORT = SEGMENTS[HEX_E];
			break;
		case HEX_F:
			SEG_CC_PORT = SEGMENTS[HEX_F];
			break;
		default:
			SEG_CC_PORT = SEGMENTS[dgts[idx]];
	}
}