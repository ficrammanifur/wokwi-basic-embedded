/*
 * Mutex - Mutex
 * 
 * Konsep: Mengamankan shared resource menggunakan mutex
 * 
 * Komponen:
 * - LED1 (D2)
 * - LED2 (D4)
 * 
 * Pinout:
 * - LED1 -> GPIO 2
 * - LED2 -> GPIO 4
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

const int LED1_PIN = 2;
const int LED2_PIN = 4;

// Shared resource
int sharedCounter = 0;

// Mutex handle
SemaphoreHandle_t mutex;

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  Serial.println("Mutex Demo Started");
  
  // Create mutex
  mutex = xSemaphoreCreateMutex();
  
  if (mutex == NULL) {
    Serial.println("Failed to create mutex");
    return;
  }
  
  // Create tasks that access shared resource
  xTaskCreate(
    task1,
    "Task 1",
    2048,
    NULL,
    1,
    NULL
  );
  
  xTaskCreate(
    task2,
    "Task 2",
    2048,
    NULL,
    2,
    NULL
  );
  
  Serial.println("Mutex created and tasks started");
}

void task1(void* parameter) {
  while (1) {
    // Try to acquire mutex
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      // Access shared resource
      sharedCounter++;
      Serial.print("Task 1: Counter = ");
      Serial.println(sharedCounter);
      
      digitalWrite(LED1_PIN, HIGH);
      vTaskDelay(200 / portTICK_PERIOD_MS);
      digitalWrite(LED1_PIN, LOW);
      
      // Release mutex
      xSemaphoreGive(mutex);
    }
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void* parameter) {
  while (1) {
    // Try to acquire mutex
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      // Access shared resource
      sharedCounter += 2;
      Serial.print("Task 2: Counter = ");
      Serial.println(sharedCounter);
      
      digitalWrite(LED2_PIN, HIGH);
      vTaskDelay(300 / portTICK_PERIOD_MS);
      digitalWrite(LED2_PIN, LOW);
      
      // Release mutex
      xSemaphoreGive(mutex);
    }
    
    vTaskDelay(1500 / portTICK_PERIOD_MS);
  }
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
