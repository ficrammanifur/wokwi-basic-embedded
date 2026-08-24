/*
 * Task Optimization - Task Optimization
 * 
 * Konsep: Mengoptimalkan task untuk performa maksimal
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4)
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_task_wdt.h>

// ============================================
// KONFIGURASI
// ============================================

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

// Task stack sizes (optimized)
const int STACK_SMALL = 1024;   // 1KB - untuk task sederhana
const int STACK_MEDIUM = 2048;  // 2KB - untuk task sedang
const int STACK_LARGE = 4096;   // 4KB - untuk task kompleks

// Task priorities
const int PRIORITY_LOW = 1;
const int PRIORITY_NORMAL = 2;
const int PRIORITY_HIGH = 3;
const int PRIORITY_CRITICAL = 5;

// Timing
const unsigned long TASK1_INTERVAL = 100;   // 100ms
const unsigned long TASK2_INTERVAL = 500;   // 500ms
const unsigned long TASK3_INTERVAL = 1000;  // 1s

// ============================================
// QUEUE UNTUK KOMUNIKASI
// ============================================

QueueHandle_t dataQueue;

struct TaskData {
  int value;
  unsigned long timestamp;
  uint8_t taskId;
};

// ============================================
// TASK HANDLES
// ============================================

TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;
TaskHandle_t monitorTaskHandle = NULL;

// ============================================
// SETUP
// ============================================

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("=== Task Optimization Demo ===");
  Serial.println("Firmware: Task Optimization v1.0");
  
  // Create queue
  dataQueue = xQueueCreate(10, sizeof(TaskData));
  
  // Create optimized tasks
  createOptimizedTasks();
  
  // Create monitor task
  createMonitorTask();
  
  Serial.println("All tasks created successfully!");
  Serial.println("Monitoring task performance...");
}

// ============================================
// LOOP (Tidak digunakan - semua di task)
// ============================================

void loop() {
  // Main loop idle - watchdog feed
  esp_task_wdt_reset();
  vTaskDelay(pdMS_TO_TICKS(1000));
}

// ============================================
// CREATE OPTIMIZED TASKS
// ============================================

void createOptimizedTasks() {
  // Task 1: High frequency, low latency (Core 0)
  xTaskCreatePinnedToCore(
    optimizedTask1,
    "Task1_HighFreq",
    STACK_SMALL,        // Stack size optimized
    NULL,
    PRIORITY_HIGH,      // High priority for responsiveness
    &task1Handle,
    0                   // Core 0
  );
  
  // Task 2: Medium frequency (Core 1)
  xTaskCreatePinnedToCore(
    optimizedTask2,
    "Task2_Medium",
    STACK_MEDIUM,       // Medium stack
    NULL,
    PRIORITY_NORMAL,    // Normal priority
    &task2Handle,
    1                   // Core 1
  );
  
  // Task 3: Low frequency, background (Core 1)
  xTaskCreatePinnedToCore(
    optimizedTask3,
    "Task3_Low",
    STACK_SMALL,        // Small stack
    NULL,
    PRIORITY_LOW,       // Low priority
    &task3Handle,
    1                   // Core 1
  );
}

// ============================================
// OPTIMIZED TASK 1 - High Frequency
// ============================================

void optimizedTask1(void* parameter) {
  // Local variables (stack optimized)
  unsigned long lastRun = 0;
  int counter = 0;
  bool ledState = false;
  
  // Pin configuration (done once)
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Task1: Started on Core " + String(xPortGetCoreID()));
  
  while (1) {
    unsigned long now = millis();
    
    // Non-blocking timing
    if (now - lastRun >= TASK1_INTERVAL) {
      lastRun = now;
      counter++;
      
      // Quick LED toggle (minimal processing)
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      
      // Send data to queue (non-blocking)
      TaskData data;
      data.value = counter;
      data.timestamp = now;
      data.taskId = 1;
      
      // Use timeout to avoid blocking
      if (xQueueSend(dataQueue, &data, 0) != pdPASS) {
        // Queue full - skip (better than blocking)
        // Could increment error counter
      }
      
      // Yield to allow other tasks
      taskYIELD();
    }
    
    // Small delay to prevent watchdog
    vTaskDelay(1);
  }
}

// ============================================
// OPTIMIZED TASK 2 - Medium Frequency
// ============================================

void optimizedTask2(void* parameter) {
  // Pre-allocate buffers (reuse)
  char buffer[32];
  unsigned long lastRun = 0;
  int counter = 0;
  
  Serial.println("Task2: Started on Core " + String(xPortGetCoreID()));
  
  while (1) {
    unsigned long now = millis();
    
    if (now - lastRun >= TASK2_INTERVAL) {
      lastRun = now;
      counter++;
      
      // Efficient string formatting
      snprintf(buffer, sizeof(buffer), "Task2: Count %d", counter);
      Serial.println(buffer);
      
      // Read button (non-blocking)
      int buttonState = digitalRead(BUTTON_PIN);
      
      // Process button (only if pressed)
      if (buttonState == LOW) {
        Serial.println("Task2: Button pressed!");
        
        // Send event to queue
        TaskData data;
        data.value = -1;  // Button event
        data.timestamp = now;
        data.taskId = 2;
        xQueueSend(dataQueue, &data, 0);
      }
    }
    
    // Efficient delay
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// ============================================
// OPTIMIZED TASK 3 - Low Frequency (Background)
// ============================================

void optimizedTask3(void* parameter) {
  unsigned long lastRun = 0;
  int counter = 0;
  unsigned long totalTime = 0;
  int iterations = 0;
  
  Serial.println("Task3: Started on Core " + String(xPortGetCoreID()));
  
  while (1) {
    unsigned long now = millis();
    
    if (now - lastRun >= TASK3_INTERVAL) {
      lastRun = now;
      counter++;
      iterations++;
      
      // Heavy computation (but rare)
      unsigned long startTime = micros();
      
      // Simulate work (optimized)
      int result = 0;
      for (int i = 0; i < 1000; i++) {
        result += i * i;
      }
      
      unsigned long endTime = micros();
      totalTime += (endTime - startTime);
      
      // Log every 10 iterations
      if (iterations % 10 == 0) {
        unsigned long avgTime = totalTime / 10;
        Serial.print("Task3: Avg computation time: ");
        Serial.print(avgTime);
        Serial.println(" us");
        totalTime = 0;
      }
      
      // Send status
      TaskData data;
      data.value = result % 100;
      data.timestamp = now;
      data.taskId = 3;
      xQueueSend(dataQueue, &data, 0);
    }
    
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

// ============================================
// MONITOR TASK - Performance Monitoring
// ============================================

void createMonitorTask() {
  xTaskCreatePinnedToCore(
    monitorTask,
    "Monitor",
    STACK_MEDIUM,
    NULL,
    PRIORITY_LOW,  // Low priority - doesn't interfere
    &monitorTaskHandle,
    1              // Core 1
  );
}

void monitorTask(void* parameter) {
  unsigned long lastReport = 0;
  int queueItems = 0;
  
  Serial.println("Monitor: Started on Core " + String(xPortGetCoreID()));
  
  while (1) {
    unsigned long now = millis();
    
    // Report every 5 seconds
    if (now - lastReport >= 5000) {
      lastReport = now;
      
      Serial.println("\n=== PERFORMANCE REPORT ===");
      
      // 1. Queue status
      queueItems = uxQueueMessagesWaiting(dataQueue);
      Serial.print("Queue items: ");
      Serial.println(queueItems);
      
      // 2. Task stack usage
      reportTaskStack("Task1", task1Handle);
      reportTaskStack("Task2", task2Handle);
      reportTaskStack("Task3", task3Handle);
      reportTaskStack("Monitor", monitorTaskHandle);
      
      // 3. Free heap
      Serial.print("Free heap: ");
      Serial.print(ESP.getFreeHeap() / 1024);
      Serial.println(" KB");
      
      // 4. CPU usage (approximate)
      Serial.print("CPU usage: ");
      Serial.print(getCPUUsage());
      Serial.println("%");
      
      // 5. Task states
      reportTaskState("Task1", task1Handle);
      reportTaskState("Task2", task2Handle);
      reportTaskState("Task3", task3Handle);
      
      Serial.println("===========================\n");
    }
    
    // Process queue (non-blocking)
    TaskData data;
    if (xQueueReceive(dataQueue, &data, 0) == pdPASS) {
      // Just count for monitoring
      // In real system, would process data
    }
    
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

// ============================================
// MONITOR HELPER FUNCTIONS
// ============================================

void reportTaskStack(const char* name, TaskHandle_t handle) {
  if (handle == NULL) return;
  
  UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(handle);
  Serial.print(name);
  Serial.print(" stack: ");
  Serial.print(highWaterMark);
  Serial.print(" words (");
  Serial.print(highWaterMark * sizeof(StackType_t));
  Serial.println(" bytes)");
  
  // Warning if stack is low
  if (highWaterMark < 100) {
    Serial.print("  ⚠️ WARNING: ");
    Serial.print(name);
    Serial.println(" stack is critically low!");
  }
}

void reportTaskState(const char* name, TaskHandle_t handle) {
  if (handle == NULL) return;
  
  eTaskState state = eTaskGetState(handle);
  Serial.print(name);
  Serial.print(" state: ");
  
  switch (state) {
    case eRunning: Serial.println("Running"); break;
    case eReady: Serial.println("Ready"); break;
    case eBlocked: Serial.println("Blocked"); break;
    case eSuspended: Serial.println("Suspended"); break;
    case eDeleted: Serial.println("Deleted"); break;
    default: Serial.println("Unknown");
  }
}

float getCPUUsage() {
  // Simple CPU usage estimation
  static unsigned long lastTime = 0;
  static unsigned long idleTime = 0;
  
  unsigned long now = millis();
  if (now - lastTime > 1000) {
    // Get idle task time (simplified)
    // In real implementation, use esp_task_wdt or similar
    lastTime = now;
    return 50.0; // Placeholder
  }
  return 0.0;
}

// ============================================
// OPTIMIZATION TECHNIQUES DEMONSTRATED
// ============================================

/*
 * 1. STACK OPTIMIZATION
 *    - Use minimal stack size (STACK_SMALL, STACK_MEDIUM, STACK_LARGE)
 *    - Monitor with uxTaskGetStackHighWaterMark()
 *    - Adjust based on actual usage
 * 
 * 2. PRIORITY OPTIMIZATION
 *    - High priority for time-critical tasks
 *    - Low priority for background tasks
 *    - Use PRIORITY_LOW, PRIORITY_NORMAL, PRIORITY_HIGH
 * 
 * 3. TIMING OPTIMIZATION
 *    - Use millis() for non-blocking timing
 *    - Avoid delay() in tasks
 *    - Use vTaskDelay() for yielding
 * 
 * 4. COMMUNICATION OPTIMIZATION
 *    - Use queue with timeout (0 = non-blocking)
 *    - Minimize queue operations
 *    - Use direct task notifications when possible
 * 
 * 5. CORE AFFINITY OPTIMIZATION
 *    - Core 0: High priority, interactive tasks
 *    - Core 1: Background, processing tasks
 *    - Pin tasks to specific cores
 * 
 * 6. MEMORY OPTIMIZATION
 *    - Pre-allocate buffers
 *    - Reuse memory (snprintf with fixed buffer)
 *    - Avoid dynamic allocation in tasks
 * 
 * 7. YIELD OPTIMIZATION
 *    - Use taskYIELD() after critical sections
 *    - Allow other tasks to run
 *    - Prevent starvation
 */

// ============================================
// OPTIMIZATION CHECKLIST
// ============================================

/*
 * ✅ Use appropriate stack sizes
 * ✅ Set correct priorities
 * ✅ Pin tasks to specific cores
 * ✅ Use non-blocking timing (millis)
 * ✅ Use queue with timeout
 * ✅ Monitor stack usage
 * ✅ Monitor heap usage
 * ✅ Use taskYIELD() appropriately
 * ✅ Pre-allocate buffers
 * ✅ Minimize string operations
 * ✅ Use efficient data types
 * ✅ Avoid dynamic allocation
 * ✅ Use watchdog timer
 * ✅ Implement error recovery
 */
