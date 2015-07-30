// Timer Example - A non-blocking clock that counts seconds
// Copyright 2015 Alex Taujenis
// MIT License

#include <Timer.h>
#define BAUD 11500
Timer timer;
unsigned long count = 0;

void setup() {
  Serial.begin(BAUD);
  timer.setTimeout(1000);
}

void loop() {
  if(timer.isInactive()) {
    timer.restart();
    Serial.println(count++);
  }
}
