#pragma once

#include <Arduino.h>

class Relay {
 public:
  Relay(int pin) : pin_(pin) {}

  void Init() {
    pinMode(pin_, OUTPUT);
    this->TurnOff();
  }

  void TurnOn() { digitalWrite(pin_, LOW); }

  void TurnOff() { digitalWrite(pin_, HIGH); }

 private:
  int pin_;
};
