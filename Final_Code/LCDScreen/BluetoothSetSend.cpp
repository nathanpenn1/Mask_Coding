#include "ArduinoBLE.h"
#include "ScreenDraw.h"

BLEService uvMaskService("180C"); //User define service

// create percentage characteristic and allow remote device to get notifications
BLEIntCharacteristic percentageCharacteristic("2A57", BLERead | BLENotify);
// create UV intesity characteristic and allow remote device to get notifications
BLEIntCharacteristic intesityCharacteristic("2A58", BLERead | BLENotify);
// creat time chracteristic and allow remote device to get notifications
BLEIntCharacteristic timeChracteristic("2A59", BLERead | BLENotify);
// creat buttonOnOff chracteristic and allow remote device to get notifications
BLEIntCharacteristic buttonOnOffChar("111E", BLERead | BLENotify | BLEWrite);

void bluetoothSetup(){
  Serial.begin(9600); // initialize serial communication
  
  if(!BLE.begin()){     // initialize BLE
    Serial.println("starting BLE failed!");
    while(1);
  }
  BLE.setLocalName("Nano33BLE");  // Set name for connection
  BLE.setAdvertisedService(uvMaskService); // Advertise unMaskService
  uvMaskService.addCharacteristic(percentageCharacteristic); // Add percentage Characteristic
  uvMaskService.addCharacteristic(intesityCharacteristic);  // Add intesity Characteristic
  uvMaskService.addCharacteristic(timeChracteristic);  // Add time Characteristic
  uvMaskService.addCharacteristic(buttonOnOffChar);  // Add buttonOnOff Characteristic
  
  
  BLE.addService(uvMaskService); // Add service
  
  percentageCharacteristic.writeValue(0);
  intesityCharacteristic.writeValue(500);
  timeChracteristic.writeValue(0);
  buttonOnOffChar.writeValue(0);
  
  BLE.advertise();  // Start advertising

}

void bluetoothStatus(){
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect

}

// void intesityStatus(int dataPoint){
//   // read the current percentage value
//   int percentage = analogRead(A0);

//   // has the value changed since the last read
//   boolean intestyChanged = (intesityCharacteristic.value() != percentage); // is the percentage in the loop

//   //if(intestyChanged){
//     intesityCharacteristic.writeValue(percentage);
//     //Serial.print("intesity changed to : ");////
//     //Serial.print(dataPoint);////
//     //Serial.println("");////
//   //}

// }

void percentageStatus(int inc){

  int checking = checkScreenSelect();

  // has the value changed since the last read
  boolean percentageChanged = (percentageCharacteristic.value() != inc); // is the percentage in the loop

  //if(percentageChanged){
    percentageCharacteristic.writeValue(inc);
    if (checking == 1)
    {
      //percentageOutput(inc); // Removing from first screen and placing into the second screen.
    }

    else if (checking == 2)
    {
      printPercentage_SECONDSCREEN(inc);
    }

    else
    { 
      // PRINT THE ERROR IF THERE IS AN ERROR.
      int randomNumber = 123;
      percentageOutput(randomNumber);
      printPercentage_SECONDSCREEN(randomNumber);
    }
    
}


double convertFromADC (){
  double sum = 0;
  for(int i = 0; i < 1000; i++){
    double v = analogRead(A0);
    v = (3.3/1023)*v;
    sum = v + sum;
  }
  return (double)(sum / 1000 * 100); // returns mV value
}

// Based of ma2shita's Arduino library for GUVA-S12SD
double calculateUVIndex(double i){
  double mV = convertFromADC();
  double uv_index = (mV / 1024) / 0.1;
  //Serial.print("guvaUV_index: ");Serial.print(uv_index);Serial.println("   ");  // Print to serial monitor for testing. 
}


void intensityStatus(){
  // read the current percentage value
  //int percentage = analogRead(A0);
  double mV = convertFromADC();
  calculateUVIndex(mV);

  // Maybe remove this? The intensity value will likely stay the same, but just wanted to give out a thought. 
  // has the value changed since the last read
  //boolean intestyChanged = (intesityCharacteristic.value() != mV); // is the percentage in the loop

  intesityCharacteristic.writeValue(mV);

}

void printVal (char string[] , float data){
  Serial.println(string);
  Serial.print(data);
}


void buttonOnOff(){
  if(buttonOnOffChar.written()){
    if(buttonOnOffChar.value() == 1){
      digitalWrite(D5, HIGH);
    } else {
      digitalWrite(D5, LOW);
    }
  }
}
