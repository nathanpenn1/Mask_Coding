
#include "SPI.h"
#include "ScreenDraw.h"
#include "BluetoothSetSend.h"
#include "UVSensorSetSend.h"
#include "ButtonControl.h"
#include "Battery.h"

int inc = 0;
int dataPoint = 0;
int timeVal = 0;
int batteryPercentage = 0;


void setup() {
  buttonSetup();
  screenSetup();
  bluetoothSetup();
  uvSensorSetup();
}

void loop() {
  int batteryPinVoltage = analogRead(A7); // Read the voltage that the battery pack is sending.
  checkFrameTime();
  updateButton();
  batteryPercentage = calculateBatteryPercentage(batteryPinVoltage);
  Serial.println(batteryPinVoltage);
//  batteryPercentage = calculateBatteryPercentage(inc);

  bluetoothStatus();
//  percentageStatus(inc);
  percentageStatus(batteryPercentage); // for when we have a battery percentage to report
  intesityStatus(dataPoint);
  uvSensorStatus();
  checkButton();

  // Raven 3/6/21
  printUV();
  graphUV();

  // incrementing percentage
  if (inc < 4)
    inc = inc + 1;
  else
    inc = 0;

  if (dataPoint < 50)
    dataPoint = dataPoint + 1;
  else
    dataPoint = 0;

  
    
  delay(100);
}
