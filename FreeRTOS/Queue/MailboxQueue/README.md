# MailboxQueue Example

A FreeRTOS Mailbox is a single length queue where the data is overwritten and looked at rather than adding and removing from a queue

### Functions Used

1. `vUpdateMailbox` function
	`xQueueOverwrite() API`
	
2. 	`vReadMailbox` function
	`xQueuePeek() API`	

### Explanation

1. We overwrite the struct `Data_t` inside the `xMailbox` Queue
2. We read the data (by peeking) from the `xMailbox` Queue
