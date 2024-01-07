#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

void connectOLEDDisplay(void);
void initOLEDDisplay(void);
void sendDataOLEDDisplay(const char []);
void disconnectOLEDDisplay(void);

#endif
