/*
 * Deep Sleep - Deep Sleep
 * 
 * Konsep: Menghemat konsumsi daya dengan deep sleep
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4) - Wake-up
 * 
 * Pinout:
 * - LED    -> GPIO 2
 * - Button -> GPIO 4 (EXT0 Wake-up)
 */

#define LED_PIN     2
#define BUTTON_PIN  4   // Harus RTC GPIO agar bisa dipakai EXT0

// Waktu deep sleep dalam mikrodetik (contoh: 30 detik)
#define TIME_TO_SLEEP_SEC  30
#define uS_TO_S_FACTOR     1000000ULL

RTC_DATA_ATTR int bootCount = 0;  // Nilai ini tetap tersimpan meski deep sleep

// Fungsi untuk menampilkan alasan wake-up
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Wake-up disebabkan oleh sinyal EXT0 (tombol)");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Wake-up disebabkan oleh sinyal EXT1");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Wake-up disebabkan oleh timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Wake-up disebabkan oleh touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Wake-up disebabkan oleh program ULP");
      break;
    default:
      Serial.printf("Wake-up bukan dari deep sleep: %d\n", wakeup_reason);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN); // Tombol aktif HIGH saat ditekan

  // Hitung jumlah boot (increment setiap kali wake-up/reset)
  bootCount++;
  Serial.println("=========================");
  Serial.println("Boot number: " + String(bootCount));

  // Tampilkan alasan wake-up sebelumnya
  print_wakeup_reason();

  // Indikasi LED menyala sebentar saat bangun
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);

  // ----- Konfigurasi Wake-up -----

  // 1. Wake-up via tombol (EXT0) - saat GPIO4 HIGH
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 1);

  // 2. (Opsional) Wake-up via timer, misal setelah 30 detik
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_SEC * uS_TO_S_FACTOR);

  Serial.println("Perangkat akan masuk deep sleep dalam 5 detik...");
  Serial.println("Tekan tombol pada GPIO4 untuk membangunkan lebih awal.");
  Serial.flush();

  // Beri jeda sebelum tidur (misal untuk simulasi kerja normal)
  delay(5000);

  Serial.println("Masuk mode Deep Sleep sekarang...");
  Serial.flush();

  // Masuk deep sleep
  esp_deep_sleep_start();

  // Kode di bawah ini TIDAK akan pernah dieksekusi
}

void loop() {
  // Tidak dipakai karena ESP32 akan reset setelah wake-up dari deep sleep
}
