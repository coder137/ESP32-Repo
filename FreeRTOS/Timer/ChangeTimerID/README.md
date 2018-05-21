# ChangeTimerID Example

Pass same timer function to different to *OneShotTimer* and *AutoReloadTimer* and perform different task with each

TimerID is changed of subsequent timers created in this example

### Functions used

1. `pvTimerGetTimerID() API`

2. `vTimerSetTimerID() API`

3. `xTimerStop() API`

### Explanation

1. Two timers are created and started in the main loop
2. Both the timers `OneShotTimer` and `AutoReloadTimer` have a single callback function
3. The callback function reads the TimerID and sets a new timerID to the respective timer
4. The if else loop then categories the Timer and runs the appropriate block
5. The AutoReloadTimer is stopped once the timerID reaches 5
