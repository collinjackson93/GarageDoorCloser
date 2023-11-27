#pragma once

#include <Arduino.h>

class DoorSensor {
 public:
  DoorSensor(int pin) : pin_(pin) {}

  void Init() { pinMode(pin_, INPUT); }

  bool Open() { return digitalRead(pin_) == HIGH; }

 private:
  int pin_;
};
