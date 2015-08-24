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

float Timer::getPercentValue() {
  return getValue() / float(_timeout);
}

float Timer::getInversePercentValue() {
  return 1 - getPercentValue();
}