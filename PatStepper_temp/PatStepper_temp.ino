/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:

#include <Psx.h> //playstation lib  



// the pins to use for the PSX controller
#define dataPin 8 //BROWN
#define cmndPin 9 // ORANGE
#define attPin 11 // YELLOW
#define clockPin 10 // BLUE
Psx Psx;                                                  // Initializes the library
unsigned int data = 0;      
//power red and black. use 3.3v on the psOne controller



void setup() {
 
  
  //setup the PSX controller
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
           Serial.begin(9600);                                               // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
}


void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):



  //uint8_t buttons = lcd.readButtons();
  //if (buttons & BUTTON_UP) {
  data = Psx.read();      
  if (data) {
     
 
   
    if (data & psxUp) {
    
     Serial.println("up");
    }
    else if (data & psxDown) {
      
    }
    else if (data & psxR1) {
      
    }
    else if (data & psxL1) {
     
    }
    else if (data & psxLeft) 
    {
    
    }
    else if (data & psxRight )
    {
     
    }
    else if (data & psxSlct )
    {
    
    }
    else if (data & psxX) {//rotate the number of degrees set
    
    }
    
  }
  
}


