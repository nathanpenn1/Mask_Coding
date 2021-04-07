#include "ButtonControl.h"
#include <EasyButton.h>

#define batteryPercentPin A7
#define oneButtonPIN D2 // 3/16/21
#define LEDtoTestOneButtonFunc D3 // 3/16/21

bool buttonPressed = 0;
bool buttonPressedFourSeconds = 0;

int timePressed_foursec = 4000; // 4 seconds, or 4000 milliseconds
//attachInterrupt(digitalPinToInterrupt(oneButtonPin), oneButtonISR, FALLING);
EasyButton oneButton(oneButtonPIN);

void buttonSetup()
{
  oneButton.begin(); // Initialize the button

  oneButton.onPressed(oneTap);
  oneButton.onPressedFor(timePressed_foursec, fourSecFunc); // Set up the button for a 4 second long press


  if (oneButton.supportsInterrupt())
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
    Serial.println("Button held for four seconds");
    buttonPressedFourSeconds = 0;
  }
}
