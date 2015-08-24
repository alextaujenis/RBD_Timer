# Arduino Timer Library
Never write delay() or millis() again! This is a high-level foundation for managing many concurrent timed events. This library also handles Arduino timer rollover correctly.


#Why?
The Arduino real-time loop stops advancing when you write delay() in your sketch. You can keep the real-time loop moving by using millis() to track time and create delay, but it's more complicated and soon becomes messy to manage. The Timer class is a very simple replacement for all your millis() math.

#Relative vs. Absolute Time
This library works with relative time instead of absolute. This means there will be a few microseconds of time loss between cycles if you want to run something (for example) precisely every 5 minutes. This library is better suited for managing immediate program flow, (for example) like starting a timer and using the reported percentage to dim an LED over the course of 1 second. You should use this timer really hard while it's active, then consider it dead and restart it to use it again.

#Example Sketch
0. Install this Arduino Library by copying it to your libraries folder
0. Compile and load the [example.ino](https://github.com/alextaujenis/Timer/blob/master/example/example.ino) to the Arduino
0. Open the Serial prompt at 115200 BAUD
0. Watch two independent timers report their status


#Documentation

##Public Methods
* [setTimeout(unsigned long)](https://github.com/alextaujenis/Timer#settimeoutunsigned-long)
* [restart()](https://github.com/alextaujenis/Timer#restart)
* [isActive()](https://github.com/alextaujenis/Timer#isactive)
* [isExpired()](https://github.com/alextaujenis/Timer#isexpired)
* [getValue()](https://github.com/alextaujenis/Timer#getvalue)
* [getInverseValue()](https://github.com/alextaujenis/Timer#getinversevalue)
* [getPercentValue()](https://github.com/alextaujenis/Timer#getpercentvalue)
* [getInversePercentValue()](https://github.com/alextaujenis/Timer#getinversepercentvalue)

##setTimeout(unsigned long)
Change how long the timer will run (in milliseconds). This can be done inside of setup(), and/or called at runtime to change the value on the fly.

    #include <Timer.h>
    Timer timer;

    int timeout = 1000; // ms

    void setup() {
      // set the initial timeout
      timer.setTimeout(timeout);
    }

    void loop() {
      if(timer.isExpired()) {
        // increase timeout size +1ms each iteration
        timer.setTimeout(timeout++);
        // keep running forever
        timer.restart();
      }
    }

##restart()
There are no start() or stop() methods. All you need to do is restart() the timer when you want to use it.

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
    }

    void loop() {
      if(timer.isExpired()) {
        // keep running forever
        timer.restart();
      }
    }

##isActive()
Returns true if time is available.

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
      // timer starts expired; call restart to trigger isActive below
      timer.restart();
    }

    void loop() {
      if(timer.isActive()){
        // called many times during one iteration
        foo.performRealtimeAction();
      }
    }

##isExpired()
Returns true if time has run out.

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
    }

    void loop() {
      if(timer.isExpired()){
        // called once each iteration
        foo.performActionOnce();
        // keep running forever
        timer.restart();
      }
    }

##getValue()
Returns how many milliseconds that have passed since the start of the timer.

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
      // timer starts expired; call restart to trigger isActive below
      timer.restart();
    }

    void loop() {
      if(timer.isActive()) {
        // return number of milliseconds timer has been running
        timer.getValue();
      }
    }

##getInverseValue()
Returns how many milliseconds left until the end of the timer.

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
      // timer starts expired; call restart to trigger isActive below
      timer.restart();
    }

    void loop() {
      if(timer.isActive()) {
        // return number of milliseconds timer has until finished
        timer.getInverseValue();
      }
    }

##getPercentValue()
Returns how much time has passed as a percentage of the total interval. If the interval is 2000ms, and 500ms have passed: this method will return 25

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
      // timer starts expired; call restart to trigger isActive below
      timer.restart();
    }

    void loop() {
      if(timer.isActive()) {
        // return percent of time finished for this iteration
        timer.getPercentValue();
      }
    }

##getInversePercentValue()
Returns the inverse of how much time has passed as a percentage of the total interval. If the interval is 2000ms, and 500ms have passed: this method will return 75

    #include <Timer.h>
    Timer timer;

    void setup() {
      // set the initial timeout
      timer.setTimeout(1000);
      // timer starts expired; call restart to trigger isActive below
      timer.restart();
    }

    void loop() {
      if(timer.isActive()) {
        // return the opposite of the percent of time finished for this iteration
        timer.getInversePercentValue();
      }
    }

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).