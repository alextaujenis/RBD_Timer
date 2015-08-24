// Arduino Timer - An encapsulation of timing with non-blocking millis and no delay
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <Timer.h>

void Timer::setTimeout(unsigned long value) {
  _timeout = value;
}

void Timer::restart() {
  _waypoint = millis();
}

bool Timer::isActive() {
  return _timeout > getValue();
}

bool Timer::isExpired() {
  return _timeout <= getValue();
}

unsigned long Timer::getValue() {
  return millis() - _waypoint;
}

unsigned long Timer::getInverseValue() {
  return _timeout - getValue();
}

int Timer::getPercentValue() {
  return int(getValue() / float(_timeout) * 100);
}

int Timer::getInversePercentValue() {
  return 100 - getPercentValue();
}