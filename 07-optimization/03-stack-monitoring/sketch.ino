/*
 * Stack Monitoring - Stack Monitoring
 * 
 * Konsep: Memantau penggunaan stack
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

const int LED_PIN = 2;

TaskHandle_t monitoredTaskHandle = NULL;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Stack Monitoring Demo Started");
  
  // Create task to monitor
  xTaskCreate(
    monitoredTask,
    "Monitored Task",
    4096,
    NULL,
    1,
    &monitoredTaskHandle
  );
  
  Serial.println("Monitored task created");
  
  // Create monitoring task
  xTaskCreate(
    monitorTask,
    "Monitor Task",
    2048,
    NULL,
    2,
    NULL
  );
}

void monitoredTask(void* parameter) {
  // Stack variables
  uint8_t stackBuffer[1000];
  static int counter = 0;
  
  while (1) {
    // Use stack
    for (int i = 0; i < 1000; i++) {
      stackBuffer[i] = i % 256;
    }
    
    counter++;
    if (counter % 10 == 0) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void monitorTask(void* parameter) {
  while (1) {
    // Check stack usage
    if (monitoredTaskHandle != NULL) {
      UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(monitoredTaskHandle);
      
      Serial.print("Monitored Task Stack High Water Mark: ");
      Serial.print(highWaterMark);
      Serial.print(" words (");
      Serial.print(highWaterMark * sizeof(StackType_t));
      Serial.println(" bytes)");
      
      // Check for stack overflow risk
      if (highWaterMark < 100) {
        Serial.println("WARNING: Stack low!");
      }
    }
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
