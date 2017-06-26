
#include <nikonIrControl.h>
#include <XBee.h>

 


// Define SoftSerial TX/RX pins
// Connect Arduino pin 8 to TX of usb-serial device
uint8_t ssRX = 8;
// Connect Arduino pin 9 to RX of usb-serial device
uint8_t ssTX = 9;
int CameraIrPin = 12; 
XBee xbee = XBee();
// SH + SL of your remote radio
XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, 0x4079D0EA);




void setup() { 
  pinMode(CameraIrPin, OUTPUT);
   Serial.begin(9600);
   xbee.begin(Serial);
   //wait for the xbee to join the PAN 
  delay(5000);
  switchLight1On();
  switchLight2On();
  //keep the lights on  for 1 min to allow the exposure to be set up correctly
  delay(60000);
}

void loop() {
  
switchLight1On();
switchLight2On();
delay(10000);
cameraSnap(CameraIrPin);
delay(10000);
switchLight1Off();
switchLight2Off();
delay(172000);
}

void switchLight1On() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '1' };
uint8_t d0Value[] = { 0x5 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  
remoteAtRequest.clearCommandValue();
}

void switchLight1Off() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '1' };
uint8_t d0Value[] = { 0x4 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  remoteAtRequest.clearCommandValue();
}

void switchLight2On() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '2' };
uint8_t d0Value[] = { 0x5 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  
remoteAtRequest.clearCommandValue();
}

void switchLight2Off() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '2' };
uint8_t d0Value[] = { 0x4 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  remoteAtRequest.clearCommandValue();
}
