#ifndef SEG7_DISPLAY_H
#define SEG7_DISPLAY_H

#include <stdint.h>

void initSeg7Display(void);
void fillHexDigits(uint8_t [], const uint8_t, uint8_t);
void switchDigits(const uint8_t);
void switchSegments(const uint8_t [], const uint8_t);

#endif
