<h1 align="center">Wokwi Basic Embedded</h1>

<p align="center">
  <a href="https://ficrammanifur.github.io/wokwi-basic-embedded/">
    <img src="https://img.shields.io/badge/GitHub%20Pages-Live%20Demo-10b981?style=for-the-badge&logo=github" alt="GitHub Pages">
  </a>
  <a href="https://www.espressif.com/en/products/socs/esp32">
    <img src="https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32">
  </a>
  <a href="https://www.arduino.cc/">
    <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino">
  </a>
  <a href="https://www.freertos.org/">
    <img src="https://img.shields.io/badge/FreeRTOS-000000?style=for-the-badge&logo=freertos&logoColor=white" alt="FreeRTOS">
  </a>
  <a href="https://www.hivemq.com/">
    <img src="https://img.shields.io/badge/HiveMQ%20MQTT-Ready%20WSS-059669?style=for-the-badge&logo=hivemq" alt="MQTT">
  </a>
  <a href="https://wokwi.com/">
    <img src="https://img.shields.io/badge/Wokwi-Simulator-FF6C37?style=for-the-badge&logo=wokwi&logoColor=white" alt="Wokwi">
  </a>
  <a href="https://isocpp.org/">
    <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
  </a>
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="License">
  </a>
  <a href="https://github.com/ficrammanifur/wokwi-basic-embedded/stargazers">
    <img src="https://img.shields.io/github/stars/ficrammanifur/wokwi-basic-embedded?style=for-the-badge&logo=github" alt="GitHub Stars">
  </a>
  <a href="https://github.com/ficrammanifur/wokwi-basic-embedded/network/members">
    <img src="https://img.shields.io/github/forks/ficrammanifur/wokwi-basic-embedded?style=for-the-badge&logo=github" alt="GitHub Forks">
  </a>
  <a href="https://github.com/ficrammanifur/wokwi-basic-embedded/issues">
    <img src="https://img.shields.io/github/issues/ficrammanifur/wokwi-basic-embedded?style=for-the-badge&logo=github" alt="GitHub Issues">
  </a>
</p>

Kumpulan pembelajaran **Embedded System menggunakan ESP32** yang dibuat secara bertahap dari konsep dasar hingga integrasi beberapa fitur.

Repository ini menggunakan **Wokwi** sebagai simulator sehingga setiap materi dapat dipelajari, dijalankan, dan diuji tanpa membutuhkan hardware fisik.

> 🎯 **Goal:** memahami konsep embedded programming dari dasar sampai mampu menggabungkan beberapa konsep menjadi sebuah sistem ESP32 yang terstruktur.

---

## 📌 Daftar Isi

1. [Project Overview](#-project-overview)
2. [Learning Roadmap](#-learning-roadmap)
3. [Struktur Folder](#-struktur-folder)
4. [Tech Stack](#-tech-stack)
5. [Cara Menggunakan Repository Ini](#-cara-menggunakan-repository-ini)
6. [Learning Goal](#-learning-goal)
7. [Author](#-author)
8. [Status](#-status)

---

## 🌟 Project Overview

**Wokwi Basic Embedded** adalah learning path lengkap untuk mempelajari Embedded System dari dasar hingga mahir menggunakan ESP32 dan Wokwi Simulator.

Repository ini dirancang dengan prinsip:
- **No Hardware Required**: 100% menggunakan Wokwi Simulator, bisa diakses dari browser.
- **Step-by-Step Learning**: Dari konsep dasar GPIO hingga sistem embedded lengkap.
- **Single Source of Truth**: Setiap materi memiliki source code, diagram, dan penjelasan konsep.
- **Real-World Ready**: Konsep yang dipelajari dapat langsung diaplikasikan ke proyek nyata.

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

# [01 — Fundamental](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/01-fundamental)

Konsep dasar yang menjadi fondasi pemrograman ESP32.

| No | Materi                   | Pembahasan                           |   Wokwi   |
| -: | ------------------------ | ------------------------------------ | :-------: |
| 01 | GPIO                     | Digital Input & Output               | [▶️ Open](https://wokwi.com/projects/473243606471710721) |
| 02 | ADC                      | Membaca sinyal analog                | [▶️ Open](https://wokwi.com/projects/473241427551174657) |
| 03 | PWM                      | Mengatur duty cycle                  | [▶️ Open](https://wokwi.com/projects/448772289285109761) |
| 04 | Interrupt                | Merespons event secara langsung      | [▶️ Open](https://wokwi.com/projects/473244403344647169) |
| 05 | Timer                    | Menjalankan proses berdasarkan waktu | [▶️ Open](https://wokwi.com/projects/473240844295318529) |
| 06 | Non-Blocking Programming | `millis()` tanpa `delay()`           | [▶️ Open](https://wokwi.com/projects/473245265387627521) |

---

# [02 Communication](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/02-communication)

Mempelajari cara ESP32 berkomunikasi dengan perangkat lain maupun jaringan.

| No | Materi        | Pembahasan                                |   Wokwi   |
| -: | ------------- | ----------------------------------------- | :-------: |
| 01 | UART / Serial | Komunikasi serial                         | [▶️ Open](https://wokwi.com/projects/473245568742842369) |
| 02 | I2C           | Komunikasi dua kabel                      | [▶️ Open](https://wokwi.com/projects/473258801882043393) |
| 03 | SPI           | Komunikasi berkecepatan tinggi            | [▶️ Open](https://wokwi.com/projects/473258960371197953) |
| 04 | WiFi          | Koneksi ESP32 ke jaringan                 | [▶️ Open](https://wokwi.com/projects/473260149265807361) |
| 05 | MQTT          | Komunikasi IoT berbasis publish/subscribe | [▶️ Open](https://wokwi.com/projects/473260296273045505) |

---

# [03 Multitasking](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/03-multitasking)

Mempelajari bagaimana ESP32 menjalankan beberapa proses menggunakan FreeRTOS.

| No | Materi          | Pembahasan                            |   Wokwi   |
| -: | --------------- | ------------------------------------- | :-------: |
| 01 | FreeRTOS Task   | Membuat task                          | [▶️ Open](https://wokwi.com/projects/473260380649870337) |
| 02 | Task Scheduling | Mengatur eksekusi task                | [▶️ Open](https://wokwi.com/projects/473260629274617857) |
| 03 | Task Priority   | Menentukan prioritas task             | [▶️ Open](https://wokwi.com/projects/473260954151834625) |
| 04 | Dual Core       | Menjalankan task pada Core 0 & Core 1 | [▶️ Open](https://wokwi.com/projects/473261039534247937) |
| 05 | Task Affinity   | Menentukan core untuk task            | [▶️ Open](https://wokwi.com/projects/473261137869732865) |

---

# [04 Task Communication & Synchronization](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/04-synchronization)

Mempelajari bagaimana task saling berkomunikasi dan bagaimana resource bersama dikendalikan.

| No | Materi            | Pembahasan                     |   Wokwi   |
| -: | ----------------- | ------------------------------ | :-------: |
| 01 | Queue             | Mengirim data antar-task       | [▶️ Open](https://wokwi.com/projects/473261240357564417) |
| 02 | Semaphore         | Sinkronisasi antar-task        | [▶️ Open](https://wokwi.com/projects/473261362491528193) |
| 03 | Mutex             | Mengamankan shared resource    | [▶️ Open](https://wokwi.com/projects/473261560705986561) |
| 04 | Event Group       | Sinkronisasi berdasarkan event | [▶️ Open](https://wokwi.com/projects/473261663339578369) |
| 05 | Task Notification | Komunikasi ringan antar-task   | [▶️ Open](https://wokwi.com/projects/473261809130462209) |

---

# [05 System Management & Reliability](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/05-system-management)

Konsep untuk membuat sistem ESP32 lebih stabil, aman, hemat daya, dan mudah dipelihara.

| No | Materi            | Pembahasan                       |   Wokwi   |
| -: | ----------------- | -------------------------------- | :-------: |
| 01 | Watchdog Timer    | Mendeteksi task/system yang hang | [▶️ Open](https://wokwi.com/projects/473261962517235713) |
| 02 | Deep Sleep        | Menghemat konsumsi daya          | [▶️ Open](https://wokwi.com/projects/473262122340168705) |
| 03 | NVS / Preferences | Menyimpan konfigurasi            | [▶️ Open](https://wokwi.com/projects/473262390742115329) |
| 04 | OTA               | Update firmware melalui jaringan | [▶️ Open](https://wokwi.com/projects/473263193942066177) |
| 05 | Memory Management | Pengelolaan RAM dan heap         | [▶️ Open](https://wokwi.com/projects/473263653325406209) |
| 06 | Stack Monitoring  | Memantau penggunaan stack        | [▶️ Open](https://wokwi.com/projects/473263990688039937) |

---

# [06 Program Architecture](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/06-program-architecture)

Mempelajari cara membuat program embedded yang lebih terstruktur dan mudah dikembangkan.

| No | Materi                   | Pembahasan                          |   Wokwi   |
| -: | ------------------------ | ----------------------------------- | :-------: |
| 01 | State Machine            | Mengatur alur berdasarkan state     | [▶️ Open] |
| 02 | Modular Programming      | Memisahkan program menjadi modul    | [▶️ Open] |
| 03 | Event-Driven Programming | Program berdasarkan event           | [▶️ Open] |
| 04 | Error Handling           | Menangani kondisi error             | [▶️ Open] |
| 05 | Configuration Management | Memisahkan konfigurasi dari program | [▶️ Open] |

---

# [07 Optimization](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/07-optimization)

Mempelajari bagaimana meningkatkan performa dan efisiensi sistem.

| No | Materi              | Pembahasan                      |   Wokwi   |
| -: | ------------------- | ------------------------------- | :-------: |
| 01 | CPU Usage           | Memantau penggunaan CPU         | [▶️ Open] |
| 02 | Heap Monitoring     | Memantau penggunaan heap        | [▶️ Open] |
| 03 | Stack Optimization  | Mengoptimalkan penggunaan stack | [▶️ Open] |
| 04 | Memory Optimization | Mengurangi penggunaan memory    | [▶️ Open] |
| 05 | Task Optimization   | Mengoptimalkan task             | [▶️ Open] |

---

# [08 System Integration](https://github.com/ficrammanifur/wokwi-basic-embedded/tree/main/08-integration)

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

## 🗂️ Struktur Folder

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

## 🛠️ Tech Stack

| Teknologi | Deskripsi |
|-----------|-----------|
| ![ESP32](https://img.shields.io/badge/ESP32-000000?style=flat&logo=espressif&logoColor=white) | Microcontroller target |
| ![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=arduino&logoColor=white) | Framework pemrograman |
| ![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white) | Bahasa pemrograman |
| ![FreeRTOS](https://img.shields.io/badge/FreeRTOS-000000?style=flat&logo=freertos&logoColor=white) | Real-time OS |
| ![Wokwi](https://img.shields.io/badge/Wokwi-Simulator-FF6C37?style=flat&logo=wokwi&logoColor=white) | Simulator |
| ![MQTT](https://img.shields.io/badge/MQTT-059669?style=flat&logo=hivemq) | IoT Communication |
| ![Git](https://img.shields.io/badge/Git-F05032?style=flat&logo=git&logoColor=white) | Version Control |
| ![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white) | Repository hosting |

---

## 🚀 Cara Menggunakan Repository Ini

### 1. Clone Repository

```bash
git clone https://github.com/ficrammanifur/wokwi-basic-embedded.git
cd wokwi-basic-embedded
```

### 2. Akses Via Wokwi

1. Buka [Wokwi.com](https://wokwi.com)
2. Pilih "ESP32 Dev Kit V1"
3. Copy-paste kode dari `sketch.ino`
4. Copy-paste diagram dari `diagram.json`
5. Klik "Start Simulation"

### 3. Jalankan Secara Lokal (Opsional)

```bash
# Install Arduino IDE atau PlatformIO
# Buka folder project
# Upload ke ESP32 fisik
```

---

## 🎯 Learning Goal

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

<p align="center">
  <strong>Ficram Manifur</strong>
</p>

<p align="center">
  <a href="https://github.com/ficrammanifur">
    <img src="https://img.shields.io/badge/GitHub-@ficrammanifur-181717?style=for-the-badge&logo=github" alt="GitHub">
  </a>
  <a href="https://www.linkedin.com/in/ficram-manifur-farissa-418280376">
    <img src="https://img.shields.io/badge/LinkedIn-Ficram%20Manifur-0A66C2?style=for-the-badge&logo=linkedin" alt="LinkedIn">
  </a>
  <a href="mailto:ficramm@gmail.com">
    <img src="https://img.shields.io/badge/Email-ficramm@gmail.com-EA4335?style=for-the-badge&logo=gmail" alt="Email">
  </a>
</p>

<p align="center">
  Electrical Engineering<br>
  Embedded System • IoT • Robotics • AI
</p>

---

## 📌 Status

🚧 **Under Development**

Project akan ditambahkan secara bertahap.  
Setiap materi akan dilengkapi dengan:

- [x] Source code
- [x] Circuit diagram
- [x] Penjelasan konsep
- [ ] Wokwi simulation
- [ ] Example output
- [ ] Notes / learning points

### Progress Tracker

| Modul | Status | Progress |
|-------|--------|----------|
| 01 Fundamental | ✅ Complete | 100% |
| 02 Communication | 🚧 In Progress | 60% |
| 03 Multitasking | 📝 Planned | 0% |
| 04 Synchronization | 📝 Planned | 0% |
| 05 System Management | 📝 Planned | 0% |
| 06 Program Architecture | 📝 Planned | 0% |
| 07 Optimization | 📝 Planned | 0% |
| 08 System Integration | 📝 Planned | 0% |

---

## 🤝 Kontribusi

Kontribusi sangat diterima! Silakan:

1. Fork repository ini
2. Buat branch baru (`git checkout -b feature/improvement`)
3. Commit perubahan (`git commit -m 'Add some improvement'`)
4. Push ke branch (`git push origin feature/improvement`)
5. Buat Pull Request

---

## 📄 License

<p align="center">
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="MIT License">
  </a>
</p>

<p align="center">
  <a href="LICENSE">MIT License</a> — Copyright © 2025 Ficram Manifur
</p>

---

<div align="center">

**⚡ Built with ESP32**

**⭐ Star this repo if you like it!**

<p><a href="#top">⬆ Kembali ke Atas</a></p>

</div>
