#include <Arduino.h>
#include <arduino-timer.h>

#include "DoorSensor.h"
#include "Relay.h"

enum class DoorState { Open, Closed };

// minutes, seconds, milliseconds
unsigned long const maxOpenTime = 2ul * 60ul * 1000ul;

Timer<> timer;
DoorSensor door(2);
Relay relay(4);
DoorState doorState{DoorState::Closed};

bool CloseDoor(void*) {
  relay.TurnOn();
  delay(250);
  relay.TurnOff();
  return false;
}

void setup() {
  door.Init();
  relay.Init();
  doorState = door.Open() ? DoorState::Open : DoorState::Closed;
}

void loop() {
  timer.tick<void>();

  switch (doorState) {
    case DoorState::Open: {
      if (!door.Open()) {
        timer.cancel();
        doorState = DoorState::Closed;
      }
      break;
    }
    case DoorState::Closed: {
      if (door.Open()) {
        timer.in(maxOpenTime, CloseDoor);
        doorState = DoorState::Open;
      }
      break;
    }
  }
}
