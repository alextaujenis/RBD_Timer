// Arduino Timer Example - Two independent timers reporting operational status to the serial port
// Copyright 2015 Alex Taujenis
// MIT License

#include <Timer.h>

#define BAUD 115200
bool rising = true;

Timer timer1;
Timer timer2;

void setup() {
  Serial.begin(BAUD);
  timer1.setTimeout(3000);
  timer2.setHertz(1);
  timer1.restart();
  timer2.restart();
}

void loop() {
  updateTimer1();
  updateTimer2();
}

void updateTimer1() {
  if(timer1.isExpired()) {
    timer1.restart();
    Serial.println("THREE SECONDS PASSED");
  }
}

void updateTimer2() {
  if(timer2.isActive()) {
    if(rising) { Serial.println(timer2.getPercentValue()); }
    else { Serial.println(timer2.getInversePercentValue()); }
  }
  else {
    timer2.restart();
    rising = !rising;
  }
}