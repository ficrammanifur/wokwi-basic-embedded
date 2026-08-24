/*
 * Configuration Management - Configuration Management
 * 
 * Konsep: Memisahkan konfigurasi dari program utama
 * 
 * Komponen:
 * - LED (D2)
 * - Button (D4)
 * 
 * Pinout:
 * - LED   -> GPIO 2
 * - Button -> GPIO 4
 */

#include "Config.h"
#include "LoggerModule.h"
#include "LedModule.h"
#include "ButtonModule.h"  // ← PASTIKAN INI ADA!
#include "SystemManager.h"

void setup() {
  // Initialize modules
  LoggerModule::init(Config::LOG_LEVEL);
  
  LoggerModule::log(LogLevel::INFO, "=== System Starting ===");
  LoggerModule::log(LogLevel::INFO, "Firmware Version: " + String(Config::FIRMWARE_VERSION));
  LoggerModule::log(LogLevel::DEBUG, "Debug mode: " + String(Config::DEBUG_MODE ? "ON" : "OFF"));
  
  // Initialize hardware
  LedModule::init(Config::LED_PIN);
  ButtonModule::init(Config::BUTTON_PIN);  // ← PASTIKAN INI!
  
  // Initialize system manager
  SystemManager::init();
  
  LoggerModule::log(LogLevel::INFO, "System initialized successfully");
}

void loop() {
  // Update modules
  ButtonModule::update();  // ← PASTIKAN INI!
  SystemManager::update();
  LedModule::update();
  
  delay(10);
}
