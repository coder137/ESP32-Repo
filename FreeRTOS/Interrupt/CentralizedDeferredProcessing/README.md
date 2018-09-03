# CentralizedDeferredProcessing Example

> Refer to *Esp32->Peripherals->gpio->Interrupt* example

Defers the ESP32 Interrupt to a FreeRTOS Task

**NOTE: Do not use `printf` or `ESP_LOGW` functions inside interrupts**

### Functions used

1. `xTimerPendFunctionCallFromISR() API`

### Explanation

1. Attach Interrupt to GPIO4
2. Each toggle of LED will cause an interrupt from low to high transition `blink_task` function
3. In the `interrupt_task` function, the interrupt is deferred to a timer function using the `xTimerPendFunctionCallFromISR() API`
4. This *API* sends this function to a stack, containing all the other **pending function calls**.
5. `vInterruptHandler` timer function runs after all the other stack functions have run.

**NOTE: The `vInterruptHandler` function has a higher priority than the `blink_task` function, since `ulPeriodicTaskPriority = configTIMER_TASK_PRIORITY - 1`**
