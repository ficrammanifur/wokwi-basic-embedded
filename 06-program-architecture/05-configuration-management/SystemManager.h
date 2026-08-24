#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <Arduino.h>
#include "Config.h"
#include "LoggerModule.h"
#include "LedModule.h"

// System States
enum class SystemState {
  INITIALIZING = 0,
  IDLE = 1,
  RUNNING = 2,
  ERROR = 3,
  SHUTDOWN = 4
};

class SystemManager {
private:
  static SystemState currentState;
  static unsigned long stateStartTime;
  static int errorCount;
  static unsigned long lastUpdateTime;
  
  static const char* stateToString(SystemState state) {
    switch (state) {
      case SystemState::INITIALIZING: return "INITIALIZING";
      case SystemState::IDLE: return "IDLE";
      case SystemState::RUNNING: return "RUNNING";
      case SystemState::ERROR: return "ERROR";
      case SystemState::SHUTDOWN: return "SHUTDOWN";
      default: return "UNKNOWN";
    }
  }
  
public:
  static void init() {
    currentState = SystemState::INITIALIZING;
    stateStartTime = millis();
    errorCount = 0;
    lastUpdateTime = 0;
    
    LoggerModule::info("System Manager initialized");
    LoggerModule::info(Config::getConfigString().c_str());
    
    // Show startup animation
    for (int i = 0; i < 3; i++) {
      LedModule::setState(true);
      delay(100);
      LedModule::setState(false);
      delay(100);
    }
    
    setState(SystemState::IDLE);
  }
  
  static void update() {
    unsigned long now = millis();
    
    if (now - lastUpdateTime < Config::SYSTEM_UPDATE_INTERVAL) {
      return;
    }
    lastUpdateTime = now;
    
    switch (currentState) {
      case SystemState::INITIALIZING:
        updateInitializing();
        break;
      case SystemState::IDLE:
        updateIdle();
        break;
      case SystemState::RUNNING:
        updateRunning();
        break;
      case SystemState::ERROR:
        updateError();
        break;
      case SystemState::SHUTDOWN:
        updateShutdown();
        break;
    }
  }
  
  static SystemState getState() {
    return currentState;
  }
  
  static const char* getStateString() {
    return stateToString(currentState);
  }
  
private:
  static void setState(SystemState newState) {
    if (currentState == newState) return;
    
    String msg = "State change: " + String(stateToString(currentState)) + 
                 " → " + String(stateToString(newState));
    LoggerModule::info(msg.c_str());
    
    currentState = newState;
    stateStartTime = millis();
    
    switch (newState) {
      case SystemState::RUNNING:
        LedModule::enableBlink(Config::LED_BLINK_INTERVAL);
        LoggerModule::info("System is RUNNING");
        break;
      case SystemState::ERROR:
        handleErrorEntry();
        break;
      default:
        break;
    }
  }
  
  static void updateInitializing() {
    if (millis() - stateStartTime > 2000) {
      setState(SystemState::IDLE);
    }
  }
  
  static void updateIdle() {
    LoggerModule::debug("System IDLE - waiting for trigger");
    
    if (millis() - stateStartTime > 5000) {
      setState(SystemState::RUNNING);
    }
  }
  
  static void updateRunning() {
    if (errorCount >= Config::MAX_ERROR_COUNT) {
      setState(SystemState::ERROR);
    }
  }
  
  static void updateError() {
    if (millis() - stateStartTime > Config::WATCHDOG_INTERVAL) {
      if (Config::AUTO_RECOVERY) {
        LoggerModule::warn("Attempting auto-recovery...");
        errorCount = 0;
        setState(SystemState::IDLE);
      }
    }
  }
  
  static void updateShutdown() {
    if (millis() - stateStartTime > 2000) {
      LoggerModule::info("System shutdown complete");
    }
  }
  
  static void handleErrorEntry() {
    for (int i = 0; i < 5; i++) {
      LedModule::setState(true);
      delay(100);
      LedModule::setState(false);
      delay(100);
    }
    
    LoggerModule::error("System entered ERROR state!");
    LoggerModule::error(("Error count: " + String(errorCount)).c_str());
  }
};

// Static member definitions
SystemState SystemManager::currentState = SystemState::INITIALIZING;
unsigned long SystemManager::stateStartTime = 0;
int SystemManager::errorCount = 0;
unsigned long SystemManager::lastUpdateTime = 0;

#endif
