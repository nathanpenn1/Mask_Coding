
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
  checkFrameTime();
  
  updateButton();
  batteryPercentage = calculateBatteryPercentage(batteryPinVoltage);
  intesityStatus(dataPoint);
  uvSensorStatus();
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

  if (dataPoint < 50)
    dataPoint = dataPoint + 1;
  else
    dataPoint = 0;

  
    
  delay(100);
}
