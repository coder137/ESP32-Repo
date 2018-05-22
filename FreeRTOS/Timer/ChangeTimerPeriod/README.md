# ChangeTimerPeriod Example

This example uses the `xTimerChangePeriod API` to change the Timer delay/period dynamically

### Functions used

1. `xTimerChangePeriod() API`

### Explanation

1. `vSimulateError` task is created to change the value of `xErrorValue` from `0` to `1` to indicate error
2. `prvCheckErrorCallback` which is a timer callback checks the value of `xErrorValue` variable.
3. If `error == 1` is detected the timerPeriod is changed to `xErrorDelay`
4. If `error == 0` is detected the timerPeriod is changed to `xHealthyDelay`
5. This delay values are also fed to the LED blink (in the `blink_task` task) and the value of the LED and the output on the serial monitor changes accordingly
