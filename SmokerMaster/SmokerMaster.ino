/*********************

  Example code for the Adafruit RGB Character LCD Shield and Library

  This code displays text on the shield, and also reads the buttons on the keypad.
  When a button is pressed, the backlight changes color.

**********************/

// Start Include
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Servo.h>
#include <SPI.h>
#include "Adafruit_MAX31855.h"2
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
//End includes

//Start My contants and global variables
int fullyOpen = 0;
int fullyClosed = 70;
double smoker = 0, meat = 0;
int valvePos = 0;
double setpoint = 140.0;
unsigned int statsInterval = 1000;
unsigned int milisSinceLastUpdate = 0L;
unsigned long lastUpdteTime =0;

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//Set up the servo motor on pin 5
#define SERVO_PULSE 5

//Set up the clock, data and chip select pins for the thermocouple boards
#define MAXDO   12 //18 on chip
#define MAXCS1   9 //15 on chip
//#define MAXCS2   11 //17 on chip
#define MAXCS3   10 //16 on chip
#define MAXCLK  13// 19 on chip

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple1(MAXCLK, MAXCS1, MAXDO);
//Adafruit_MAX31855 thermocouple2(MAXCLK, MAXCS2, MAXDO);
Adafruit_MAX31855 thermocouple3(MAXCLK, MAXCS3, MAXDO);


Servo myservo;  // create servo object to control a servo
long counter;// create a counter to use for timeseries output
int activityMon = 0;

//End my constants and global variables


//Start PID and Autotune params
double input = 0, output = 0;
double kp = 2, ki = 0.5, kd = 2;
byte ATuneModeRemember = 2;
double kpmodel = 1.5, taup = 100, theta[50];
double outputStart = 5;


double aTuneStep = 50, aTuneNoise = 1, aTuneStartValue = 100;
unsigned int aTuneLookBack = 20;

boolean tuning = false;

unsigned long  modelTime, serialTime;

PID myPID(&input, &output, &setpoint, kp, ki, kd, REVERSE);
PID_ATune aTune(&input, &output);



void setup() {

  Serial.begin(9600);
  myservo.attach(SERVO_PULSE);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("Smoker Master");
  delay(1000);
  input = thermocouple1.readCelsius();
  //turn the PID on
  //Setup the pid
  myPID.SetMode(AUTOMATIC);

  if (tuning)
  {
    tuning = false;
    changeAutoTune();
    tuning = true;
  }

  serialTime = 0;
}

void loop() {


  // get the temperature
  input = thermocouple1.readCelsius();
  meat = thermocouple3.readCelsius();
  updateDisplay();
  if (input > 0.0) // only do stuff if we havent got a duff reading from the thermocouple
  {
    counter++;
    if (tuning)
    {
      byte val = (aTune.Runtime());
      if (val != 0)
      {
        tuning = false;
      }
      if (!tuning)
      { //we're done, set the tuning parameters
        kp = aTune.GetKp();
        ki = aTune.GetKi();
        kd = aTune.GetKd();
        myPID.SetTunings(kp, ki, kd);
        AutoTuneHelper(false);
      }
    }
    else myPID.Compute();
    valvePos = calculateValvePosition(output);
    setValve(valvePos);

    if((milisSinceLastUpdate ==0L)||(milisSinceLastUpdate>=statsInterval))
    {
    	serialSend();
    }
  }
  delay(1000);
}

int calculateValvePosition(double output) {

  double range = fullyClosed - fullyOpen;
  double pos = (range / 255) * output;
  return (int)pos;
}

void setValve(int pos)
{
  myservo.write(pos);

}

void updateDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print("Smoker  :");
  lcd.print(input);
  lcd.setCursor(19, 0);
  if (activityMon == 0) {
    activityMon = 1;
    lcd.print("|");
  }
  else {
    activityMon = 0;
    lcd.print("-");
  }


  lcd.setCursor(0, 1);
  lcd.print("Meat    :");
  lcd.print(meat);
  lcd.setCursor(0, 2);
  lcd.print("Setpoint:");
  lcd.print(setpoint);
  lcd.setCursor(0, 3);
  lcd.print("Valve   :");
  lcd.print(valvePos);

}
void changeAutoTune()
{
  if (!tuning)
  {
    //Set the output to the desired starting frequency.
    output = aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(boolean start)
{
  if (start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
}


void serialSend()
{
  //Print to the data logger
  Serial.print(counter);
  Serial.print("|");
  Serial.print(input);
  Serial.print("|");
  Serial.print(meat);
  Serial.print("|");
  Serial.print(output);
  Serial.print("|");
  Serial.print(tuning);
  Serial.print("|");
  Serial.print(valvePos);
  Serial.print("|");
  Serial.print(kp);
  Serial.print("|");
  Serial.print(ki);
  Serial.print("|");
  Serial.print(kd);
  Serial.print("\r\n");
}

void SerialReceive()
{
  if (Serial.available())
  {
    char b = Serial.read();
    Serial.flush();
    if ((b == '1' && !tuning) || (b != '1' && tuning))changeAutoTune();
  }
}

void DoModel()
{
  //cycle the dead time
  for (byte i = 0; i < 49; i++)
  {
    theta[i] = theta[i + 1];
  }
  //compute the input
  input = (kpmodel / taup) * (theta[0] - outputStart) + input * (1 - 1 / taup) + ((float)random(-10, 10)) / 100;

}


