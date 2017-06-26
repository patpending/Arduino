/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of XBee-Arduino.
 *
 * XBee-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XBee-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <XBee.h>
//#include <SoftwareSerial.h>

/*
This example is for Series 1 (10C8 or later firmware) or Series 2 XBee
Sends two Remote AT commands to configure the remote radio for I/O line monitoring

This example uses the SoftSerial library to view the XBee communication.  I am using a 
Modern Device USB BUB board (http://moderndevice.com/connect) and viewing the output
with the Arduino Serial Monitor.
*/

// Define SoftSerial TX/RX pins
// Connect Arduino pin 8 to TX of usb-serial device
uint8_t ssRX = 8;
// Connect Arduino pin 9 to RX of usb-serial device
uint8_t ssTX = 9;

XBee xbee = XBee();
// SH + SL of your remote radio
XBeeAddress64 remoteAddress = XBeeAddress64(0x0013a200, 0x4079D0EA);




void setup() { 
  Serial.begin(9600);
  xbee.begin(Serial);
  delay(5000);
}

void loop() {
  
switchPlug1On();
delay(5000);
switchPlug1Off();
delay(5000);
switchPlug2On();
delay(5000);
switchPlug2Off();
delay(5000);
 
}

void switchPlug1On() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '1' };
uint8_t d0Value[] = { 0x5 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  
remoteAtRequest.clearCommandValue();
}

void switchPlug1Off() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '1' };
uint8_t d0Value[] = { 0x4 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  remoteAtRequest.clearCommandValue();
}

void switchPlug2On() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '2' };
uint8_t d0Value[] = { 0x5 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  
remoteAtRequest.clearCommandValue();
}

void switchPlug2Off() {
// Set DIO0 (pin 20) to Analog Input
uint8_t d0Cmd[] = { 'D', '2' };
uint8_t d0Value[] = { 0x4 };
// Create a remote AT request with the IR command
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(remoteAddress, d0Cmd, d0Value, sizeof(d0Value));
xbee.send(remoteAtRequest);  remoteAtRequest.clearCommandValue();
}
