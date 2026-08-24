/*
 * Memory Management - Memory Management
 * 
 * Konsep: Pengelolaan RAM dan heap
 * 
 * Komponen:
 * - Tidak ada komponen fisik
 * 
 * Pinout:
 * - Tidak ada pin
 */

#include <esp_heap_caps.h>

void setup() {
  Serial.begin(115200);
  
  Serial.println("Memory Management Demo Started");
  
  // Get heap information
  printMemoryInfo();
  
  // Allocate memory example
  allocateMemory();
  
  // Show fragmentation
  printFragmentation();
}

void loop() {
  // Monitor memory usage
  static unsigned long lastPrint = 0;
  
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    printMemoryInfo();
  }
  
  delay(1000);
}

void printMemoryInfo() {
  Serial.println("\n=== Memory Information ===");
  
  // Total heap
  size_t totalHeap = ESP.getHeapSize();
  Serial.print("Total Heap: ");
  Serial.print(totalHeap / 1024);
  Serial.println(" KB");
  
  // Free heap
  size_t freeHeap = ESP.getFreeHeap();
  Serial.print("Free Heap: ");
  Serial.print(freeHeap / 1024);
  Serial.println(" KB");
  
  // Minimum free heap
  size_t minFreeHeap = ESP.getMinFreeHeap();
  Serial.print("Min Free Heap: ");
  Serial.print(minFreeHeap / 1024);
  Serial.println(" KB");
  
  // Heap used by all tasks
  size_t usedHeap = totalHeap - freeHeap;
  Serial.print("Used Heap: ");
  Serial.print(usedHeap / 1024);
  Serial.println(" KB");
  
  // Free heap percentage
  Serial.print("Heap Usage: ");
  Serial.print((usedHeap * 100) / totalHeap);
  Serial.println("%");
  
  // PSRAM (if available)
  if (psramFound()) {
    size_t totalPSRAM = ESP.getPsramSize();
    size_t freePSRAM = ESP.getFreePsram();
    Serial.print("Total PSRAM: ");
    Serial.print(totalPSRAM / 1024);
    Serial.println(" KB");
    Serial.print("Free PSRAM: ");
    Serial.print(freePSRAM / 1024);
    Serial.println(" KB");
  }
}

void allocateMemory() {
  Serial.println("\n=== Memory Allocation Example ===");
  
  // Allocate 1KB
  void* ptr = malloc(1024);
  
  if (ptr != NULL) {
    Serial.println("Allocated 1KB successfully");
    
    // Fill with data
    memset(ptr, 0, 1024);
    
    // Free memory
    free(ptr);
    Serial.println("Memory freed");
  } else {
    Serial.println("Failed to allocate memory");
  }
}

void printFragmentation() {
  heap_caps_get_info(NULL, MALLOC_CAP_8BIT);
  
  // Get largest free block
  size_t largestFreeBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  size_t totalFree = heap_caps_get_free_size(MALLOC_CAP_8BIT);
  
  Serial.println("\n=== Memory Fragmentation ===");
  Serial.print("Largest Free Block: ");
  Serial.print(largestFreeBlock / 1024);
  Serial.println(" KB");
  
  if (totalFree > 0) {
    int fragmentation = (1 - (float)largestFreeBlock / totalFree) * 100;
    Serial.print("Fragmentation: ");
    Serial.print(fragmentation);
    Serial.println("%");
  }
}
