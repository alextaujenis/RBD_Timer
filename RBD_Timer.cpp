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

  bool Timer::isActive() {
    return _timeout > getValue() && _active;
  }

  bool Timer::isExpired() {
    return _timeout <= getValue() || !_active;
  }

  bool Timer::onRestart() {
    if(isActive()) {
      return false;
    }
    else {
      restart();
      return true;
    }
  }

  bool Timer::onActive() {
    if(isActive()) {
      if(!_has_been_active) {
        _has_been_active = true;
        return true;
      }
      return false;
    }
    else {
      _has_been_active = false;
      return false;
    }
  }

  bool Timer::onExpired() {
    if(isExpired()) {
      if(!_has_been_expired) {
        _has_been_expired = true;
        return true;
      }
      return false;
    }
    else {
      _has_been_expired = false;
      return false;
    }
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