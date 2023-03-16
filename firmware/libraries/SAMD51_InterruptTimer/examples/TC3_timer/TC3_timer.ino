#include <Arduino.h>
#include "SAMD51_InterruptTimer.h"

#define Ser Serial

volatile bool toggle = true;
volatile bool updated = false;
volatile uint32_t dT = 0;
void myISR() {
  uint32_t now = micros();
  static uint32_t prev_tick = now;
  
  dT = now - prev_tick;
  prev_tick = now;
  updated = true;

  digitalWrite(PIN_LED, toggle);
  toggle = not(toggle);
}

void setup() {
  Ser.begin(9600);
  
  pinMode(PIN_LED, OUTPUT);

  TC.startTimer(100000, myISR); // 100000 usec
}

void loop() {
  //*
  if (updated) {
    Ser.println(dT);
    
    noInterrupts();
    updated = false;
    interrupts();
  }
  //*/
}