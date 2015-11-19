#include <ArduinoUnit.h>
#include <RBD_Timer.h>

RBD::Timer timer;

// describe constructor
  test(constructor_should_begin_expired) {
    assertTrue(timer.isExpired());
    assertFalse(timer.isActive());
  }

// describe setTimeout
  test(setTimeout_should_set_the_timeout_in_milliseconds) {
    timer.setTimeout(100);
    timer.restart();

    assertEqual(timer.getInverseValue(), 100);
  }

// describe setHertz
  test(setHertz_should_set_the_refresh_rate_per_second) {
    timer.setHertz(10);
    timer.restart();

    assertEqual(timer.getInverseValue(), 100);
  }

// describe restart
  test(restart_should_make_it_active) {
    timer.setTimeout(1);
    timer.restart();

    assertTrue(timer.isActive());
    assertFalse(timer.isExpired());
  }

// describe isActive
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

// onRestart
  testing(onRestart_should_return_true_if_the_timer_expires) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    if(timer.onRestart() == true) {
      pass();
    }
    else {
      fail();
    }
  }

  testing(onRestart_should_return_false_the_second_time_after_the_timer_expires) {
    timer.setTimeout(1);
    timer.restart();
    delay(1);

    timer.onRestart();

    if(timer.onRestart() == false) {
      pass();
    }
    else {
      fail();
    }
  }

// onActive
  test(onActive_should_return_false_if_the_timer_has_not_been_restarted) {
    timer.setTimeout(1);
    assertFalse(timer.onActive());
  }

  testing(onActive_should_return_true_after_the_timer_is_restarted) {
    timer.setTimeout(1);
    timer.restart();

    if(timer.onActive() == true) {
      pass();
    }
    else {
      fail();
    }
  }

  testing(onActive_should_return_false_the_second_time_after_the_timer_is_restarted) {
    timer.setTimeout(1);
    timer.restart();
    timer.onActive();

    if(timer.onActive() == false) {
      pass();
    }
    else {
      fail();
    }
  }

// onExpired
  test(onExpired_should_return_false_if_the_timer_has_not_been_restarted) {
    timer.setTimeout(1);
    assertFalse(timer.onExpired());
  }

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

    timer.onExpired();
    assertFalse(timer.onExpired());
  }

// getValue
  test(getValue_should_return_the_time_passed_since_restart) {
    timer.setTimeout(2);
    timer.restart();
    delay(2);

    assertEqual(timer.getValue(), 2);
  }

// getInversValue
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