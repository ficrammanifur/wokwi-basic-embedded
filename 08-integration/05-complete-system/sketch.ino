/*
 * Integration 05: Complete Embedded System
 * 
 * Konsep: Menggabungkan semua konsep menjadi satu sistem
 * 
 * Komponen:
 * - Potentiometer (GPIO 35) - ADC
 * - Button (GPIO 4) - Interrupt
 * - LED1 (GPIO 2) - PWM
 * - LED2 (GPIO 5) - Output
 * 
 * Fitur:
 * - GPIO, ADC, PWM, Timer, Interrupt
 * - FreeRTOS, Dual Core, Queue, Mutex
 * - WiFi, MQTT
 * - State Machine, Watchdog
 * 
 * Pinout:
 * - Sensor  -> GPIO 35 (ADC)
 * - Button  -> GPIO 4 (Interrupt)
 * - LED1    -> GPIO 2 (PWM)
 * - LED2    -> GPIO 5
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>
#include <esp_task_wdt.h>

// ===== CONFIGURATION =====
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqtt_port = 1883;

// ===== PIN DEFINITIONS =====
const int SENSOR_PIN = 35;
const int BUTTON_PIN = 4;
const int LED1_PIN = 2;  // PWM
const int LED2_PIN = 5;

// ===== PWM CONFIGURATION =====
const int PWM_CHANNEL = 0;
const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 8;

// ===== SYSTEM COMPONENTS =====
// State Machine
enum SystemState {
  STATE_INIT,
  STATE_IDLE,
  STATE_RUNNING,
  STATE_ERROR,
  STATE_SLEEP
};

// Task handles
TaskHandle_t sensorTaskHandle = NULL;
TaskHandle_t controlTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;

// Queue
QueueHandle_t sensorQueue;
QueueHandle_t commandQueue;

// Mutex
SemaphoreHandle_t dataMutex;

// MQTT
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// ===== SHARED DATA =====
struct SensorData {
  int value;
  float voltage;
  int percentage;
  unsigned long timestamp;
};

struct Command {
  String type;
  String payload;
};

SystemState currentState = STATE_INIT;
volatile bool buttonPressed = false;

// ===== INTERRUPT HANDLER =====
void IRAM_ATTR buttonISR() {
  buttonPressed = true;
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED2_PIN, OUTPUT);
  
  // ADC configuration
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  
  // ===== PWM CONFIGURATION (FIXED for ESP32 Core 3.0+) =====
  // Cara baru: ledcAttach(pin, freq, resolution)
  ledcAttach(LED1_PIN, PWM_FREQ, PWM_RESOLUTION);
  
  // Set initial duty cycle to 0
  ledcWrite(LED1_PIN, 0);
  
  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  
  // Initialize components
  initWatchdog();
  initWiFi();
  initMQTT();
  initFreeRTOS();
  
  Serial.println("=== Complete Embedded System Started ===");
  currentState = STATE_IDLE;
}

// ===== WATCHDOG =====
void initWatchdog() {
  // New ESP32 watchdog API requires config struct
  esp_task_wdt_config_t wdt_config = {
    .timeout_ms = 10000,      // 10 seconds
    .idle_core_mask = 0,      // Don't watch idle tasks
    .trigger_panic = true     // Panic on timeout
  };
  esp_task_wdt_init(&wdt_config);
  esp_task_wdt_add(NULL);
  Serial.println("Watchdog initialized");
}

void feedWatchdog() {
  esp_task_wdt_reset();
}

// ===== WiFi =====
void initWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed");
  }
}

// ===== MQTT =====
void initMQTT() {
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(mqttCallback);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("MQTT Received: ");
  Serial.print(topic);
  Serial.print(" -> ");
  Serial.println(message);
  
  // Process command
  if (String(topic) == "esp32/command") {
    if (message == "ON") {
      ledcWrite(LED1_PIN, 255);
    } else if (message == "OFF") {
      ledcWrite(LED1_PIN, 0);
    } else if (message == "TOGGLE") {
      static bool state = false;
      state = !state;
      ledcWrite(LED1_PIN, state ? 255 : 0);
    }
  }
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect("ESP32Complete")) {
      Serial.println("Connected!");
      mqttClient.subscribe("esp32/command");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying...");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  }
}

// ===== FREERTOS =====
void initFreeRTOS() {
  // Create queues
  sensorQueue = xQueueCreate(10, sizeof(SensorData));
  commandQueue = xQueueCreate(5, sizeof(Command));
  
  // Create mutex
  dataMutex = xSemaphoreCreateMutex();
  
  // Create tasks pinned to different cores
  xTaskCreatePinnedToCore(
    sensorTask,
    "Sensor",
    4096,
    NULL,
    3,
    &sensorTaskHandle,
    0  // Core 0
  );
  
  xTaskCreatePinnedToCore(
    controlTask,
    "Control",
    4096,
    NULL,
    2,
    &controlTaskHandle,
    1  // Core 1
  );
  
  xTaskCreatePinnedToCore(
    mqttTask,
    "MQTT",
    4096,
    NULL,
    1,
    &mqttTaskHandle,
    0  // Core 0
  );
  
  Serial.println("FreeRTOS tasks created");
}

// ===== TASK: SENSOR =====
void sensorTask(void* parameter) {
  Serial.print("Sensor Task on Core: ");
  Serial.println(xPortGetCoreID());
  
  SensorData data;
  unsigned long lastRead = 0;
  const unsigned long READ_INTERVAL = 500;
  
  while (1) {
    feedWatchdog();
    
    if (millis() - lastRead >= READ_INTERVAL) {
      lastRead = millis();
      
      // Read sensor
      data.value = analogRead(SENSOR_PIN);
      data.voltage = (data.value / 4095.0) * 3.3;
      data.percentage = map(data.value, 0, 4095, 0, 100);
      data.timestamp = millis();
      
      // Send to queue
      if (xQueueSend(sensorQueue, &data, 0) != pdPASS) {
        Serial.println("Sensor queue full!");
      }
      
      Serial.print("Sensor: ");
      Serial.print(data.value);
      Serial.print(" (");
      Serial.print(data.percentage);
      Serial.println("%)");
    }
    
    // Handle button interrupt
    if (buttonPressed) {
      buttonPressed = false;
      // Toggle LED2
      digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
      Serial.println("Button interrupt: LED2 toggled");
    }
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

// ===== TASK: CONTROL =====
void controlTask(void* parameter) {
  Serial.print("Control Task on Core: ");
  Serial.println(xPortGetCoreID());
  
  SensorData data;
  bool ledState = false;
  unsigned long lastPWMUpdate = 0;
  
  while (1) {
    feedWatchdog();
    
    // Process sensor data
    if (xQueueReceive(sensorQueue, &data, 100 / portTICK_PERIOD_MS) == pdPASS) {
      // Update system state
      updateStateMachine(data);
      
      // Control outputs
      if (currentState == STATE_RUNNING) {
        // PWM control based on sensor
        int pwmValue = map(data.value, 0, 4095, 0, 255);
        ledcWrite(LED1_PIN, pwmValue);
        
        // LED2 indication
        if (data.percentage > 70) {
          digitalWrite(LED2_PIN, HIGH);
        } else {
          digitalWrite(LED2_PIN, LOW);
        }
        
        // Publish to MQTT if connected
        if (mqttClient.connected()) {
          String payload = String(data.value) + "," + 
                           String(data.voltage, 2) + "," + 
                           String(data.percentage);
          mqttClient.publish("esp32/sensor", payload.c_str());
        }
      }
    }
    
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

// ===== STATE MACHINE =====
void updateStateMachine(const SensorData& data) {
  SystemState newState = currentState;
  
  switch (currentState) {
    case STATE_IDLE:
      if (data.percentage > 10) {
        newState = STATE_RUNNING;
        Serial.println("State: IDLE -> RUNNING");
      }
      break;
      
    case STATE_RUNNING:
      if (data.percentage > 95) {
        newState = STATE_ERROR;
        Serial.println("State: RUNNING -> ERROR");
      } else if (data.percentage < 5) {
        newState = STATE_IDLE;
        Serial.println("State: RUNNING -> IDLE");
      }
      break;
      
    case STATE_ERROR:
      if (data.percentage < 50) {
        newState = STATE_RUNNING;
        Serial.println("State: ERROR -> RUNNING");
      }
      break;
      
    default:
      break;
  }
  
  if (newState != currentState) {
    currentState = newState;
    onStateChange();
  }
}

void onStateChange() {
  switch (currentState) {
    case STATE_IDLE:
      ledcWrite(LED1_PIN, 0);
      Serial.println("System IDLE");
      break;
    case STATE_RUNNING:
      Serial.println("System RUNNING");
      break;
    case STATE_ERROR:
      // Blink LED2 to indicate error
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED2_PIN, HIGH);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        digitalWrite(LED2_PIN, LOW);
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
      Serial.println("System ERROR");
      break;
    default:
      break;
  }
}

// ===== TASK: MQTT =====
void mqttTask(void* parameter) {
  Serial.print("MQTT Task on Core: ");
  Serial.println(xPortGetCoreID());
  
  while (1) {
    feedWatchdog();
    
    if (!mqttClient.connected()) {
      connectMQTT();
    }
    mqttClient.loop();
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

// ===== MAIN LOOP =====
void loop() {
  // Feed watchdog
  feedWatchdog();
  
  // Status report
  static unsigned long lastStatus = 0;
  if (millis() - lastStatus > 10000) {
    lastStatus = millis();
    Serial.print("Status: ");
    Serial.print(getStateString());
    Serial.print(" | Heap: ");
    Serial.print(ESP.getFreeHeap() / 1024);
    Serial.println(" KB");
  }
  
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

String getStateString() {
  switch (currentState) {
    case STATE_INIT: return "INIT";
    case STATE_IDLE: return "IDLE";
    case STATE_RUNNING: return "RUNNING";
    case STATE_ERROR: return "ERROR";
    case STATE_SLEEP: return "SLEEP";
    default: return "UNKNOWN";
  }
}
