// Arduino Timer - An encapsulation of timing with non-blocking millis and no delay
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class Timer {
  public:
    void setTimeout(unsigned long value); // set/change how long the timer will run
    void restart();                       // reset and start the timer
    bool isActive();                      // check if time is left
    bool isExpired();                     // check if the time has run out
    unsigned long getValue();             // how many milliseconds that have passed since the start of the timer
    unsigned long getInverseValue();      // how many milliseconds the timer has until finished
    int getPercentValue();                // how much time has passed as a percentage of the interval
    int getInversePercentValue();         // how much time is left as a percentage of the interval
  private:
    unsigned long _timeout;   // how long this timer should run for
    unsigned long _waypoint;  // the point in time the timer was started or reset
};

#endif