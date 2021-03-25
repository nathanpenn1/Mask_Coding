#include "ButtonControl.h"
#include <EasyButton.h>

#define batteryPercentPin A7
#define oneButtonPIN D2 // 3/16/21
#define turnOffSystemPin D3 // 3/24/21 

bool buttonPressed = 0;
bool buttonPressedFourSeconds = 0;

int timePressed_foursec = 4000; // 4 seconds, or 4000 milliseconds
//attachInterrupt(digitalPinToInterrupt(oneButtonPin), oneButtonISR, FALLING);
EasyButton oneButton(oneButtonPIN);

void buttonSetup()
{
  // Setting up turnOffSystemPin to turn on. With Brandon's circuit it should latch
  // the system to stay on. To turn off the system, set turnOffSystemPin to off
  pinMode(turnOffSystemPin, OUTPUT);
  digitalWrite(turnOffSystemPin, HIGH);

  oneButton.begin(); // Initialize the button
  oneButton.onPressed(oneTap); // Set up the button for a single tap/press
  oneButton.onPressedFor(timePressed_foursec, fourSecFunc); // Set up the button for a 4 second long press

  if (oneButton.supportsInterrupt()) // Setting up interrupts using the EasyButton library
  {
    oneButton.enableInterrupt(oneButtonISR);
    Serial.println("Settings interrupts with the oneButton");
  }
}

void fourSecFunc()
{
  buttonPressedFourSeconds = 1;
}

void oneButtonISR()
{
  oneButton.read();// Updating button status
}


void oneTap()
{
  buttonPressed = 1;
}

void updateButton()
{
  oneButton.update();
}

void checkButton()
{
  if (buttonPressed)
  {
    Serial.println("Tapped once");
    buttonPressed = 0;
  }
  else if (buttonPressedFourSeconds)
  {
    Serial.println("Button held for four seconds. Turning off the system.");
    buttonPressedFourSeconds = 0;
    digitalWrite(turnOffSystemPin, LOW); // Turn off the system. 
  }
}
