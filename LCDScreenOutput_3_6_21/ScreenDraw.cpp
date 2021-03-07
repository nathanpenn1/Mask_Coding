#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "ScreenDraw.h"

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

int prevX = 45;
int prevY = 0;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RESET, TFT_MISO);

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
  tft.println("UV Intensity Graph");
  
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
  tft.println("mW/cm2");
}

void drawingF(int Cx, int Cy, int R, int G, int B, int textSize)
{
  tft.setCursor(Cx,Cy); // set the cursor
  tft.setTextColor(tft.color565(R, G, B)); // BUGHERE, it was R, B, B
  tft.setTextSize(textSize);
}

void percentageOutput(int i){
    tft.fillRoundRect(270,15, 50, 15, 0, tft.color565(0, 0, 0)); 
    tft.setCursor(270,15); // set the cursor
    tft.setTextColor(tft.color565(255, 0, 0));
    tft.setTextSize(2);
    tft.print(i);
    tft.print("%");
}


void printUV(){

    // Printing the string "UV Analog Value"
    // drawing label "Percentage"
    drawingF(140, 30, 100, 100, 100, 2);
    tft.println("UV Analog: ");

    
    //Printing out the sensor on the arduino for testing. 
    tft.fillRoundRect(270,30, 50, 15, 0, tft.color565(0, 0, 0)); // Draw a black rectangle to reset value shown. 
    tft.setCursor(270,30); // set the cursor
    tft.setTextColor(tft.color565(255, 0, 0));
    tft.setTextSize(2);

    int sensorValue; // Create variable to print. 
    sensorValue = analogRead(A0);
    tft.print(sensorValue);
    
}

void graphUV(){
  
  //////////////////////////////////////////////////
  // The graph is divided are divided into 7 quadrants, both in the X and Y direction
  //////////////////////////////////////////////////
  
  // Draw a black circle to get rid of the old one. 
  tft.drawCircle(prevX,prevY, 1, tft.color565(0, 0, 0));

  // I've divided our width into 7 quadrants, if it surpasses it go back to the 1st quadrant
  prevX += 45;
  if ( prevX >= 360){
    prevX = 45;
  }
  
 
  int sensorValue; 
    sensorValue = analogRead(A0);

  if (sensorValue >= 620){
    tft.drawCircle(prevX,70, 1, tft.color565(255, 255, 255)); // Draw circle
    prevY = 70;
  }

  else if (sensorValue >= 520){
    tft.drawCircle(prevX,90, 1, tft.color565(255, 255, 255));
    prevY = 90;
  }

  else if (sensorValue >= 420){
    tft.drawCircle(prevX,115, 1, tft.color565(255, 255, 255));
    prevY = 115;
  }

  else if (sensorValue >= 320){
    tft.drawCircle(prevX,135, 1, tft.color565(255, 255, 255));
    prevY = 135;
  }

  else if (sensorValue >= 220){
    tft.drawCircle(prevX,160, 1, tft.color565(255, 255, 255));
    prevY = 160;
  }

  else if (sensorValue >= 120){
    tft.drawCircle(prevX,185, 1, tft.color565(255, 255, 255));
    prevY = 185;
  }

  else if (sensorValue >= 20){
    tft.drawCircle(prevX,210, 1, tft.color565(255, 255, 255));
    prevY = 210;
  }
    
  

}
