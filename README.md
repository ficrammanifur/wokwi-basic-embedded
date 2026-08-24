# Wokwi Basic Embedded

Kumpulan pembelajaran **Embedded System menggunakan ESP32** yang dibuat secara bertahap dari konsep dasar hingga integrasi beberapa fitur.

Repository ini menggunakan **Wokwi** sebagai simulator sehingga setiap materi dapat dipelajari, dijalankan, dan diuji tanpa membutuhkan hardware fisik.

> 🎯 **Goal:** memahami konsep embedded programming dari dasar sampai mampu menggabungkan beberapa konsep menjadi sebuah sistem ESP32 yang terstruktur.

---

## 📚 Learning Roadmap

```text
01 Fundamental
      ↓
02 Communication
      ↓
03 Multitasking
      ↓
04 Task Communication & Synchronization
      ↓
05 System Management & Reliability
      ↓
06 Program Architecture
      ↓
07 Optimization
      ↓
08 System Integration
```

---

# 01 — Fundamental

Konsep dasar yang menjadi fondasi pemrograman ESP32.

| No | Materi                   | Pembahasan                           |   Wokwi   |
| -: | ------------------------ | ------------------------------------ | :-------: |
| 01 | GPIO                     | Digital Input & Output               | [▶️ Open] |
| 02 | ADC                      | Membaca sinyal analog                | [▶️ Open] |
| 03 | PWM                      | Mengatur duty cycle                  | [▶️ Open] |
| 04 | Interrupt                | Merespons event secara langsung      | [▶️ Open] |
| 05 | Timer                    | Menjalankan proses berdasarkan waktu | [▶️ Open] |
| 06 | Non-Blocking Programming | `millis()` tanpa `delay()`           | [▶️ Open] |

---

# 02 — Communication

Mempelajari cara ESP32 berkomunikasi dengan perangkat lain maupun jaringan.

| No | Materi        | Pembahasan                                |   Wokwi   |
| -: | ------------- | ----------------------------------------- | :-------: |
| 01 | UART / Serial | Komunikasi serial                         | [▶️ Open] |
| 02 | I2C           | Komunikasi dua kabel                      | [▶️ Open] |
| 03 | SPI           | Komunikasi berkecepatan tinggi            | [▶️ Open] |
| 04 | WiFi          | Koneksi ESP32 ke jaringan                 | [▶️ Open] |
| 05 | MQTT          | Komunikasi IoT berbasis publish/subscribe | [▶️ Open] |

---

# 03 — Multitasking

Mempelajari bagaimana ESP32 menjalankan beberapa proses menggunakan FreeRTOS.

| No | Materi          | Pembahasan                            |   Wokwi   |
| -: | --------------- | ------------------------------------- | :-------: |
| 01 | FreeRTOS Task   | Membuat task                          | [▶️ Open] |
| 02 | Task Scheduling | Mengatur eksekusi task                | [▶️ Open] |
| 03 | Task Priority   | Menentukan prioritas task             | [▶️ Open] |
| 04 | Dual Core       | Menjalankan task pada Core 0 & Core 1 | [▶️ Open] |
| 05 | Task Affinity   | Menentukan core untuk task            | [▶️ Open] |

---

# 04 — Task Communication & Synchronization

Mempelajari bagaimana task saling berkomunikasi dan bagaimana resource bersama dikendalikan.

| No | Materi            | Pembahasan                     |   Wokwi   |
| -: | ----------------- | ------------------------------ | :-------: |
| 01 | Queue             | Mengirim data antar-task       | [▶️ Open] |
| 02 | Semaphore         | Sinkronisasi antar-task        | [▶️ Open] |
| 03 | Mutex             | Mengamankan shared resource    | [▶️ Open] |
| 04 | Event Group       | Sinkronisasi berdasarkan event | [▶️ Open] |
| 05 | Task Notification | Komunikasi ringan antar-task   | [▶️ Open] |

---

# 05 — System Management & Reliability

Konsep untuk membuat sistem ESP32 lebih stabil, aman, hemat daya, dan mudah dipelihara.

| No | Materi            | Pembahasan                       |   Wokwi   |
| -: | ----------------- | -------------------------------- | :-------: |
| 01 | Watchdog Timer    | Mendeteksi task/system yang hang | [▶️ Open] |
| 02 | Deep Sleep        | Menghemat konsumsi daya          | [▶️ Open] |
| 03 | NVS / Preferences | Menyimpan konfigurasi            | [▶️ Open] |
| 04 | OTA               | Update firmware melalui jaringan | [▶️ Open] |
| 05 | Memory Management | Pengelolaan RAM dan heap         | [▶️ Open] |
| 06 | Stack Monitoring  | Memantau penggunaan stack        | [▶️ Open] |

---

# 06 — Program Architecture

Mempelajari cara membuat program embedded yang lebih terstruktur dan mudah dikembangkan.

| No | Materi                   | Pembahasan                          |   Wokwi   |
| -: | ------------------------ | ----------------------------------- | :-------: |
| 01 | State Machine            | Mengatur alur berdasarkan state     | [▶️ Open] |
| 02 | Modular Programming      | Memisahkan program menjadi modul    | [▶️ Open] |
| 03 | Event-Driven Programming | Program berdasarkan event           | [▶️ Open] |
| 04 | Error Handling           | Menangani kondisi error             | [▶️ Open] |
| 05 | Configuration Management | Memisahkan konfigurasi dari program | [▶️ Open] |

---

# 07 — Optimization

Mempelajari bagaimana meningkatkan performa dan efisiensi sistem.

| No | Materi              | Pembahasan                      |   Wokwi   |
| -: | ------------------- | ------------------------------- | :-------: |
| 01 | CPU Usage           | Memantau penggunaan CPU         | [▶️ Open] |
| 02 | Heap Monitoring     | Memantau penggunaan heap        | [▶️ Open] |
| 03 | Stack Optimization  | Mengoptimalkan penggunaan stack | [▶️ Open] |
| 04 | Memory Optimization | Mengurangi penggunaan memory    | [▶️ Open] |
| 05 | Task Optimization   | Mengoptimalkan task             | [▶️ Open] |

---

# 08 — System Integration

Bagian ini mulai menggabungkan beberapa konsep menjadi satu sistem.

### Integration 01 — Sensor + Timer

```text
Sensor
   ↓
Timer
   ↓
Read Sensor
   ↓
Process Data
```

[▶️ Open Wokwi Project]

---

### Integration 02 — Sensor + FreeRTOS Task

```text
┌───────────────┐
│ Sensor Task   │
└───────┬───────┘
        ↓
   Read Sensor
        ↓
     Process
```

[▶️ Open Wokwi Project]

---

### Integration 03 — Sensor + Queue + MQTT

```text
┌───────────────┐
│ Sensor Task   │
└───────┬───────┘
        ↓
      Queue
        ↓
┌───────────────┐
│   MQTT Task   │
└───────┬───────┘
        ↓
      MQTT
        ↓
      Broker
```

[▶️ Open Wokwi Project]

---

### Integration 04 — Dual Core + FreeRTOS

```text
              ESP32
                │
       ┌────────┴────────┐
       ↓                 ↓
    CORE 0            CORE 1
       │                 │
   MQTT Task         Sensor Task
   WiFi Task         Control Task
```

[▶️ Open Wokwi Project]

---

### Integration 05 — Complete Embedded System

Gabungan:

* GPIO
* ADC
* PWM
* Timer
* Interrupt
* FreeRTOS
* Dual Core
* Queue
* Mutex
* WiFi
* MQTT
* State Machine
* Watchdog

```text
                    ESP32
                      │
        ┌─────────────┴─────────────┐
        │                           │
     CORE 0                      CORE 1
        │                           │
   WiFi / MQTT                  Sensor Task
        │                       Control Task
        │                           │
        └───────────┬───────────────┘
                    │
                  Queue
                    │
                    ▼
              Data Processing
                    │
          ┌─────────┴─────────┐
          ↓                   ↓
       Actuator             MQTT
          │                   │
          ↓                   ↓
       Hardware             Broker
```

[▶️ Open Wokwi Project]

---

# 🗂️ Repository Structure

```text
wokwi-basic-embedded/
│
├── 01-fundamental/
│   ├── 01-gpio/
│   ├── 02-adc/
│   ├── 03-pwm/
│   ├── 04-interrupt/
│   ├── 05-timer/
│   └── 06-non-blocking/
│
├── 02-communication/
│   ├── 01-uart/
│   ├── 02-i2c/
│   ├── 03-spi/
│   ├── 04-wifi/
│   └── 05-mqtt/
│
├── 03-multitasking/
│   ├── 01-freertos-task/
│   ├── 02-task-scheduling/
│   ├── 03-task-priority/
│   ├── 04-dual-core/
│   └── 05-task-affinity/
│
├── 04-synchronization/
│   ├── 01-queue/
│   ├── 02-semaphore/
│   ├── 03-mutex/
│   ├── 04-event-group/
│   └── 05-task-notification/
│
├── 05-system-management/
│   ├── 01-watchdog/
│   ├── 02-deep-sleep/
│   ├── 03-nvs-preferences/
│   ├── 04-ota/
│   └── 05-memory-management/
│
├── 06-program-architecture/
│   ├── 01-state-machine/
│   ├── 02-modular-programming/
│   ├── 03-event-driven/
│   └── 04-error-handling/
│
├── 07-optimization/
│   ├── 01-cpu-usage/
│   ├── 02-heap-monitoring/
│   ├── 03-stack-monitoring/
│   └── 04-memory-optimization/
│
└── 08-integration/
    ├── 01-sensor-timer/
    ├── 02-sensor-freertos/
    ├── 03-sensor-queue-mqtt/
    ├── 04-dual-core-system/
    └── 05-complete-system/
```

---

# 🛠️ Tools

* **ESP32**
* **Arduino Framework**
* **C/C++**
* **FreeRTOS**
* **Wokwi Simulator**
* **MQTT**
* **Git & GitHub**

Wokwi menyediakan simulasi ESP32 beserta berbagai peripheral seperti GPIO, ADC, PWM, UART, I2C, SPI, WiFi, timer, dan watchdog, sehingga cocok digunakan sebagai media latihan dalam repository ini.

---

# 🎯 Learning Goal

Repository ini dibuat sebagai **learning path**, bukan sekadar kumpulan source code.

Setiap project diharapkan menjawab tiga pertanyaan:

1. **Apa konsep yang dipelajari?**
2. **Bagaimana konsep tersebut bekerja?**
3. **Bagaimana konsep tersebut digunakan dalam sistem nyata?**

Target akhirnya adalah mampu berpindah dari:

```text
Basic GPIO
     ↓
Sensor & Actuator
     ↓
Communication
     ↓
Multitasking
     ↓
Synchronization
     ↓
System Management
     ↓
Program Architecture
     ↓
System Integration
```

hingga mampu membangun sistem embedded/IoT yang **terstruktur, reliable, dan scalable**.

---

## 👨‍💻 Author

**Ficram Manifur**

Electrical Engineering
Embedded System • IoT • Robotics • AI

GitHub: [@ficrammanifur](https://github.com/ficrammanifur)

---

## 📌 Status

🚧 **Under Development**

Project akan ditambahkan secara bertahap.
Setiap materi akan dilengkapi dengan:

* Source code
* Circuit diagram
* Penjelasan konsep
* Wokwi simulation
* Example output
* Notes / learning points
