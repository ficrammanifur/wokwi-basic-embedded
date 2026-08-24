/*
 * Modular Programming - Modular Programming
 * 
 * Konsep: Memisahkan program menjadi modul-modul
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

// Module includes
#include "LedModule.h"
#include "TimerModule.h"
#include "LoggerModule.h"

void setup() {
  // Initialize modules
  LoggerModule::init();
  LedModule::init(LED_PIN);
  
  LoggerModule::log("System started");
  LoggerModule::log("LED Module initialized");
  
  // Set timer
  TimerModule::setInterval(1000, onTimer);
}

void loop() {
  // Update timer module
  TimerModule::update();
}

// Timer callback
void onTimer() {
  static bool state = false;
  state = !state;
  LedModule::setState(state);
  LoggerModule::log("LED toggled");
}
