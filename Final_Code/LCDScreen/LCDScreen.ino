
/*
 ARDUINO PINOUTS:
 For the screen, please refer to the top of ScreenDraw.cpp

 UVSensor output is connected to A0
 The pin to turn off the system is connected to D4
 The button is connected to D2

 Currently, A1 is set as an input, but I dont think we are currently using this. Refer to UVSensorSetSend. 

*/

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
  // Read and save desired information into variables
  int batteryPinVoltage = analogRead(A6); 
  int uvAnalogValue = analogRead(A0);
  
  // Updates the button's status. Can be configured with and without interrupts inside ButtonControl.cpp
  updateButton(); 

  // Calculate battery percentage and UV intensity, and send data via Bluetooth to the app.
  batteryPercentage = calculateBatteryPercentage(batteryPinVoltage);
  intensityStatus();
  uvSensorStatus(uvAnalogValue);

  // Checking if button is pressed. 
  // If tapped once, the screen will switch from screen 1 to screen 2
  // If long pressed for approximately two seconds, turns off the system after releasing the button.
  checkButton(); 

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

  
    
  delay(100); // Can be removed I think, to make the arduino processor work faster. 
}
