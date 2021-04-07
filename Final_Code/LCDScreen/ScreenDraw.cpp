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

// Creating variable to hold the UV Sensor value
int sensorValue; 

// Variables used for graphing the UV sensor value
int x1 = 45;
int yOne = 0;
int x2 = x1 + 45;
int y2 = 0;

// Variables used for changing the screen
int mode = 1; // Default is 1, which is the screen which shows the graph. 

// Creating instantiation of the screen. 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RESET, TFT_MISO); // Bringing instantiation of screen outside ScreenDraw.cpp

// Variables used for the UV Graph
#define numOfPoints 7 // 7 
bool initializePoints = 1;
unsigned int coordinatesX[numOfPoints] = {0};
unsigned int coordinatesY[numOfPoints] = {0};
// we got 300 pixels to work with for the screen. Correct me if I'm wrong. 
unsigned int divisionSize = 300/numOfPoints;
unsigned int point = 0;

// 3/22/2021
unsigned long lastFrameTime = millis();
int timer = 20; // 20 ms seconds per frame

void screenSetup(){
  
  // Turn on backlight
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  // Init display
  tft.begin();
  //printWarning(); // Print the warning label. Comment this out to hasten debugging

  setUpGraphCoords(initializePoints);
  initializePoints = 0; // Set this to 0. This flag is used to fix a bug, where it would truncate a part of the graph's output everytime you change screen. 
  
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

void setUpGraphCoords(bool q)  
{
  if (q == 1)
  {
    // Setting up coordinates.
    for (int dummyVariable = 0 ; dummyVariable < numOfPoints ; dummyVariable++)
    {
      if (dummyVariable == 0)
        coordinatesX[dummyVariable] += divisionSize;
      else
        coordinatesX[dummyVariable] += divisionSize*(dummyVariable+1);
    }
  
    for (int dummyVariable = 0 ; dummyVariable < numOfPoints ; dummyVariable++)
    {
      coordinatesY[dummyVariable] = 180; //Defaulting to this value for now. 
    }
  }

  else
  {
    // do nothing, since the points have been initialized. 
  }
  
}

void printWarning()
{
  tft.setRotation(3);
  tft.fillScreen(tft.color565(255, 255, 255));
  
  // Title (UV Mask)
  drawingF(5, 15, 0, 0, 0, 3);
  tft.println("WARNING:");
  
  // drawing label "Percentage"
  drawingF(5, 45, 0, 0, 0, 3);
  tft.println("Contains harmful");
  
  // drawing label "UV Intesity Graph"
  drawingF(5, 75, 0, 0, 0, 3);
  tft.println("UV lights");

  drawingF(5, 100, 0, 0, 0, 3);
  tft.println("Be careful");

  delay(5000);
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

    // Print out the current sensor value into the screen. 
    sensorValue = analogRead(A0);
    tft.print(sensorValue);
    
}

// Handles the algorithm for placing the data point into the graph, and making a line between the points. 
void graphUV(){
  
  // Check if you past the graph division limit. 
  // If you past the limit, reset back to the first point and clear the lines on the graph.
  if (point >= numOfPoints){
    
    // Reseting the graph by drawing over the lines that were previously graphed.
    for ( int i = 1 ; i < numOfPoints ; i++)
    {
      tft.drawLine(coordinatesX[i-1],coordinatesY[i-1], coordinatesX[i],coordinatesY[i],tft.color565(0, 0, 0));
    }
    tft.drawCircle(coordinatesX[numOfPoints-1],coordinatesY[numOfPoints-1], 1, tft.color565(0, 0, 0)); // A pixel is left not cleared. This will clear this anomaly. 



  // Redraw everything, but throw away the first point

  // This "for" loop will handle throwing away the first point and shifting our stuff over by 1
  for (int dummyVariable = 0 ; dummyVariable < numOfPoints - 1 ; dummyVariable++)
  {
    // Overwrite the coordinates with the value of the next point. 
    // NOTE: X values dont change, but the Y values will change. 
    coordinatesY[dummyVariable] = coordinatesY[dummyVariable+1];

  }

  // This "for" loop will redraw the line, with the first point removed. 
  for ( int i = 1 ; i <= numOfPoints - 2 ; i++)
  {
      tft.drawLine(coordinatesX[i-1],coordinatesY[i-1], coordinatesX[i],coordinatesY[i],tft.color565(255, 255, 255));
  }

    // Reset current point to the last point, which will receive the current UV sensor data. 
    point = 6;

  }
  
  

  sensorValue = analogRead(A0);
  if (sensorValue >= 620){
    tft.drawCircle(coordinatesX[point],70, 1, tft.color565(255, 255, 255)); // Draw circle
    coordinatesY[point] = 70;
    
    
  }

  else if (sensorValue >= 520){
    tft.drawCircle(coordinatesX[point],90, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 90;
   
  }

  else if (sensorValue >= 420){
    tft.drawCircle(coordinatesX[point],115, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 115;
   
  }

  else if (sensorValue >= 320){
    tft.drawCircle(coordinatesX[point],135, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 135;  
   
  }

  else if (sensorValue >= 220){
    tft.drawCircle(coordinatesX[point],160, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 160;  
    
  }

  else if (sensorValue >= 120){
    tft.drawCircle(coordinatesX[point],185, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 185;
    
  }

  else if (sensorValue >= 20){
    tft.drawCircle(coordinatesX[point],210, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 210;
    
  }

  else if (sensorValue >= 0){
    tft.drawCircle(coordinatesX[point],215, 1, tft.color565(255, 255, 255));
    coordinatesY[point] = 215;
   
  }

  
  // Draw black circle over the previous one, and draw a line
  if ( point != 0)
  {
    tft.drawCircle(coordinatesX[point-1],coordinatesY[point-1], 1, tft.color565(0, 0, 0)); // Draw over the previous circle
    tft.drawLine(coordinatesX[point-1],coordinatesY[point-1], coordinatesX[point],coordinatesY[point],tft.color565(255, 255, 255));
  }

  point++;
  
}

void rePrintFirstScreen()
{
  mode = 1;
  // Turn on backlight
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);

  /*
  // Setting up coordinates.
  for (int dummyVariable = 0 ; dummyVariable < numOfPoints ; dummyVariable++)
  {
    if (dummyVariable == 0)
      coordinatesX[dummyVariable] += divisionSize;
    else
      coordinatesX[dummyVariable] += divisionSize*(dummyVariable+1);
  }
  
  for (int dummyVariable = 0 ; dummyVariable < numOfPoints ; dummyVariable++)
  {
    coordinatesY[dummyVariable] = 180; //Defaulting to this value for now. 
    
  }
  */
   
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Second screen functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printSecondScreen()
{
  mode = 2; // Change screenSelect to 2, symbolizing that you are now on the second screen. 
  
  // Turn on backlight
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  
  tft.setRotation(3);
  tft.fillScreen(tft.color565(0, 0, 0));
  
  // draw the title
  drawingF(5, 15, 80, 149, 201, 2);
  tft.println("BetterBreath: 2nd Screen");
  
  // drawing label "Percentage"
  drawingF(5, 50, 100, 100, 100, 2);
  tft.println("Percentage: ");
  
  // drawing label "UV Analog"
  drawingF(5, 65, 100, 100, 100, 2);
  tft.println("UV Analog: ");
}


void printUV_SECONDSCREEN(){
    //Printing out the sensor on the arduino for testing. 
    tft.fillRoundRect(135,65, 50, 15, 0, tft.color565(0, 0, 0)); // Draw a black rectangle to reset value shown. 
    tft.setCursor(135,65); // set the cursor
    tft.setTextColor(tft.color565(255, 0, 0));
    tft.setTextSize(2);

    // Print out the current sensor value into the screen. 
    sensorValue = analogRead(A0);
    tft.print(sensorValue);
}

void printPercentage_SECONDSCREEN(int i){
    tft.fillRoundRect(135,50, 50, 15, 0, tft.color565(0, 0, 0)); 
    tft.setCursor(135,50); // set the cursor
    tft.setTextColor(tft.color565(255, 0, 0));
    tft.setTextSize(2);
    tft.print(i);
    tft.print("%");
}



int checkScreenSelect()
{
  return mode; // return the mode. 
}

// This function is used to check how many milliseconds it takes for each frame.
/*
3/22/21 Average framerate was around 360 milliseconds, resulting in a frame rate/ refresh rate of 
This includes everything, including the calculation for all the sensors, graphing and bluetooth. 
Without   bluetoothStatus(), percentageStatus(inc), intesityStatus(dataPoint) and uvSensorStatus(), thhe refresh rate
is about 290 ms per frame, which is about 4 frames per second. 
3/23/21 Around 2:18 AM
Average framerate is around 330 ms per frame (or about 3 frames per second, if my math is right.), 
when redrawing the line and shifting everything by 1 to the left. This is without bluetoothStatus(),
percentageStatus(inc), intesityStatus(dataPoint) and uvSensorStatus(), 
WITH these functions, its about 500 or 400 ms per frame, leading up to 2 frames per second in the best
case scenario. 
*/
void checkFrameTime(){
  
  timer--;
  if (timer == 0){
    timer = 20;

    //print frame time
    tft.fillRect(0,0,50,15,ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.print(millis()-lastFrameTime);
  }

  while ((millis() - lastFrameTime) < 20);
  lastFrameTime = millis();
  
}
