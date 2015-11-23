// Arduino RBD Timer Library v1.1.0 - Unit test coverage.
// https://github.com/alextaujenis/RBD_Timer
// Copyright 2015 Alex Taujenis
// MIT License

#include <ArduinoUnit.h> // https://github.com/mmurdoch/arduinounit
#include <RBD_Timer.h>   // https://github.com/alextaujenis/RBD_Timer

RBD::Timer timer;

// constructor
  test(constructor_should_begin_expired) {
    assertTrue(timer.isExpired());
    assertFalse(timer.isActive());
  }

// setTimeout
  test(setTimeout_should_set_the_timeout_in_milliseconds) {
    timer.setTimeout(100);
    timer.restart();

    assertEqual(timer.getInverseValue(), 100);
  }

// setHertz
  test(setHertz_should_set_the_refresh_rate_per_second) {
    timer.setHertz(10);
    timer.restart();

    assertEqual(timer.getInverseValue(), 100);
  }

// restart
  test(restart_should_make_it_active) {
    timer.setTimeout(1);
    timer.restart();

    assertTrue(timer.isActive());
    assertFalse(timer.isExpired());
  }

// isActive
  test(isActive_should_return_true_if_time_is_available) {
    timer.setTimeout(1);
    timer.restart();

    assertTrue(timer.isActive());
  }

  test(isActive_should_return_false_if_time_has_run_out) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertFalse(timer.isActive());
  }

  test(isActive_should_remain_false_on_timer_rollover) {
    timer.setTimeout(1);
    timer.restart();

    delay(1);
    assertFalse(timer.isActive());

    timer.setTimeout(5); // make it active again without calling restart: almost like timer rollover

    assertFalse(timer.isActive());
  }

// isExpired
  test(isExpired_should_return_false_if_time_is_available) {
    timer.setTimeout(1);
    timer.restart();

    assertFalse(timer.isExpired());
  }

  test(isExpired_should_return_true_if_time_has_run_out) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertTrue(timer.isExpired());
  }

  test(isExpired_should_remain_true_on_timer_rollover) {
    timer.setTimeout(1);
    timer.restart();

    delay(1);
    assertTrue(timer.isExpired());

    timer.setTimeout(5); // make it active again without calling restart: almost like timer rollover

    assertTrue(timer.isExpired());
  }

// isStopped
  test(isStopped_should_return_true_if_stopped) {
    timer.setTimeout(1);
    timer.restart();
    timer.stop();

    assertTrue(timer.isStopped());
  }

  test(isStopped_should_return_false_if_active) {
    timer.setTimeout(1);
    timer.restart();

    assertTrue(timer.isActive());
    assertFalse(timer.isStopped());
  }

  test(isStopped_should_return_false_if_expired) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertTrue(timer.isExpired());
    assertFalse(timer.isStopped());
  }

// onRestart
  test(onRestart_should_return_true_if_the_timer_expires) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertTrue(timer.onRestart());
  }

  test(onRestart_should_return_false_the_second_time_after_the_timer_expires) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);
    timer.onRestart();

    assertFalse(timer.onRestart());
  }

// onActive
  test(onActive_should_return_false_if_the_timer_has_not_been_restarted) {
    timer.setTimeout(1);
    assertFalse(timer.onActive());
  }

  test(onActive_should_return_true_after_the_timer_is_restarted) {
    timer.setTimeout(1);
    timer.restart();

    assertTrue(timer.onActive());
  }

  test(onActive_should_return_false_the_second_time_after_the_timer_is_restarted) {
    timer.setTimeout(1);
    timer.restart();
    timer.onActive();

    assertFalse(timer.onActive());
  }

  test(onActive_should_return_false_on_timer_rollover) {
    timer.setTimeout(1);
    timer.restart();

    assertTrue(timer.onActive());
    assertFalse(timer.onActive());

    timer.setTimeout(5); // make it active again without calling restart: almost like timer rollover

    assertFalse(timer.onActive());
  }

// onExpired
  test(onExpired_should_return_true_after_the_timer_expires) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertTrue(timer.onExpired());
  }

  test(onExpired_should_return_false_the_second_time_after_the_timer_is_restarted) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertTrue(timer.onExpired());
    assertFalse(timer.onExpired());
  }

  test(onExpired_should_return_false_on_timer_rollover) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    assertTrue(timer.onExpired());
    assertFalse(timer.onExpired());

    timer.setTimeout(5); // make it active again without calling restart, then wait for it to expire: almost like timer rollover
    delay(5);

    assertFalse(timer.onExpired());
  }

// stop
  test(isActive_and_onActive_should_return_false_after_stop) {
    timer.setTimeout(1);
    timer.restart();
    timer.stop();

    assertFalse(timer.isActive());
    assertFalse(timer.onActive());
  }

  test(isExpired_and_onExpired_should_return_false_after_stop) {
    timer.setTimeout(1);
    timer.restart();
    timer.stop();
    delay(1);

    assertFalse(timer.isExpired());
    assertFalse(timer.onExpired());
  }

  test(onRestart_should_return_false_after_stop) {
    timer.setTimeout(1);
    timer.restart();
    timer.stop();
    delay(1);

    assertFalse(timer.onRestart());
  }

// getValue
  test(getValue_should_return_the_time_passed_since_restart) {
    timer.setTimeout(2);
    timer.restart();
    delay(2);

    assertEqual(timer.getValue(), 2);
  }

// getInverseValue
  test(getInverseValue_should_return_the_time_left_until_timeout) {
    timer.setTimeout(5);
    timer.restart();
    delay(2);

    assertEqual(timer.getInverseValue(), 3);
  }

// getPercentValue
  test(getPercentValue_should_return_the_percentage_of_time_passed) {
    timer.setTimeout(5);
    timer.restart();
    delay(2);

    assertEqual(timer.getPercentValue(), 40);
  }

// getInversePercentValue
  test(getInversePercentValue_should_return_the_percentage_of_time_remaining) {
    timer.setTimeout(5);
    timer.restart();
    delay(2);

    assertEqual(timer.getInversePercentValue(), 60);
  }


void setup() {
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  Test::run();
}
