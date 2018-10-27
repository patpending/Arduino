#include <Wire.h>
#include <Tone.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  3;      // the number of the LED pin
int speakerOut = 9;
hd44780_I2Cexp lcd;

int buttonState=0;
Tone myTone;
void setup() {
    // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // put your setup code here, to run once:
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  myTone.begin(speakerOut);
  lcd.print("Do Mo Flo Smash!");
  delay(3000);
  lcd.setBacklight(1);

}

void loop() {

  lcd.clear();
  lcd.setCursor(8,0);
  lcd.print("3");
  delay(1000);
  lcd.setCursor(8,0);
  lcd.print("2");
  delay(1000);
  lcd.setCursor(8,0);
  lcd.print("1");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  int randNumber = random(3000, 10000);
  delay(randNumber);
   myTone.play(NOTE_A3);
  delay(10);
  lcd.print("*** SMASH IT ***");
  digitalWrite(ledPin, HIGH);
  long timeNow=millis();
  buttonState = digitalRead(buttonPin);
  while(buttonState==HIGH)
  {
    buttonState = digitalRead(buttonPin);
  }
  myTone.stop();
  lcd.clear();
  digitalWrite(ledPin,LOW);
  lcd.print("You scored: ");
  lcd.print(millis()-timeNow);
  lcd.setCursor(0,1);
  lcd.print("Play again..");
  delay(2000);
  buttonState = digitalRead(buttonPin);
  while(buttonState==HIGH)
  {
    buttonState = digitalRead(buttonPin);
  }

}
