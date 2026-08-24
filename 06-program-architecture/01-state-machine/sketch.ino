/*
 * State Machine - State Machine
 * 
 * Konsep: Mengatur alur program berdasarkan state
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4)
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4
 */

const int LED_PIN = 2;
const int BUTTON_PIN = 4;

// State definitions
enum SystemState {
  STATE_IDLE,
  STATE_STARTUP,
  STATE_RUNNING,
  STATE_ERROR,
  STATE_SHUTDOWN
};

SystemState currentState = STATE_IDLE;
unsigned long stateStartTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("State Machine Demo Started");
  
  // Start in IDLE state
  changeState(STATE_IDLE);
}

void loop() {
  // Update state machine
  switch (currentState) {
    case STATE_IDLE:
      handleIdleState();
      break;
    case STATE_STARTUP:
      handleStartupState();
      break;
    case STATE_RUNNING:
      handleRunningState();
      break;
    case STATE_ERROR:
      handleErrorState();
      break;
    case STATE_SHUTDOWN:
      handleShutdownState();
      break;
  }
  
  delay(50);
}

void changeState(SystemState newState) {
  currentState = newState;
  stateStartTime = millis();
  
  // Entry actions
  switch (newState) {
    case STATE_IDLE:
      Serial.println("State: IDLE - Waiting for button press");
      digitalWrite(LED_PIN, LOW);
      break;
    case STATE_STARTUP:
      Serial.println("State: STARTUP - Initializing system");
      digitalWrite(LED_PIN, HIGH);
      break;
    case STATE_RUNNING:
      Serial.println("State: RUNNING - System operational");
      break;
    case STATE_ERROR:
      Serial.println("State: ERROR - System error occurred");
      break;
    case STATE_SHUTDOWN:
      Serial.println("State: SHUTDOWN - Shutting down");
      digitalWrite(LED_PIN, LOW);
      break;
  }
}

void handleIdleState() {
  // Check for button press to transition
  if (digitalRead(BUTTON_PIN) == LOW) {
    changeState(STATE_STARTUP);
    delay(200); // Debounce
  }
}

void handleStartupState() {
  static int step = 0;
  
  // Simulate startup process
  if (millis() - stateStartTime > 500) {
    step++;
    Serial.print("Startup step ");
    Serial.println(step);
    
    if (step >= 3) {
      // Startup complete, transition to RUNNING
      changeState(STATE_RUNNING);
    }
  }
}

void handleRunningState() {
  // Blink LED to indicate running
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  
  if (millis() - lastBlink > 500) {
    lastBlink = millis();
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.println("System running...");
  }
  
  // Check for error condition (simulate)
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Simulate error on button press while running
    changeState(STATE_ERROR);
    delay(200); // Debounce
  }
}

void handleErrorState() {
  // Flash error pattern
  static unsigned long lastFlash = 0;
  static bool flashState = false;
  
  if (millis() - lastFlash > 200) {
    lastFlash = millis();
    flashState = !flashState;
    digitalWrite(LED_PIN, flashState ? HIGH : LOW);
  }
  
  // Auto-recover after 3 seconds
  if (millis() - stateStartTime > 3000) {
    Serial.println("Error recovered, restarting");
    changeState(STATE_IDLE);
  }
}

void handleShutdownState() {
  // Perform shutdown sequence
  static int step = 0;
  
  if (millis() - stateStartTime > 500) {
    step++;
    Serial.print("Shutdown step ");
    Serial.println(step);
    
    if (step >= 2) {
      Serial.println("Shutdown complete");
      // Reset system (in real system, go to deep sleep)
      changeState(STATE_IDLE);
    }
  }
}
