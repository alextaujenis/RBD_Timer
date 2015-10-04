// Arduino RBD Timer - An encapsulation of timing with non-blocking millis and no delay
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Timer.h>

namespace RBD {
  void Timer::setTimeout(unsigned long value) {
    _timeout = value;
  }

  void Timer::setHertz(int value) {
    if(value > 0 && value < 1001) {
      _timeout = (unsigned long)(1000 / value);
    }
  }

  void Timer::restart() {
    _waypoint = millis();
    _active   = true;
  }

  bool Timer::onRestart() {
    if(isExpired()) {
      restart();
      return true;
    }
    else {
      return false;
    }
  }

  bool Timer::isActive() {
    return _timeout > getValue() && _active;
  }

  bool Timer::isExpired() {
    return _timeout <= getValue() || !_active;
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
}