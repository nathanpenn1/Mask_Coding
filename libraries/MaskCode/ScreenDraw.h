#ifndef SCREENDRAW_H
#define SCREENDRAW_H

void screenSetup();

void drawingF(int Cx, int Cy, int R, int G, int B, int textSize);

void percentageOutput(int i, int R, int G, int B);

void printWarning(); // Raven 3/17/21

void printUV(); // Raven 3/6/21

void graphUV(); // Raven 3/6/21

void read_y2(); // Raven 3/12/21

void checkFrameTime(); // Raven 3/22/2021

void updateArray(int data);

void calcCoordinates(int val[], int value);

void drawLineGraph();

void draw( int R, int G, int B);

#endif