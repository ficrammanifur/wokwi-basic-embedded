# 06 — Program Architecture

Mempelajari cara membuat program embedded yang lebih terstruktur dan mudah dikembangkan.

**Materi:** State Machine • Modular Programming • Event-Driven • Error Handling • Configuration Management

---

## 📚 Daftar Materi

| No | Materi | Deskripsi |
|:--:|--------|-----------|
| 01 | State Machine | Mengatur alur berdasarkan state |
| 02 | Modular Programming | Memisahkan program menjadi modul |
| 03 | Event-Driven | Program berdasarkan event |
| 04 | Error Handling | Menangani kondisi error |
| 05 | Configuration Management | Memisahkan konfigurasi dari program |

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan modul ini, Anda akan mampu:

1. **State Machine** - Mengelola alur program dengan state
2. **Modular Programming** - Membuat kode yang terstruktur
3. **Event-Driven** - Membangun program responsive
4. **Error Handling** - Menangani error dengan baik
5. **Configuration Management** - Mengelola konfigurasi

---

## 📖 Penjelasan Setiap Materi

---

### 01-state-machine — State Machine

**Konsep:** Mempelajari cara mengelola alur program menggunakan state machine.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input |

**State Definitions:**
```
STATE_IDLE     -> Menunggu input
STATE_STARTUP  -> Inisialisasi
STATE_RUNNING  -> Operasi normal
STATE_ERROR    -> Kondisi error
STATE_SHUTDOWN -> Shutdown
```

**Cara Kerja:**
1. Definisikan states dengan enum
2. Setiap state memiliki handler function
3. Transisi antar state berdasarkan kondisi
4. Entry/exit actions untuk setiap state

**Kode Penting:**
```cpp
enum SystemState {
  STATE_IDLE,
  STATE_STARTUP,
  STATE_RUNNING,
  STATE_ERROR,
  STATE_SHUTDOWN
};

void handleIdleState() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    changeState(STATE_STARTUP);
  }
}
```

**Output yang Diharapkan:**
```
State: IDLE - Waiting for button press
State: STARTUP - Initializing system
Startup step 1
Startup step 2
State: RUNNING - System operational
```

**Learning Points:**
- State machine concept
- State transitions
- Entry/exit actions
- Event-driven state changes

---

### 02-modular-programming — Modular Programming

**Konsep:** Mempelajari cara memisahkan program menjadi modul-modul yang terstruktur.

**Komponen:**
- 1x LED (GPIO 2)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |

**Modul:**
1. **LedModule** - Kontrol LED
2. **TimerModule** - Timer management
3. **LoggerModule** - Logging system

**Cara Kerja:**
1. Setiap modul memiliki header dan implementation
2. Modul memiliki interface yang jelas
3. Modul independen dan reusable
4. Main program menggunakan modul

**Kode Penting:**
```cpp
// LedModule.h
class LedModule {
public:
  static void init(int pin);
  static void setState(bool state);
  static void toggle();
};

// main.cpp
LedModule::init(LED_PIN);
LedModule::setState(true);
```

**Output yang Diharapkan:**
```
[LOG] 0ms: System started
[LOG] 0ms: LED Module initialized
[LOG] 1000ms: LED toggled
```

**Learning Points:**
- Separation of concerns
- Interface design
- Code reuse
- Maintainability

---

### 03-event-driven — Event-Driven Programming

**Konsep:** Mempelajari program yang berbasis event.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input |

**Event Types:**
```
EVENT_BUTTON_PRESSED
EVENT_BUTTON_RELEASED
EVENT_TIMER_TICK
EVENT_LED_TOGGLE
EVENT_LED_ON
EVENT_LED_OFF
```

**Cara Kerja:**
1. Events di-generate oleh input/sensor/timer
2. Events dimasukkan ke queue
3. Event handler memproses event
4. System merespons berdasarkan event

**Kode Penting:**
```cpp
struct Event {
  EventType type;
  unsigned long timestamp;
  void* data;
};

void enqueueEvent(EventType type);
void processEvents();
void registerEventHandler(EventType type, EventHandler handler);
```

**Output yang Diharapkan:**
```
Event enqueued: 0
Event enqueued: 3
Dispatching event: 0
Button pressed - Toggling LED
LED toggled to: ON
```

**Learning Points:**
- Event-driven architecture
- Event queue
- Event handlers
- Loose coupling

---

### 04-error-handling — Error Handling

**Konsep:** Mempelajari cara menangani kondisi error dengan baik.

**Komponen:**
- 1x LED (GPIO 2)
- 1x Push Button (GPIO 4)

**Pinout:**
| Komponen | GPIO | Fungsi |
|----------|------|--------|
| LED | 2 | Output |
| Button | 4 | Input |

**Error Codes:**
```
ERR_NONE = 0
ERR_MEMORY_ALLOCATION
ERR_TIMEOUT
ERR_INVALID_STATE
ERR_HARDWARE_FAILURE
ERR_COMMUNICATION
```

**Cara Kerja:**
1. Detect error conditions
2. Throw/catch exceptions
3. Handle error dengan visual indication
4. Attempt recovery
5. Log error information

**Kode Penting:**
```cpp
try {
  initializeSystem();
} catch (const std::exception& e) {
  handleError(ERR_HARDWARE_FAILURE, e.what());
}

void handleError(ErrorCode code, const char* message) {
  // Log error
  // Visual indication (blink LED)
  // Attempt recovery
}
```

**Output yang Diharapkan:**
```
=== ERROR OCCURRED ===
Error Code: 4
Message: Button pressed during initialization
Timestamp: 12345
Error Count: 1
======================
```

**Learning Points:**
- Error detection
- Exception handling
- Error recovery
- Error logging
- User notification

---

## ✅ Checklist Pemahaman

- [ ] Saya bisa membuat state machine
- [ ] Saya bisa membuat modular program
- [ ] Saya bisa membuat event-driven program
- [ ] Saya bisa menangani error dengan baik
- [ ] Saya bisa mengelola konfigurasi

---

## 🔗 Navigasi

- [⬅ Kembali ke Home](../README.md)
- [➡ Lanjut ke Optimization](../07-optimization/README.md)
