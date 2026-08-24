#ifndef LOGGER_MODULE_H
#define LOGGER_MODULE_H

#include <Arduino.h>
#include "Config.h"

// Log Levels
enum class LogLevel {
  ERROR = 0,
  WARN = 1,
  INFO = 2,
  DEBUG = 3
};

class LoggerModule {
private:
  static bool enabled;
  static int logLevel;
  
  static const char* getLevelString(LogLevel level) {
    switch (level) {
      case LogLevel::ERROR: return "[ERROR]";
      case LogLevel::WARN:  return "[WARN] ";
      case LogLevel::INFO:  return "[INFO] ";
      case LogLevel::DEBUG: return "[DEBUG]";
      default: return "[UNKNOWN]";
    }
  }
  
public:
  static void init(int level = 2) {
    enabled = true;
    logLevel = level;
    Serial.begin(115200);
  }
  
  static void setEnabled(bool e) {
    enabled = e;
  }
  
  static void setLogLevel(int level) {
    logLevel = level;
  }
  
  static void log(LogLevel level, const char* message) {
    if (!enabled) return;
    if (static_cast<int>(level) > logLevel) return;
    
    Serial.print(millis());
    Serial.print("ms ");
    Serial.print(getLevelString(level));
    Serial.print(": ");
    Serial.println(message);
  }
  
  static void log(LogLevel level, String message) {
    log(level, message.c_str());
  }
  
  static void error(const char* message) {
    log(LogLevel::ERROR, message);
  }
  
  static void warn(const char* message) {
    log(LogLevel::WARN, message);
  }
  
  static void info(const char* message) {
    log(LogLevel::INFO, message);
  }
  
  static void debug(const char* message) {
    log(LogLevel::DEBUG, message);
  }
};

// Static member definitions
bool LoggerModule::enabled = true;
int LoggerModule::logLevel = 2;

#endif
