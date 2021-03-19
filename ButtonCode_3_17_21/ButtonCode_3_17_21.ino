#include <EasyButton.h>

const byte BUTTON_PIN = 2;
int duration = 3000; // 3 seconds
int state = 0; // hold the state 
const int OFF = 0; // OFF STATE
const int DISP_1 = 1;
const int DISP_2 = 2;
const int DISP_3 = 3;
const int NEXT_STATE = 1;

EasyButton powerButton(BUTTON_PIN);

//void onPressedForDuration()
//{
//  Serial.println("Hello after 3 seconds");
//}

void buttonPressed()
{
  Serial.println("Pressed");
}


void changeStateSequence()
{
//  if(state == 3)
//  {
//    state = 1;
//  }
//  else
//  {
//    state += 1; 
//  }

//  Serial.println(state);
  Serial.println("HELLO");
  
}

void offStateSequence()
{
//  state = 0;
//  Serial.println(state);
  Serial.println("GOODBYE");
}

void buttonISR()
{
  powerButton.read();
}

void setup() {
  Serial.begin(9600);
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  powerButton.begin();
//  powerButton.onPressedFor(duration, onPressedForDuration);
  powerButton.onPressed(buttonPressed);
  
//  powerButton.onSequence(2, 1000, changeStateSequence);
  
//  powerButton.onSequence(3, duration, offStateSequence);

  if (powerButton.supportsInterrupt())
  {
    powerButton.enableInterrupt(buttonISR);
    Serial.println("Button will be used through interrupts");
  }

//  Serial.println("Hello the current state is:");
//  Serial.println(state);
}

void loop() {
  // put your main code here, to run repeatedly:
// powerButton.update(); 
  
}
