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
  delay(1000); // beri waktu Serial siap

  Serial.println("Memory Management Demo Started");

  printMemoryInfo();
  allocateMemory();
  printFragmentation();
}

void loop() {
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    printMemoryInfo();
    printFragmentation();
  }

  delay(1000);
}

void printMemoryInfo() {
  Serial.println("\n=== Memory Information ===");

  size_t totalHeap = ESP.getHeapSize();
  size_t freeHeap = ESP.getFreeHeap();
  size_t minFreeHeap = ESP.getMinFreeHeap();
  size_t usedHeap = totalHeap - freeHeap;

  Serial.print("Total Heap: ");
  Serial.print(totalHeap / 1024);
  Serial.println(" KB");

  Serial.print("Free Heap: ");
  Serial.print(freeHeap / 1024);
  Serial.println(" KB");

  Serial.print("Min Free Heap: ");
  Serial.print(minFreeHeap / 1024);
  Serial.println(" KB");

  Serial.print("Used Heap: ");
  Serial.print(usedHeap / 1024);
  Serial.println(" KB");

  if (totalHeap > 0) {
    Serial.print("Heap Usage: ");
    Serial.print((usedHeap * 100) / totalHeap);
    Serial.println("%");
  }

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

  void* ptr = malloc(1024);

  if (ptr != NULL) {
    Serial.println("Allocated 1KB successfully");
    memset(ptr, 0, 1024);
    free(ptr);
    Serial.println("Memory freed");
  } else {
    Serial.println("Failed to allocate memory");
  }
}

void printFragmentation() {
  // FIX: siapkan struct untuk menampung hasil, jangan kirim NULL
  multi_heap_info_t info;
  heap_caps_get_info(&info, MALLOC_CAP_8BIT);

  size_t largestFreeBlock = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
  size_t totalFree = heap_caps_get_free_size(MALLOC_CAP_8BIT);

  Serial.println("\n=== Memory Fragmentation ===");
  Serial.print("Largest Free Block: ");
  Serial.print(largestFreeBlock / 1024);
  Serial.println(" KB");

  Serial.print("Total Free (8BIT cap): ");
  Serial.print(totalFree / 1024);
  Serial.println(" KB");

  Serial.print("Allocated blocks: ");
  Serial.println(info.allocated_blocks);

  Serial.print("Free blocks: ");
  Serial.println(info.free_blocks);

  if (totalFree > 0) {
    int fragmentation = (int)((1.0f - (float)largestFreeBlock / (float)totalFree) * 100);
    Serial.print("Fragmentation: ");
    Serial.print(fragmentation);
    Serial.println("%");
  } else {
    Serial.println("Fragmentation: N/A (totalFree = 0)");
  }
}
