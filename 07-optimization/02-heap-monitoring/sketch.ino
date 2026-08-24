/*
 * Heap Monitoring - Heap Monitoring
 * 
 * Konsep: Memantau penggunaan heap
 * 
 * Komponen:
 * - Tidak ada komponen fisik
 * 
 * Pinout:
 * - Tidak ada pin
 */

#include <esp_heap_caps.h>

#define MONITOR_INTERVAL 5000
#define WARNING_THRESHOLD 80  // 80% heap usage

unsigned long lastMonitor = 0;

void setup() {
  Serial.begin(115200);
  
  Serial.println("Heap Monitoring Demo Started");
  
  // Allocate memory to simulate heap usage
  allocateTestMemory();
}

void loop() {
  // Monitor heap periodically
  if (millis() - lastMonitor > MONITOR_INTERVAL) {
    lastMonitor = millis();
    monitorHeap();
  }
  
  delay(100);
}

void monitorHeap() {
  // Get heap information
  size_t totalHeap = ESP.getHeapSize();
  size_t freeHeap = ESP.getFreeHeap();
  size_t minFreeHeap = ESP.getMinFreeHeap();
  size_t usedHeap = totalHeap - freeHeap;
  size_t largestFreeBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  
  float heapUsage = (float)usedHeap / totalHeap * 100;
  
  Serial.println("\n=== Heap Monitoring ===");
  Serial.printf("Total Heap: %zu KB\n", totalHeap / 1024);
  Serial.printf("Free Heap: %zu KB\n", freeHeap / 1024);
  Serial.printf("Used Heap: %zu KB\n", usedHeap / 1024);
  Serial.printf("Heap Usage: %.1f%%\n", heapUsage);
  Serial.printf("Largest Free Block: %zu KB\n", largestFreeBlock / 1024);
  Serial.printf("Minimum Free Heap: %zu KB\n", minFreeHeap / 1024);
  
  // Check for memory issues
  if (heapUsage > WARNING_THRESHOLD) {
    Serial.println("WARNING: Heap usage exceeds threshold!");
  }
  
  if (largestFreeBlock < 1024) {
    Serial.println("WARNING: Memory fragmentation detected!");
  }
  
  // Show allocation details
  showAllocationDetails();
}

void showAllocationDetails() {
  // Get heap info for different capabilities
  size_t total_8bit = heap_caps_get_total_size(MALLOC_CAP_8BIT);
  size_t free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  size_t total_32bit = heap_caps_get_total_size(MALLOC_CAP_32BIT);
  size_t free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);
  
  Serial.println("\n--- Allocation Details ---");
  Serial.printf("8-bit Capable: %zu KB total, %zu KB free\n", 
                total_8bit / 1024, free_8bit / 1024);
  Serial.printf("32-bit Capable: %zu KB total, %zu KB free\n", 
                total_32bit / 1024, free_32bit / 1024);
}

void allocateTestMemory() {
  Serial.println("Allocating test memory...");
  
  // Allocate memory in chunks
  void* ptrs[5];
  size_t sizes[] = {1024, 2048, 4096, 8192, 16384};
  
  for (int i = 0; i < 5; i++) {
    ptrs[i] = malloc(sizes[i]);
    if (ptrs[i] != NULL) {
      Serial.printf("Allocated %zu bytes (chunk %d)\n", sizes[i], i+1);
      // Fill with data
      memset(ptrs[i], 0xFF, sizes[i]);
    } else {
      Serial.printf("Failed to allocate %zu bytes (chunk %d)\n", sizes[i], i+1);
    }
  }
  
  // Free in reverse order
  for (int i = 4; i >= 0; i--) {
    if (ptrs[i] != NULL) {
      free(ptrs[i]);
      Serial.printf("Freed chunk %d\n", i+1);
    }
  }
}
