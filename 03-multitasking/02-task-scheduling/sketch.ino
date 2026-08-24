/*
 * Task Scheduling - Task Scheduling
 * 
 * Konsep: Mengatur eksekusi task dengan delay dan timing
 * 
 * Komponen:
 * - LED (D2)
 * 
 * Pinout:
 * - LED -> GPIO 2
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

const int LED_PIN = 2;

TimerHandle_t timer1;
TimerHandle_t timer2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Task Scheduling Demo Started");
  
  // Create timer untuk scheduling
  timer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(500), pdTRUE, (void*)0, timer1Callback);
  timer2 = xTimerCreate("Timer2", pdMS_TO_TICKS(1000), pdTRUE, (void*)1, timer2Callback);
  
  // Start timers
  xTimerStart(timer1, 0);
  xTimerStart(timer2, 0);
  
  Serial.println("Timers started!");
}

void timer1Callback(TimerHandle_t xTimer) {
  static bool state = false;
  state = !state;
  digitalWrite(LED_PIN, state ? HIGH : LOW);
  Serial.println("Timer 1: LED toggled");
}

void timer2Callback(TimerHandle_t xTimer) {
  Serial.println("Timer 2: Task scheduled every 1000ms");
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
