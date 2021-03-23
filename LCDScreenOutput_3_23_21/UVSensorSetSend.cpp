#include "BluetoothSetSend.h"
#include "SPI.h"

#define UVOUT A0
#define REF_3V3 A1

////#define changeScreen D2 // 3/16/21
////#define LEDtoTestOneButtonFunc D3 // 3/16/21
////volatile byte state = LOW; // 3/16/21

/*
// 3/16/21
void blink(){
  state = !state;
  digitalWrite(LEDtoTestOneButtonFunc, state);

}
*/


int averageAnalogRead(int pinToRead){
	byte numberOfReadings = 8;
	unsigned int runningValue = 0;

	for(int x = 0; x < numberOfReadings; x++)
		runningValue += analogRead(pinToRead);
	runningValue /= numberOfReadings;

	return(runningValue);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){

  // Used for testing, feel free to remove. 
  /*
  Serial.print("x = ");
  Serial.println(x);

  Serial.print("in_min = ");
  Serial.println(in_min);

  Serial.print("in_max ");
  Serial.println(in_max);

  Serial.print("out_min = ");
  Serial.println(out_min);

  Serial.print("out_max = ");
  Serial.println(out_max);
  */

  // Code below should fix the negative intensity
  // Error when x < 0.99.
  // makes the entire thing UV intensity go to -8.20.

  
  float firstPart = x - in_min;
  float returnThis;

  if (firstPart < 0){
    returnThis = 0; // Make it 0, since the UV sensor is not detecting anything. 
  }

  else{
    returnThis = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  return returnThis;

	
}

void uvSensorSetup(){
	//Serial.begin(9600);
	pinMode(UVOUT, INPUT);
	pinMode(REF_3V3, INPUT);

  /*
  //// pinMode(LEDtoTestOneButtonFunc, OUTPUT);
  //// pinMode(changeScreen, INPUT_PULLUP);


  // Setting up D2 for interrupts
  attachInterrupt(digitalPinToInterrupt(changeScreen), blink, CHANGE); //3/16/21

  //Set LED to off first.
  digitalWrite(LEDtoTestOneButtonFunc, state);

  */
}

void uvSensorStatus(){
	int uvAnalog = averageAnalogRead(UVOUT);
	int refVoltage = averageAnalogRead(REF_3V3); // Using 3.3 Volts for our reference voltage, for good accuracy

	float sensorOutputVoltage = 3.3 / refVoltage * uvAnalog;
	// Convert the voltage to a UV intensity level
	float uvIntensity = mapfloat(sensorOutputVoltage, 0.99, 2.8, 0.0, 15.0);

  /*
	// Print into the serial monitor for testing/debugging
	Serial.print("output: ");
	Serial.println(refVoltage);

	Serial.print("Parallax 28091 output: "); // Missing semi colon here. 
	Serial.println(uvAnalog);

	Serial.print("Parallax 28091 voltage: ");
	Serial.println(sensorOutputVoltage);

	Serial.print("UV Intensity (mW/cm^2): ");
	Serial.println(uvIntensity);

  Serial.println("");
  Serial.println("");
  */
 
  
	
}	
