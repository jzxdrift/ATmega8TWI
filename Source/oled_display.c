#include <avr/pgmspace.h>

#include "twi.h"

#define SLAVE_ADDRESS			0x78
#define SA0				0x00		/*or 0x02 (hardware dependent)*/
#define READ_MODE			0x01
#define WRITE_MODE			0x00

#define CONTINUE_DATA_ONLY		0x00
#define CONTINUE_DATA_CMD		0x80
#define DATA_SELECT			0x40
#define CMD_SELECT			0x00
#define CONTROL_BYTE			0x00

#define SET_COLUMN_ADDRESS		0x21
#define COLUMN_START_ADDRESS		0x00
#define COLUMN_END_ADDRESS		0x7F

#define SET_PAGE_ADDRESS		0x22
#define PAGE_START_ADDRESS		0x00
#define PAGE_END_ADDRESS		0x07

#define BYTE				8
#define OLED_RESOLUTION			(128 * 64)

#define FIRST_CHAR			32
#define CHAR_COLUMNS			5

extern const uint8_t INIT_COMMANDS[];
extern const uint8_t INIT_COMMANDS_SIZE;
extern const uint8_t CHARACTERS[];

void connectOLEDDisplay(void)
{
	startTWI();
	transmitTWI(SLAVE_ADDRESS | SA0 | WRITE_MODE);
}

void initOLEDDisplay(void)
{
	connectOLEDDisplay();
	
	for(uint8_t i = 0; i < INIT_COMMANDS_SIZE; ++i)
	{
		transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
		transmitTWI(pgm_read_byte(&INIT_COMMANDS[i]));
	}
	
	transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
	transmitTWI(SET_COLUMN_ADDRESS);
	transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
	transmitTWI(COLUMN_START_ADDRESS);
	transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
	transmitTWI(COLUMN_END_ADDRESS);
	
	transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
	transmitTWI(SET_PAGE_ADDRESS);
	transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
	transmitTWI(PAGE_START_ADDRESS);
	transmitTWI(CONTINUE_DATA_CMD | CMD_SELECT | CONTROL_BYTE);
	transmitTWI(PAGE_END_ADDRESS);
	
	transmitTWI(CONTINUE_DATA_ONLY | DATA_SELECT | CONTROL_BYTE);
	/*clear display*/
	for(uint16_t i = 0; i < OLED_RESOLUTION / BYTE; ++i)
		transmitTWI(0x00);
}

void sendDataOLEDDisplay(const char data[])
{
	transmitTWI(CONTINUE_DATA_ONLY | DATA_SELECT | CONTROL_BYTE);
	
	for(uint8_t i = 0; data[i] != '\0'; ++i)
	{
		for(uint16_t j = 0, k = (data[i] - FIRST_CHAR) * CHAR_COLUMNS; j < CHAR_COLUMNS; ++j, ++k)
			transmitTWI(pgm_read_byte(&CHARACTERS[k]));
	}
}

void disconnectOLEDDisplay(void)
{
	stopTWI();
}
