/*
 * MQTT - MQTT Communication
 * 
 * Konsep: Komunikasi IoT menggunakan protokol MQTT
 * 
 * Komponen:
 * - ESP32 dengan WiFi dan MQTT
 * 
 * Pinout:
 * - Tidak ada pin khusus
 */

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT Broker
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/test";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublish = 0;
int counter = 0;

void setup() {
  Serial.begin(115200);
  
  Serial.println("MQTT Demo Started");
  
  // Connect to WiFi
  connectWiFi();
  
  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
}

void loop() {
  // Maintain MQTT connection
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
  
  // Publish data every 5 seconds
  if (millis() - lastPublish > 5000) {
    lastPublish = millis();
    counter++;
    
    String payload = "Hello from ESP32 #" + String(counter);
    client.publish(mqtt_topic, payload.c_str());
    
    Serial.print("Published: ");
    Serial.println(payload);
  }
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    
    if (client.connect("ESP32Client")) {
      Serial.println("Connected!");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}
