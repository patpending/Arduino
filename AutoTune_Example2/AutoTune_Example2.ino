#include <PID_AutoTune_v0.h>
// Start Include
#include <Wire.h>
#include <SPI.h>
#include <PID_v1.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidTWI2.h>

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

byte ATuneModeRemember = 2;
double input = 80, output = 50, setpoint = 60;
double kp = 200, ki = 0.5, kd = 2;

double kpmodel = 1.5, taup = 100, theta[50];
double outputStart = 5;
double aTuneStep = 50, aTuneNoise = 1, aTuneStartValue = 100;
unsigned int aTuneLookBack = 20;
// 5 second Time Proportional Output window
int windowSize = 5000;
int relay = 0;
unsigned long minWindow = 50;
unsigned long windowStartTime;

// Connect via i2c, default address #0
LiquidTWI2 lcd(0);

boolean tuning = true;
unsigned long  modelTime, serialTime;

PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

PID_ATune aTune(&input, &output);

//set to false to connect to the real world
boolean useSimulation = false;

void setup()
{
  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, windowSize);
  DeviceAddress tempDeviceAddress;
  sensors.begin();
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.getAddress(tempDeviceAddress, 1);
  sensors.setResolution(tempDeviceAddress, 12);
  sensors.getAddress(tempDeviceAddress, 2);
  sensors.setResolution(tempDeviceAddress, 12);
  if (useSimulation)
  {
    for (byte i = 0; i < 50; i++)
    {
      theta[i] = outputStart;
    }
    modelTime = 0;
  }
  //Setup the pid
  myPID.SetMode(AUTOMATIC);

  if (tuning)
  {
    tuning = false;
    changeAutoTune();
    tuning = true;
  }

  serialTime = 0;
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.setMCPType(LTI_TYPE_MCP23017);
  // set up the LCD's number of rows and columns:
  lcd.begin(20, 4);

}

void loop()
{

  unsigned long now = millis();

  if (!useSimulation)
  { //pull the input in from the real world
    sensors.requestTemperatures();
    // get the temperature
    input = sensors.getTempCByIndex(0); //get temparature from a dallas device
  }

  if (tuning)
  {
    byte val = (aTune.Runtime());
    if (val != 0)
    {
      tuning = false;
    }
    if (!tuning)
    { //we're done, set the tuning parameters
      kp = aTune.GetKp();
      ki = aTune.GetKi();
      kd = aTune.GetKd();
      myPID.SetTunings(kp, ki, kd);
      AutoTuneHelper(false);
    }
  }
  else myPID.Compute();

  if (useSimulation)
  {
    theta[30] = output;
    if (now >= modelTime)
    {
      modelTime += 100;
      DoModel();
    }
  }
  else
  {
    /************************************************
      do a super slow PID with a sliding window windowSize
    ************************************************/
    unsigned long now = millis();

    //if were at the end of the window. Advance to the next window
    if ((now - windowStartTime) > windowSize) {
      windowStartTime = now;
      sensors.requestTemperatures();
      // get the temperature
      input = sensors.getTempCByIndex(0); //get temparature from a dallas device
      myPID.Compute();
    }
    unsigned int outputInt = (int) output;
    if ((outputInt >= 0) && (outputInt > (millis() - windowStartTime))) {

      mcpDigitalWrite(OUTPUT1, HIGH);

    } else {

      mcpDigitalWrite(OUTPUT1, LOW);


    }
  }

  //send-receive with processing if it's time
  if (millis() > serialTime)
  {
    SerialReceive();
    SerialSend();
    serialTime += 500;
  }
}

void changeAutoTune()
{
  if (!tuning)
  {
    //Set the output to the desired starting frequency.
    output = aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(boolean start)
{
  if (start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
}


void SerialSend()
{
  Serial.print("setpoint: "); Serial.print(setpoint); Serial.print(" ");
  Serial.print("input: "); Serial.print(input); Serial.print(" ");
  Serial.print("output: "); Serial.print(output); Serial.print(" ");
  if (tuning) {
    Serial.println("tuning mode");
  } else {
    Serial.print("kp: "); Serial.print(myPID.GetKp()); Serial.print(" ");
    Serial.print("ki: "); Serial.print(myPID.GetKi()); Serial.print(" ");
    Serial.print("kd: "); Serial.print(myPID.GetKd()); Serial.println();
  }
}

void SerialReceive()
{
  if (Serial.available())
  {
    char b = Serial.read();
    Serial.flush();
    if ((b == '1' && !tuning) || (b != '1' && tuning))changeAutoTune();
  }
}

void DoModel()
{
  //cycle the dead time
  for (byte i = 0; i < 49; i++)
  {
    theta[i] = theta[i + 1];
  }
  //compute the input
  input = (kpmodel / taup) * (theta[0] - outputStart) + input * (1 - 1 / taup) + ((float)random(-10, 10)) / 100;

}
/**
   Method to write to the GPIOA register of the MCP23017 chip.
   Example mcpDigitalWrite(OUTPUT1, LOW);
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
