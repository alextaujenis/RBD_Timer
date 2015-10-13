# Arduino Timer Library
The Arduino real-time loop stops advancing when you write delay() or use interrupts in your sketch. You can keep the real-time loop moving by using millis() to track time and create delay, but it's more complicated and soon becomes messy to manage.

This lightweight library manages time the same way you would by setting a waypoint and calculating elapsed millis(). It is a simple replacement to manage your timed events with english instead of math.

##Soft Real-Time
This library performs in Soft Real-Time, which means that it will mostly stay on time but is allowed to slip if performance is an issue. This could look like a microsecond of time loss when the timer expires but before it is restarted. Or this could look like a busy Arduino loop() where the timer resolution degrades to only fire an event within 25 microseconds of an actual event. (A microsecond is a small fraction of a millisecond).

There are other solutions for Hard Real-Time problems that require exact timing, which cannot slip for any reason. These are consideration when using this timer within a project, but for the most part; performance is awesome and you should use this library.

#Example Setup
0. Install this library and load the example sketch on to an Arduino
0. Open a serial connection at 115200 BAUD
0. Watch an interval timer print to serial every three seconds

**Example Sketch:**

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

#Documentation

##Public Methods
* [constructor()](#constructor)
<hr />
* [setTimeout(value)](#settimeoutvalue)
* [setHertz(value)](#sethertzvalue)
<hr />
* [getValue()](#getvalue)
* [getInverseValue()](#getinversevalue)
* [getPercentValue()](#getpercentvalue)
* [getInversePercentValue()](#getinversepercentvalue)
<hr />
* [restart()](#restart)
* [isActive()](#isactive)
* [isExpired()](#isexpired)
<hr />
* [onRestart()](#onrestart)
* [onActive()](#onactive)
* [onExpired()](#onexpired)

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

##restart()
There are no start or stop methods. All you need to do is restart the timer when you want to use it. When you first initialize the timer; it will always start expired. This can be used with [isExpired()](#isexpired) to create a continuous loop. If you would like a tighter loop that does not wait for your code to run in order to restart the timer, then use [onRestart()](#onrestart) instead.

    void loop() {
      if(timer.isExpired()) {
        // run code here, then restart the timer
        timer.restart();
      }
    }

##isActive()
Returns true if time is available. Use this method with [getPercentValue()](#getpercentvalue) or [getInversePercentValue()](#getinversepercentvalue) to perform real-time actions tweened over time.

Use [onActive()](#onactive) to only fire a single event when the timer goes active.

    void loop() {
      if(timer.isActive()) {
        Serial.println(timer.getPercentValue());
      }
    }

##isExpired()
Returns true if time has run out. This can be used for a single non-blocking delay, or it can be used with [restart()](#restart) to create a continuous loop that you restart when an action has completed.

Use [onExpired()](#onexpired) to fire a single event and not restart the timer right away.

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
        // code only runs once per event
        Serial.println("Timer Restarted");
      }
    }

##onActive()
This method will fire a single event when the timer goes active. The timer must expire and then be restarted for this event to fire again.

    void loop() {
      if(timer.onActive()) {
        // code only runs once per event
        Serial.println("Timer Active");
      }
    }

##onExpired()
This method will fire a single event when the timer expires. The timer must be restarted and then allowed to expire for this event to fire again.

    void loop() {
      if(timer.onExpired()) {
        // code only runs once per event
        Serial.println("Timer Expired");
      }
    }

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).