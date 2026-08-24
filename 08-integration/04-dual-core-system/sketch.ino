/*
 * Integration 04: Dual Core + FreeRTOS
 * 
 * Konsep: Menjalankan task berbeda pada core berbeda
 * 
 * Komponen:
 * - Potentiometer (GPIO 36)
 * - LED1 (GPIO 2)
 * - LED2 (GPIO 4)
 * 
 * Pinout:
 * - Sensor -> GPIO 36 (ADC)
 * - LED1   -> GPIO 2
 * - LED2   -> GPIO 4
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

const int SENSOR_PIN = 36;
const int LED1_PIN = 2;
const int LED2_PIN = 4;

// Queue for inter-core communication
QueueHandle_t sensorQueue;

// Sensor data
struct SensorData {
  int value;
  float voltage;
  int percentage;
  unsigned long timestamp;
};

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  // ADC configuration
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  
  // Create queue
  sensorQueue = xQueueCreate(10, sizeof(SensorData));
  
  Serial.println("Dual Core + FreeRTOS Integration Started");
  Serial.print("Running on Core: ");
  Serial.println(xPortGetCoreID());
  
  // Create tasks pinned to different cores
  
  // Core 0: Sensor and MQTT (Network)
  xTaskCreatePinnedToCore(
    core0Task,
    "Core 0 Task",
    4096,
    NULL,
    2,
    NULL,
    0  // Core 0
  );
  
  // Core 1: Control and Processing
  xTaskCreatePinnedToCore(
    core1Task,
    "Core 1 Task",
    4096,
    NULL,
    1,
    NULL,
    1  // Core 1
  );
  
  Serial.println("Tasks pinned to different cores");
}

void core0Task(void* parameter) {
  Serial.print("Core 0 Task starting on Core: ");
  Serial.println(xPortGetCoreID());
  
  while (1) {
    // Read sensor
    SensorData data;
    data.value = analogRead(SENSOR_PIN);
    data.voltage = (data.value / 4095.0) * 3.3;
    data.percentage = map(data.value, 0, 4095, 0, 100);
    data.timestamp = millis();
    
    // Send to queue
    if (xQueueSend(sensorQueue, &data, 0) == pdPASS) {
      Serial.print("Core 0: Sensor value ");
      Serial.println(data.value);
    }
    
    // Blink LED1 on Core 0
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
    
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void core1Task(void* parameter) {
  Serial.print("Core 1 Task starting on Core: ");
  Serial.println(xPortGetCoreID());
  
  SensorData data;
  
  while (1) {
    // Receive from queue
    if (xQueueReceive(sensorQueue, &data, 100 / portTICK_PERIOD_MS) == pdPASS) {
      // Process data on Core 1
      Serial.print("Core 1: Processing value ");
      Serial.print(data.value);
      Serial.print(" (");
      Serial.print(data.percentage);
      Serial.println("%)");
      
      // Control LED2 based on sensor value
      if (data.percentage > 50) {
        digitalWrite(LED2_PIN, HIGH);
        Serial.println("Core 1: LED2 ON");
      } else {
        digitalWrite(LED2_PIN, LOW);
        Serial.println("Core 1: LED2 OFF");
      }
      
      // Calculate average (simulate processing)
      int average = 0;
      for (int i = 0; i < 10; i++) {
        average += data.value;
      }
      average = average / 10;
      
      Serial.print("Core 1: Average value = ");
      Serial.println(average);
    }
  }
}

void loop() {
  // Main loop - not used
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
