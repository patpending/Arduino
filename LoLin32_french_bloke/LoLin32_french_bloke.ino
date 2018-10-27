
#include <WiFi.h>
//https://www.arduino.cc/en/Reference/WiFi
#include <PubSubClient.h>
//https://github.com/knolleary/pubsubclient

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>


#define uS_TO_S_FACTOR 1000000 /* Conversion factor for u seconds to seconds */
#define TIME_TO_SLEEP 60        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int successCount = 0;
RTC_DATA_ATTR int errorCount = 0;

#define DEBUG 1

#if DEBUG
#define LOG(S) Serial.print(S);
#define ERROR(S) Serial.print(S);
#else
#define LOG(S)
#define ERROR(S) Serial.print(S);
#endif

#define WIFI_SSID ""
#define WIFI_PASS ""

const char MQTT_SERVER[] = "192.168.0.6";
const int MQTT_PORT = 1883;
double temp = 0.0;
int powerPin = 27;
// Define temp sensor
#define ONE_WIRE_BUS 14
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress;
  
void setup()
{
  Serial.begin(115200);
    // set the digital pin as output to power the OneWire:
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  //set the resolution for the temperature sensor
  sensors.begin();
  sensors.getAddress(tempDeviceAddress, 0);
  sensors.setResolution(tempDeviceAddress, 12);


    

  //-- Wifi -------------------------------------------------------------------
  WiFi.disconnect();
  LOG("Connecting to wifi: wlan");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  //-- Attente active du wifi --
  int wifiCount = 100;
  while (WiFi.status() != WL_CONNECTED && wifiCount--)
  {
    LOG(".");
    delay(100);
  }
  LOG("\n");
  if (WiFi.status() != WL_CONNECTED)
  {
    // Battery safety, go to sleep if failed
    ERROR("Failed to connect wifi: ");
    ERROR(WiFi.status());
    ERROR("\n");
    errorCount++;
    return;
  }
  LOG("Connected to wifi, with ip: ");
  LOG(WiFi.localIP());
  LOG("\n");

  //-- MQTT -------------------------------------------------------------------
  LOG("Connecting to MQTT\n");
  String boardId("lolin32lite");

  WiFiClient wifiClient;
  PubSubClient client(wifiClient);
  client.setServer(MQTT_SERVER, MQTT_PORT);
  if (!client.connect(boardId.c_str(), NULL, NULL))
  {
    // Battery safety, go to sleep if failed
    ERROR("Unable to connect MQTT\n");
    errorCount++;
    return;
  }
  LOG("Connected to MQTT\n");
  
  //get the temperature reading
  sensors.requestTemperatures(); // Send the command to get temperatures 
  temp = sensors.getTempCByIndex(0);
  LOG("Temperature: ");
  LOG(temp);
  LOG("C\n")
  digitalWrite(powerPin,LOW);
  if(temp >-50)
  {
    //-- Préparation du message -------------------------------------------------
    String payload = "{";
    payload += "\"success\":";
    payload += successCount;
    payload += ",\"error\":";
    payload += errorCount;
    payload += ",\"temperature\":";
    payload += temp;
    payload += "}";
  
    String topic = "sensors/ESP32/outside";
  
    // Send payload
    if (client.publish(topic.c_str(), payload.c_str(), true)) {
      LOG("Published\n");
    } else {
      ERROR("MQTT publish failed\n");
      errorCount++;
      return;
    }
    //client.loop();
  }
  client.disconnect();
  wifiClient.flush();
  
  //-- Increment boot number and print it every reboot ------------------------
  successCount++;
  delay(1000); // I don't know why, but I needed to wait for data to be
              // transmitted. Even with the flush. I did not manage however
              // to figure out where it came from.

  //-- Success ----------------------------------------------------------------
}

void loop()
{
  //-- Deep sleep -------------------------------------------------------------
  LOG("Entering deep sleep\n");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();

  // DEAD CODE AFTER THIS
  // DEAD CODE AFTER THIS
  // DEAD CODE AFTER THIS
}
