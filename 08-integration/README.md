# 08 — System Integration

Menggabungkan semua konsep yang telah dipelajari menjadi satu sistem yang terintegrasi.

**Materi:** Sensor + Timer • Sensor + FreeRTOS • Sensor + Queue + MQTT • Dual Core + FreeRTOS • Complete Embedded System

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | Sensor + Timer | Membaca sensor periodik dengan timer |
| 02 | Sensor + FreeRTOS | Sensor dengan FreeRTOS task |
| 03 | Sensor + Queue + MQTT | Sensor, queue, dan MQTT integration |
| 04 | Dual Core + FreeRTOS | Dual core task execution |
| 05 | Complete System | Semua konsep digabungkan |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **Integration 01** - Menggabungkan sensor dan timer
2. **Integration 02** - Menggabungkan sensor dan FreeRTOS
3. **Integration 03** - Integrasi sensor, queue, dan MQTT
4. **Integration 04** - Dual core system
5. **Complete System** - Membangun sistem embedded lengkap

---

## 📖 Penjelasan Setiap Materi

---

### Integration 01 — Sensor + Timer

**Konsep:** Menggabungkan pembacaan sensor dengan timer non-blocking.

**Komponen:**
- 1x Potentiometer (GPIO 36)
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| Sensor | 36 | ADC Input |
| LED | 2 | Output |

**Arsitektur:**
```
Sensor → Timer → Read Sensor → Process Data → Output
```

**Cara Kerja:**
1. Timer menggunakan millis() untuk periodik
2. Sensor dibaca setiap 500ms
3. Data diproses dan LED dikontrol
4. Non-blocking - program tetap responsif

**Kode Penting:**
```cpp
if (millis() - lastRead >= READ_INTERVAL) {
  lastRead = millis();
  int value = analogRead(SENSOR_PIN);
  // Process data
}
```

**Output yang Diharapkan:**
```
Sensor: 2048 | Voltage: 1.65V | 50%
Sensor: 3072 | Voltage: 2.48V | 75%
```

---

### Integration 02 — Sensor + FreeRTOS Task

**Konsep:** Menggabungkan sensor dengan FreeRTOS task.

**Komponen:**
- 1x Potentiometer (GPIO 36)
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| Sensor | 36 | ADC Input |
| LED | 2 | Output |

**Arsitektur:**
```
┌───────────────┐
│ Sensor Task   │ → Read Sensor → Process
└───────────────┘
```

**Cara Kerja:**
1. Sensor Task membaca sensor periodik
2. Data dikirim via queue ke Process Task
3. Process Task mengontrol LED
4. Task berjalan paralel

**Kode Penting:**
```cpp
void sensorTask(void* parameter) {
  while (1) {
    int value = analogRead(SENSOR_PIN);
    xQueueSend(queue, &value, 0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```

---

### Integration 03 — Sensor + Queue + MQTT

**Konsep:** Mengintegrasikan sensor, queue, dan MQTT.

**Komponen:**
- 1x Potentiometer (GPIO 36)
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| Sensor | 36 | ADC Input |
| LED | 2 | Output |

**Arsitektur:**
```
┌───────────────┐     ┌───────────────┐     ┌───────────────┐
│ Sensor Task   │ →   │    Queue      │ →   │   MQTT Task   │
└───────────────┘     └───────────────┘     └───────────────┘
                                                    ↓
                                              ┌───────────┐
                                              │  Broker   │
                                              └───────────┘
```

**Cara Kerja:**
1. Sensor Task membaca sensor
2. Data dikirim ke queue
3. MQTT Task mengambil dari queue
4. Data dipublish ke MQTT broker

**Kode Penting:**
```cpp
void mqttTask(void* parameter) {
  while (1) {
    if (xQueueReceive(queue, &data, portMAX_DELAY)) {
      client.publish("esp32/sensor", payload);
    }
  }
}
```

---

### Integration 04 — Dual Core + FreeRTOS

**Konsep:** Menjalankan task di dual core ESP32.

**Komponen:**
- 1x Potentiometer (GPIO 36)
- 1x LED Merah (GPIO 2)
- 1x LED Biru (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| Sensor | 36 | ADC Input |
| LED1 | 2 | Core 0 Output |
| LED2 | 4 | Core 1 Output |

**Arsitektur:**
```
              ESP32
                │
       ┌────────┴────────┐
       ↓                 ↓
    CORE 0            CORE 1
       │                 │
   Sensor Task       Control Task
   MQTT Task         LED Control
```

**Cara Kerja:**
1. Core 0: Sensor + MQTT (Network)
2. Core 1: Control + Processing
3. Queue untuk komunikasi antar core

**Kode Penting:**
```cpp
xTaskCreatePinnedToCore(
  core0Task, NULL, 4096, NULL, 2, NULL, 0  // Core 0
);

xTaskCreatePinnedToCore(
  core1Task, NULL, 4096, NULL, 1, NULL, 1  // Core 1
);
```

---

### Integration 05 — Complete Embedded System

**Konsep:** Menggabungkan SEMUA konsep menjadi satu sistem.

**Komponen:**
- 1x Potentiometer (GPIO 36) - ADC
- 1x Push Button (GPIO 4) - Interrupt
- 1x LED (GPIO 2) - PWM
- 1x LED (GPIO 5) - Output

**Arsitektur:**
```
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

**Features:**
- ✅ GPIO - Digital I/O
- ✅ ADC - Analog reading
- ✅ PWM - LED control
- ✅ Timer - Periodic tasks
- ✅ Interrupt - Button response
- ✅ FreeRTOS - Multitasking
- ✅ Dual Core - Parallel execution
- ✅ Queue - Task communication
- ✅ Mutex - Shared resource protection
- ✅ WiFi - Network connectivity
- ✅ MQTT - IoT communication
- ✅ State Machine - Program flow control
- ✅ Watchdog - System reliability

**Kode Penting:**
```cpp
// Complete system initialization
initWatchdog();
initWiFi();
initMQTT();
initFreeRTOS();

// State machine
updateStateMachine(data);

// Task communication
xQueueSend(sensorQueue, &data, 0);
xQueueReceive(sensorQueue, &data, portMAX_DELAY);

// Interrupt
void IRAM_ATTR buttonISR() { buttonPressed = true; }
```

**Output yang Diharapkan:**
```
=== Complete Embedded System Started ===
Sensor Task on Core: 0
Control Task on Core: 1
MQTT Task on Core: 0
Sensor: 2048 (50%)
State: IDLE -> RUNNING
Status: RUNNING | Heap: 280 KB
Button interrupt: LED2 toggled
MQTT Published: 2048,1.65,50
```

---

## 🎯 Final Learning Outcomes

Setelah menyelesaikan semua modul, Anda akan mampu:

1. **Membangun sistem embedded** - Dari nol hingga sistem lengkap
2. **Menggunakan ESP32 features** - GPIO, ADC, PWM, Timer, Interrupt
3. **Komunikasi** - UART, I2C, SPI, WiFi, MQTT
4. **Multitasking** - FreeRTOS, dual core
5. **Sinkronisasi** - Queue, Semaphore, Mutex
6. **Manajemen sistem** - Watchdog, Deep Sleep, NVS, OTA
7. **Arsitektur** - State Machine, Modular, Event-Driven
8. **Optimasi** - CPU, Memory, Stack
9. **Integrasi** - Semua komponen menjadi satu sistem

---

## ✅ Final Checklist

- [ ] Saya bisa menggunakan GPIO, ADC, PWM
- [ ] Saya bisa menggunakan Timer dan Interrupt
- [ ] Saya bisa membuat program non-blocking
- [ ] Saya bisa berkomunikasi via UART, I2C, SPI
- [ ] Saya bisa connect WiFi dan MQTT
- [ ] Saya bisa membuat FreeRTOS task
- [ ] Saya bisa menggunakan dual core
- [ ] Saya bisa menggunakan queue, semaphore, mutex
- [ ] Saya bisa menggunakan watchdog dan deep sleep
- [ ] Saya bisa menyimpan data di NVS
- [ ] Saya bisa melakukan OTA
- [ ] Saya bisa membuat state machine
- [ ] Saya bisa membuat program modular
- [ ] Saya bisa mengoptimasi sistem
- [ ] Saya bisa mengintegrasikan semua konsep

---

**🎉 Selamat! Anda telah menyelesaikan semua modul!**

---

**Author:** Ficram Manifur
**GitHub:** [@ficrammanifur](https://github.com/ficrammanifur)

---

# 📁 Struktur Folder Lengkap

```text
wokwi-basic-embedded/
│
├── 01-fundamental/
│   ├── 01-gpio/
│   │   ├── sketch.ino
│   │   ├── diagram.json
│   │   └── README.md
│   ├── 02-adc/
│   │   ├── sketch.ino
│   │   ├── diagram.json
│   │   └── README.md
│   ├── 03-pwm/
│   │   ├── sketch.ino
│   │   ├── diagram.json
│   │   └── README.md
│   ├── 04-interrupt/
│   │   ├── sketch.ino
│   │   ├── diagram.json
│   │   └── README.md
│   ├── 05-timer/
│   │   ├── sketch.ino
│   │   ├── diagram.json
│   │   └── README.md
│   ├── 06-non-blocking/
│   │   ├── sketch.ino
│   │   ├── diagram.json
│   │   └── README.md
│   └── README.md
│
├── 02-communication/
│   ├── 01-uart/
│   ├── 02-i2c/
│   ├── 03-spi/
│   ├── 04-wifi/
│   ├── 05-mqtt/
│   └── README.md
│
├── 03-multitasking/
│   ├── 01-freertos-task/
│   ├── 02-task-scheduling/
│   ├── 03-task-priority/
│   ├── 04-dual-core/
│   ├── 05-task-affinity/
│   └── README.md
│
├── 04-synchronization/
│   ├── 01-queue/
│   ├── 02-semaphore/
│   ├── 03-mutex/
│   ├── 04-event-group/
│   ├── 05-task-notification/
│   └── README.md
│
├── 05-system-management/
│   ├── 01-watchdog/
│   ├── 02-deep-sleep/
│   ├── 03-nvs-preferences/
│   ├── 04-ota/
│   ├── 05-memory-management/
│   └── README.md
│
├── 06-program-architecture/
│   ├── 01-state-machine/
│   ├── 02-modular-programming/
│   ├── 03-event-driven/
│   ├── 04-error-handling/
│   └── README.md
│
├── 07-optimization/
│   ├── 01-cpu-usage/
│   ├── 02-heap-monitoring/
│   ├── 03-stack-monitoring/
│   ├── 04-memory-optimization/
│   └── README.md
│
└── 08-integration/
    ├── 01-sensor-timer/
    ├── 02-sensor-freertos/
    ├── 03-sensor-queue-mqtt/
    ├── 04-dual-core-system/
    ├── 05-complete-system/
    └── README.md
```

---

Semua README.md telah dibuat lengkap dengan:
- ✅ Deskripsi level
- ✅ Daftar materi
- ✅ Tujuan pembelajaran
- ✅ Komponen dan pinout
- ✅ Penjelasan setiap materi
- ✅ Cara kerja
- ✅ Kode penting
- ✅ Output yang diharapkan
- ✅ Learning points
- ✅ Checklist pemahaman

Selamat belajar! 🚀

---

## 🔗 Navigasi

- [⬅ Kembali ke Home](../README.md)
