#include <Tone.h>
#include <Adafruit_NeoPixel.h>
#define NEO_PIN 6
int ledPin = 13;
int lives = 8;

int CHOPSTICKS = 2;
int speakerOut = 9;
// notes in the melody:

Tone myTone;
//Neopixel library provided by Adafruit
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEO_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(NEO_PIN, OUTPUT);
  pinMode(CHOPSTICKS, INPUT_PULLUP);
  myTone.begin(speakerOut);
  strip.setBrightness(50);
  updateStrip();
}

void loop() {
  //playPinky();
  int chopsticksTouched = digitalRead(CHOPSTICKS);
  if (chopsticksTouched == LOW)
  {
    //lose a life
    lives --;

    Serial.print(lives);
    Serial.print("\n");
    if (lives >= 0)
    {
      poo();
      updateStrip();

    }

    //wait a bit
    delay(1000);
    if (lives == 0)
    {
      playLoser();
    }
  }

}


void poo()
{

  myTone.play(NOTE_A3);
  delay(10);
  myTone.stop();
  delay(10);
  myTone.play(NOTE_A3);
  delay(10);
  myTone.stop();
  delay(10);
  myTone.play(NOTE_A3);
  delay(10);
  myTone.stop();
  delay(10);
}
void playLoser()
{
  myTone.play(NOTE_A3);

  delay(20);
  uint8_t wait = 100;
  uint32_t color = strip.Color(255, 0, 0);
  theaterChase(color, wait);
  
  myTone.play(NOTE_B3);
  myTone.play(NOTE_C3);
  delay(20);
  color = strip.Color(0, 255, 0);
  theaterChase(color, wait);
  color = strip.Color(0, 0, 255);
  theaterChase(color, wait);
  setToBlack();
  myTone.stop();
  delay(6000);
  lives = 8;
  updateStrip();
  
}
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void updateStrip()
{
  uint32_t color;
  if (lives > 6)
  {
    //green lives
    color = strip.Color(0, 255, 0);

  }
  else if ((lives > 3) && (lives <= 6))
  {
    //orange
    color = strip.Color(255, 255, 0);
  }
  else
  {
    //red
    color = strip.Color(255, 0, 0);
  }
  setToBlack();
  for (int i = 0; i < lives; i++)
  {
    strip.setPixelColor(i, color );
  }
  strip.show();

}
void setToBlack()
{
  for (int i = 0; i < 8; i++)
  {
    strip.setPixelColor(i, 0 );
  }
  strip.show();
}
void playPinky()
{

}

