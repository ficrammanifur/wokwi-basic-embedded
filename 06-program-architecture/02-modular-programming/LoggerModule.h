#ifndef LOGGER_MODULE_H
#define LOGGER_MODULE_H

#include <Arduino.h>

class LoggerModule {
private:
  static bool enabled;
  static int logLevel;
  
public:
  static void init() {
    enabled = true;
    logLevel = 1;
    Serial.begin(115200);
  }
  
  static void setEnabled(bool e) {
    enabled = e;
  }
  
  static void setLogLevel(int level) {
    logLevel = level;
  }
  
  static void log(const char* message) {
    if (enabled) {
      Serial.print("[LOG] ");
      Serial.print(millis());
      Serial.print("ms: ");
      Serial.println(message);
    }
  }
  
  static void log(String message) {
    log(message.c_str());
  }
  
  static void logInfo(const char* message) {
    if (enabled && logLevel <= 1) {
      Serial.print("[INFO] ");
      Serial.println(message);
    }
  }
  
  static void logError(const char* message) {
    if (enabled && logLevel <= 0) {
      Serial.print("[ERROR] ");
      Serial.println(message);
    }
  }
};

bool LoggerModule::enabled = true;
int LoggerModule::logLevel = 1;

#endif
