/*
 * Timer - Hardware Timer
 *
 * Konsep: Menjalankan fungsi secara periodik menggunakan timer
 *
 * Komponen:
 * - LED (D2) dengan resistor 220Ω
 *
 * Pinout:
 * - LED -> GPIO 2
 */

#include <esp_timer.h>

const int LED_PIN = 2;

volatile bool timerFlag = false;
bool ledState = false;

// ========================================
// TIMER CALLBACK
// ========================================
void timerCallback(void* arg) {
  timerFlag = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // ========================================
  // KONFIGURASI TIMER
  // ========================================
  const esp_timer_create_args_t timerArgs = {
    .callback = &timerCallback,
    .arg = NULL,
    .dispatch_method = ESP_TIMER_TASK,
    .name = "periodic_timer"
  };

  esp_timer_handle_t timer;

  esp_timer_create(&timerArgs, &timer);

  // Timer berjalan setiap 500 ms
  esp_timer_start_periodic(timer, 500000);

  Serial.println("Timer Demo Started");
  Serial.println("LED berkedip setiap 500ms");
}

void loop() {

  // ========================================
  // CEK TIMER
  // ========================================
  if (timerFlag) {

    timerFlag = false;

    ledState = !ledState;

    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    Serial.print("Timer Triggered - LED: ");

    if (ledState) {
      Serial.println("ON");
    } else {
      Serial.println("OFF");
    }
  }

  // Main loop tetap berjalan
  Serial.println("Main loop running...");

  delay(2000);
}
