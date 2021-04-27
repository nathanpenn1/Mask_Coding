//#include "BluetoothSetSend.h"
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