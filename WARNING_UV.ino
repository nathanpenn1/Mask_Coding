

/////////////////////////////////////////////////////////
// Code for the Warning Sign for the 2.2 Inch LCD Screen.
/////////////////////////////////////////////////////////

// Including Arduino LCD libraries 
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// Setting pin definitions as defined within our "LCD screen"
#define cs   3
#define dc   5
#define rst  4

/* Default values from example code
#define cs   10
#define dc   9
#define rst  8
*/

// Create an instance of the LCD screen
// Provide pin locations for cs, dc and rst according to prototype. 
TFT lcd_screen = TFT(cs, dc, rst);

// Warning Text to display. 
char warningPart1 = "WARNING";
char warningPart2 = "Contains harmful UV LED's";
char warningPart3 = "which may harm your skin/eyes.";
char warningPart4 = "Please avoid opening the facemask";
char warningPart5 = "and contact the manufacturer";
char warningPart6 = "for any assistance.";

void setup() {

  // Must use .begin() before doing anything.
  lcd_screen.begin();

  // Make black background
  lcd_screen.background(0, 0, 0);

  // Set up text that will show up in the beginning. 
  lcd_screen.stroke(255, 255, 255); // Set text color to white
  lcd_screen.setTextSize(2); // text size to '2'
  lcd_screen.text("Insert Text :\n ", 0, 0); // text in the beginning 
  lcd_screen.setTextSize(5); // text size to '5'
}

void loop() {

  /* Printing warning part 1    */
  lcd_screen.stroke(255, 255, 255); // Setting to white color. 
  lcd_screen.text(warningPart1, 0, 20); // Printing warning part 1;
  delay(3000); // 3000 ms delay
  
  /* Printing warning part 2    */
  lcd_screen.stroke(0, 0, 0); // Erase the previous
  lcd_screen.stroke(255, 255, 255); // Setting to white color. 
  lcd_screen.text(warningPart2, 0, 20);
  delay(3000); // 3000 ms delay
  
    /* Printing warning part 3    */
  lcd_screen.stroke(0, 0, 0); // Erase the previous
  lcd_screen.stroke(255, 255, 255); // Setting to white color. 
  lcd_screen.text(warningPart3, 0, 20);
  delay(3000); // 3000 ms delay
  
    /* Printing warning part 4    */
  lcd_screen.stroke(0, 0, 0); // Erase the previous
  lcd_screen.stroke(255, 255, 255); // Setting to white color. 
  lcd_screen.text(warningPart4, 0, 20);
  delay(3000); // 3000 ms delay
  
    /* Printing warning part 5    */
  lcd_screen.stroke(0, 0, 0); // Erase the previous
  lcd_screen.stroke(255, 255, 255); // Setting to white color. 
  lcd_screen.text(warningPart5, 0, 20);
  delay(3000); // 3000 ms delay
  
    /* Printing warning part 6    */
  lcd_screen.stroke(0, 0, 0); // Erase the previous
  lcd_screen.stroke(255, 255, 255); // Setting to white color. 
  lcd_screen.text(warningPart6, 0, 20);
  delay(3000); // 3000 ms delay

}

