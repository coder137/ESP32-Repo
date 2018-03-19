# DelayTasks Example

> Example 04

This API puts a particular task into blocked state for that duration of time

The API pdMS_TO_TICKS converts a duration to time into Tick period that are understood by the FreeRTOS kernel

### Functions Used

`pdMS_TO_TICKS() API`

`vTaskDelay() API`

NOTE: Will only work if the Tick Duration is lesser than 1000HZ or 1KHZ
