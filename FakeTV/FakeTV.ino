//DIY Fake TV
//Keep burglars at bay while you are away
//Created by Jonathan Bush
//Last Updated 3/24/2015
//Runnig on ATTiny 85

#include <Adafruit_NeoPixel.h>

#define PIN 6
int POTPIN = A1;

//Neopixel library provided by Adafruit
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int BRIGHTNESS = 0;
int RED = 0;
int BLUE = 0;
int GREEN = 0;
int TIMEDEL = 0;
int MAXBRIGHT = 0;
int potval = 0;


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(PIN,OUTPUT);
}

void loop() {
  
  potval = analogRead(POTPIN); //Reads analog value from Potentiometer/voltage divider
  //MAXBRIGHT = map(potval,0,1023,11,255); //Maps voltage divider reading to set max brightness btwn 11 and 255
  MAXBRIGHT = 50;
  BRIGHTNESS = random (10,MAXBRIGHT); //Change display brightness from 20% to 100% randomly each cycle
  RED = random (150 ,256); //Set the red component value from 150 to 255
  BLUE = random (150,256); //Set the blue component value from 150 to 255
  GREEN = random (150,256); //Set the green component value from 150 to 255
  TIMEDEL = random (300,2000); //Change the time interval randomly between 1/3 of a second to 2 seconds
  strip.setBrightness(BRIGHTNESS);
  colorWipe(strip.Color(RED, GREEN, BLUE),0); //Instantly change entire strip to new randomly generated color
  
  delay(TIMEDEL);
}
  
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
