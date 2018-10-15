# BinarySemaphore Example

> FreeRTOS Example 16

> Refer to *Esp32->Peripherals->gpio->Interrupt* example

Defers the ESP32 Interrupt to a FreeRTOS Task

**NOTE: Do not use `printf` or `ESP_LOGW` functions inside interrupts**

### Functions used

1. `xSemaphoreCreateBinary() API`

2. `xSemaphoreGiveFromISR() API`

3. `xSemaphoreTake() API`

### Explanation

1. Create a Binary Semaphore using the `xSemaphoreCreateBinary() API`
2. Attach Interrupt to GPIO4
3. Each toggle of LED will cause an interrupt from low to high transition
4. In the `interrupt_task` function, the semaphore is given using the `xSemaphoreGiveFromISR() API`
4. This causes the `vInterruptHandler` function to become active (previously in blocked state)
5. Using `xSemaphoreTake() API` the function performs its processing and goes back into blocked state once the BinarySemaphore is empty

**NOTE: The `vInterruptHandler` function has a higher priority than the `blink_task` function**
