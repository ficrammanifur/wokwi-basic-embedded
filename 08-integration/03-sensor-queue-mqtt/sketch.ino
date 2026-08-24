/*
 * Integration 03: Sensor + Queue + MQTT
 * 
 * Konsep: Membaca sensor, kirim ke queue, publish ke MQTT
 * 
 * Komponen:
 * - Potentiometer (GPIO 35)
 * - LED (GPIO 2)
 * 
 * Pinout:
 * - Sensor -> GPIO 35 (ADC)
 * - LED    -> GPIO 2
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT Broker
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqtt_port = 1883;

const int SENSOR_PIN = 35;
const int LED_PIN = 2;

// Queue
QueueHandle_t sensorQueue;

// Sensor data structure
struct SensorData {
  int value;
  float voltage;
  int percentage;
  unsigned long timestamp;
};

// MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // ADC configuration
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  
  // Connect WiFi
  connectWiFi();
  
  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
  
  // Create queue
  sensorQueue = xQueueCreate(10, sizeof(SensorData));
  
  // Create tasks
  xTaskCreate(
    sensorTask,
    "Sensor Task",
    4096,
    NULL,
    2,
    NULL
  );
  
  xTaskCreate(
    mqttTask,
    "MQTT Task",
    4096,
    NULL,
    1,
    NULL
  );
  
  Serial.println("Sensor + Queue + MQTT Integration Started");
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

void sensorTask(void* parameter) {
  SensorData data;
  
  while (1) {
    // Read sensor
    data.value = analogRead(SENSOR_PIN);
    data.voltage = (data.value / 4095.0) * 3.3;
    data.percentage = map(data.value, 0, 4095, 0, 100);
    data.timestamp = millis();
    
    // Send to queue
    if (xQueueSend(sensorQueue, &data, 0) != pdPASS) {
      Serial.println("Queue full!");
    }
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void mqttTask(void* parameter) {
  SensorData data;
  
  while (1) {
    // Maintain MQTT connection
    if (!client.connected()) {
      reconnectMQTT();
    }
    client.loop();
    
    // Receive from queue with timeout
    if (xQueueReceive(sensorQueue, &data, 100 / portTICK_PERIOD_MS) == pdPASS) {
      // Publish to MQTT
      String payload = String(data.value) + "," + 
                       String(data.voltage, 2) + "," + 
                       String(data.percentage);
      
      if (client.publish("esp32/sensor", payload.c_str())) {
        Serial.println("Published to MQTT: " + payload);
        
        // Control LED based on sensor
        if (data.percentage > 50) {
          digitalWrite(LED_PIN, HIGH);
        } else {
          digitalWrite(LED_PIN, LOW);
        }
      }
    }
  }
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
    
    if (client.connect("ESP32Sensor")) {
      Serial.println("Connected!");
      client.subscribe("esp32/control");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  }
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
