#include "BluetoothSetSend.h"
#include "SPI.h"

#define UVOUT A0
#define REF_3V3 A1
#define K 3
#define N (int)(1<<K)

#define REF_3V3 A1
#define K 3
#define N (int)(1<<K)

void uvSensorSetup(){
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
  
  double uvAverage = AverageFilter(data); // uvLevel needs to be replaced

  // Serial prints for testing. Uncomment for testing
  
  //Serial.println("output: ");
  //Serial.print(refLevel);

  //Serial.println("ML8511 output: ")
  //Serial.print(uvLevel);

  //Serial.println("ML8511 voltage: ");
  //Serial.print(outputVoltage);
  
  //Serial.print("UV Intensity (mW/cm^2): ");
  //Serial.println(uvAverage);

  // Implementing ma2shita's GUVA library functions here. Uncomment for testing

  // read()
  //float mV = uvAverage * 3.3;

  // index()
  //float uv_index = (mV / 1024) / 0.1;
  //Serial.print("guvaUV_index: ");Serial.print(uv_index);
  
}

// Old uvSensorStatus
//void uvSensorStatus(){
//  int uvAnalog = averageAnalogRead(UVOUT);
//  int refVoltage = averageAnalogRead(REF_3V3); // Using 3.3 Volts for our reference voltage, for good accuracy
//
//  float sensorOutputVoltage = 3.3 / refVoltage * uvAnalog;
//  // Convert the voltage to a UV intensity level
//  float uvIntensity = mapfloat(sensorOutputVoltage, 0.99, 2.8, 0.0, 15.0);
//
//  /*
//  // Print into the serial monitor for testing/debugging
//  Serial.print("output: ");
//  Serial.println(refVoltage);
//
//  Serial.print("Parallax 28091 output: "); // Missing semi colon here. 
//  Serial.println(uvAnalog);
//
//  Serial.print("Parallax 28091 voltage: ");
//  Serial.println(sensorOutputVoltage);
//
//  Serial.print("UV Intensity (mW/cm^2): ");
//  Serial.println(uvIntensity);
//
//  Serial.println("");
//  Serial.println("");
//  */
// 
//  
//  
//} 
