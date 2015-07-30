# Timer - An Arduino library
An encapsulation of timing with non-blocking millis and no delay.

#(Lazy) Documentation
    void setTimeout(unsigned long value); // set/change how long the timer will run
    void restart();                       // reset and start the timer
    bool isActive();                      // check if time is left
    bool isInactive();                    // check if the time has run out
    unsigned long getRelativeValue();     // how many milliseconds that have passed since the start of the timer
    float getPercentValue();              // how much time has passed as a percentage of the interval
    float getInversePercentValue();       // inverse of how much time has passed as a percentage of the interval

#Example
0. Install this library
0. Load up the example.ino on your Arduino
0. Attach to your Serial prompt at 11500 baud
0. Watch a non-blocking clock tick by the seconds

#License
This code is avaliable under the [MIT License](http://opensource.org/licenses/mit-license.php).