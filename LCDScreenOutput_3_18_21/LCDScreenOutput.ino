
#include "SPI.h"
#include "ScreenDraw.h"
#include "BluetoothSetSend.h"
#include "UVSensorSetSend.h"

#include <EasyButton.h> // 3/17/21

int inc = 0;
int dataPoint = 0;
int timeVal = 0;
int batteryPercentage = 0;


#define batteryPercentPin A7
#define oneButtonPIN D2 // 3/16/21
#define LEDtoTestOneButtonFunc D3 // 3/16/21
bool buttonPressed = 0;
bool buttonPressedFourSeconds = 0;



int timePressed_foursec = 4000; // 4 seconds, or 4000 milliseconds
//attachInterrupt(digitalPinToInterrupt(oneButtonPin), oneButtonISR, FALLING);
EasyButton oneButton(oneButtonPIN);


void setup() {
  screenSetup();
  bluetoothSetup();
  uvSensorSetup();

  //pinMode(oneButtonPIN, INPUT_PULLUP);

  oneButton.begin(); // Initialize the button

  oneButton.onPressed(oneTap);
  oneButton.onPressedFor(timePressed_foursec, foursecfunc); // Set up the button for a 4 second long press


  if (oneButton.supportsInterrupt())
  {
    oneButton.enableInterrupt(oneButtonISR);
    Serial.println("Settings interrupts with the oneButton");
  }

}

void loop() {
  oneButton.update();

  bluetoothStatus();
  percentageStatus(inc);
  intesityStatus(dataPoint);
  uvSensorStatus();

  // Raven 3/6/21
  printUV();
  graphUV();

  // incrementing percentage
  if (inc < 100)
    inc = inc + 1;
  else
    inc = 0;

  if (dataPoint < 50)
    dataPoint = dataPoint + 1;
  else
    dataPoint = 0;

  if (buttonPressed)
  {
    Serial.println("Tapped once");
    buttonPressed = 0;
  }
  else if (buttonPressedFourSeconds)
  {
    Serial.println("Button held for four seconds");
    buttonPressedFourSeconds = 0;
  }
    

  delay(100);
}




void foursecfunc()
{
  buttonPressedFourSeconds = 1;
}

void oneButtonISR()
{
  oneButton.read();// Updating button status
}

// Note to Self -- long press for 4 seconds is good, but cant work with a single tap. 


void oneTap()
{
  buttonPressed = 1;
}

void calculateBatteryPercentage()
{
  int batteryVoltage = 6; // Max Battery voltage is 6 volts 

  int pinVoltage = analogRead(A7); // Read the voltage that the battery pack is sending.

  batteryPercentage = pinVoltage/batteryVoltage; // Calculate the battery percentage, and set it via percentageStatus(), which has not been coded yet.

  
}
