/*
 * Semaphore - Semaphore
 * 
 * Konsep: Sinkronisasi antar task menggunakan semaphore
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4)
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

SemaphoreHandle_t semaphore;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Semaphore Demo Started");
  
  // Create binary semaphore
  semaphore = xSemaphoreCreateBinary();
  
  if (semaphore == NULL) {
    Serial.println("Failed to create semaphore");
    return;
  }
  
  // Create task that waits for semaphore
  xTaskCreate(
    waitTask,
    "Wait Task",
    2048,
    NULL,
    1,
    NULL
  );
  
  Serial.println("Semaphore created");
  Serial.println("Press button to trigger semaphore");
}

void waitTask(void* parameter) {
  while (1) {
    Serial.println("Wait Task: Waiting for semaphore...");
    
    // Wait for semaphore with timeout
    if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdTRUE) {
      Serial.println("Wait Task: Semaphore acquired!");
      
      // Do work
      digitalWrite(LED_PIN, HIGH);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      digitalWrite(LED_PIN, LOW);
      
      Serial.println("Wait Task: Work done");
    }
  }
}

void loop() {
  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed - Giving semaphore");
    
    // Give semaphore
    xSemaphoreGive(semaphore);
    
    delay(500); // Debounce
  }
  
  vTaskDelay(10 / portTICK_PERIOD_MS);
}
