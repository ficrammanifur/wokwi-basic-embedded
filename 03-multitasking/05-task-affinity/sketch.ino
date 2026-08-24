/*
 * Task Affinity - Task Affinity
 * 
 * Konsep: Menentukan core untuk task dengan affinity
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

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Task Affinity Demo Started");
  Serial.print("Main Task running on Core: ");
  Serial.println(xPortGetCoreID());
  
  // Create task with affinity to Core 0
  xTaskCreatePinnedToCore(
    taskWithAffinity,
    "Affinity Task",
    2048,
    (void*)0,  // Core 0
    2,
    &task1Handle,
    0  // Core 0
  );
  
  // Create task with affinity to Core 1
  xTaskCreatePinnedToCore(
    taskWithAffinity,
    "Affinity Task 2",
    2048,
    (void*)1,  // Core 1
    2,
    &task2Handle,
    1  // Core 1
  );
  
  Serial.println("Tasks created with different core affinity");
}

void taskWithAffinity(void* parameter) {
  int core = (int)parameter;
  while (1) {
    Serial.print("Task on Core ");
    Serial.print(core);
    Serial.print(" - Current Core: ");
    Serial.println(xPortGetCoreID());
    
    // Toggle LED based on core
    if (core == 0) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void loop() {
  // Check button press to change affinity
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed - Changing task affinity");
    
    // Move task1 to Core 1
    vTaskPrioritySet(task1Handle, 0); // Suspend task
    vTaskDelete(task1Handle);
    
    xTaskCreatePinnedToCore(
      taskWithAffinity,
      "Affinity Task",
      2048,
      (void*)1,
      2,
      &task1Handle,
      1  // Core 1
    );
    
    delay(500); // Debounce
  }
  
  vTaskDelay(100 / portTICK_PERIOD_MS);
}
