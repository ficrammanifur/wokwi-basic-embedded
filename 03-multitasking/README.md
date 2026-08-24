# 03 — Multitasking

Mempelajari bagaimana ESP32 menjalankan beberapa proses secara paralel menggunakan FreeRTOS.

**Materi:** FreeRTOS Task • Task Scheduling • Task Priority • Dual Core • Task Affinity

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | FreeRTOS Task | Membuat dan menjalankan task |
| 02 | Task Scheduling | Mengatur eksekusi task |
| 03 | Task Priority | Menentukan prioritas task |
| 04 | Dual Core | Menjalankan task pada Core 0 & Core 1 |
| 05 | Task Affinity | Menentukan core untuk task |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **Membuat Task** - Membuat dan menjalankan FreeRTOS task
2. **Mengatur Scheduling** - Mengontrol eksekusi task
3. **Mengatur Prioritas** - Menentukan prioritas task
4. **Menggunakan Dual Core** - Memanfaatkan kedua core ESP32
5. **Mengatur Affinity** - Menentukan core untuk task

---

## 🔧 Komponen yang Digunakan

- ESP32 Dev Kit V1
- LED (Merah, Biru)
- Resistor 220Ω

---

## 📖 Penjelasan Setiap Materi

---

### 01-freertos-task — FreeRTOS Task

**Konsep:** Mempelajari cara membuat dan menjalankan task menggunakan FreeRTOS.

**Komponen:**
- 1x LED Merah (GPIO 2)
- 1x LED Biru (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED1 | 2 | Task 1 Output |
| LED2 | 4 | Task 2 Output |

**Cara Kerja:**
1. Buat dua task dengan xTaskCreate()
2. Task 1 mengedipkan LED1 setiap 500ms
3. Task 2 mengedipkan LED2 setiap 1000ms
4. Task berjalan paralel (concurrent)

**Kode Penting:**
```cpp
xTaskCreate(
  task1Code,      // Function
  "Task 1",       // Name
  2048,           // Stack size
  NULL,           // Parameters
  1,              // Priority
  &task1Handle    // Handle
);

void task1Code(void* parameter) {
  while (1) {
    // Do work
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
```

**Output yang Diharapkan:**
- LED1 berkedip 500ms
- LED2 berkedip 1000ms
- Serial monitor menampilkan status

**Learning Points:**
- FreeRTOS task lifecycle
- vTaskDelay() vs delay()
- Stack size allocation
- Task handle untuk kontrol

---

### 02-task-scheduling — Task Scheduling

**Konsep:** Mempelajari cara mengatur eksekusi task menggunakan timer dan scheduling.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Cara Kerja:**
1. Buat timer dengan xTimerCreate()
2. Timer callback dijalankan periodik
3. LED dikontrol oleh timer callback

**Kode Penting:**
```cpp
TimerHandle_t timer = xTimerCreate(
  "Timer1",
  pdMS_TO_TICKS(500),
  pdTRUE,  // Auto-reload
  (void*)0,
  timerCallback
);
xTimerStart(timer, 0);
```

**Output yang Diharapkan:**
- LED berkedip setiap 500ms
- Timer callback menampilkan log

**Learning Points:**
- Software timer vs hardware timer
- Timer auto-reload
- Timer callback

---

### 03-task-priority — Task Priority

**Konsep:** Mempelajari bagaimana prioritas task mempengaruhi eksekusi.

**Komponen:**
- 1x LED Merah (GPIO 2)
- 1x LED Biru (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED1 | 2 | Low Priority Task |
| LED2 | 4 | High Priority Task |

**Cara Kerja:**
1. Task 1 dengan prioritas rendah (1)
2. Task 2 dengan prioritas tinggi (2)
3. Task prioritas tinggi lebih sering dieksekusi

**Kode Penting:**
```cpp
xTaskCreate(
  lowPriorityTask,
  "Low Priority",
  2048,
  NULL,
  1,  // Priority 1 (low)
  NULL
);

xTaskCreate(
  highPriorityTask,
  "High Priority",
  2048,
  NULL,
  2,  // Priority 2 (high)
  NULL
);
```

**Output yang Diharapkan:**
- LED2 berkedip lebih sering
- Serial menunjukkan prioritas task

**Learning Points:**
- Prioritas task (1 = rendah, configMAX_PRIORITIES-1 = tinggi)
- Preemptive scheduling
- Starvation prevention

---

### 04-dual-core — Dual Core Execution

**Konsep:** Mempelajari cara menjalankan task pada core yang berbeda.

**Komponen:**
- 1x LED Merah (GPIO 2)
- 1x LED Biru (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED1 | 2 | Core 0 Task |
| LED2 | 4 | Core 1 Task |

**Cara Kerja:**
1. Task 1 dipin ke Core 0
2. Task 2 dipin ke Core 1
3. Kedua task berjalan paralel di core berbeda

**Kode Penting:**
```cpp
xTaskCreatePinnedToCore(
  core0Task,
  "Core 0 Task",
  2048,
  NULL,
  1,
  NULL,
  0  // Core 0
);

xTaskCreatePinnedToCore(
  core1Task,
  "Core 1 Task",
  2048,
  NULL,
  1,
  NULL,
  1  // Core 1
);

int core = xPortGetCoreID(); // Dapatkan core ID
```

**Output yang Diharapkan:**
- Serial menunjukkan core ID setiap task
- LED berkedip di core masing-masing

**Learning Points:**
- Dual core architecture ESP32
- xPortGetCoreID()
- Pinned tasks
- Core isolation

---

### 05-task-affinity — Task Affinity

**Konsep:** Mempelajari cara menentukan core affinity untuk task.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input (Affinity Change) |

**Cara Kerja:**
1. Task dibuat dengan affinity ke Core 0
2. Tombol digunakan untuk mengubah affinity
3. Task dipindahkan ke Core 1 saat tombol ditekan

**Kode Penting:**
```cpp
// Create with affinity
xTaskCreatePinnedToCore(
  taskWithAffinity,
  "Affinity Task",
  2048,
  (void*)0,  // Core 0
  2,
  &taskHandle,
  0
);

// Change affinity (delete and recreate)
vTaskDelete(taskHandle);
xTaskCreatePinnedToCore(
  taskWithAffinity,
  "Affinity Task",
  2048,
  (void*)1,  // Core 1
  2,
  &taskHandle,
  1
);
```

**Output yang Diharapkan:**
- Task berjalan di Core 0
- Saat tombol ditekan, task pindah ke Core 1

**Learning Points:**
- CPU affinity
- Dynamic affinity change
- Task migration antar core

---

## 📊 Perbandingan

| Metode | Kelebihan | Kekurangan |
|--------|-----------|------------|
| **Single Core** | Sederhana | Tidak parallel |
| **Dual Core** | Parallel, performa | Kompleksitas |
| **Fixed Affinity** | Predictable | Kurang fleksibel |
| **Dynamic Affinity** | Fleksibel | Overhead migrasi |

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa membuat FreeRTOS task
- [ ] Saya bisa mengatur scheduling task
- [ ] Saya bisa mengatur prioritas task
- [ ] Saya bisa menjalankan task di dual core
- [ ] Saya bisa mengatur task affinity
