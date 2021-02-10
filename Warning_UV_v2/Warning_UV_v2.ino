// Attach your libraries 
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// aadding this library because to fix the compilation error. 
#include <Adafruit_I2CDevice.h>

// Setting up pin constants for our 2.2 LCD Screen.
#define TFT_DC 20 
#define TFT_CS 21 
#define TFT_MOSI 29 
#define TFT_CLK 1 
#define TFT_RST 13 
#define TFT_MISO 30 

// Setting up the tft object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

// Runs only once. 
void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
  tft.begin();
  
  ////////////////////////////////////////
  // Start displaying the warning label.
  ////////////////////////////////////////
  
  tft.fillScreen(ILI9341_BLACK); // change the screen to black. 

  // Display line 1
  tft.setCursor(0, 0); // go to x= 0, and y = 0
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.println("WARNING");
  
  // Display line 2
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.println("Contains harmful UV LED's");

  // Display line 3
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println("which may harm your skin/eyes.");

  // Display line 4
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(1);
  tft.println("Please avoid opening the facemask");

  // Display line 5
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(1);
  tft.println("and contact the manufacturer for any assistance");

  

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Printing the Warning Label only once."); 
}
