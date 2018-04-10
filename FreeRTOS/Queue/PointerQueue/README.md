# PointerQueue Example

Allocate a buffer from inside `vSenderTask` and send it to queue

Queue is read by `vReceiverTask` and buffer memory is freed

### Functions Used

`pvPortMalloc() API`

`vPortFree() API`


### Detailed Explanation

`vSenderTask`

1. Allocate buffer space using FreeRTOS safe `pvPortMalloc()` method

2. Copy a string into the buffer that is allocated

3. Send the pointer of that buffer into the queue `xQueueSendToBack()`

`vReceiverTask`

4. Receive the string from the queue `xQueueReceive()`

5. Use the string 

6. Free the space using FreeRTOS safe `vPortFree()` method
