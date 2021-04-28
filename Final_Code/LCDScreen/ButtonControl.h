#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H

void buttonSetup();

// This is called fourSecFunc, because everytime I change the name I get a compiler error. I think my Arduino IDE on my computer may be broken - R
void fourSecFunc(); 

void oneButtonISR();

void oneTap();

void updateButton();

void checkButton();

int ledStatus();

#endif
