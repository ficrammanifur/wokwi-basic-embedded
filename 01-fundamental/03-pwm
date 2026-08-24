/*
 * PWM - Pulse Width Modulation
 * 
 * Konsep: Mengatur kecerahan LED dengan PWM
 * 
 * Komponen:
 * - LED (D2) dengan resistor 220Ω
 * 
 * Pinout:
 * - LED -> GPIO 2 (PWM channel 0)
 */
const int LED_PIN = 2;
const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 8;

void setup() {
  Serial.begin(115200);

  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);

  Serial.println("PWM Demo Started");
  Serial.println("LED akan fade in dan fade out");
}

void loop() {
  // Fade in
  for (int duty = 0; duty <= 255; duty++) {
    ledcWrite(LED_PIN, duty);

    Serial.print("Duty Cycle: ");
    Serial.println(duty);

    delay(10);
  }

  // Fade out
  for (int duty = 255; duty >= 0; duty--) {
    ledcWrite(LED_PIN, duty);

    Serial.print("Duty Cycle: ");
    Serial.println(duty);

    delay(10);
  }
}
