# Arduino Timer Library
Never write delay() or millis() again! This is a high-level foundation for managing many concurrent timed events. This library also handles Arduino timer rollover correctly.


##Why?
The Arduino real-time loop stops advancing when you write delay() in your sketch. You can keep the real-time loop moving by using millis() to track time and create delay, but it's more complicated and soon becomes messy to manage. The Timer class is a very simple replacement for all your millis() math.

##Relative vs. Absolute Time
This library works well with relative time instead of absolute. Absolute timing (for example) of running on an **interval of precisely 5 minutes** would incure a **few microseconds of time loss** each cycle. You can get a _pretty close_ interval by restarting the timer immediately if you don't mind losing one second every few hundred timeout cycles.

This library is **better suited for managing immediate program flow** over relative time, (for example) like starting a timer and using the reported percentage to dim an LED **over the course of 1 second**. It will not lose any time during the active cycle. You should use this timer really hard while it's active, then consider it dead and restart it to use it again.

#Example Setup
0. Install this library and load the example sketch on to an Arduino
0. Open a serial connection at 115200 BAUD
0. Watch two independent timers report their status

##[example.ino](https://github.com/alextaujenis/Timer/blob/master/example/example.ino)

    #include <Timer.h>

    #define BAUD 115200
    bool rising = true;

    Timer timer1;
    Timer timer2;

    void setup() {
      Serial.begin(BAUD);
      timer1.setTimeout(3000);
      timer2.setTimeout(1000);
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



#Documentation

##Public Methods
* [constructor()](https://github.com/alextaujenis/Timer#constructor)
* [setTimeout(unsigned long)](https://github.com/alextaujenis/Timer#settimeoutunsigned-long)
* [restart()](https://github.com/alextaujenis/Timer#restart)
* [isActive()](https://github.com/alextaujenis/Timer#isactive)
* [isExpired()](https://github.com/alextaujenis/Timer#isexpired)
* [getValue()](https://github.com/alextaujenis/Timer#getvalue)
* [getInverseValue()](https://github.com/alextaujenis/Timer#getinversevalue)
* [getPercentValue()](https://github.com/alextaujenis/Timer#getpercentvalue)
* [getInversePercentValue()](https://github.com/alextaujenis/Timer#getinversepercentvalue)

##constructor()
Create a new timer instance.

    Timer timer;

##setTimeout(value)
Provide an unsigned long value to change how long the timer will run (in milliseconds). This can be done inside of setup() or called at runtime to change the value on the fly.

    timer.setTimeout(5000);

##restart()
There are no start() or stop() methods. All you need to do is restart() the timer when you want to use it.

    timer.restart();

##isActive()
Returns true if time is available.

    timer.isActive();

##isExpired()
Returns true if time has run out.

    timer.isExpired();

##getValue()
Returns an unsigned long of how many milliseconds that have passed since the start of the timer.

    timer.getValue();

##getInverseValue()
Returns an unsigned long of how many milliseconds left until the end of the timer.

    timer.getInverseValue();

##getPercentValue()
Returns an integer from 0 - 100 of how much time has passed as a percentage of the total interval. If the interval is 2000ms, and 500ms have passed: this method will return 25.

    timer.getPercentValue();

##getInversePercentValue()
Returns an integer from 100 - 0 of the inverse of how much time has passed as a percentage of the total interval. If the interval is 2000ms, and 500ms have passed: this method will return 75.

    timer.getInversePercentValue();

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).