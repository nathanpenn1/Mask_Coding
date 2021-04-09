#include "SPI.h"
#include "ScreenDraw.h"
#include "BluetoothSetSend.h"
#include "UVSensorSetSend.h"
#include "ButtonControl.h"
#include "Battery.h"

// Test variables
int inc = 0;
int dataPoint = 0;

// Battery Percentage Variables
int batteryPercentage = 0;

// Screen-related variables
unsigned int screenSelect = checkScreenSelect();



void setup() {
  buttonSetup();
  screenSetup();
  bluetoothSetup();
  uvSensorSetup();
}

void loop() {

  int batteryPinVoltage = analogRead(A6); // Read the voltage that the battery pack is sending.
  int uvAnalogValue = analogRead(A0);
  checkFrameTime();
  
  updateButton();
  batteryPercentage = calculateBatteryPercentage(batteryPinVoltage);
  Serial.println(batteryPinVoltage);
  //batteryPercentage = calculateBatteryPercentage(inc);

  bluetoothStatus();
  //percentageStatus(inc);
  percentageStatus(batteryPercentage); // for when we have a battery percentage to report

  intesityStatus(dataPoint);
  uvSensorStatus(uvAnalogValue);

  checkButton();


  screenSelect = checkScreenSelect();
  if (screenSelect == 1){
    printUV();
    graphUV();
  }

  else if (screenSelect == 2){
    printUV_SECONDSCREEN();
    //printPercentage_SECONDSCREEN(i);
  }  
  delay(100);
}
