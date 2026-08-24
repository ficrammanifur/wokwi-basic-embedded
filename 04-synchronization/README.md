# 04 — Task Communication & Synchronization

Mempelajari bagaimana task saling berkomunikasi dan bagaimana resource bersama dikendalikan.

**Materi:** Queue • Semaphore • Mutex • Event Group • Task Notification

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | Queue | Mengirim data antar-task |
| 02 | Semaphore | Sinkronisasi antar-task |
| 03 | Mutex | Mengamankan shared resource |
| 04 | Event Group | Sinkronisasi berdasarkan event |
| 05 | Task Notification | Komunikasi ringan antar-task |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **Queue** - Mengirim data antar task dengan aman
2. **Semaphore** - Sinkronisasi task menggunakan semaphore
3. **Mutex** - Melindungi shared resource
4. **Event Group** - Sinkronisasi multiple event
5. **Task Notification** - Komunikasi cepat antar task

---

## 📖 Penjelasan Setiap Materi

---

### 01-queue — Queue Communication

**Konsep:** Mempelajari cara mengirim data antar task menggunakan queue.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Cara Kerja:**
1. Producer task menghasilkan data
2. Data dikirim ke queue
3. Consumer task menerima data dari queue
4. Data diproses dan LED dikontrol

**Kode Penting:**
```cpp
QueueHandle_t dataQueue = xQueueCreate(10, sizeof(SensorData));

// Send to queue
xQueueSend(dataQueue, &data, 0);

// Receive from queue
xQueueReceive(dataQueue, &receivedData, portMAX_DELAY);
```

**Output yang Diharapkan:**
```
Producer: Sent value 42 (Item 1)
Consumer: Received value 42 at 12345
Producer: Sent value 87 (Item 2)
Consumer: Received value 87 at 12845
```

**Learning Points:**
- Queue creation and configuration
- Sending with timeout
- Receiving with timeout
- Multiple producers/consumers

---

### 02-semaphore — Semaphore

**Konsep:** Mempelajari sinkronisasi antar task menggunakan semaphore.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input |

**Cara Kerja:**
1. Task menunggu semaphore
2. Button press memberikan semaphore
3. Task yang menunggu akan berjalan
4. LED menyala setelah semaphore diberikan

**Kode Penting:**
```cpp
SemaphoreHandle_t semaphore = xSemaphoreCreateBinary();

// Wait for semaphore
xSemaphoreTake(semaphore, portMAX_DELAY);

// Give semaphore
xSemaphoreGive(semaphore);
```

**Output yang Diharapkan:**
```
Wait Task: Waiting for semaphore...
Button pressed - Giving semaphore
Wait Task: Semaphore acquired!
Wait Task: Work done
```

**Learning Points:**
- Binary semaphore
- Semaphore take/give
- Task synchronization
- Timeout handling

---

### 03-mutex — Mutex

**Konsep:** Mempelajari cara mengamankan shared resource menggunakan mutex.

**Komponen:**
- 1x LED Merah (GPIO 2)
- 1x LED Biru (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED1 | 2 | Task 1 |
| LED2 | 4 | Task 2 |

**Cara Kerja:**
1. Shared counter dilindungi mutex
2. Dua task mengakses counter dengan mutex
3. Mutex memastikan akses terurut
4. Tanpa mutex terjadi race condition

**Kode Penting:**
```cpp
SemaphoreHandle_t mutex = xSemaphoreCreateMutex();

// Access shared resource
xSemaphoreTake(mutex, portMAX_DELAY);
sharedCounter++;
xSemaphoreGive(mutex);
```

**Output yang Diharapkan:**
```
Task 1: Counter = 1
Task 2: Counter = 3
Task 1: Counter = 4
Task 2: Counter = 6
```

**Learning Points:**
- Mutex vs Binary Semaphore
- Priority inversion
- Recursive mutex
- Mutex for shared resources

---

### 04-event-group — Event Group

**Konsep:** Mempelajari sinkronisasi berdasarkan event menggunakan event group.

**Komponen:**
- 1x LED Merah (GPIO 2)
- 1x LED Biru (GPIO 4)
- 1x Push Button (GPIO 5)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED1 | 2 | Output |
| LED2 | 4 | Output |
| Button | 5 | Input |

**Cara Kerja:**
1. Event group memiliki 2 bit event
2. Task menunggu kedua event terjadi
3. Button men-set event secara berurutan
4. Task berjalan setelah semua event terjadi

**Kode Penting:**
```cpp
EventGroupHandle_t eventGroup = xEventGroupCreate();

// Set event
xEventGroupSetBits(eventGroup, EVENT_BIT_1);

// Wait for events
EventBits_t bits = xEventGroupWaitBits(
  eventGroup,
  EVENT_ALL,    // Bits to wait for
  pdTRUE,       // Clear on exit
  pdTRUE,       // Wait for all bits
  portMAX_DELAY
);
```

**Output yang Diharapkan:**
```
Waiting for events...
Button pressed - Setting events
Event 1 set
Event 2 set
All events received!
```

**Learning Points:**
- Event group bits
- OR/AND synchronization
- Wait with timeout
- Multiple event handling

---

### 05-task-notification — Task Notification

**Konsep:** Mempelajari komunikasi ringan antar-task menggunakan task notification.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input |

**Cara Kerja:**
1. Receiver task menunggu notification
2. Button mengirim notification dengan nilai
3. Receiver menerima nilai dan aksinya
4. 32-bit value dapat membawa command

**Kode Penting:**
```cpp
// Send notification
xTaskNotify(receiverTaskHandle, command, eSetValueWithOverwrite);

// Receive notification
xTaskNotifyWait(0, ULONG_MAX, &notificationValue, portMAX_DELAY);
```

**Output yang Diharapkan:**
```
Receiver: Waiting for notification...
Main: Notification sent with value: 1
Receiver: Notification received with value: 1
Receiver: LED ON
```

**Learning Points:**
- Task notification vs queue
- 32-bit value for command
- Lightweight communication
- Direct to task

---

## 📊 Perbandingan Metode

| Metode | Kecepatan | Ukuran | Penggunaan |
|--------|-----------|--------|------------|
| **Queue** | Sedang | Fleksibel | Data transfer |
| **Semaphore** | Cepat | 1 bit | Sinkronisasi |
| **Mutex** | Cepat | 1 bit | Shared resource |
| **Event Group** | Cepat | 24 bit | Multiple events |
| **Notification** | Sangat Cepat | 32 bit | Command/data |

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa mengirim data dengan queue
- [ ] Saya bisa sinkronisasi dengan semaphore
- [ ] Saya bisa mengamankan resource dengan mutex
- [ ] Saya bisa menggunakan event group
- [ ] Saya bisa menggunakan task notification
