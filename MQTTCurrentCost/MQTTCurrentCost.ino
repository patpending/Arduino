#include <Wire.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <SoftwareSerial.h>

SoftwareSerial currentCost(14, 12, false, 256);


/************ WIFIInformation (CHANGE THESE FOR YOUR SETUP) ******************/
const char* ssid = "****"; //type your WIFI information inside the quotes
const char* password = "*****";




/**************************** OTA **************************************************/
#define SENSORNAME "currentcost" //change this to whatever you want to call your device
#define OTApassword "*****" //the password you will need to enter to upload remotely via the ArduinoIDE
int OTAport = 8266;
int lastMsg = 0;


/************* MQTT  **************************/
const String topic = "sensors/ESP8266/currentcost";
const char* mqtt_server = "192.168.0.6";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port = 1883;
#define MQTT_MAX_PACKET_SIZE 512

WiFiClient espClient;
PubSubClient client(espClient);
double temperature;

void setup() {
  Serial.begin(9600);
  currentCost.setTimeout(1000);
  currentCost.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  //OTA SETUP
  ArduinoOTA.setPort(OTAport);
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(SENSORNAME);

  // No authentication by default
  ArduinoOTA.setPassword((const char *)OTApassword);

  ArduinoOTA.begin();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  IPAddress ip(192, 168, 0, 212);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}

/********************************** RECONNECT*****************************************/
void reconnectToMQTT() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    client.connect(SENSORNAME, mqtt_username, mqtt_password);
    delay(5000);
  }
}

String parseMessage(String message) {
  int power = message.substring(message.indexOf("<ch1><watts>") + 12, message.indexOf("</watts></ch1>")).toInt();
  float temp = message.substring(message.indexOf("<tmpr>") + 6, message.indexOf("</tmpr>")).toFloat();

  String payload = "{";
  payload += "\"power\":";
  payload += power;
  payload += ",\"temperature\":";
  payload += temp;
  payload += "}";
  return payload;
}

void loop() {

  if (!client.connected()) {
    reconnectToMQTT();
  }

  if (WiFi.status() != WL_CONNECTED) {
    delay(1);
    setup_wifi();
    return;
  }
  client.loop();

  ArduinoOTA.handle();

  String temp;
  while (currentCost.available())
  {
    temp += currentCost.readString();
  }

  if (temp.length() > 100)
  {
    String payload = parseMessage(temp);
    Serial.println(payload);
    client.publish(topic.c_str(), payload.c_str(), true);
    temp = "";
  }
}


