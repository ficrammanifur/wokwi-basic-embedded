#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#include <Arduino.h>

class TimerModule {
private:
  struct Timer {
    unsigned long interval;
    unsigned long lastTrigger;
    void (*callback)();
    bool active;
  };
  
  static const int MAX_TIMERS = 5;
  static Timer timers[MAX_TIMERS];
  static int timerCount;
  
public:
  static void init() {
    timerCount = 0;
    for (int i = 0; i < MAX_TIMERS; i++) {
      timers[i].active = false;
    }
  }
  
  static bool setInterval(unsigned long interval, void (*callback)()) {
    if (timerCount >= MAX_TIMERS) {
      return false;
    }
    
    timers[timerCount].interval = interval;
    timers[timerCount].lastTrigger = millis();
    timers[timerCount].callback = callback;
    timers[timerCount].active = true;
    timerCount++;
    
    return true;
  }
  
  static void update() {
    unsigned long currentTime = millis();
    
    for (int i = 0; i < timerCount; i++) {
      if (timers[i].active) {
        if (currentTime - timers[i].lastTrigger >= timers[i].interval) {
          timers[i].lastTrigger = currentTime;
          if (timers[i].callback != NULL) {
            timers[i].callback();
          }
        }
      }
    }
  }
};

// Static member definitions
TimerModule::Timer TimerModule::timers[MAX_TIMERS];
int TimerModule::timerCount = 0;

#endif
