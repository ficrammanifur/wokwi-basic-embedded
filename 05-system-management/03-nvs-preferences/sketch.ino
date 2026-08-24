/*
 * NVS / Preferences - NVS / Preferences
 * 
 * Konsep: Menyimpan konfigurasi secara non-volatile
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4)
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4
 */

#include <Preferences.h>

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

Preferences preferences;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("NVS / Preferences Demo Started");
  
  // Open preferences namespace
  preferences.begin("myapp", false);
  
  // Read stored values
  int bootCount = preferences.getInt("bootCount", 0);
  String lastMessage = preferences.getString("lastMessage", "None");
  
  bootCount++;
  
  Serial.print("Boot count: ");
  Serial.println(bootCount);
  Serial.print("Last message: ");
  Serial.println(lastMessage);
  
  // Save values
  preferences.putInt("bootCount", bootCount);
  preferences.putString("lastMessage", "Hello from ESP32!");
  
  // Save LED state preference
  bool ledState = preferences.getBool("ledState", false);
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  
  Serial.println("Preferences saved");
  Serial.println("Press button to toggle LED and save state");
}

void loop() {
  // Check button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Toggle LED
    bool currentState = digitalRead(LED_PIN);
    digitalWrite(LED_PIN, !currentState);
    
    // Save LED state
    preferences.putBool("ledState", !currentState);
    
    Serial.print("LED toggled to: ");
    Serial.println(!currentState ? "ON" : "OFF");
    
    delay(500); // Debounce
  }
  
  delay(10);
}
