#include "ArduinoBLE.h"
#include "ScreenDraw.h"

BLEService uvMaskService("180C"); //User define service

// create percentage characteristic and allow remote device to get notifications
BLEIntCharacteristic percentageCharacteristic("2A57", BLERead | BLENotify);
// create UV intesity characteristic and allow remote device to get notifications
BLEIntCharacteristic intesityCharacteristic("2A58", BLERead | BLENotify);
// creat time chracteristic and allow remote device to get notifications
BLEIntCharacteristic timeChracteristic("2A59", BLERead | BLENotify);

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
  
  BLE.addService(uvMaskService); // Add service
  
  percentageCharacteristic.writeValue(0);
  intesityCharacteristic.writeValue(0);
  timeChracteristic.writeValue(0);
  
  BLE.advertise();  // Start advertising

}

void bluetoothStatus(){
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect
}

void percentageStatus(int inc){

  int checking = checkScreenSelect();

  // has the value changed since the last read
  boolean percentageChanged = (percentageCharacteristic.value() != inc); // is the percentage in the loop

  //if(percentageChanged){
    percentageCharacteristic.writeValue(inc);
    if (checking == 1)
    {
      percentageOutput(inc);
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

void intensityStatus(){
  // read the current percentage value
  //int percentage = analogRead(A0);
  double mV = convertFromADC();

  // has the value changed since the last read
  //boolean intestyChanged = (intesityCharacteristic.value() != mV); // is the percentage in the loop

  intesityCharacteristic.writeValue(mV);

}

void printVal (char string[] , float data){
  Serial.println(string);
  Serial.print(data);
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