# ResetSoftwareTimer Example

> FreeRTOS example 15

Reset a Timer to its default state using the `xTimerReset() API`

OR

Implementing a watchdog timer using FreeRTOS Software Timer

### Functions used

1. `xTimerReset() API`

### Explanation

A key press (on `make monitor`) causes the Software Timer to reset and LED to light up
After the Software Timer runs the LED is switched off

1. Initialize the GPIO pin 2 for output
2. Created Task `vKeyHitTask` which is a polling loop that reads the keyboard press
	> NOTE: Set a small `vTaskDelay` here else this function will never stop running

3. If keyboard is pressed, the LED is turned ON and Software Timer is reset (re-begins)
4. Software Timer callback added to turn the LED OFF, once it runs after a default period
