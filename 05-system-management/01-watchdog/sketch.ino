/*
 * Watchdog - Watchdog Timer
 * 
 * Konsep: Mendeteksi task/system yang hang menggunakan watchdog
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

#include <esp_task_wdt.h>

const int LED_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Watchdog Demo Started");
  
  // Initialize watchdog with 5 second timeout
  esp_task_wdt_init(5, true);
  esp_task_wdt_add(NULL);
  
  Serial.println("Watchdog initialized with 5s timeout");
  Serial.println("LED will blink, then system will reset if watchdog not fed");
}

void loop() {
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  
  // Blink LED
  if (millis() - lastBlink > 1000) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.println("LED toggled");
    
    // Feed watchdog every 2 seconds
    esp_task_wdt_reset();
    Serial.println("Watchdog fed");
  }
  
  // Simulate hang with delay
  // Uncomment this to trigger watchdog reset
  // if (millis() > 10000) {
  //   Serial.println("Simulating hang...");
  //   delay(10000); // This will cause watchdog reset
  // }
  
  delay(100);
}
