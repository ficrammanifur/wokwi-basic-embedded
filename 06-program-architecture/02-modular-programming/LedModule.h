#ifndef LED_MODULE_H
#define LED_MODULE_H

#include <Arduino.h>

class LedModule {
private:
  static int pin;
  static bool state;
  
public:
  static void init(int p) {
    pin = p;
    state = false;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  
  static void setState(bool s) {
    state = s;
    digitalWrite(pin, state ? HIGH : LOW);
  }
  
  static bool getState() {
    return state;
  }
  
  static void toggle() {
    state = !state;
    digitalWrite(pin, state ? HIGH : LOW);
  }
};

int LedModule::pin = 0;
bool LedModule::state = false;

#endif
