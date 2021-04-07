#include "BluetoothSetSend.h"
#include "SPI.h"

#define UVOUT A0
#define REF_3V3 A1

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

void uvSensorStatus(int data){
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
  
}


//void uvSensorStatus(){
//	int uvAnalog = averageAnalogRead(UVOUT);
//	int refVoltage = averageAnalogRead(REF_3V3); // Using 3.3 Volts for our reference voltage, for good accuracy
//
//	float sensorOutputVoltage = 3.3 / refVoltage * uvAnalog;
//	// Convert the voltage to a UV intensity level
//	float uvIntensity = mapfloat(sensorOutputVoltage, 0.99, 2.8, 0.0, 15.0);
//
//  /*
//	// Print into the serial monitor for testing/debugging
//	Serial.print("output: ");
//	Serial.println(refVoltage);
//
//	Serial.print("Parallax 28091 output: "); // Missing semi colon here. 
//	Serial.println(uvAnalog);
//
//	Serial.print("Parallax 28091 voltage: ");
//	Serial.println(sensorOutputVoltage);
//
//	Serial.print("UV Intensity (mW/cm^2): ");
//	Serial.println(uvIntensity);
//
//  Serial.println("");
//  Serial.println("");
//  */
// 
//  
//	
//}	
