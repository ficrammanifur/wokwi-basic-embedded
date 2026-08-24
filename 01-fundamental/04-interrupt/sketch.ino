/*
 * Interrupt - External Interrupt
 * 
 * Konsep: Merespons event tombol secara langsung menggunakan interrupt
 * 
 * Komponen:
 * - LED (D2) dengan resistor 220Ω
 * - Push Button (D4) dengan pull-up internal
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4 (Interrupt)
 */

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

volatile bool ledState = false;
volatile bool interruptFlag = false;

void IRAM_ATTR buttonISR() {
  // ISR - Hanya set flag, jangan lakukan operasi berat
  interruptFlag = true;
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Attach interrupt pada falling edge (button pressed)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  
  Serial.println("Interrupt Demo Started");
  Serial.println("Tekan tombol untuk toggle LED (via interrupt)");
}

void loop() {
  // Proses interrupt di loop (main context)
  if (interruptFlag) {
    interruptFlag = false;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    
    Serial.print("LED toggled: ");
    Serial.println(ledState ? "ON" : "OFF");
  }
  
  // Lakukan tugas lain di sini
  delay(10);
}
