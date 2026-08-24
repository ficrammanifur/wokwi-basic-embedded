/*
 * Dual Core - Dual Core Execution
 * 
 * Konsep: Menjalankan task pada Core 0 dan Core 1
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

const int LED1_PIN = 2;
const int LED2_PIN = 4;

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  Serial.println("Dual Core Demo Started");
  
  // Get core information
  Serial.print("Running on Core: ");
  Serial.println(xPortGetCoreID());
  
  // Create task on Core 0
  xTaskCreatePinnedToCore(
    core0Task,
    "Core 0 Task",
    2048,
    NULL,
    1,
    NULL,
    0  // Core 0
  );
  
  // Create task on Core 1
  xTaskCreatePinnedToCore(
    core1Task,
    "Core 1 Task",
    2048,
    NULL,
    1,
    NULL,
    1  // Core 1
  );
  
  Serial.println("Tasks pinned to different cores");
}

void core0Task(void* parameter) {
  while (1) {
    digitalWrite(LED1_PIN, HIGH);
    Serial.print("Core 0: LED1 ON - Core ID: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    digitalWrite(LED1_PIN, LOW);
    Serial.print("Core 0: LED1 OFF - Core ID: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void core1Task(void* parameter) {
  while (1) {
    digitalWrite(LED2_PIN, HIGH);
    Serial.print("Core 1: LED2 ON - Core ID: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(750 / portTICK_PERIOD_MS);
    
    digitalWrite(LED2_PIN, LOW);
    Serial.print("Core 1: LED2 OFF - Core ID: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(750 / portTICK_PERIOD_MS);
  }
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
