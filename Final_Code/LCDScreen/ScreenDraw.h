#ifndef SCREENDRAW_H
#define SCREENDRAW_H

void screenSetup();

// General functions
void drawingF(int Cx, int Cy, int R, int G, int B, int textSize);
void checkFrameTime(); 
int checkScreenSelect();
void setUpGraphCoords(bool q); // Used to setup the variables for the UV graph.
void serialPrintUV();

// First Screen Functions
void percentageOutput(int i);
void printWarning(); 
void printUV(); 
void graphUV(); 
void rePrintFirstScreen();

// Second Screen Functions
void printSecondScreen();
void printUV_SECONDSCREEN();
void printPercentage_SECONDSCREEN(int i);


#endif
