/*
 * Memory Optimization - Memory Optimization
 * 
 * Konsep: Mengurangi penggunaan memory
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

#include <pgmspace.h>

const int LED_PIN = 2;

// Constant strings stored in flash memory (PROGMEM)
const char message1[] PROGMEM = "This string is stored in flash memory";
const char message2[] PROGMEM = "Another flash string";
const char* const flashMessages[] PROGMEM = {
  "Message 1 from flash",
  "Message 2 from flash",
  "Message 3 from flash"
};

// Using smaller data types
typedef struct {
  uint8_t ledState : 1;    // Bit field - uses 1 bit
  uint8_t errorFlag : 1;
  uint8_t reserved : 6;
} StatusFlags;

// Using int instead of long when possible
int smallCounter = 0;
// Use uint8_t for small values
uint8_t byteCounter = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Memory Optimization Demo Started");
  
  printMemoryInfo();
  demonstrateFlashUsage();
  demonstrateBitFields();
  
  Serial.println("Press button to demonstrate optimization");
}

void loop() {
  static unsigned long lastPrint = 0;
  
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    printMemoryInfo();
  }
  
  demonstrateOptimization();
  delay(100);
}

void printMemoryInfo() {
  Serial.println("\n=== Memory Info ===");
  Serial.printf("Free Heap: %u KB\n", ESP.getFreeHeap() / 1024);
  Serial.printf("Total Heap: %u KB\n", ESP.getHeapSize() / 1024);
}

void demonstrateFlashUsage() {
  Serial.println("\n=== Flash (PROGMEM) Usage ===");
  
  // Read strings from flash
  char buffer[40];
  
  strcpy_P(buffer, message1);
  Serial.println(buffer);
  
  strcpy_P(buffer, message2);
  Serial.println(buffer);
  
  // Read array from flash
  for (int i = 0; i < 3; i++) {
    const char* msg = (const char*)pgm_read_ptr(&flashMessages[i]);
    Serial.println(msg);
  }
}

void demonstrateBitFields() {
  Serial.println("\n=== Bit Fields Example ===");
  
  StatusFlags flags = {0, 0, 0};
  
  flags.ledState = 1;
  flags.errorFlag = 0;
  
  Serial.printf("StatusFlags size: %u bytes\n", sizeof(StatusFlags));
  Serial.printf("LED State: %d, Error Flag: %d\n", flags.ledState, flags.errorFlag);
}

void demonstrateOptimization() {
  // Use smaller data types
  smallCounter++;
  byteCounter++;
  
  if (byteCounter > 100) {
    byteCounter = 0;
  }
  
  // Use efficient string operations
  char temp[20];
  snprintf(temp, sizeof(temp), "Counter: %d", smallCounter);
  
  // Only print every 100 iterations
  if (smallCounter % 100 == 0) {
    Serial.println(temp);
    
    // Toggle LED efficiently
    static bool state = false;
    state = !state;
    digitalWrite(LED_PIN, state ? HIGH : LOW);
  }
}
