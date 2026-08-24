/*
 * SPI - SPI Communication
 * 
 * Konsep: Komunikasi SPI dengan sensor suhu
 * 
 * Komponen:
 * - MAX6675 (Thermocouple Sensor)
 * 
 * Pinout:
 * - SCK  -> GPIO 18
 * - MISO -> GPIO 19
 * - CS   -> GPIO 5
 */

#include <SPI.h>

// SPI pins
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_CS 5

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi SPI
  SPI.begin(SPI_SCK, SPI_MISO, -1, SPI_CS);
  SPI.setFrequency(1000000); // 1MHz
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);
  
  Serial.println("SPI Demo Started");
}

void loop() {
  // Read temperature from MAX6675
  float temp = readMAX6675();
  
  if (temp != -999.0) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
  } else {
    Serial.println("Failed to read temperature");
  }
  
  delay(1000);
}

float readMAX6675() {
  // Select device
  digitalWrite(SPI_CS, LOW);
  delayMicroseconds(10);
  
  // Read 16-bit data
  uint16_t data = SPI.transfer16(0x0000);
  
  // Deselect device
  digitalWrite(SPI_CS, HIGH);
  
  // Check if thermocouple is connected
  if (data & 0x0004) {
    return -999.0; // Error: no thermocouple
  }
  
  // Extract temperature (12-bit)
  uint16_t tempRaw = (data >> 3) & 0x0FFF;
  
  // Convert to Celsius (0.25°C resolution)
  return tempRaw * 0.25;
}
