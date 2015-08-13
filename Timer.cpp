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
  return _timeout > getRelativeValue();
}

bool Timer::isExpired() {
  return _timeout <= getRelativeValue();
}

unsigned long Timer::getRelativeValue() {
  return millis() - _waypoint;
}

float Timer::getPercentValue() {
  return getRelativeValue() / float(_timeout);
}

float Timer::getInversePercentValue() {
  return 1 - getPercentValue();
}