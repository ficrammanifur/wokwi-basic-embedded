/*
 * Integration 02: Sensor + FreeRTOS Task
 * 
 * Konsep: Membaca sensor menggunakan FreeRTOS task
 * 
 * Komponen:
 * - Potentiometer (GPIO 36)
 * - LED (GPIO 2)
 * 
 * Pinout:
 * - Sensor -> GPIO 36 (ADC)
 * - LED    -> GPIO 2
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

const int SENSOR_PIN = 36;
const int LED_PIN = 2;

// Queue for sensor data
QueueHandle_t sensorQueue;

// Sensor data structure
struct SensorData {
  int value;
  float voltage;
  int percentage;
  unsigned long timestamp;
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // ADC configuration
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  
  // Create queue
  sensorQueue = xQueueCreate(10, sizeof(SensorData));
  
  // Create tasks
  xTaskCreate(
    sensorTask,
    "Sensor Task",
    2048,
    NULL,
    1,
    NULL
  );
  
  xTaskCreate(
    processTask,
    "Process Task",
    2048,
    NULL,
    1,
    NULL
  );
  
  Serial.println("Sensor + FreeRTOS Integration Started");
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
    
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void processTask(void* parameter) {
  SensorData data;
  
  while (1) {
    // Receive from queue
    if (xQueueReceive(sensorQueue, &data, portMAX_DELAY) == pdPASS) {
      // Process data
      Serial.print("Sensor: ");
      Serial.print(data.value);
      Serial.print(" | ");
      Serial.print(data.percentage);
      Serial.println("%");
      
      // Control LED
      if (data.percentage > 50) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
