#include "ButtonControl.h"
#include "ScreenDraw.h"
#include <EasyButton.h>

// Arduino Pinouts
#define oneButtonPIN D2 
#define ledPIN D3
#define turnOffSystemPin D4 

// Variables that will be used to determine which event to do
bool buttonPressed = 0;
bool buttonLongPressed = 0;
int timePressed_milliseconds = 2000; // 2.0 seconds, or 2000 milliseconds.

// Variables for the button, using the EasyButton library
unsigned int debounce = 0;
bool pullup = true;
bool invert = true;
EasyButton oneButton(oneButtonPIN, debounce, pullup,  invert); //Uncomment this if you to use button WITH interrupts
//EasyButton oneButton(oneButtonPIN); // Uncomment this if you want to use button WITHOUT interrupts

// Variables to use button WITHOUT interrupts. Comment them out if not in use to save space for Arduino
// int lastTime = millis();
// int counter = 0;

void buttonSetup()
{
  // Setting up turnOffSystemPin to turn on. With Brandon's circuit it should latch
  // the system to stay on. To turn off the system, set turnOffSystemPin to off using the logic found in this .cpp file
  pinMode(turnOffSystemPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(turnOffSystemPin, HIGH); // Set pin to high, so when button is pushed and turns on the system, it latches the mosfet thing and stays on
  digitalWrite(ledPin, HIGH); // Set pin to high, to turn on the UV LED's inside the mask. 

  oneButton.begin(); // Initialize the button
  oneButton.onPressed(oneTap); // Set up the button for a single tap/press
  oneButton.onPressedFor(timePressed_milliseconds, fourSecFunc); // Set up the button for a 4 second long press

  
  if (oneButton.supportsInterrupt()) // Setting up interrupts using the EasyButton library
  {
    oneButton.enableInterrupt(oneButtonISR);
    Serial.println("Settings interrupts with the oneButton");
  }
  
}

void oneButtonISR()
{
  oneButton.read();// Updating button status
}


void fourSecFunc()                 // This is called fourSecFunc, because everytime I change the name I get a compiler error. I think my Arduino IDE on my computer may be broken - R
{
  buttonLongPressed = 1;
}

void oneTap()
{
  buttonPressed = 1;

  
  //counter++;                     // Uncomment this if you want to use the button without interrupts. 
  //Serial.println("Tapped once"); // For testing purposes
  //Serial.print("Counter: ");     // For testing purposes
  //Serial.println(counter);       // For testing purposes
}

void updateButton()
{
  //oneButton.read(); // uncomment this if you're using the button WITHOUT interrupts. Only works with oneButton.onPressed(oneTap), 
  oneButton.update(); // uncomment this if you're using the button WITH interrupts
}


// If the button is pressed once, switch the screens
// If the button is long pressed for approximately 2 seconds, turn off the system. 
void checkButton()
{
  int checking = checkScreenSelect();
  if (buttonPressed)
  {
    Serial.println("Tapped once"); // Tapped once, change the screen
    buttonPressed = 0;

    if(checking == 1){
      printSecondScreen();
    }

    if(checking == 2){
      rePrintFirstScreen();
    }

    
  }
  else if (buttonLongPressed)
  {
    Serial.print("Button held for");
    Serial.print(timePressed_milliseconds);
    Serial.print(" milliseconds. Turning off the system");
    buttonLongPressed = 0;
    digitalWrite(turnOffSystemPin, LOW); // Turn off the system. 
  }



  ///////////////////////////////////////
  ///////////////////////////////////////
  // Uncomment the code below to use the button without interrupts. Please remember to comment out the if and else-if statements above if you want to do this. 
  // NOTE: this removes the ability to switch between screens, because I forgot to code it. 
  /*
  
  if (counter >= 5)
  {
    Serial.println("Button held for four seconds. Turning off the system.");
    buttonLongPressed = 0;
    digitalWrite(turnOffSystemPin, LOW); // Turn off the system. 
  }

  else 
  {
    Serial.println("Restarting counter");
    if (millis() - lastTime > 2000){
      Serial.println("AAAAAAAAAAAAAAA");
      lastTime = millis();
      if (counter < 0)
      {
        counter = 0;
      }
 
      else{
        counter--;
      }

      Serial.print("RCounter: ");
      Serial.println(counter);
    }
  }

  /*
   
   */



   
} // end of checkButton();
