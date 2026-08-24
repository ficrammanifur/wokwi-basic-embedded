/*
 * SPI - SPI Communication
 *
 * Konsep:
 * Komunikasi SPI antara ESP32 dan TFT LCD ILI9341
 *
 * Komponen:
 * - ESP32
 * - ILI9341 2.8" TFT LCD
 *
 * Pinout:
 * - SCK  -> GPIO 18
 * - MISO -> GPIO 19
 * - MOSI -> GPIO 23
 * - CS   -> GPIO 5
 * - DC   -> GPIO 2
 * - RST  -> GPIO 4
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// ==============================
// SPI PIN
// ==============================

#define SPI_SCK  18
#define SPI_MISO 19
#define SPI_MOSI 23

#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

// ==============================
// TFT OBJECT
// ==============================

Adafruit_ILI9341 tft(
  TFT_CS,
  TFT_DC,
  TFT_RST
);

// ==============================
// SETUP
// ==============================

void setup() {

  Serial.begin(115200);

  // Inisialisasi SPI
  SPI.begin(
    SPI_SCK,
    SPI_MISO,
    SPI_MOSI,
    TFT_CS
  );

  Serial.println("SPI Demo Started");

  // Inisialisasi TFT
  tft.begin();

  // Orientasi layar
  tft.setRotation(1);

  // Bersihkan layar
  tft.fillScreen(ILI9341_BLACK);

  // Judul
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  tft.setCursor(20, 20);
  tft.println("SPI Communication");

  // Informasi
  tft.setTextSize(2);

  tft.setCursor(20, 60);
  tft.println("ESP32 + ILI9341");

  tft.setCursor(20, 100);
  tft.println("SCK  : GPIO 18");

  tft.setCursor(20, 130);
  tft.println("MISO : GPIO 19");

  tft.setCursor(20, 160);
  tft.println("MOSI : GPIO 23");

  tft.setCursor(20, 190);
  tft.println("CS   : GPIO 5");
}

// ==============================
// LOOP
// ==============================

void loop() {

  static int counter = 0;

  // Hapus area counter
  tft.fillRect(
    20,
    220,
    280,
    30,
    ILI9341_BLACK
  );

  // Tampilkan counter
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);

  tft.setCursor(20, 220);
  tft.print("Counter: ");
  tft.print(counter);

  // Serial Monitor
  Serial.print("SPI Counter: ");
  Serial.println(counter);

  counter++;

  delay(1000);
}
