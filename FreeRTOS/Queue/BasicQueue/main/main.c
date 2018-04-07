#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

//uninit variables
QueueHandle_t xQueue;

//variables used
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

//Functions Created
void blink_task(void *pvParameters);
static void vSenderTask(void *pvParameters);
static void vReceiverTask(void *pvParameters);

//DONE, Change the Project Name in Makefile
//TODO, Test this with ESP32
void app_main()
{
    xTaskCreate(blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    printf("Creating Queue\n");
    xQueue = xQueueCreate(5, sizeof(int32_t) );

    //This is to check if xQueue can create queues or no
    if(xQueue != NULL)
    {
    	//Queue has been created
    	printf("Queue created\n");
    	UBaseType_t queueSpaces = uxQueueSpacesAvailable(xQueue);
    	printf("Spaces: %d\n", queueSpaces);

    	xTaskCreate(vReceiverTask, "receiver", 2048, NULL, 2, NULL); //higher priority

		//This is for the queues
		xTaskCreate(vSenderTask, "sender 1", 2048, (void *)100, 1, NULL);
		xTaskCreate(vSenderTask, "sender 2", 2048, (void *)200, 1, NULL);
    }
    else
    {
    	//Queue is not created
    	printf("Queue was not created\n");
    }

}

void blink_task(void *pvParameters)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while(1)
    {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(xDelay250ms);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(xDelay250ms);
    }

    vTaskDelete(NULL);
}

static void vSenderTask(void *pvParameters)
{
	int32_t lSendValue;
	BaseType_t xStatus;
	lSendValue = (int32_t) pvParameters;

	while(1)
	{
		//printf("Sending: %d\n", lSendValue);
		// this will always be empty so no need to wait
		xStatus = xQueueSendToBack(xQueue, &lSendValue, 0);

		if(xStatus != pdPASS)
		{
			printf("Could not send %d to queue\n", lSendValue);
		}
	}

	vTaskDelete(NULL);
}

static void vReceiverTask(void *pvParameters)
{
	int32_t lReceiveValue;
	BaseType_t xStatus;
	const TickType_t xTickToWait = pdMS_TO_TICKS(100); //we wait for 50ms

	while(1)
	{
		UBaseType_t uxMessages = uxQueueMessagesWaiting(xQueue);
		if(uxMessages !=  0)
		{
			printf("Waiting: %d\n", uxMessages);
		}

		//printf("Getting value from xQueue\n");
		//Receive from back
		xStatus = xQueueReceive(xQueue, &lReceiveValue, xTickToWait);

		if(xStatus == pdPASS)
		{
			//we got the data
			printf("Received: %d\n", lReceiveValue);
		}
		else
		{
			//we could not get the data
			printf("Could not receive from the queue\n");
		}
	}

	vTaskDelete(NULL);
}
