# 07 — Optimization

Mempelajari bagaimana meningkatkan performa dan efisiensi sistem.

**Materi:** CPU Usage • Heap Monitoring • Stack Optimization • Memory Optimization • Task Optimization

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | CPU Usage | Memantau penggunaan CPU |
| 02 | Heap Monitoring | Memantau penggunaan heap |
| 03 | Stack Optimization | Mengoptimalkan penggunaan stack |
| 04 | Memory Optimization | Mengurangi penggunaan memory |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **CPU Usage** - Memonitor dan mengoptimalkan CPU
2. **Heap Monitoring** - Memantau penggunaan heap
3. **Stack Optimization** - Mengoptimalkan stack
4. **Memory Optimization** - Mengurangi memory footprint

---

## 📖 Penjelasan Setiap Materi

---

### 01-cpu-usage — CPU Usage Monitoring

**Konsep:** Mempelajari cara memantau penggunaan CPU pada ESP32.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Cara Kerja:**
1. Get task statistics dengan uxTaskGetSystemState()
2. Hitung CPU usage per task
3. Tampilkan idle CPU
4. Optimasi berdasarkan data

**Kode Penting:**
```cpp
UBaseType_t taskCount = uxTaskGetNumberOfTasks();
TaskStatus_t* taskStatusArray;
taskStatusArray = (TaskStatus_t*)malloc(taskCount * sizeof(TaskStatus_t));

uxTaskGetSystemState(taskStatusArray, taskCount, NULL);

float cpuUsage = (float)task.ulRunTimeCounter / configTICK_RATE_HZ * 100;
```

**Output yang Diharapkan:**
```
=== CPU Usage Report ===
Task Name          CPU Usage   State
IDLE               45.5%       Ready
Sensor Task        30.2%       Running
MQTT Task          15.3%       Blocked
Control Task       9.0%        Blocked
------------------------
Idle CPU: 54.5%
```

**Learning Points:**
- Task statistics
- CPU usage calculation
- Idle task monitoring
- Bottleneck identification

---

### 02-heap-monitoring — Heap Monitoring

**Konsep:** Mempelajari cara memantau penggunaan heap memory.

**Komponen:**
- Tidak ada komponen fisik

**Cara Kerja:**
1. Monitor total heap dan free heap
2. Track largest free block (fragmentation)
3. Monitor heap usage percentage
4. Deteksi memory issues

**Kode Penting:**
```cpp
size_t totalHeap = ESP.getHeapSize();
size_t freeHeap = ESP.getFreeHeap();
size_t largestFreeBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);

float heapUsage = (float)(totalHeap - freeHeap) / totalHeap * 100;
```

**Output yang Diharapkan:**
```
=== Heap Monitoring ===
Total Heap: 320 KB
Free Heap: 180 KB
Heap Usage: 43.8%
Largest Free Block: 120 KB
Minimum Free Heap: 150 KB
```

**Learning Points:**
- Heap fragmentation
- Memory leak detection
- Memory allocation patterns
- Heap monitoring tools

---

### 03-stack-monitoring — Stack Monitoring

**Konsep:** Mempelajari cara memantau penggunaan stack task.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Cara Kerja:**
1. Dapatkan stack high water mark
2. Monitor stack usage
3. Deteksi stack overflow risk
4. Optimasi stack size

**Kode Penting:**
```cpp
UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(taskHandle);
// Returns minimum free stack space in words

if (highWaterMark < 100) {
  Serial.println("WARNING: Stack low!");
}
```

**Output yang Diharapkan:**
```
Monitored Task Stack High Water Mark: 800 words (3200 bytes)
WARNING: Stack low!
```

**Learning Points:**
- Stack vs Heap
- Stack high water mark
- Stack overflow prevention
- Stack size optimization

---

### 04-memory-optimization — Memory Optimization

**Konsep:** Mempelajari cara mengurangi penggunaan memory.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Teknik Optimasi:**
1. **PROGMEM** - Store strings in flash
2. **Bit Fields** - Smaller data structures
3. **Smaller Data Types** - Use uint8_t instead of int
4. **Efficient Strings** - Avoid String class overhead

**Kode Penting:**
```cpp
// PROGMEM
const char message[] PROGMEM = "Flash string";

// Bit fields
typedef struct {
  uint8_t ledState : 1;
  uint8_t errorFlag : 1;
} StatusFlags;

// Efficient string
char buffer[20];
snprintf(buffer, sizeof(buffer), "Value: %d", value);
```

**Output yang Diharapkan:**
```
=== Memory Info ===
Free Heap: 280 KB (before optimization)
Free Heap: 310 KB (after optimization)
```

**Learning Points:**
- PROGMEM usage
- Data type selection
- String optimization
- Memory efficient structures

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa memonitor CPU usage
- [ ] Saya bisa memonitor heap usage
- [ ] Saya bisa memonitor stack usage
- [ ] Saya bisa mengoptimalkan memory

---

## 🔗 Navigasi

- [⬅ Kembali ke Home](../README.md)
- [➡ Lanjut ke Integration](../08-integration/README.md)
