#ifndef TWI_H
#define TWI_H

#include <stdint.h>

void initTWI(void);
void startTWI(void);
void stopTWI(void);
void transmitTWI(const uint8_t);
uint8_t getStatusTWI(void);

#endif
