// Timer.h - An encapsulation of timing with non-blocking millis and no delay

#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class Timer {
  public:
    Timer();
    void setTimeout(unsigned long value); // set/change how long the timer will run
    void restart();                       // reset and start the timer
    void stop();                          // stop the timer
    bool isActive();                      // check if it's running with time left
    bool isInactive();                    // check if the time has run out or stopped
    unsigned long getRelativeValue();     // how many milliseconds that have passed since the start of the timer
    float getPercentValue();              // how much time has passed as a percentage of the interval
  private:
    unsigned long _timeout;   // how long this timer should run for
    unsigned long _waypoint;  // the point in time the timer was started or reset
    bool _active;             // if the timer should currently be active
};

#endif