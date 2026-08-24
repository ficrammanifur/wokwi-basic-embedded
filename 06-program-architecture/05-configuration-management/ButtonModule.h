#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

#include <Arduino.h>
#include "Config.h"
#include "LoggerModule.h"

// Button Events
enum class ButtonEvent {
  NONE,
  PRESSED,
  RELEASED,
  LONG_PRESSED,
  DOUBLE_CLICKED
};

class ButtonModule {
private:
  static int pin;
  static int lastState;
  static int currentState;
  static unsigned long lastDebounceTime;
  static unsigned long pressStartTime;
  static bool isPressed;
  static int clickCount;
  static unsigned long lastClickTime;
  static ButtonEvent lastEvent;
  
public:
  static void init(int p) {
    pin = p;
    lastState = HIGH;
    currentState = HIGH;
    lastDebounceTime = 0;
    pressStartTime = 0;
    isPressed = false;
    clickCount = 0;
    lastClickTime = 0;
    lastEvent = ButtonEvent::NONE;
    
    if (Config::BUTTON_PULLUP) {
      pinMode(pin, INPUT_PULLUP);
    } else {
      pinMode(pin, INPUT);
    }
    
    String msg = "Button initialized on pin " + String(pin);
    LoggerModule::debug(msg.c_str());
  }
  
  static void update() {
    int reading = digitalRead(pin);
    
    // Debounce
    if (reading != lastState) {
      lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > Config::BUTTON_DEBOUNCE_DELAY) {
      if (reading != currentState) {
        currentState = reading;
        
        // Button pressed (active state)
        if (currentState == Config::BUTTON_ACTIVE_STATE) {
          onPressed();
        } 
        // Button released
        else {
          onReleased();
        }
      }
    }
    
    lastState = reading;
    
    // Check for long press
    if (isPressed && (millis() - pressStartTime) > Config::BUTTON_LONG_PRESS_DELAY) {
      isPressed = false;
      lastEvent = ButtonEvent::LONG_PRESSED;
      LoggerModule::debug("Button: Long press detected");
    }
  }
  
  static ButtonEvent getEvent() {
    ButtonEvent event = lastEvent;
    lastEvent = ButtonEvent::NONE;
    return event;
  }
  
  static bool isPressedNow() {
    return currentState == Config::BUTTON_ACTIVE_STATE;
  }
  
private:
  static void onPressed() {
    isPressed = true;
    pressStartTime = millis();
    lastEvent = ButtonEvent::PRESSED;
    LoggerModule::debug("Button: Pressed");
  }
  
  static void onReleased() {
    isPressed = false;
    
    // Check for double click
    if (millis() - lastClickTime < 500) {
      clickCount++;
      if (clickCount >= 2) {
        lastEvent = ButtonEvent::DOUBLE_CLICKED;
        clickCount = 0;
        LoggerModule::debug("Button: Double click detected");
      }
    } else {
      clickCount = 1;
    }
    
    lastClickTime = millis();
    lastEvent = ButtonEvent::RELEASED;
    LoggerModule::debug("Button: Released");
  }
};

// Static member definitions
int ButtonModule::pin = 0;
int ButtonModule::lastState = HIGH;
int ButtonModule::currentState = HIGH;
unsigned long ButtonModule::lastDebounceTime = 0;
unsigned long ButtonModule::pressStartTime = 0;
bool ButtonModule::isPressed = false;
int ButtonModule::clickCount = 0;
unsigned long ButtonModule::lastClickTime = 0;
ButtonEvent ButtonModule::lastEvent = ButtonEvent::NONE;

#endif
