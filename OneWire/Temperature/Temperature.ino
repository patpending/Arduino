#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>


// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 10

//set up the pixel ring
#define PIN 9
int POTPIN = A1;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


//Neopixel vars
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

long counter;
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(PIN,OUTPUT);

  // Start up the library
  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}


void loop(void)
{ 
  counter++;
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures 
  Serial.print(counter);
  Serial.print("|");
  double temp = sensors.getTempCByIndex(0);
  Serial.print(temp);
  Serial.print("\n");
  delay(1000);
}


