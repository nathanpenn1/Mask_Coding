
#include "SPI.h"
#include "ScreenDraw.h"
#include "BluetoothSetSend.h"
#include "UVSensorSetSend.h"

int inc = 0;
int dataPoint = 0;
int timeVal = 0;

void setup() {
  screenSetup();
  bluetoothSetup();
  uvSensorSetup();
}

void loop() {
  bluetoothStatus();
  percentageStatus(inc);
  intesityStatus(dataPoint);
  uvSensorStatus();
  // incrementing percentage  
  if(inc < 100)
    inc = inc + 1;
  else
    inc = 0;

  if(dataPoint < 50)
    dataPoint = dataPoint + 1;
  else
    dataPoint = 0;  
    
  delay(100);
}
