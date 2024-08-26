# FlashTimer
A timer code for the onboard flash button on most ESP boards. Catches single, double and long clicks, and has a timer.
The aim of this project is to implement a working environment for ESP boards without the need of extra buttons or labor.
This is my first project, done on Arduino IDE 2.X., and I have very little experience, so don't expect much help.
I don't guarantee it's functionability, reliability, or efficiency. It's just a code I made.
The implementation of the code uses getters to pass the clicks and their indexes, timers, and the debug variables to external code.
It was tested on the Arduino IDE's serial monitor with a NodeMCU ESP8266 board and a T-Display ESP32 board.
The examples are for the serial monitor and ESP8266 board's 0.96" display.
It runs a loop that checks for button state changes, then go through a machine of states that uses timers and flags to filter the input, and then indexes them.
It works well, respecting the boards limitations, and two single clicks on a loop iteration can happen.
The timers are for total run time, press duration, double click interval, and unpressed duration.
The machine of state has flags that can be used to help train the user's timing.
For example, if "P" on the debug code is on 2 after holding the button for a bit, it's already a long click.
The same way, if you release the button, you can doubleclick while "P" is at 3.
If you miss that just for a bit you can still get 2 single clicks on that loop iteration though.
