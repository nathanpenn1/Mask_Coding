#ifndef UVSENSORSETSEND_H
#define UVSENSORSETSEND_H

int averageAnalogRead(int pinToRead);

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);

void uvSensorSetup();

void uvSensorStatus();

void blink();



#endif
