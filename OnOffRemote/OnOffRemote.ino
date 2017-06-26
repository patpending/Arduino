#include <XBee.h>

XBee xbee = XBee();

ZBRxIoSampleResponse ioSample = ZBRxIoSampleResponse();

XBeeAddress64 test = XBeeAddress64();

// what xbee pins have we got attached to which buttons
int greenButton = 2;
int redButton = 3;
unsigned char relayPin[4] = {4,5,6,7};

void setup() { 
  int i;
  // set all the relay pins to output mode
  for(i = 0; i < 4; i++)
  {
    pinMode(relayPin[i],OUTPUT);
  }
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  
  //attempt to read a packet    
  xbee.readPacket();
 
          
  if (xbee.getResponse().isAvailable()) {
    // got something from the xbee
 
    if (xbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE) {
      xbee.getResponse().getZBRxIoSampleResponse(ioSample);
      // its an IO sample!

      if (ioSample.containsDigital()) {
        // its a digital sample! We're in business!
  
  // RED BUTTON
        if(!ioSample.isDigitalOn(redButton))
        {
            digitalWrite(relayPin[0],HIGH);
        }
         if(ioSample.isDigitalOn(redButton))
        {
            digitalWrite(relayPin[0],LOW);
        }
  // GREEN BUTTON
        if(!ioSample.isDigitalOn(greenButton))
        {
            digitalWrite(relayPin[1],HIGH);
        }
         if(ioSample.isDigitalOn(greenButton))
        {
            digitalWrite(relayPin[1],LOW);
        }
        
      }      

    } 
}
}
