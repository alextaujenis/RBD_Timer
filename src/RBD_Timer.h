// Arduino RBD Timer Library v1.1.0 - Manage many timed events.
// https://github.com/alextaujenis/RBD_Timer
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef RBD_TIMER_H
#define RBD_TIMER_H

#include "Arduino.h"

namespace RBD {
  class Timer {
    public:
      void setTimeout(unsigned long value); // set/change how long until the timer expires in milliseconds
      void setHertz(int value);             // set/change how many times the timer can be restarted in one second
      void restart();                       // reset and start the timer
      void stop();                          // stop the timer
      bool isActive();                      // check if time is left
      bool isExpired();                     // returns true if time has run out
      bool isStopped();                     // returns true if the timer is stopped
      bool onRestart();                     // returns true if the timer is expired and restarts the timer automatically
      bool onActive();                      // returns true once the timer is active, then waits for it to expire and go active again
      bool onExpired();                     // returns true once the timer is expired, then waits for it to go active and expire again
      unsigned long getValue();             // how many milliseconds that have passed since the start of the timer
      unsigned long getInverseValue();      // how many milliseconds the timer has until finished
      int getPercentValue();                // how much time has passed as a percentage of the interval
      int getInversePercentValue();         // how much time is left as a percentage of the interval
    private:
      unsigned long _timeout;               // how long this timer should run for
      unsigned long _waypoint;              // the point in time the timer was started or reset
      bool _has_been_active  = false;       // helps fire the onActive event only once
      bool _has_been_expired = false;       // helps fire the onExpired event only once
      enum {ACTIVE, EXPIRED, STOPPED} _state = EXPIRED;  // timer internal state
      void _updateState();                  // update state according to current state and current value
  };
}

#endif