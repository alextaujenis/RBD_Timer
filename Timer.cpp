#include <Arduino.h>
#include <Timer.h>

Timer::Timer() {
  // no op
}

void Timer::setTimeout(unsigned long value) {
  _timeout = value;
}

void Timer::restart() {
  _waypoint = millis();
  _active   = true;
}

void Timer::stop() {
  _waypoint = 0;
  _active   = false;
}

bool Timer::isActive() {
  return _active && _timeout > getRelativeValue();
}

bool Timer::isInactive() {
  return !_active || _timeout < getRelativeValue();
}
unsigned long Timer::getRelativeValue() {
  return millis() - _waypoint;
}

float Timer::getPercentValue() {
  return getRelativeValue() / float(_timeout);
}