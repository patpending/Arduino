
#include <WiFi.h>
//https://www.arduino.cc/en/Reference/WiFi
#include <PubSubClient.h>
//https://github.com/knolleary/pubsubclient

// Update these with values suitable for your network.
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;// a counter that survives in memory through the deep sleep cycle

const char* ssid = "Lobster Net";
const char* password = "lola2905";
const char* mqtt_server = "192.168.1.46";

WiFiClient espClient;
PubSubClient client(espClient);




void setup() {
  char msg[50];
  delay(1000);//give everything a second to wake up from sleep
  long wakeupTime = millis();
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
 
  /*
  First we configure the wake up source
  We set our ESP32 to wake up every n. seconds
  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);

   if (!client.connected()) {
    reconnect();
  }
  //client.loop();
  ++bootCount;
  snprintf (msg, 75, "hello world #%ld", bootCount);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("outTopic", msg);
  //shut down the wifi
  WiFi.disconnect();
  delay(2000);
  long now = millis();
  Serial.println("All done. Ive been awake for: "+String(now-wakeupTime));
  Serial.println("Going to sleep for " + String(TIME_TO_SLEEP) +" Seconds");
  
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.config(ip, dns, gateway, subnet); 
    WiFi.persistent(false);     // <-- prevents flash wearing?
  //WiFi.forceSleepWake();      // <-- WITHOUT THIS ESP CONNECTS ONLY AFTER FIRST FEW RESTARTS OR DOESN'T CONNECT AT ALL
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!!!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world: "+bootCount);
     
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
// This code is never called as we are running with deep sleep! Only setup gets called
 
}
