/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <Adafruit_RGBLCDShield.h>

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   12 //18 on chip
#define MAXCS1   9 //15 on chip
#define MAXCLK  13// 19 on chip

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple1(MAXCLK, MAXCS1, MAXDO);


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
  
void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 4);
  
  lcd.clear();
  
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
   //lcd.clear();
   //lcd.setCursor(0, 0);
   //lcd.print("TC1 = ");
   //lcd.print(thermocouple1.readInternal());
   // lcd.setCursor(0, 1);
    //lcd.print("TC2 = ");
  // lcd.print(thermocouple2.readCelciusl());
  lcd.setCursor(0, 0);
  lcd.print("The Data Fabric");
  lcd.setCursor(0, 1);
  lcd.print("Is totally awesome!"); 
  lcd.setCursor(0, 2);
  lcd.print("Temp: ") ;
  lcd.print(thermocouple1.readCelsius());
  //lcd.setCursor(0, 3);
  //lcd.print("Bella is awesome");
     
  // double c = thermocouple.readCelsius();
  // lcd.setCursor(0, 1);
  // if (isnan(c)) 
  // {
  //   lcd.print("T/C Problem");
  // } 
  // else 
  // {
  //   lcd.print("C = "); 
    // lcd.print(c);
  //   lcd.print("  "); 
     //Serial.print("Thermocouple Temp = *");
     //Serial.println(c);
   //}
 
   delay(1000);
}
