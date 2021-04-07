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

  double uvAverage = AverageFilter(data); // uvLevel needs to be replaced

  Serial.println("UV Intensity (mW/cm^2): ");
  Serial.print(uvAverage);
  
}