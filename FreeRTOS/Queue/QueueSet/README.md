# QueueSet Example

Adding multiple queues into a queueSet and reading and writing to such a queueSet

### Functions Used

`xQueueCreateSet() API`

`xQueueAddToSet() API`

`xQueueSelectFromSet() API`

### Explanation

1. We create the queues that we are sending data to
2. We create a queueSet with number of queues added to it
3. We add the queues created to the queueSet
4. Using a sender task `vSenderTask1` and `vSenderTask2` we send data to the respective queues
5. We use a receiver task `vReceiverTask` to get the queue handle which contains data, then we read the data from that respective queue
