/*
 * Event-Driven - Event-Driven Programming
 * 
 * Konsep: Program berdasarkan event
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

// Event types
enum EventType {
  EVENT_BUTTON_PRESSED,
  EVENT_BUTTON_RELEASED,
  EVENT_TIMER_TICK,
  EVENT_LED_TOGGLE,
  EVENT_LED_ON,
  EVENT_LED_OFF
};

// Event structure
struct Event {
  EventType type;
  unsigned long timestamp;
  void* data;
};

// Event queue
const int MAX_EVENTS = 10;
Event eventQueue[MAX_EVENTS];
int eventCount = 0;

// Event handlers
typedef void (*EventHandler)(const Event& event);
EventHandler buttonPressHandler = NULL;
EventHandler timerTickHandler = NULL;

unsigned long lastTick = 0;
const unsigned long TICK_INTERVAL = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  Serial.println("Event-Driven Demo Started");
  
  // Register event handlers
  registerEventHandler(EVENT_BUTTON_PRESSED, onButtonPressed);
  registerEventHandler(EVENT_TIMER_TICK, onTimerTick);
  
  Serial.println("Event handlers registered");
}

void loop() {
  // Generate events
  generateEvents();
  
  // Process events
  processEvents();
  
  delay(10);
}

void generateEvents() {
  // Check button
  static int lastButtonState = HIGH;
  int buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      enqueueEvent(EVENT_BUTTON_PRESSED);
    } else {
      enqueueEvent(EVENT_BUTTON_RELEASED);
    }
    lastButtonState = buttonState;
  }
  
  // Check timer
  if (millis() - lastTick >= TICK_INTERVAL) {
    lastTick = millis();
    enqueueEvent(EVENT_TIMER_TICK);
  }
}

void enqueueEvent(EventType type) {
  if (eventCount < MAX_EVENTS) {
    eventQueue[eventCount].type = type;
    eventQueue[eventCount].timestamp = millis();
    eventQueue[eventCount].data = NULL;
    eventCount++;
    
    Serial.print("Event enqueued: ");
    Serial.println(type);
  } else {
    Serial.println("Event queue full!");
  }
}

void processEvents() {
  // Process all events in queue
  while (eventCount > 0) {
    Event event = eventQueue[0];
    
    // Shift remaining events
    for (int i = 0; i < eventCount - 1; i++) {
      eventQueue[i] = eventQueue[i + 1];
    }
    eventCount--;
    
    // Dispatch event
    dispatchEvent(event);
  }
}

void dispatchEvent(const Event& event) {
  Serial.print("Dispatching event: ");
  Serial.println(event.type);
  
  switch (event.type) {
    case EVENT_BUTTON_PRESSED:
      if (buttonPressHandler != NULL) {
        buttonPressHandler(event);
      }
      break;
      
    case EVENT_TIMER_TICK:
      if (timerTickHandler != NULL) {
        timerTickHandler(event);
      }
      break;
      
    case EVENT_LED_TOGGLE:
      toggleLED();
      break;
      
    case EVENT_LED_ON:
      digitalWrite(LED_PIN, HIGH);
      break;
      
    case EVENT_LED_OFF:
      digitalWrite(LED_PIN, LOW);
      break;
      
    default:
      Serial.println("Unknown event");
      break;
  }
}

void registerEventHandler(EventType type, EventHandler handler) {
  switch (type) {
    case EVENT_BUTTON_PRESSED:
      buttonPressHandler = handler;
      break;
    case EVENT_TIMER_TICK:
      timerTickHandler = handler;
      break;
    default:
      Serial.println("Cannot register handler for this event");
      break;
  }
}

void onButtonPressed(const Event& event) {
  Serial.println("Button pressed - Toggling LED");
  enqueueEvent(EVENT_LED_TOGGLE);
}

void onTimerTick(const Event& event) {
  Serial.println("Timer tick");
  // Do periodic tasks here
}

void toggleLED() {
  static bool state = false;
  state = !state;
  digitalWrite(LED_PIN, state ? HIGH : LOW);
  Serial.print("LED toggled to: ");
  Serial.println(state ? "ON" : "OFF");
}
