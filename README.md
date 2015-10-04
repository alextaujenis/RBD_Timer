# Arduino Timer Library
The Arduino real-time loop stops advancing when you write delay() in your sketch. You can keep the real-time loop moving by using millis() to track time and create delay, but it's more complicated and soon becomes messy to manage. The Timer class is a very simple replacement for all your millis() math.

##Relative vs. Absolute Time
This library works well with relative time instead of absolute. Absolute timing (for example) of running on an **interval of precisely 5 minutes** would incure a **few microseconds of time loss** each cycle. You can get a _pretty close_ interval by restarting the timer immediately if you don't mind losing one second every few hundred-thousand timeout cycles.

This library is **better suited for managing immediate program flow** over relative time, (for example) like starting a timer and using the reported percentage to dim an LED **over the course of 1 second**. It will not lose any time during the active cycle. You should use this timer really hard while it's active, then consider it dead and restart it to use it again.

#Example Setup
0. Install this library and load the example sketch on to an Arduino
0. Open a serial connection at 115200 BAUD
0. Watch two independent timers report their status

##[example.ino](https://github.com/alextaujenis/RBD_Timer/blob/master/example/example.ino)

    #include <RBD_Timer.h>

    #define BAUD 115200
    bool rising = true;

    RBD::Timer timer1;
    RBD::Timer timer2;

    void setup() {
      Serial.begin(BAUD);

      timer1.setTimeout(3000);
      timer1.restart();

      timer2.setHertz(1);
      timer2.restart();
    }

    void loop() {

      if(timer1.onRestart()) {
        Serial.println("THREE SECONDS PASSED");
      }

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
* [constructor()](#constructor)
* [setTimeout(value)](#settimeoutvalue)
* [setHertz(value)](#sethertzvalue)
* [restart()](#restart)
* [isActive()](#isactive)
* [isExpired()](#isexpired)
* [onRestart()](#onrestart)
* [onActive()](#onactive)
* [onExpired()](#onexpired)
* [getValue()](#getvalue)
* [getInverseValue()](#getinversevalue)
* [getPercentValue()](#getpercentvalue)
* [getInversePercentValue()](#getinversepercentvalue)

##constructor()
Create a new timer instance.

    RBD::Timer timer;

    void setup() {
      ...
    }

##setTimeout(value)
Provide an unsigned long value to change how long the timer will run (in milliseconds). This can be done inside of setup() or also inside of loop() to change the value at runtime. This will override any value given to [setHertz()](#sethertzvalue).

    void setup() {
      timer.setTimeout(200);  // expire after 200ms
    }

    void loop() {
      if(timer.isExpired()) {
        // returns true after 200ms
      }
    }

##setHertz(value)
Provide an integer from 1 - 1000 to set approximately how many times the timer will restart in one second. This can be done inside of setup() or also inside of loop() to change the value at runtime. This will override any value given to [setTimeout()](#settimeoutvalue).

    void setup() {
      timer.setHertz(5);  // expire after 200ms
    }

    void loop() {
      if(timer.onRestart()) {
        // events fired here are close to 5Hz
      }
    }

##restart()
There are no start or stop methods. All you need to do is restart the timer when you want to use it. When you first initialize the timer; it will always start expired. This can be used with [isExpired()](#isexpired) to create a continuous loop. If you would like a tighter time loop that doesn't wait for your code to run in order to restart the timer, then use [onRestart()](#onrestart) instead.

    void loop() {
      if(timer.isExpired()) {
        timer.restart();
      }
    }

##isActive()
Returns true if time is available. Use this method with [getPercentValue()](#getpercentvalue) or [getInversePercentValue()](#getinversepercentvalue) to perform real-time actions tweened over time.

    void loop() {
      if(timer.isActive()) {
        Serial.println(timer.getPercentValue());
      }
    }

##isExpired()
Returns true if time has run out. This can be used for a single non-blocking delay, or it can be used with [restart()](#restart) to create a continuous loop that you restart when an action has completed. If you would like a tighter time loop that doesn't wait for your code to run in order to restart the timer, then use [onRestart()](#onrestart) instead.

    void loop() {
      if(timer.isExpired()) {
        // run code here and restart when finished
        timer.restart();
      }
    }

##onRestart()
This method will fire a single event and restart the timer each time it expires, mimicking the same process of creating a loop by calling [isExpired()](#isexpired) and [restart()](#restart) together, but with a simple syntax and a tighter time loop.

    void loop() {
      if(timer.onRestart()) {
        // code block runs once per restart
        Serial.println("Timer Restarted");
      }
    }

##onActive()
This method will fire a single event when the timer goes active. The timer must expire and then be restarted for this event to fire again.

    void loop() {
      if(timer.onActive()) {
        // code block runs once per active event
        Serial.println("Timer Active");
      }
    }

##onExpired()
This method will fire a single event when the timer expires. The timer must be restarted and then allowed to expire for this event to fire again.

    void loop() {
      if(timer.onExpired()) {
        // code block runs once per event
        Serial.println("Timer Expired");
      }
    }


##getValue()
Returns an unsigned long of how many milliseconds that have passed since the start of the timer.

    void loop() {
      Serial.println(timer.getValue());
    }

##getInverseValue()
Returns an unsigned long of how many milliseconds left until the end of the timer.

    void loop() {
      Serial.println(timer.getInverseValue());
    }

##getPercentValue()
Returns an integer from 0 - 100 of how much time has passed as a percentage of the total interval. If the interval is 2000ms, and 500ms have passed: this method will return 25.

    void loop() {
      Serial.println(timer.getPercentValue());
    }

##getInversePercentValue()
Returns an integer from 100 - 0 of the inverse of how much time has passed as a percentage of the total interval. If the interval is 2000ms, and 500ms have passed: this method will return 75.

    void loop() {
      Serial.println(timer.getInversePercentValue());
    }

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).