
/*
 ARDUINO PINOUTS:
 For the screen, please refer to the top of ScreenDraw.cpp

 UVSensor output is connected to A0
 Pins related to single button functionality and LED's are located in ButtonControl.cpp

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
  ///////////////////   BLUETOOTH STATUS  ///////////////////////////
  /* listening for BLE peripherals to connect */
  bluetoothStatus();

  /////////////////// BATTERY PERCENTAGE  ///////////////////////////
  /* grabs the battery voltage and send data via Bluetooth to the app and LCD Screen.*/
  int batteryPinVoltage = analogRead(A6);
  batteryPercentage = calculateBatteryPercentage(batteryPinVoltage);
  percentageStatus(batteryPercentage);

  ////////////////// APP BUTTON ON / OFF ///////////////////////////
  /* a value is written to characteristic from the app and turns ON or OFF the D3 pin */
  buttonOnOff();

  ////////////////// UV SENSORY STATUS //////////////////////////////
  /* grabs the uv sensory value and calculates it and sends it to the app and LCD Screen*/
  intensityStatus();
  
  
  // Updates the button's status. Can be configured with and without interrupts inside ButtonControl.cpp
  updateButton(); 

  checkButton();


  // Checking if button is pressed. 
  // If tapped once, the screen will switch from screen 1 to screen 2
  // If long pressed for approximately two seconds, turns off the system after releasing the button.
  checkButton(); 

  // Decide which screenDraw functions to use based on which screen the user is on.
  screenSelect = checkScreenSelect();
  if (screenSelect == 1){
    printUV(); 
    serialPrintUV(); // Printing uv intensity to the serial monitor for testing. 
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
