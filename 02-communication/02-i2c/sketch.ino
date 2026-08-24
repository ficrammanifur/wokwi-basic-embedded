/*
 * I2C - I2C Communication
 *
 * Konsep:
 * Komunikasi I2C antara ESP32 dan LCD 16x2
 *
 * Komponen:
 * - ESP32
 * - LCD 16x2 I2C
 *
 * Pinout:
 * - SDA -> GPIO 21
 * - SCL -> GPIO 22
 *
 * Alamat I2C:
 * - Umumnya 0x27 atau 0x3F
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ==============================
// I2C PIN
// ==============================

#define I2C_SDA 21
#define I2C_SCL 22

// Alamat LCD I2C
#define LCD_ADDRESS 0x27

// LCD 16 kolom x 2 baris
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

// ==============================
// SETUP
// ==============================

void setup() {

  Serial.begin(115200);

  // Inisialisasi I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(100000); // 100 kHz

  Serial.println("I2C Demo Started");
  Serial.println("================");

  // Scan perangkat I2C
  scanI2C();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();

  // Tampilkan pesan
  lcd.setCursor(0, 0);
  lcd.print("I2C Demo");

  lcd.setCursor(0, 1);
  lcd.print("ESP32 + LCD");
}

// ==============================
// LOOP
// ==============================

void loop() {

  // Contoh komunikasi/data yang berubah
  static int counter = 0;

  lcd.setCursor(0, 0);
  lcd.print("I2C Communication");

  lcd.setCursor(0, 1);
  lcd.print("Count: ");
  lcd.print(counter);

  // Bersihkan sisa karakter
  lcd.print("        ");

  Serial.print("Counter: ");
  Serial.println(counter);

  counter++;

  delay(1000);
}

// ==============================
// I2C SCANNER
// ==============================

void scanI2C() {

  Serial.println("Scanning I2C devices...");

  byte deviceCount = 0;

  for (byte address = 1; address < 127; address++) {

    Wire.beginTransmission(address);

    byte error = Wire.endTransmission();

    if (error == 0) {

      Serial.print("Found I2C device at 0x");

      if (address < 16) {
        Serial.print("0");
      }

      Serial.println(address, HEX);

      deviceCount++;
    }
  }

  if (deviceCount == 0) {
    Serial.println("No I2C devices found!");
  } else {
    Serial.print("Found ");
    Serial.print(deviceCount);
    Serial.println(" I2C device(s).");
  }

  Serial.println("================");
}
