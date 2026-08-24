/*
 * Config.h - Centralized Configuration
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ============================================
// 1. PIN CONFIGURATION
// ============================================

namespace Config {
  // Hardware Pins
  const int LED_PIN = 2;
  const int BUTTON_PIN = 4;
  const int BUZZER_PIN = 5;
  
  // I2C Pins
  const int I2C_SDA = 21;
  const int I2C_SCL = 22;
}

// ============================================
// 2. SYSTEM CONFIGURATION
// ============================================

namespace Config {
  const char* FIRMWARE_VERSION = "1.0.0";
  const bool DEBUG_MODE = true;
  const int LOG_LEVEL = 3;
  const char* SYSTEM_NAME = "ESP32-Embedded-System";
}

// ============================================
// 3. TIMING CONFIGURATION
// ============================================

namespace Config {
  const unsigned long LED_BLINK_INTERVAL = 1000;
  const unsigned long LED_PWM_FREQ = 5000;
  const int LED_PWM_RESOLUTION = 8;
  const unsigned long BUTTON_DEBOUNCE_DELAY = 50;
  const unsigned long BUTTON_LONG_PRESS_DELAY = 1000;
  const unsigned long WATCHDOG_INTERVAL = 5000;
  const unsigned long SYSTEM_UPDATE_INTERVAL = 100;
}

// ============================================
// 4. FEATURE FLAGS
// ============================================

namespace Config {
  const bool ENABLE_WIFI = true;
  const bool ENABLE_MQTT = true;
  const bool ENABLE_DEEP_SLEEP = false;
  const bool ENABLE_OTA = true;
  const bool AUTO_RECOVERY = true;
  const int MAX_ERROR_COUNT = 5;
}

// ============================================
// 5. WIFI CONFIGURATION
// ============================================

namespace Config {
  const char* WIFI_SSID = "Wokwi-GUEST";
  const char* WIFI_PASSWORD = "";
  const int WIFI_TIMEOUT = 30000;
  const int WIFI_RETRY_COUNT = 3;
  const int WIFI_RETRY_DELAY = 5000;
}

// ============================================
// 6. MQTT CONFIGURATION
// ============================================

namespace Config {
  const char* MQTT_BROKER = "broker.mqttdashboard.com";
  const int MQTT_PORT = 1883;
  const char* MQTT_CLIENT_ID = "ESP32Client";
  const char* MQTT_TOPIC_SENSOR = "esp32/sensor";
  const char* MQTT_TOPIC_CONTROL = "esp32/control";
  const char* MQTT_TOPIC_STATUS = "esp32/status";
  const int MQTT_QOS = 1;
  const bool MQTT_RETAIN = false;
}

// ============================================
// 7. BEHAVIOR CONFIGURATION
// ============================================

namespace Config {
  const bool LED_INVERT_LOGIC = false;
  const int LED_DEFAULT_BRIGHTNESS = 128;
  const bool BUTTON_PULLUP = true;
  const int BUTTON_ACTIVE_STATE = LOW;
  const bool STARTUP_LED_BLINK = true;
  const int STARTUP_BLINK_COUNT = 3;
  const int STARTUP_BLINK_DELAY = 200;
}

// ============================================
// 8. HELPER FUNCTIONS
// ============================================

namespace Config {
  inline String getConfigString() {
    String config = "\n=== SYSTEM CONFIGURATION ===\n";
    config += "Version: " + String(FIRMWARE_VERSION) + "\n";
    config += "System: " + String(SYSTEM_NAME) + "\n";
    config += "Debug: " + String(DEBUG_MODE ? "ON" : "OFF") + "\n";
    config += "Log Level: " + String(LOG_LEVEL) + "\n";
    config += "WiFi: " + String(ENABLE_WIFI ? "Enabled" : "Disabled") + "\n";
    config += "MQTT: " + String(ENABLE_MQTT ? "Enabled" : "Disabled") + "\n";
    config += "===========================";
    return config;
  }
  
  inline const char* getStateString(int state) {
    switch (state) {
      case 0: return "INITIALIZING";
      case 1: return "IDLE";
      case 2: return "RUNNING";
      case 3: return "ERROR";
      case 4: return "SHUTDOWN";
      default: return "UNKNOWN";
    }
  }
}

#endif
