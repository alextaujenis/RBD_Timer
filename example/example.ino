// Arduino RBD Timer Example - Three second interval timer printing to serial output.
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h>

RBD::Timer timer;

void setup() {
  Serial.begin(115200);
  timer.setTimeout(3000);
  timer.restart();
}

void loop() {
  if(timer.onRestart()) {
    Serial.println("Three seconds passed");
  }
}