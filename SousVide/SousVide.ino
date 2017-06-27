/*********************

 Example code for the Adafruit RGB Character LCD Shield and Library

 This code displays text on the shield, and also reads the buttons on the keypad.
 When a button is pressed, the backlight changes color.

 **********************/

// Start Include
#include <Wire.h>
#include <LiquidTWI2.h>
#include <SPI.h>
#include <PID_v1.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//End includes
// ************************************************
// Pins and such
// ************************************************
//Digital pin 2 (4 on the actual chip)
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// Stuff for the MCP23017 OUTPUT. Here we write to the GPIOA bank and only use the 4 pins as below
#define OUTPUT1 1 //Blue-white/Plug pin 4
#define OUTPUT2 2 //Orange/Plug pin 2
#define OUTPUT3 3 //Blue/Plug pin 1
#define OUTPUT4 4 //Green/Plig pin 6
// Plug Pin 3 and 5 (orange-white, green-white) are earth
byte REGISTER = 0x00;
int relay = 0;
unsigned int statsInterval = 1000; //how often were going to send info to the Raspberry pi
unsigned int screenRefreshInterval = 2000; //how often were going to refresh the LCD screen
unsigned long lastStatsUpdateTime, lastScreenUpdateTime = 0;

// Connect via i2c, default address #0
LiquidTWI2 lcd(0);

long counter, window;  // create a counter to use for timeseries output
int activityMon = 0;

// ************************************************
// PID Variables and constants
// ************************************************
double kp = 300, ki = 5, kd = 1;
//Define Variables we'll be connecting to
double input, output;
double setpoint = 60;
//Specify the links and initial tuning parameters
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);


// 5 second Time Proportional Output window
int windowSize = 5000;
unsigned long minWindow = 50;
unsigned long windowStartTime;

byte degree[8] = // define the degree symbol
		{
		B00110,
		B01001,
		B01001,
		B00110,
		B00000,
		B00000,
		B00000,
		B00000 };

void setup() {

	Serial.begin(9600);  //start the serial port

	// set up the LCD's number of columns and rows:
	lcd.setMCPType(LTI_TYPE_MCP23017);
	// set up the LCD's number of rows and columns:
	lcd.begin(20, 4);
	//show the splash screen
	lcd.print("Sous Vide");
	delay(2000);

	//turn the PID on
	//Setup the pid
	myPID.SetMode(AUTOMATIC);


	/**
	 * Get the dallas sensors working. @TODO this should really be some sort of loop
	 * Here we set them to 12bit resolution
	 */

	DeviceAddress tempDeviceAddress;
	sensors.begin();
	sensors.getAddress(tempDeviceAddress, 0);
	sensors.setResolution(tempDeviceAddress, 12);
	sensors.getAddress(tempDeviceAddress, 1);
	sensors.setResolution(tempDeviceAddress, 12);
	sensors.getAddress(tempDeviceAddress, 2);
	sensors.setResolution(tempDeviceAddress, 12);
	mcpDigitalWrite(OUTPUT1, LOW);

	//tell the PID to range between 0 and the full window size
	myPID.SetOutputLimits(0, windowSize);
	myPID.SetSampleTime(1000);
	myPID.Compute();
}

void loop() {

	int now = millis();
	sensors.requestTemperatures();
	// get the temperature
	input = sensors.getTempCByIndex(0);	//get temparature from a dallas device

	controlRelay(); //control relay **and compute** need a better name
	//Check if its time to send stats. The stats are running slower than the PID. only update at the refresh period
	if (now - lastStatsUpdateTime >= statsInterval) {
		counter++;
		serialSend();
		lastStatsUpdateTime = now;
	}

	// Check if its time to update the LCD

	if (now - lastScreenUpdateTime >= screenRefreshInterval) {
		updateDisplay();
		lastScreenUpdateTime = now;
	}

}

void controlRelay() {
	/************************************************
	 * do a super slow PID with a sliding window windowSize
	 ************************************************/
	unsigned long now = millis();

	//if were at the end of the window. Advance to the next window
	if ((now - windowStartTime) > windowSize) {

		sensors.requestTemperatures();
		// get the temperature
		input = sensors.getTempCByIndex(0);	//get temparature from a dallas device
		myPID.Compute();
		windowStartTime = now;
		window++;
	}
	unsigned int outputInt = (int) output;
	if ((outputInt +600> (millis() - windowStartTime))) {
		if (relay == 0) {
			mcpDigitalWrite(OUTPUT1, HIGH);
			relay = 1;
		}
	} else {
		if (relay == 1) {
			relay = 0;
			mcpDigitalWrite(OUTPUT1, LOW);
		}

	}
}

/**
 * Update the LCD Display
 */
void updateDisplay() {
	lcd.setCursor(0, 0);
	lcd.print("Water  :");
	lcd.print(input);
	lcd.setCursor(19, 0);
	if (activityMon == 0) {
		activityMon = 1;
		lcd.print("|");
	} else {
		activityMon = 0;
		lcd.print("-");
	}

	lcd.setCursor(0, 1);

	lcd.print("P:");
	lcd.print(kp);
	lcd.print(" I:");
	lcd.print(ki);
	lcd.print(" D:");
	lcd.print(kd);
	lcd.setCursor(0, 2);
	lcd.print("Set:");
	lcd.print(setpoint);
	lcd.createChar(1, degree);
	lcd.setCursor(0, 3);
	lcd.print("Relay:");
	lcd.print(relay);

}

/**
 * Write pipe separated data to the serial/XBEE to be received by the raspberry pi
 */
void serialSend() {
//	Serial.print(counter);
//	Serial.print("|");
//	Serial.print(input);
//	Serial.print("|");
//	Serial.print(relay);
//	Serial.print("|");
//	Serial.print(output);
//	Serial.print("|");
//	Serial.print(tuning);
//	Serial.print("|");
//	Serial.print("");
//	Serial.print("|");
//	Serial.print(kp);
//	Serial.print("|");
//	Serial.print(ki);
//	Serial.print("|");
//	Serial.print(kd);
//	Serial.print("\r\n");

	Serial.print(output);
	Serial.print("|");
	Serial.print(windowStartTime);
	Serial.print("|");
	Serial.print(window);
	Serial.print("|");
	Serial.print(relay);
	Serial.print("|");
	Serial.print(input);
	Serial.print("\r\n");
}

/**
 * Method to write to the GPIOA register of the MCP23017 chip.
 * Example mcpDigitalWrite(OUTPUT1, LOW);
 */
void mcpDigitalWrite(int pin, boolean value) {

	uint8_t oldRegister = REGISTER;
	REGISTER ^= (-value ^ REGISTER) & (1 << pin);

	if (oldRegister != REGISTER) {
		// now write it to the MCP23017 over I2C
		Wire.beginTransmission(0x20);
		Wire.write(0x12); // GPIOA
		Wire.write(REGISTER); // port A
		Wire.endTransmission();
	}
}


