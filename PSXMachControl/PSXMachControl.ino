/*********************
//playstation controller constants
psxLeft  LITERAL1
psxDown LITERAL1
psxRight  LITERAL1
psxUP LITERAL1
psxStrt LITERAL1
psxSlct LITERAL1
psxSqu  LITERAL1
psxX  LITERAL1
psxO  LITERAL1
psxTri  LITERAL1
psxR1 LITERAL1
psxL1 LITERAL1
psxR2 LITERAL1
psxL2 LITERAL1


Keyboard functions
https://www.arduino.cc/en/Reference/KeyboardModifiers



**********************/

#include <Psx.h> //playstation lib  
#include <Keyboard.h>




//CONSTANTS


// the pins to use for the PSX controller
#define dataPin 8 //BROWN
#define cmndPin 9 // ORANGE
#define attPin 11 // YELLOW
#define clockPin 10 // BLUE

Psx Psx;                                          
unsigned int data = 0;    
unsigned int button =0;  
boolean buttonPressed = false;
//power red and black. use 3.3v on the psOne controller


void setup() {
  // Debugging output
  Serial.begin(9600);
  Keyboard.begin();
  //setup the PSX controller
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 20);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
}


void loop() {

    
   
    data = Psx.read(); 
         
    if (data) {

      /**
       * LEFT DIGITAL JOY PAD
       */
      //If up is pressed on the joystick
      if (data & psxUp) {

       if((buttonPressed==false)&&(button!=psxUp))
       {
        button=psxUp;
        buttonPressed=true;
        Keyboard.press(',');
       }
      }
      //If down is pressed on the joystick
      if (data & psxDown) {

       if((buttonPressed==false)&&(button!=psxDown))
       {
        button=psxDown;
        buttonPressed=true;
        Keyboard.press('.');
       }
      }
      //If left is pressed on the joystick
      if (data & psxLeft) {

       if((buttonPressed==false)&&(button!=psxLeft))
       {
        button=psxLeft;
        buttonPressed=true;
        Keyboard.press('/');
       }
      }
      //If left is pressed on the joystick
      if (data & psxRight) {

       if((buttonPressed==false)&&(button!=psxRight))
       {
        button=psxRight;
        buttonPressed=true;
        Keyboard.press('-');
       }
      }
      /**
       * RIGHT Colourful Buttons
       */
      //If Square button is pressed on the joystick
      if (data & psxSqu) {

       if((buttonPressed==false)&&(button!=psxSqu))
       {
        button=psxSqu;
        buttonPressed=true;
        Keyboard.press('=');
       }
      }
      //If Triangle button is pressed on the joystick
      if (data & psxTri) {

       if((buttonPressed==false)&&(button!=psxTri))
       {
        button=psxTri;
        buttonPressed=true;
        Keyboard.press('[');
       }
      }
      //If O button is pressed on the joystick
      if (data & psxO) {

       if((buttonPressed==false)&&(button!=psxO))
       {
        button=psxO;
        buttonPressed=true;
        Keyboard.press(']');
       }
      }
      //If X button is pressed on the joystick
      if (data & psxX) {

       if((buttonPressed==false)&&(button!=psxX))
       {
        button=psxX;
        buttonPressed=true;
        Keyboard.press('`');
       }
      }
       /**
       * big buttons
       */
       //If L1 button is pressed on the joystick
      if (data & psxL1) {

       if((buttonPressed==false)&&(button!=psxL1))
       {
        button=psxL1;
        buttonPressed=true;
        Keyboard.press('r');
       }
      }
       //If R1 button is pressed on the joystick
      if (data & psxR1) {

       if((buttonPressed==false)&&(button!=psxR1))
       {
        button=psxR1;
        buttonPressed=true;
        Keyboard.press('t');
       }
      }
      //If L2 button is pressed on the joystick
      if (data & psxL2) {

       if((buttonPressed==false)&&(button!=psxL2))
       {
        button=psxL2;
        buttonPressed=true;
        Keyboard.press('y');
       }
      }
      //If R2 button is pressed on the joystick
      if (data & psxR2) {

       if((buttonPressed==false)&&(button!=psxR2))
       {
        button=psxR2;
        buttonPressed=true;
        Keyboard.press('u');
       }
      }
    
    //If Select button is pressed on the joystick
      if (data & psxSlct) {

       if((buttonPressed==false)&&(button!=psxSlct))
       {
        button=psxSlct;
        buttonPressed=true;
        Keyboard.press('i');
       }
      }
    
    //If Select button is pressed on the joystick
      if (data & psxStrt) {

       if((buttonPressed==false)&&(button!=psxStrt))
       {
        button=psxStrt;
        buttonPressed=true;
        Keyboard.press('o');
       }
      }
    }

  // Release the pressed key 
  else  if (buttonPressed==true){
        buttonPressed=false;
        button=0;
        Keyboard.releaseAll();
      }
}
