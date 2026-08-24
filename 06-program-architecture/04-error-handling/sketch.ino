/*
 * Error Handling - Error Handling
 * 
 * Konsep: Menangani kondisi error dengan baik
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4)
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4
 */

#include <exception>

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

// Error codes
enum ErrorCode {
  ERR_NONE = 0,
  ERR_MEMORY_ALLOCATION,
  ERR_TIMEOUT,
  ERR_INVALID_STATE,
  ERR_HARDWARE_FAILURE,
  ERR_COMMUNICATION
};

// Error structure
struct SystemError {
  ErrorCode code;
  const char* message;
  unsigned long timestamp;
};

SystemError lastError = {ERR_NONE, "No error", 0};
int errorCount = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Error Handling Demo Started");
  
  try {
    // Initialize system
    initializeSystem();
  } catch (const std::exception& e) {
    handleError(ERR_HARDWARE_FAILURE, e.what());
  }
}

void loop() {
  try {
    // Main application logic
    runApplication();
  } catch (const std::exception& e) {
    handleError(ERR_INVALID_STATE, e.what());
  }
  
  // Check for errors
  if (lastError.code != ERR_NONE) {
    handleErrorRecovery();
  }
  
  delay(50);
}

void initializeSystem() {
  Serial.println("Initializing system...");
  
  // Simulate initialization with potential errors
  if (digitalRead(BUTTON_PIN) == LOW) {
    throw std::runtime_error("Button pressed during initialization");
  }
  
  // Simulate memory allocation failure
  // void* ptr = malloc(100000000); // This would fail
  // if (ptr == NULL) {
  //   throw std::bad_alloc();
  // }
  
  Serial.println("System initialized successfully");
}

void runApplication() {
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  
  // Simulate application logic
  if (millis() - lastBlink > 1000) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.println("Application running");
  }
  
  // Simulate error condition
  if (digitalRead(BUTTON_PIN) == LOW) {
    throw std::runtime_error("Button error condition");
  }
}

void handleError(ErrorCode code, const char* message) {
  lastError.code = code;
  lastError.message = message;
  lastError.timestamp = millis();
  errorCount++;
  
  Serial.println("=== ERROR OCCURRED ===");
  Serial.print("Error Code: ");
  Serial.println(code);
  Serial.print("Message: ");
  Serial.println(message);
  Serial.print("Timestamp: ");
  Serial.println(millis());
  Serial.print("Error Count: ");
  Serial.println(errorCount);
  Serial.println("======================");
  
  // Visual error indication
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
}

void handleErrorRecovery() {
  Serial.println("Attempting error recovery...");
  
  // Clear error after handling
  if (millis() - lastError.timestamp > 3000) {
    Serial.println("Error recovered");
    lastError.code = ERR_NONE;
    lastError.message = "No error";
  }
}
