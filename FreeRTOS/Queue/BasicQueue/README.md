# BasicQueue Example

2 sender tasks send data to a queue, which is read by a single receiver task

Here the receiver task has the priority since once the queue is non empty, it goes from its blocked state to running state

### Datatypes used

`QueueHandle_t`

### Functions Used

`xQueueCreate() API`

`uxQueueSpacesAvailable() API`

* Inside `vSenderTask`:

	`xQueueSendToBack() API`

* Inside `vReceiverTask`:

	`uxQueueMessagesWaiting() API`

	`xQueueReceive() API`


# NOTE

**Make sure in the `make menuconfig` you set Component Config -> FreeRTOS to -> Run on first core**
