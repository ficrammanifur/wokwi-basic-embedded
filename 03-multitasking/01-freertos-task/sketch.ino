/*
 * FreeRTOS Task - Creating Task
 * 
 * Konsep: Membuat task FreeRTOS untuk menjalankan fungsi secara paralel
 * 
 * Komponen:
 * - LED1 (D2)
 * - LED2 (D4)
 * 
 * Pinout:
 * - LED1 -> GPIO 2
 * - LED2 -> GPIO 4
 */

const int LED1_PIN = 2;
const int LED2_PIN = 4;

// Task handles
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  Serial.println("FreeRTOS Task Demo Started");
  
  // Create Task 1
  xTaskCreate(
    task1Code,         // Function
    "Task 1",          // Name
    2048,              // Stack size (bytes)
    NULL,              // Parameters
    1,                 // Priority
    &task1Handle       // Task handle
  );
  
  // Create Task 2
  xTaskCreate(
    task2Code,         // Function
    "Task 2",          // Name
    2048,              // Stack size (bytes)
    NULL,              // Parameters
    1,                 // Priority
    &task2Handle       // Task handle
  );
  
  Serial.println("Tasks created!");
}

// Task 1: Blink LED1 every 500ms
void task1Code(void* parameter) {
  while (1) {
    digitalWrite(LED1_PIN, HIGH);
    Serial.println("Task 1: LED1 ON");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    digitalWrite(LED1_PIN, LOW);
    Serial.println("Task 1: LED1 OFF");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Task 2: Blink LED2 every 1000ms
void task2Code(void* parameter) {
  while (1) {
    digitalWrite(LED2_PIN, HIGH);
    Serial.println("Task 2: LED2 ON");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    digitalWrite(LED2_PIN, LOW);
    Serial.println("Task 2: LED2 OFF");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void loop() {
  // Main loop - tidak digunakan
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
