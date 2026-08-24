/*
 * GPIO - Digital Input & Output
 * 
 * Konsep: Mengontrol LED (Output) dan membaca tombol (Input)
 * 
 * Komponen:
 * - LED (D2) dengan resistor 220Ω
 * - Push Button (D4) dengan pull-up internal
 * 
 * Pinout:
 * - LED   -> GPIO 2 (D2)
 * - Button -> GPIO 4 (D4)
 */

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

void setup() {
  Serial.begin(115200);
  
  // Konfigurasi pin
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("GPIO Demo Started");
  Serial.println("Tekan tombol untuk menyalakan LED");
}

void loop() {
  // Baca status tombol (LOW saat ditekan karena pull-up)
  int buttonState = digitalRead(BUTTON_PIN);
  
  // Balik logika: tombol aktif LOW
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON - Tombol ditekan");
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(50); // Debounce sederhana
}
