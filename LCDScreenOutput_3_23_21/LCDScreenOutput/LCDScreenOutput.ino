
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
  
  checkFrameTime(); // This could be removed in the final product.
  
  updateButton(); // Updates the button's status. Can be configured with and without interrupts inside ButtonControl.cpp
  batteryPercentage = calculateBatteryPercentage(batteryPinVoltage);
  intesityStatus(dataPoint);
  uvSensorStatus(uvAnalogValue);
  checkButton(); // Checking if button is pressed. 

  // Decide which screenDraw functions to use based on which screen the user is on.
  screenSelect = checkScreenSelect();
  if (screenSelect == 1){
    printUV();
    graphUV();
  }

  else if (screenSelect == 2){
    printUV_SECONDSCREEN();
    //printPercentage_SECONDSCREEN(i);
  }

  // Testing purposes without access to UV sensor
  if (dataPoint < 50)
    dataPoint = dataPoint + 1;
  else
    dataPoint = 0;

  
    
  delay(100); // Can be removed if you want. 
}
