# 05 — System Management & Reliability

Mempelajari konsep untuk membuat sistem ESP32 lebih stabil, aman, hemat daya, dan mudah dipelihara.

**Materi:** Watchdog Timer • Deep Sleep • NVS/Preferences • OTA • Memory Management • Stack Monitoring

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | Watchdog Timer | Mendeteksi task/system yang hang |
| 02 | Deep Sleep | Menghemat konsumsi daya |
| 03 | NVS/Preferences | Menyimpan konfigurasi non-volatile |
| 04 | OTA | Update firmware melalui jaringan |
| 05 | Memory Management | Pengelolaan RAM dan heap |
| 06 | Stack Monitoring | Memantau penggunaan stack |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **Watchdog** - Mencegah system hang
2. **Deep Sleep** - Menghemat daya baterai
3. **NVS** - Menyimpan data permanent
4. **OTA** - Update firmware remotely
5. **Memory Management** - Mengelola memory efisien
6. **Stack Monitoring** - Mencegah stack overflow

---

## 📖 Penjelasan Setiap Materi

---

### 01-watchdog — Watchdog Timer

**Konsep:** Mempelajari cara menggunakan Watchdog Timer untuk mendeteksi dan mereset system yang hang.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Cara Kerja:**
1. Watchdog diinisialisasi dengan timeout 5 detik
2. Task periodically feed watchdog
3. Jika watchdog tidak di-feed, system reset
4. LED berkedip sebagai indikator

**Kode Penting:**
```cpp
esp_task_wdt_init(5, true);  // 5 second timeout
esp_task_wdt_add(NULL);      // Add current task

// Feed watchdog
esp_task_wdt_reset();
```

**Output yang Diharapkan:**
```
Watchdog initialized with 5s timeout
LED toggled
Watchdog fed
LED toggled
Watchdog fed
```

**Learning Points:**
- Watchdog timer concept
- Feeding watchdog
- Task watchdog vs interrupt watchdog
- Recovery from hang

---

### 02-deep-sleep — Deep Sleep

**Konsep:** Mempelajari cara menghemat konsumsi daya dengan deep sleep mode.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4) - Wake-up

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Wake-up (EXT0) |

**Cara Kerja:**
1. ESP32 boot count disimpan di RTC memory
2. LED berkedip sesuai boot count
3. Konfigurasi wake-up sources
4. ESP32 masuk deep sleep
5. Wake-up dari button atau timer

**Kode Penting:**
```cpp
RTC_DATA_ATTR int bootCount = 0;

esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 0);
esp_deep_sleep_start();

esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
```

**Output yang Diharapkan:**
```
Boot count: 1
Entering deep sleep...
// Press button
Boot count: 2
Wake-up caused by external signal (button)
```

**Learning Points:**
- Deep sleep vs light sleep
- Wake-up sources (EXT0, EXT1, Timer, Touch)
- RTC memory persistence
- Power consumption optimization

---

### 03-nvs-preferences — NVS / Preferences

**Konsep:** Mempelajari cara menyimpan konfigurasi secara non-volatile menggunakan NVS.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input |

**Cara Kerja:**
1. Buka namespace dengan Preferences library
2. Baca nilai yang tersimpan (bootCount, lastMessage)
3. Increment bootCount
4. Simpan nilai ke NVS
5. LED state disimpan dan direstore

**Kode Penting:**
```cpp
Preferences preferences;
preferences.begin("myapp", false);

int bootCount = preferences.getInt("bootCount", 0);
preferences.putInt("bootCount", bootCount + 1);

bool ledState = preferences.getBool("ledState", false);
preferences.putBool("ledState", newState);
```

**Output yang Diharapkan:**
```
Boot count: 5
Last message: Hello from ESP32!
Preferences saved
LED toggled to: ON
```

**Learning Points:**
- NVS (Non-Volatile Storage)
- Preferences API
- Data persistence across reboot
- Configuration management

---

### 04-ota — Over-The-Air Update

**Konsep:** Mempelajari cara update firmware melalui jaringan (OTA).

**Komponen:**
- ESP32 dengan WiFi

**Cara Kerja:**
1. ESP32 connect ke WiFi
2. Start OTA server (web interface)
3. User upload firmware via browser
4. ESP32 update dan reboot

**Kode Penting:**
```cpp
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
AsyncElegantOTA.begin(&server);
server.begin();

// In loop
AsyncElegantOTA.loop();
```

**Output yang Diharapkan:**
```
Connected to WiFi
IP Address: 192.168.1.100
OTA server started
Access: http://192.168.1.100/update
```

**Learning Points:**
- OTA architecture
- Web-based update
- Firmware versioning
- Rollback capability

---

### 05-memory-management — Memory Management

**Konsep:** Mempelajari pengelolaan RAM dan heap pada ESP32.

**Komponen:**
- Tidak ada komponen fisik

**Cara Kerja:**
1. Print total heap, free heap
2. Allocate dan free memory
3. Monitor heap fragmentation
4. Show PSRAM availability

**Kode Penting:**
```cpp
size_t totalHeap = ESP.getHeapSize();
size_t freeHeap = ESP.getFreeHeap();
size_t minFreeHeap = ESP.getMinFreeHeap();

void* ptr = malloc(size);
free(ptr);

size_t largestFreeBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
```

**Output yang Diharapkan:**
```
Total Heap: 320 KB
Free Heap: 280 KB
Heap Usage: 12.5%
Largest Free Block: 280 KB
```

**Learning Points:**
- Heap vs Stack
- Memory allocation
- Fragmentation
- Memory leaks detection
- PSRAM usage

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa menggunakan watchdog timer
- [ ] Saya bisa menggunakan deep sleep
- [ ] Saya bisa menyimpan data di NVS
- [ ] Saya bisa melakukan OTA update
- [ ] Saya bisa memonitor memory usage
- [ ] Saya bisa memonitor stack usage

---

## 🔗 Navigasi

- [⬅ Kembali ke Home](../README.md)
- [➡ Lanjut ke Program Architecture](../06-program-architecture/README.md)
