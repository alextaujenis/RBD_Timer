// Arduino RBD Timer Library v1.1.0 - Manage many timed events.
// https://github.com/alextaujenis/RBD_Timer
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer

namespace RBD {
  void Timer::setTimeout(unsigned long value) {
    _timeout = (value > 0) ? value : 1;
  }

  void Timer::setHertz(int value) {
    if(value > 0 && value < 1001) {
      _timeout = (unsigned long)(1000 / value);
    }
  }

  void Timer::restart() {
    _waypoint         = millis();
    _state            = ACTIVE;
    _has_been_active  = false;
    _has_been_expired = false;
  }

  void Timer::stop() {
    _state = STOPPED;
  }

  bool Timer::isActive() {
    _updateState();
    return _state == ACTIVE;
  }

  bool Timer::isExpired() {
    _updateState();
    return _state == EXPIRED;
  }

  bool Timer::isStopped() {
    return _state == STOPPED;
  }

  bool Timer::onRestart() {
    if(isExpired()) {
      restart();
      return true;
    }
    return false;
  }

  bool Timer::onActive() {
    if(!_has_been_active && isActive()) {
      return _has_been_active = true;
    }
    return false;
  }

  bool Timer::onExpired() {
    if(!_has_been_expired && isExpired()) {
      return _has_been_expired = true;
    }
    return false;
  }

  unsigned long Timer::getValue() {
    return millis() - _waypoint;
  }

  unsigned long Timer::getInverseValue() {
    return _timeout - getValue();
  }

  int Timer::getPercentValue() {
    return getValue() / float(_timeout) * 100;
  }

  int Timer::getInversePercentValue() {
    return 100 - getPercentValue();
  }


  // private

  void Timer::_updateState() {
    if(_state == ACTIVE && getValue() >= _timeout) {
      _state = EXPIRED;
    }
  }
}