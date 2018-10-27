/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <SPI.h>
#include "Adafruit_MAX31855.h"

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

#define SERVO_PULSE 5

#define MAXDO   12 //18 on chip
#define MAXCS1   9 //15 on chip
#define MAXCS2   11 //17 on chip
#define MAXCS3   10 //16 on chip
#define MAXCLK  13// 19 on chip

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple1(MAXCLK, MAXCS1, MAXDO);
Adafruit_MAX31855 thermocouple2(MAXCLK, MAXCS2, MAXDO);
Adafruit_MAX31855 thermocouple3(MAXCLK, MAXCS3, MAXDO);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
Servo myservo;  // create servo object to control a servo

long counter;

void setup() {
  // Debugging output
  Serial.begin(9600);
  myservo.attach(SERVO_PULSE);  // attaches the servo on pin 9 to the servo object
  
  DeviceAddress tempDeviceAddress;
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 4);
  // Start up the library
  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.getAddress(tempDeviceAddress, 1);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.getAddress(tempDeviceAddress, 2);
  sensors.setResolution(tempDeviceAddress, 12);
  delay(3000);
  
}

uint8_t i=0;
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);

   counter++;
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
 sensors.requestTemperatures(); // Send the command to get temperatures 
 delay(1000);
  Serial.print(counter);
  Serial.print("|");
  double temp = sensors.getTempCByIndex(0);
  //double temp = thermocouple.readCelsius();
  //Serial.print(temp);
   //Serial.print("|");
  //double temp2 = sensors.getTempCByIndex(1);
  //Serial.print(temp2);
  // Serial.print("|");
  //double temp3 = sensors.getTempCByIndex(2);
 Serial.print(temp);
 
  lcd.setCursor(0,0);
  lcd.print("OneWire temp:");
  lcd.print(temp);
  Serial.print("|");
  lcd.setCursor(0, 2);
  temp = thermocouple3.read();
    if(isnan(temp)){
    temp=0;
  }
  lcd.print("Max3 temp: ") ;
  lcd.print(temp);
  Serial.print(temp);
    Serial.print("|");
  lcd.setCursor(0, 3);
  temp = thermocouple1.readCelsius();
  if(isnan(temp)){
    temp=0;
  }
  lcd.print("Max1 temp: ") ; 
  lcd.print(temp);
  Serial.print(temp);
   Serial.print("\n");
  //lcd.setCursor(9,0);
  //lcd.print("B=");
  //lcd.print(temp2);
   //lcd.setCursor(0,1);
  //lcd.print("C=");
  //lcd.print(temp3);
  delay(1000);
  testServo();
}

void testServo()
{
  int pos = 0;
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(40);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(40);                       // waits 15ms for the servo to reach the position
  }

}


