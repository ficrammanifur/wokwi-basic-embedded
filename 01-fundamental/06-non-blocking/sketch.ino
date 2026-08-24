/*
 * Non-Blocking Programming - millis()
 * 
 * Konsep: Menjalankan multiple task tanpa blocking menggunakan millis()
 * 
 * Komponen:
 * - LED1 (D2) dengan resistor 220Ω
 * - LED2 (D4) dengan resistor 220Ω
 * 
 * Pinout:
 * - LED1 -> GPIO 2
 * - LED2 -> GPIO 4
 */

const int LED1_PIN = 2;
const int LED2_PIN = 4;

unsigned long lastLED1Toggle = 0;
unsigned long lastLED2Toggle = 0;
bool led1State = false;
bool led2State = false;

const unsigned long LED1_INTERVAL = 500;  // 500ms
const unsigned long LED2_INTERVAL = 1000; // 1000ms

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  Serial.println("Non-Blocking Demo Started");
  Serial.println("LED1 berkedip 500ms, LED2 berkedip 1000ms");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Task 1: LED1 toggle setiap 500ms
  if (currentMillis - lastLED1Toggle >= LED1_INTERVAL) {
    lastLED1Toggle = currentMillis;
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State ? HIGH : LOW);
    Serial.println("LED1 toggled");
  }
  
  // Task 2: LED2 toggle setiap 1000ms
  if (currentMillis - lastLED2Toggle >= LED2_INTERVAL) {
    lastLED2Toggle = currentMillis;
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State ? HIGH : LOW);
    Serial.println("LED2 toggled");
  }
  
  // Task 3: Bisa menjalankan tugas lain tanpa blocking
  // Contoh: baca sensor, proses data, dll.
}
