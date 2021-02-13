
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "ArduinoBLE.h"
//#include "Adafruit_I2CDevice.h"
//#include <Adafruit_BusIO.h>

#define TFT_MISO D12
#define TFT_LED D10
#define TFT_SCK D13
#define TFT_MOSI D11
#define TFT_DC D8
#define TFT_RESET D9
#define TFT_CS D7

#define originX 20
#define sizeX 290
#define originY 220
#define sizeY 150
#define minorX 4
#define minorY 4


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RESET, TFT_MISO);

BLEService uvMaskService("180C"); //User define service

// create percentage characteristic and allow remote device to get notifications
BLEIntCharacteristic percentageCharacteristic("2A57", BLERead | BLENotify);
// create UV intesity characteristic and allow remote device to get notifications
BLEIntCharacteristic intesityCharacteristic("2A58", BLERead | BLENotify);
// creat time chracteristic and allow remote device to get notifications
BLEIntCharacteristic timeChracteristic("2A59", BLERead | BLENotify);

int inc = 0;
int dataPoint = 0;
int timeVal = 0;

void setup() {
  screenSetup();
  bluetoothSetup();
}

void loop() {
  bluetoothStatus();
  percentageStatus();
  // incrementing dataPoint
  if(dataPoint < 50)
    dataPoint = dataPoint + 1;
  else
    dataPoint = 0;
  // incrementing time
  if(timeVal < 60)
    timeVal = timeVal + 1;
  else
    timeVal = 0;
  // incrementing percentage  
  if(inc < 100)
    inc = inc + 1;
  else
    inc = 0;
    
  delay(1000);
}
void percentageStatus(){
  // read the current percentage value
  // int percentage = digitalRead(pin #);

  // has the value changed since the last read
  boolean percentageChanged = (percentageCharacteristic.value() != inc); // is the percentage in the loop

  if(percentageChanged){
    percentageCharacteristic.writeValue(inc);
    percentageOutput(inc);
    Serial.print("% changed to : ");
    Serial.print(inc);
    Serial.print("%");
    Serial.println("");
  }
}

void percentageOutput(int i){
    tft.fillRoundRect(270,15, 50, 15, 0, tft.color565(0, 0, 0)); 
    tft.setCursor(270,15); // set the cursor
    tft.setTextColor(tft.color565(255, 0, 0));
    tft.setTextSize(2);
    tft.print(i);
    tft.print("%");
    //delay(100);
}

void bluetoothStatus(){
  BLEDevice central = BLE.central();  // Wait for a BLE central to connect

  // if a central is connected to the peripheral:
  if (central) {
    Serial.print("Connected to central MAC: ");
    // print the central's BT address:
    Serial.println(central.address());
  }
  else {  
    // when the central disconnects
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
  }
}

void bluetoothSetup(){
  Serial.begin(9600); // initialize serial communication
  while(!Serial);

  pinMode(LED_BUILTIN, OUTPUT); //initialize the built-in LED pin
  
  if(!BLE.begin()){     // initialize BLE
    Serial.println("starting BLE failed!");
    while(1);
  }
  BLE.setLocalName("Nano33BLE");  // Set name for connection
  BLE.setAdvertisedService(uvMaskService); // Advertise unMaskService
  uvMaskService.addCharacteristic(percentageCharacteristic); // Add percentage Characteristic
  uvMaskService.addCharacteristic(intesityCharacteristic);  // Add intesity Characteristic
  //uvMaskService.addCharacteristic(timeChracteristic);  // Add time Characteristic
  
  BLE.addService(uvMaskService); // Add service
  
  percentageCharacteristic.writeValue(0);
  intesityCharacteristic.writeValue(0);
  timeChracteristic.writeValue(0);
  
  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
}

void screenSetup(){
  // Turn on backlight
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  // Init display
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(tft.color565(0, 0, 0));
  
  // Title (UV Mask)
  drawingF(5, 15, 80, 149, 201, 3);
  tft.println("UV MASK");
  
  // drawing label "Percentage"
  drawingF(140, 15, 100, 100, 100, 2);
  tft.println("Percentage: ");
  
  // drawing label "UV Intesity Graph"
  drawingF(60, 50, 100, 100, 100, 2);
  tft.println("UV Intesity Graph");
  
  // draw the two axis
  tft.drawLine(originX, originY, (originX + sizeX), originY,tft.color565(255, 255, 255));
  tft.drawLine(originX, originY, originX, (originY - sizeY),tft.color565(255, 255, 255));
  
  // draw the little dividers on the lines
  for(int i = originX + 6; i <= (originX + sizeX); i= i + 4){
    tft.drawLine(i, originY, i, (originY + minorY),tft.color565(255, 255, 255));
  }
  for(int i = originY - 6; i >= (originY - sizeY); i= i - 4){
    tft.drawLine(originX, i, (originX - minorX), i,tft.color565(255, 255, 255));
  }
  
  // draw the x-axis label
  drawingF(150, 230, 100, 100, 100, 1);
  tft.println("Time(s)");
  
  // draw the y-axis label
  drawingF(12, 60, 100,100, 100, 1);
  tft.println("nm");
}

void drawingF(int Cx, int Cy, int R, int G, int B, int textSize)
{
  tft.setCursor(Cx,Cy); // set the cursor
  tft.setTextColor(tft.color565(R, B, B));
  tft.setTextSize(textSize);
}
