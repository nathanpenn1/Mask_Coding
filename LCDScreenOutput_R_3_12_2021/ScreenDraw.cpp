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

int sensorValue; 

int x1 = 45;
int prevY = 0;


int x2 = x1 + 45;
int y2 = 0;
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

// Handles the algorithm for placing the data point into the graph, and making a line between the points. 
void graphUV(){
  
  //////////////////////////////////////////////////
  // The graph is divided are divided into 7 quadrants, both in the X and Y direction
  //////////////////////////////////////////////////
  
  // Draw a black circle to get rid of the old one. 
  tft.drawCircle(x1,prevY, 1, tft.color565(0, 0, 0));

  // Recording point 2
  //y2 = analogRead(A0);
  read_y2();

  // Dont draw line if point 1 is at location 7, and point 2 is at location 1.
  if (x2 <= 45 && x1 >= 315){
    // dont draw the line. Reset the graph.
    //tft.fillRect(  (originX+1),  (originY - 1),   (originX+sizeX), (originY-sizeY), tft.color565(0, 0, 0)   ); 2:25 PM
    tft.fillRect(  (originX+1),  (originY - sizeY),   sizeX, sizeY, tft.color565(0, 0, 0)   ); 
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
    Serial.println("fixing graph");
  }

  // if not then draw the line. 
  else{
    tft.drawLine(x1, prevY, x2, y2, tft.color565(255, 255, 255));
  }

  // I've divided our width into 7 quadrants, if it surpasses it go back to the 1st quadrant
  x1 += 45;
  if ( x1 >= 360){
    x1 = 45;
  }
  
  // the next point
  x2 += 45;
  if ( x2 >= 360){
    x2 = 45;
  }

  

  
  sensorValue = analogRead(A0);

  if (sensorValue >= 620){
    tft.drawCircle(x1,70, 1, tft.color565(255, 255, 255)); // Draw circle
    prevY = 70;
  }

  else if (sensorValue >= 520){
    tft.drawCircle(x1,90, 1, tft.color565(255, 255, 255));
    prevY = 90;
  }

  else if (sensorValue >= 420){
    tft.drawCircle(x1,115, 1, tft.color565(255, 255, 255));
    prevY = 115;
  }

  else if (sensorValue >= 320){
    tft.drawCircle(x1,135, 1, tft.color565(255, 255, 255));
    prevY = 135;
  }

  else if (sensorValue >= 220){
    tft.drawCircle(x1,160, 1, tft.color565(255, 255, 255));
    prevY = 160;
  }

  else if (sensorValue >= 120){
    tft.drawCircle(x1,185, 1, tft.color565(255, 255, 255));
    prevY = 185;
  }

  else if (sensorValue >= 20){
    tft.drawCircle(x1,210, 1, tft.color565(255, 255, 255));
    prevY = 210;
  }

  else if (sensorValue >= 0){
    tft.drawCircle(x1,220, 1, tft.color565(255, 255, 255));
    prevY = 220;
  }
    
  

}

void read_y2(){
  sensorValue = analogRead(A0);

  if (sensorValue >= 620){
    
    y2 = 70;
  }

  else if (sensorValue >= 520){
    
    y2 = 90;
  }

  else if (sensorValue >= 420){
    
    y2 = 115;
  }

  else if (sensorValue >= 320){
    
    y2 = 135;
  }

  else if (sensorValue >= 220){
    
    y2 = 160;
  }

  else if (sensorValue >= 120){
    
    y2 = 185;
  }

  else if (sensorValue >= 20){
    
    y2 = 210;
  }

  else if (sensorValue >= 0){
    
    y2 = 220;
  }
    
  
}
