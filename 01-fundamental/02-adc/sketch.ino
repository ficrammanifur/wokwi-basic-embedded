/*
 * ADC - Analog to Digital Converter
 *
 * Konsep:
 * Membaca nilai analog dari potensiometer
 *
 * Komponen:
 * - Potensiometer 10kΩ
 *
 * Pinout:
 * - Potensiometer SIG -> GPIO 34 (ADC1_CH6)
 */
const int POT_PIN = 34;

void setup() {
  Serial.begin(115200);

  // Konfigurasi ADC
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  Serial.println("ADC Demo Started");
  Serial.println("Putar potensiometer...");
}

void loop() {
  int adcValue = analogRead(POT_PIN);

  float voltage = (adcValue / 4095.0) * 3.3;
  int percentage = map(adcValue, 0, 4095, 0, 100);

  Serial.print("ADC Value: ");
  Serial.print(adcValue);

  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);

  Serial.print("V | Percentage: ");
  Serial.print(percentage);

  Serial.println("%");

  delay(500);
}
