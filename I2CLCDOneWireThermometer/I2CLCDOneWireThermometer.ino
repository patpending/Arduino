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

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 6

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
  Serial.print("\n");
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("A=");
  lcd.print(temp);
  lcd.setCursor(9,0);
  lcd.print("B=");
  lcd.print(temp2);
   lcd.setCursor(0,1);
  lcd.print("C=");
  lcd.print(temp3);
  
  
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
    
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
     
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
     
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
      
    }
  }
}
