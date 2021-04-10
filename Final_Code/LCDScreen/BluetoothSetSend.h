  
#ifndef BLUETOOTHSETSEND_H
#define BLUETOOTHSETSEND_H

void percentageStatus(int inc);

void intensityStatus();

void bluetoothStatus();

void bluetoothSetup();

void printVal (char string[] , float data);

double convertFromADC();
double calculateUVIndex(double i);

#endif
