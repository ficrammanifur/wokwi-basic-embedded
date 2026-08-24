/*
 * Event Group - Event Group
 * 
 * Konsep: Sinkronisasi berdasarkan event menggunakan event group
 * 
 * Komponen:
 * - LED1 (D2)
 * - LED2 (D4)
 * - Button (D5)
 * 
 * Pinout:
 * - LED1  -> GPIO 2
 * - LED2  -> GPIO 4
 * - Button -> GPIO 5
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

const int LED1_PIN = 2;
const int LED2_PIN = 4;
const int BUTTON_PIN = 5;

// Event bits
#define EVENT_BIT_1 (1 << 0)
#define EVENT_BIT_2 (1 << 1)
#define EVENT_ALL (EVENT_BIT_1 | EVENT_BIT_2)

EventGroupHandle_t eventGroup;

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Event Group Demo Started");
  
  // Create event group
  eventGroup = xEventGroupCreate();
  
  if (eventGroup == NULL) {
    Serial.println("Failed to create event group");
    return;
  }
  
  // Create task that waits for events
  xTaskCreate(
    eventWaitTask,
    "Event Wait",
    2048,
    NULL,
    1,
    NULL
  );
  
  Serial.println("Event group created");
  Serial.println("Press button to trigger events");
}

void eventWaitTask(void* parameter) {
  while (1) {
    Serial.println("Waiting for events...");
    
    // Wait for ALL events
    EventBits_t bits = xEventGroupWaitBits(
      eventGroup,
      EVENT_ALL,
      pdTRUE,  // Clear on exit
      pdTRUE,  // Wait for all bits
      portMAX_DELAY
    );
    
    if ((bits & EVENT_ALL) == EVENT_ALL) {
      Serial.println("All events received!");
      
      // Do something
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);
      vTaskDelay(500 / portTICK_PERIOD_MS);
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
    }
  }
}

void loop() {
  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Button pressed - Setting events");
    
    // Set events sequentially
    xEventGroupSetBits(eventGroup, EVENT_BIT_1);
    Serial.println("Event 1 set");
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    xEventGroupSetBits(eventGroup, EVENT_BIT_2);
    Serial.println("Event 2 set");
    
    delay(500); // Debounce
  }
  
  vTaskDelay(10 / portTICK_PERIOD_MS);
}
