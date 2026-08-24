/*
 * Queue - Queue Communication
 * 
 * Konsep: Mengirim data antar task menggunakan queue
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

const int LED_PIN = 2;

// Queue handle
QueueHandle_t dataQueue;

// Data structure
struct SensorData {
  int value;
  unsigned long timestamp;
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Queue Demo Started");
  
  // Create queue with 10 items
  dataQueue = xQueueCreate(10, sizeof(SensorData));
  
  if (dataQueue == NULL) {
    Serial.println("Failed to create queue");
    return;
  }
  
  // Create producer task
  xTaskCreate(
    producerTask,
    "Producer",
    2048,
    NULL,
    1,
    NULL
  );
  
  // Create consumer task
  xTaskCreate(
    consumerTask,
    "Consumer",
    2048,
    NULL,
    1,
    NULL
  );
  
  Serial.println("Queue created and tasks started");
}

void producerTask(void* parameter) {
  int counter = 0;
  SensorData data;
  
  while (1) {
    // Generate data
    data.value = random(0, 100);
    data.timestamp = millis();
    counter++;
    
    // Send to queue
    if (xQueueSend(dataQueue, &data, 0) == pdPASS) {
      Serial.print("Producer: Sent value ");
      Serial.print(data.value);
      Serial.print(" (Item ");
      Serial.print(counter);
      Serial.println(")");
    } else {
      Serial.println("Producer: Queue full!");
    }
    
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void consumerTask(void* parameter) {
  SensorData receivedData;
  
  while (1) {
    // Receive from queue
    if (xQueueReceive(dataQueue, &receivedData, portMAX_DELAY) == pdPASS) {
      Serial.print("Consumer: Received value ");
      Serial.print(receivedData.value);
      Serial.print(" at ");
      Serial.println(receivedData.timestamp);
      
      // Process data
      if (receivedData.value > 50) {
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
