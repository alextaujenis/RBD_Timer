// Arduino Timer Example - A non-blocking clock that counts half seconds with two independent intervals
// Copyright 2015 Alex Taujenis
// MIT License

// include the library
#include <Timer.h>

// connect to the serial port via 11500 baud
#define BAUD 11500

// create two instances of Timer
Timer one_second_timer;
Timer half_second_timer;

// local variables for tracking time
unsigned long count = 0;
bool flip_flop = true;

void setup() {
  Serial.begin(BAUD);
  // set the timeout for both timers; this can also be changed during runtime inside of loop()
  one_second_timer.setTimeout(1000);
  half_second_timer.setTimeout(500);
}

void loop() {
  // run the one second timer in real-time and only take action if it is expired
  if(one_second_timer.isExpired()) {
    // keep timing
    one_second_timer.restart();
    // increment the seconds
    Serial.println(count++);
  }

  // run the half second timer in real-time and only take action if it is expired
  if(half_second_timer.isExpired()) {
    // keep timing
    half_second_timer.restart();

    // only print half-seconds when they are .5
    if(flip_flop) {
      Serial.print(count - 1);
      Serial.print(".");
      Serial.println(5);
    }
    flip_flop = !flip_flop;
  }
}
