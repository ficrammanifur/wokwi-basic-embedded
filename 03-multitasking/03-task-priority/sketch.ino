/*
 * Task Priority - Task Priority
 * 
 * Konsep: Menentukan prioritas task untuk mengontrol eksekusi
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

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  Serial.println("Task Priority Demo Started");
  
  // Create low priority task
  xTaskCreate(
    lowPriorityTask,
    "Low Priority",
    2048,
    NULL,
    1,  // Priority 1 (low)
    NULL
  );
  
  // Create high priority task
  xTaskCreate(
    highPriorityTask,
    "High Priority",
    2048,
    NULL,
    2,  // Priority 2 (high)
    NULL
  );
  
  Serial.println("Tasks created with different priorities");
}

void lowPriorityTask(void* parameter) {
  while (1) {
    digitalWrite(LED1_PIN, HIGH);
    Serial.println("Low Priority: LED1 ON");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    
    digitalWrite(LED1_PIN, LOW);
    Serial.println("Low Priority: LED1 OFF");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void highPriorityTask(void* parameter) {
  while (1) {
    digitalWrite(LED2_PIN, HIGH);
    Serial.println("HIGH PRIORITY: LED2 ON");
    vTaskDelay(200 / portTICK_PERIOD_MS);
    
    digitalWrite(LED2_PIN, LOW);
    Serial.println("HIGH PRIORITY: LED2 OFF");
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
