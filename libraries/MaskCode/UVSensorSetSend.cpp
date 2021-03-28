#include "BluetoothSetSend.h"
#include "SPI.h"

#define UVOUT A0
#define REF_3V3 A1
#define K 3
#define N (int)(1<<K)

/*
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
*/

void uvSensorSetup(){
	//Serial.begin(9600);
	pinMode(UVOUT, INPUT);
	pinMode(REF_3V3, INPUT);
}

double AverageFilter (double input) {
	static double buf[N];
	static double sum;
	static int buf_ptr;

	sum -= buf[buf_ptr];
	buf[buf_ptr] = input;
	sum += buf[buf_ptr++];
	buf_ptr %= N;

	return ((sum / N));
}

int uvSensorStatus(int data){
	//double uvLevel = analogRead(UVOUT);
	

	//int refLevel = averageAnalogRead(REF_3V3);
	double uvAverage = AverageFilter(data); // uvLevel needs to be replaced
	// Use the 3.3V power pin as a reference to get a very accurate output value from sensor
	//float outputVoltage = 3.3 / refLevel * uvLevel;
	// Convert the voltage to a UV intensity level
	//float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);

	//printVal("output: ", refLevel);
	/*
	Serial.println("output: ");
	Serial.print(refLevel);

	Serial.println("ML8511 output: ")
	Serial.print(uvLevel);

	Serial.println("ML8511 voltage: ");
	Serial.print(outputVoltage);
	*/
	Serial.println("UV Intensity (mW/cm^2): ");
	Serial.print(uvAverage);
	return (int)uvAverage;
}
