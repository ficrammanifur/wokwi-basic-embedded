#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <Arduino.h>
#include "Config.h"
#include "LoggerModule.h"

class LedModule {
private:
  static int pin;
  static bool state;
  static int brightness;
  static unsigned long lastToggle;
  static bool blinkEnabled;
  static unsigned long blinkInterval;
  
public:
  static void init(int p) {
    pin = p;
    state = false;
    brightness = Config::LED_DEFAULT_BRIGHTNESS;
    blinkEnabled = false;
    blinkInterval = Config::LED_BLINK_INTERVAL;
    lastToggle = 0;
    
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    
    // Startup blink
    if (Config::STARTUP_LED_BLINK) {
      for (int i = 0; i < Config::STARTUP_BLINK_COUNT; i++) {
        digitalWrite(pin, HIGH);
        delay(Config::STARTUP_BLINK_DELAY);
        digitalWrite(pin, LOW);
        delay(Config::STARTUP_BLINK_DELAY);
      }
    }
  }
  
  static void setState(bool s) {
    state = s;
    bool output = Config::LED_INVERT_LOGIC ? !state : state;
    digitalWrite(pin, output ? HIGH : LOW);
  }
  
  static void toggle() {
    setState(!state);
  }
  
  static void setBrightness(int value) {
    brightness = constrain(value, 0, 255);
  }
  
  static void enableBlink(unsigned long interval = 0) {
    blinkEnabled = true;
    if (interval > 0) {
      blinkInterval = interval;
    }
    lastToggle = millis();
  }
  
  static void disableBlink() {
    blinkEnabled = false;
    setState(false);
  }
  
  static void update() {
    if (!blinkEnabled) return;
    
    unsigned long now = millis();
    if (now - lastToggle >= blinkInterval) {
      lastToggle = now;
      toggle();
      
      if (Config::DEBUG_MODE) {
        String msg = "LED toggled: " + String(state ? "ON" : "OFF");
        LoggerModule::debug(msg.c_str());
      }
    }
  }
  
  static bool getState() {
    return state;
  }
  
  static int getBrightness() {
    return brightness;
  }
};

// Static member definitions
int LedModule::pin = 0;
bool LedModule::state = false;
int LedModule::brightness = 128;
unsigned long LedModule::lastToggle = 0;
bool LedModule::blinkEnabled = false;
unsigned long LedModule::blinkInterval = 1000;

#endif
