/*
 * Task Notification - Task Notification
 * 
 * Konsep: Komunikasi ringan antar-task menggunakan task notification
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

TaskHandle_t receiverTaskHandle = NULL;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Task Notification Demo Started");
  
  // Create receiver task
  xTaskCreate(
    receiverTask,
    "Receiver",
    2048,
    NULL,
    1,
    &receiverTaskHandle
  );
  
  Serial.println("Receiver task created");
  Serial.println("Press button to send notification");
}

void receiverTask(void* parameter) {
  uint32_t notificationValue;
  
  while (1) {
    Serial.println("Receiver: Waiting for notification...");
    
    // Wait for notification
    if (xTaskNotifyWait(0, ULONG_MAX, &notificationValue, portMAX_DELAY) == pdTRUE) {
      Serial.print("Receiver: Notification received with value: ");
      Serial.println(notificationValue);
      
      // Process based on notification value
      switch (notificationValue) {
        case 1:
          digitalWrite(LED_PIN, HIGH);
          Serial.println("Receiver: LED ON");
          break;
        case 2:
          digitalWrite(LED_PIN, LOW);
          Serial.println("Receiver: LED OFF");
          break;
        case 3:
          digitalWrite(LED_PIN, !digitalRead(LED_PIN));
          Serial.println("Receiver: LED TOGGLED");
          break;
        default:
          Serial.println("Receiver: Unknown command");
      }
    }
  }
}

void loop() {
  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    static int command = 1;
    
    // Send notification with different values
    xTaskNotify(receiverTaskHandle, command, eSetValueWithOverwrite);
    
    Serial.print("Main: Notification sent with value: ");
    Serial.println(command);
    
    // Cycle through commands
    command = (command % 3) + 1;
    
    delay(500); // Debounce
  }
  
  vTaskDelay(10 / portTICK_PERIOD_MS);
}
