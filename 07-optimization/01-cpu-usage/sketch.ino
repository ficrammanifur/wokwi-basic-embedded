/*
 * CPU Usage - CPU Usage Monitoring
 * 
 * Konsep: Memantau penggunaan CPU
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

#include <esp_task.h>

const int LED_PIN = 2;

// CPU usage monitoring
typedef struct {
  float cpu_usage;
  unsigned long total_time;
  unsigned long idle_time;
} cpu_stats_t;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("CPU Usage Monitoring Demo Started");
  
  // Create tasks with different CPU loads
  xTaskCreate(
    heavyTask,
    "Heavy Task",
    4096,
    NULL,
    1,
    NULL
  );
  
  xTaskCreate(
    lightTask,
    "Light Task",
    2048,
    NULL,
    1,
    NULL
  );
  
  Serial.println("Tasks created");
}

void loop() {
  // Monitor CPU usage
  monitorCPUUsage();
  
  delay(2000);
}

void heavyTask(void* parameter) {
  while (1) {
    // Heavy computation
    volatile int result = 0;
    for (int i = 0; i < 10000; i++) {
      result += i * i;
    }
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void lightTask(void* parameter) {
  while (1) {
    // Light work
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void monitorCPUUsage() {
  // Get task statistics
  TaskStatus_t* taskStatusArray;
  UBaseType_t taskCount = uxTaskGetNumberOfTasks();
  
  taskStatusArray = (TaskStatus_t*)malloc(taskCount * sizeof(TaskStatus_t));
  
  if (taskStatusArray != NULL) {
    // Get task states
    UBaseType_t arraySize = uxTaskGetSystemState(taskStatusArray, taskCount, NULL);
    
    unsigned long totalCPU = 0;
    
    Serial.println("\n=== CPU Usage Report ===");
    Serial.println("Task Name\t\tCPU Usage\tState");
    
    for (int i = 0; i < arraySize; i++) {
      TaskStatus_t task = taskStatusArray[i];
      
      // Calculate CPU usage
      float cpuUsage = (float)task.ulRunTimeCounter / configTICK_RATE_HZ * 100;
      totalCPU += cpuUsage;
      
      // Print task info
      Serial.print(task.pcTaskName);
      Serial.print("\t\t");
      Serial.print(cpuUsage, 1);
      Serial.print("%\t\t");
      Serial.println(task.eCurrentState);
    }
    
    // Show idle task usage
    float idleCPU = 100.0 - totalCPU;
    if (idleCPU < 0) idleCPU = 0;
    
    Serial.println("------------------------");
    Serial.print("Idle CPU: ");
    Serial.print(idleCPU, 1);
    Serial.println("%");
    
    free(taskStatusArray);
  }
}
