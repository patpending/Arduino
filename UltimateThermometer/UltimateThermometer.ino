/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <LiquidTWI2.h>


// initialize the library with the numbers of the interface pins

// Connect via i2c, default address #0
LiquidTWI2 lcd(0);

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

long counter;

void setup() {
  // Debugging output
  Serial.begin(9600);
  DeviceAddress tempDeviceAddress;
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Start up the library
  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.getAddress(tempDeviceAddress, 1);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.getAddress(tempDeviceAddress, 2);
  sensors.setResolution(tempDeviceAddress, 12);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.setMCPType(LTI_TYPE_MCP23017);
  // set up the LCD's number of rows and columns:
  lcd.begin(20, 4);
  
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
  Serial.print(counter);
  Serial.print("|");
  double temp = sensors.getTempCByIndex(0);
  Serial.print(temp);
   Serial.print("|");
  double temp2 = sensors.getTempCByIndex(1);
  Serial.print(temp2);
   Serial.print("|");
  double temp3 = sensors.getTempCByIndex(2);
 Serial.print(temp3);
 Serial.print("|");
 double temp4 = sensors.getTempCByIndex(3);
 Serial.print(temp4);
  Serial.print("\n");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("A=");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("B=");
  lcd.print(temp2);
   lcd.setCursor(0,2);
  lcd.print("C=");
  lcd.print(temp3);
  lcd.setCursor(0,3);
  lcd.print("D=");
  lcd.print(temp4);
}

