#include <Wire.h>
#include <Tone.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
 unsigned int rpm;
 unsigned long timeold;
int counter;
hd44780_I2Cexp lcd;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.print("Ignition!");
    
   attachInterrupt(0, magnet_detect, RISING);//Initialize the intterrupt pin (Arduino digital pin 2)
counter=0;
   rpm = 0;
   timeold = 0;

        
}

void loop() {
 
}

 void magnet_detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   counter++;
   Serial.println("spark");
   Serial.print(counter);
   Serial.print("\n");
 }
