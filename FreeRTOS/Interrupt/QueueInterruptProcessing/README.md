# QueueInterruptProcessing Example

> FreeRTOS Example 19

> Refer to *Esp32->Peripherals->gpio->Interrupt* example

Defers the ESP32 Interrupt to a FreeRTOS Task

**NOTE: Do not use `printf` or `ESP_LOGW` functions inside interrupts**

### Functions used

- `xQueueReceiveFromISR`
- `xQueueSendFromISR`

### Explanation

- We create two Queues namely `xIntegerQueue` and `xStringQueue`
- We configure interrupt to PIN D4
- In our **Priority 1** Task `blink_task` which is the interrupt generator, we add 4 Integers to the Queue `xIntegerQueue`
- We then generate the interrupt on `blink_task`
- Once the interrupt has been generated the `interrupt_task` receives all the values from `xIntegerQueue`
- After a little processing, the `strings` are sent to `xStringQueue`
- This unblocks the **Priority 2** Task `vInterruptHandler` which prints out the values of the strings

### Output

``` bash
ulValueToSend: 4
String 0
String 1
String 2
String 3
ulValueToSend: 8
String 0
String 1
String 2
String 3
```
