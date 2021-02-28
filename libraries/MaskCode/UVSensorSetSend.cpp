#include "BluetoothSetSend.h"
#include "SPI.h"

#define UVOUT A0
#define REF_3V3 A1

int averageAnalogRead(int pinToRead){
	byte numberOfReadings = 8;
	unsigned int runningValue = 0;

	for(int x = 0; x < numberOfReadings; x++)
		runningValue += analogRead(pinToRead);
	runningValue /= numberOfReadings;

	return(runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void uvSensorSetup(){
	//Serial.begin(9600);
	pinMode(UVOUT, INPUT);
	pinMode(REF_3V3, INPUT);
}

void uvSensorStatus(){
	int uvLevel = averageAnalogRead(UVOUT);
	int refLevel = averageAnalogRead(REF_3V3);

	// Use the 3.3V power pin as a reference to get a very accurate output value from sensor
	float outputVoltage = 3.3 / refLevel * uvLevel;
	// Convert the voltage to a UV intensity level
	float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);

	//printVal("output: ", refLevel);
	/*
	Serial.println("output: ");
	Serial.print(refLevel);

	Serial.println("ML8511 output: ")
	Serial.print(uvLevel);

	Serial.println("ML8511 voltage: ");
	Serial.print(outputVoltage);

	Serial.println("UV Intensity (mW/cm^2): ");
	Serial.print(uvIntensity);
	*/
}	
