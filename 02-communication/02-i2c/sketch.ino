/*
 * I2C - I2C Communication
 * 
 * Konsep: Komunikasi I2C dengan sensor suhu/kelembaban
 * 
 * Komponen:
 * - AHT20 Temperature & Humidity Sensor
 * 
 * Pinout:
 * - SDA -> GPIO 21
 * - SCL -> GPIO 22
 */

#include <Wire.h>

// I2C pins
#define I2C_SDA 21
#define I2C_SCL 22

// AHT20 address
#define AHT20_ADDR 0x38

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(100000); // 100kHz
  
  Serial.println("I2C Demo Started");
  
  // Scan I2C devices
  scanI2C();
  
  // Initialize AHT20
  initAHT20();
}

void loop() {
  // Read temperature and humidity
  float temp, hum;
  if (readAHT20(temp, hum)) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C | Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read AHT20");
  }
  
  delay(2000);
}

void scanI2C() {
  Serial.println("Scanning I2C devices...");
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(address, HEX);
    }
  }
}

void initAHT20() {
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(0xBE); // Init command
  Wire.write(0x08);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);
}

bool readAHT20(float& temp, float& hum) {
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(0xAC); // Trigger measurement
  Wire.write(0x33);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(80);
  
  Wire.requestFrom(AHT20_ADDR, 6);
  if (Wire.available() == 6) {
    byte data[6];
    for (int i = 0; i < 6; i++) {
      data[i] = Wire.read();
    }
    
    uint32_t humRaw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    uint32_t tempRaw = ((uint32_t)(data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
    
    hum = humRaw * 100.0 / 1048576.0;
    temp = tempRaw * 200.0 / 1048576.0 - 50.0;
    
    return true;
  }
  return false;
}
