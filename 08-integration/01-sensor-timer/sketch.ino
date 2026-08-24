/*
 * Integration 01: Sensor + Timer
 * 
 * Konsep: Membaca sensor secara periodik menggunakan timer
 * 
 * Komponen:
 * - Potentiometer (GPIO 36)
 * - LED (GPIO 2)
 * 
 * Pinout:
 * - Sensor -> GPIO 36 (ADC)
 * - LED    -> GPIO 2
 */

const int SENSOR_PIN = 36;
const int LED_PIN = 2;

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 500; // 500ms

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // ADC configuration
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  
  Serial.println("Sensor + Timer Integration Started");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read sensor periodically
  if (currentMillis - lastRead >= READ_INTERVAL) {
    lastRead = currentMillis;
    
    // Read sensor
    int sensorValue = analogRead(SENSOR_PIN);
    float voltage = (sensorValue / 4095.0) * 3.3;
    int percentage = map(sensorValue, 0, 4095, 0, 100);
    
    // Process data
    Serial.print("Sensor: ");
    Serial.print(sensorValue);
    Serial.print(" | Voltage: ");
    Serial.print(voltage, 2);
    Serial.print("V | ");
    Serial.print(percentage);
    Serial.println("%");
    
    // Control LED based on sensor
    if (percentage > 50) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
  
  // Other tasks can run here
  // No delay() used - non-blocking
}
