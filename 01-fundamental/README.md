# 01 — Fundamental

Mempelajari konsep dasar pemrograman embedded pada ESP32, mulai dari mengontrol pin digital, membaca input analog, menghasilkan PWM, merespons interrupt, hingga menjalankan proses berdasarkan waktu tanpa membuat program terblokir.

**Materi:** GPIO • ADC • PWM • Interrupt • Timer • Non-Blocking Programming

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | GPIO | Digital Input & Output - Mengontrol LED dan membaca tombol |
| 02 | ADC | Analog to Digital Converter - Membaca sinyal analog dari sensor |
| 03 | PWM | Pulse Width Modulation - Mengatur kecerahan LED dengan duty cycle |
| 04 | Interrupt | External Interrupt - Merespons event secara langsung |
| 05 | Timer | Hardware Timer - Menjalankan fungsi secara periodik |
| 06 | Non-Blocking | Non-Blocking Programming - Menggunakan millis() tanpa delay() |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **Mengontrol GPIO** - Mengatur pin sebagai input/output
2. **Membaca sinyal analog** - Menggunakan ADC untuk membaca sensor
3. **Menghasilkan sinyal PWM** - Mengontrol perangkat dengan duty cycle
4. **Merespons interrupt** - Menangani event secara real-time
5. **Menggunakan timer** - Menjalankan tugas periodik
6. **Programming non-blocking** - Membuat program yang responsif

---

## 🔧 Komponen yang Digunakan

- ESP32 Dev Kit V1
- LED (Merah, Biru)
- Resistor 220Ω
- Push Button
- Potensiometer 10kΩ

---

## 📖 Penjelasan Setiap Materi

---

### 01-gpio — Digital Input & Output

**Konsep:** Mempelajari cara mengkonfigurasi pin ESP32 sebagai input dan output digital.

**Komponen:**
- 1x LED (Merah) - Output
- 1x Push Button - Input (dengan pull-up internal)
- 1x Resistor 220Ω

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output (Digital) |
| Button | 4 | Input (Digital) |

**Cara Kerja:**
1. LED dikonfigurasi sebagai OUTPUT untuk menampilkan status
2. Button dikonfigurasi sebagai INPUT_PULLUP (aktif LOW saat ditekan)
3. Program membaca status button dan menyalakan LED jika ditekan

**Kode Penting:**
```cpp
pinMode(LED_PIN, OUTPUT);           // Set sebagai output
pinMode(BUTTON_PIN, INPUT_PULLUP);  // Set sebagai input dengan pull-up
int state = digitalRead(BUTTON_PIN); // Baca input
digitalWrite(LED_PIN, HIGH);         // Tulis output
```

**Output yang Diharapkan:**
- LED menyala saat tombol ditekan
- LED mati saat tombol dilepas
- Serial monitor menampilkan status tombol

**Learning Points:**
- Perbedaan INPUT dan OUTPUT
- Penggunaan internal pull-up resistor
- Logika aktif LOW pada button

---

### 02-adc — Analog to Digital Converter

**Konsep:** Mempelajari cara membaca sinyal analog menggunakan ADC (Analog to Digital Converter) 12-bit ESP32.

**Komponen:**
- 1x Potensiometer 10kΩ

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| Potensiometer | 36 (ADC1_CH0) | Input Analog |

**Cara Kerja:**
1. ADC mengkonversi tegangan analog (0-3.3V) menjadi nilai digital (0-4095)
2. Nilai ADC dikonversi menjadi tegangan dan persentase
3. Data ditampilkan di serial monitor

**Kode Penting:**
```cpp
analogReadResolution(12);           // Set resolusi 12-bit
analogSetAttenuation(ADC_11db);     // Range 0-3.6V
int value = analogRead(POT_PIN);    // Baca nilai ADC
float voltage = (value / 4095.0) * 3.3; // Konversi ke tegangan
```

**Output yang Diharapkan:**
```
ADC Value: 2048 | Voltage: 1.65V | Percentage: 50%
ADC Value: 3072 | Voltage: 2.48V | Percentage: 75%
```

**Learning Points:**
- Resolusi ADC (12-bit = 0-4095)
- Konversi ADC ke tegangan
- Fungsi map() untuk scaling

---

### 03-pwm — Pulse Width Modulation

**Konsep:** Mempelajari cara menghasilkan sinyal PWM untuk mengontrol kecerahan LED atau kecepatan motor.

**Komponen:**
- 1x LED (Merah) - Output
- 1x Resistor 220Ω

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | PWM Output |

**Cara Kerja:**
1. LED dikontrol menggunakan PWM dengan frekuensi 5kHz
2. Duty cycle diubah dari 0% ke 100% (fade in/out)
3. Resolusi 8-bit (0-255) memberikan 256 tingkat kecerahan

**Kode Penting:**
```cpp
ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);  // Setup PWM
ledcAttachPin(LED_PIN, PWM_CHANNEL);               // Attach pin
ledcWrite(PWM_CHANNEL, duty);                      // Set duty cycle
```

**Output yang Diharapkan:**
- LED melakukan fade in (0 → 255)
- LED melakukan fade out (255 → 0)
- Serial monitor menampilkan nilai duty cycle

**Learning Points:**
- Konsep duty cycle dan frekuensi
- Resolusi PWM (8-bit = 0-255)
- Penggunaan ledc library ESP32

---

### 04-interrupt — External Interrupt

**Konsep:** Mempelajari cara merespons event eksternal secara langsung menggunakan interrupt, tanpa harus menunggu di loop().

**Komponen:**
- 1x LED (Merah) - Output
- 1x Push Button - Input (Interrupt)
- 1x Resistor 220Ω

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Interrupt Input |

**Cara Kerja:**
1. Button dihubungkan ke interrupt pin
2. Saat button ditekan (falling edge), ISR dipanggil
3. ISR hanya set flag, proses toggle LED dilakukan di loop()

**Kode Penting:**
```cpp
void IRAM_ATTR buttonISR() {
  interruptFlag = true;  // Hanya set flag di ISR
}

attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
```

**Output yang Diharapkan:**
- LED toggle setiap kali tombol ditekan
- Program tetap responsif untuk tugas lain

**Learning Points:**
- Perbedaan interrupt dan polling
- IRAM_ATTR untuk ISR
- ISR harus pendek dan cepat
- Edge detection (FALLING, RISING, CHANGE)

---

### 05-timer — Hardware Timer

**Konsep:** Mempelajari cara menggunakan hardware timer ESP32 untuk menjalankan fungsi secara periodik tanpa blocking.

**Komponen:**
- 1x LED (Merah) - Output
- 1x Resistor 220Ω

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Cara Kerja:**
1. Timer ESP32 dikonfigurasi dengan callback
2. Timer berjalan di background (interrupt)
3. LED berkedip setiap 500ms tanpa blocking

**Kode Penting:**
```cpp
const esp_timer_create_args_t timerArgs = {
  .callback = &timerCallback,
  .name = "periodic_timer"
};
esp_timer_create(&timerArgs, &timer);
esp_timer_start_periodic(timer, 500000); // 500ms
```

**Output yang Diharapkan:**
- LED berkedip setiap 500ms
- Main loop tetap berjalan (bebas tugas lain)

**Learning Points:**
- Hardware timer vs software timer
- Timer callback dijalankan di context interrupt
- ESP32 timer API

---

### 06-non-blocking — Non-Blocking Programming

**Konsep:** Mempelajari cara menjalankan multiple task secara bersamaan tanpa menggunakan delay() yang blocking.

**Komponen:**
- 1x LED (Merah) - Output 1
- 1x LED (Biru) - Output 2
- 2x Resistor 220Ω

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED1 | 2 | Output (500ms interval) |
| LED2 | 4 | Output (1000ms interval) |

**Cara Kerja:**
1. Menggunakan millis() untuk tracking waktu
2. Setiap LED memiliki interval dan lastToggle sendiri
3. Task berjalan independen tanpa saling blocking

**Kode Penting:**
```cpp
unsigned long currentMillis = millis();
if (currentMillis - lastLED1Toggle >= LED1_INTERVAL) {
  lastLED1Toggle = currentMillis;
  // Toggle LED1
}
// Task 2 berjalan independen
if (currentMillis - lastLED2Toggle >= LED2_INTERVAL) {
  lastLED2Toggle = currentMillis;
  // Toggle LED2
}
```

**Output yang Diharapkan:**
- LED1 berkedip setiap 500ms
- LED2 berkedip setiap 1000ms
- Kedua LED berkedip independen

**Learning Points:**
- Perbedaan blocking vs non-blocking
- Penggunaan millis() untuk timing
- State management dengan variabel static
- Multiple task tanpa RTOS

---

## 📊 Perbandingan Metode

| Metode | Kelebihan | Kekurangan |
|--------|-----------|------------|
| **delay()** | Sederhana | Blocking, tidak bisa multitasking |
| **millis()** | Non-blocking, multitasking | Perlu manajemen state manual |
| **Timer** | Akurat, hardware-based | Terbatas jumlahnya |
| **Interrupt** | Responsif, real-time | ISR harus pendek |

---

## 🔗 Referensi

- [ESP32 GPIO Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html)
- [ESP32 ADC Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html)
- [ESP32 PWM Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html)
- [ESP32 Timer Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_timer.html)

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa mengontrol LED dan membaca tombol
- [ ] Saya bisa membaca sensor analog
- [ ] Saya bisa mengatur kecerahan LED dengan PWM
- [ ] Saya bisa menggunakan interrupt untuk merespons event
- [ ] Saya bisa menggunakan timer untuk tugas periodik
- [ ] Saya bisa membuat program non-blocking dengan millis()

---

## 🔗 Navigasi

- [⬅ Kembali ke Home](../README.md)
- [➡ Lanjut ke Communication](../02-communication/README.md)
