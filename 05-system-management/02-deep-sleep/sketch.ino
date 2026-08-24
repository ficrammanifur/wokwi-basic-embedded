/*
 * Deep Sleep - Deep Sleep
 * 
 * Konsep: Menghemat konsumsi daya dengan deep sleep
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4) - Wake-up
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4 (EXT0 Wake-up)
 */

#include <esp_sleep.h>

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Increment boot count
  bootCount++;
  
  Serial.println("Deep Sleep Demo Started");
  Serial.print("Boot count: ");
  Serial.println(bootCount);
  
  // Blink LED to indicate boot
  for (int i = 0; i < bootCount; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  
  delay(1000);
  
  // Configure wake-up sources
  setupWakeup();
  
  Serial.println("Entering deep sleep...");
  Serial.flush();
  
  // Enter deep sleep
  esp_deep_sleep_start();
}

void setupWakeup() {
  // Wake-up from button (EXT0)
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 0); // LOW level wake-up
  
  // Wake-up from timer (optional)
  // esp_sleep_enable_timer_wakeup(10 * 1000000); // 10 seconds
  
  // Print wake-up reason
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Wake-up caused by external signal (button)");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Wake-up caused by timer");
      break;
    default:
      Serial.println("Wake-up caused by other reason");
      break;
  }
}

void loop() {
  // Not used - system goes to deep sleep
}
