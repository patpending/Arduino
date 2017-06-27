/*********************


This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include <Psx.h> //playstation lib  


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();



//CONSTANTS

int stepDelay =2; //delay between step pulses
int microsteps = 2;
int jogSteps=20;//number of steps to jog with R/L presses
int stepsPerRevolution = 200;

long gearRatio = 90;//how many rotations of the shaft per rotation of the table
long microstepsPerRevolution = microsteps * stepsPerRevolution*gearRatio;
double degreesPerMicrostep = 360.00/microstepsPerRevolution;


//Pins for the stepper motor
int STEP_PIN = 7;
int DIR_PIN = 5;
// the pins to use for the PSX controller
#define dataPin 8 //BROWN
#define cmndPin 9 // ORANGE
#define attPin 11 // YELLOW
#define clockPin 10 // BLUE
Psx Psx;                                                  // Initializes the library
unsigned int data = 0;      
//power red and black. use 3.3v on the psOne controller


double degreesPerStep=30;
int stepNo=0;
double positionDeg =0.0;

void setup() {
  // Debugging output
  Serial.begin(9600);
  Serial.print("degreesPerMicrostep: ");
  Serial.print(degreesPerMicrostep);
  Serial.println(" steps per table revolution: ");
  Serial.println(microstepsPerRevolution);
  // initialize the digital pin as an output.
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT); 
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Pat's Divider");
  delay(2000);
  lcd.clear();
  printStat();
  
  //setup the PSX controller
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
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
     
 
    lcd.setCursor(0,0);
    if (data & psxUp) {
     degreesPerStep += 1;
     
    }
    else if (data & psxDown) {
      degreesPerStep -= 1;
    }
    else if (data & psxR1) {
      degreesPerStep += 0.01;
    }
    else if (data & psxL1) {
      degreesPerStep -= 0.01;
    }
    else if (data & psxLeft) 
    {
     digitalWrite(DIR_PIN,LOW);
      moveMotor(jogSteps);
    }
    else if (data & psxRight )
    {
      digitalWrite(DIR_PIN,HIGH);
      moveMotor(jogSteps);
    }
    else if (data & psxSlct )
    {
      stepNo = 0;
      positionDeg=0.00;
    }
    else if (data & psxX) {//rotate the number of degrees set
     moveMotor(convertDegreesToSteps(degreesPerStep));
     stepNo+=1;
     positionDeg += degreesPerStep;
     if(positionDeg >= 360)
     {
        positionDeg = positionDeg-360; 
     }
    
    }
    printStat();
  }
  
  
}

void moveMotor(long steps)
  {
    Serial.print("moving ");
    Serial.print(steps);
    Serial.print(" steps");
    for(int i =0;i<steps;i++)
   {
     
      digitalWrite(STEP_PIN, HIGH);
      delay(stepDelay);
      digitalWrite(STEP_PIN, LOW);
      
   } 
  }
  long convertDegreesToSteps(double degrees)
  {
     return degrees / degreesPerMicrostep;
  }
  void printStat()
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Deg/stp: ");
  lcd.print(degreesPerStep);
  
  lcd.setCursor(0, 1);
  lcd.print("Stp:");
  lcd.print(stepNo);
  lcd.print(" Pos: ");
  lcd.print(positionDeg);
  }
