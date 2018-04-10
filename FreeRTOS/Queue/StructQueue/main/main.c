#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
QueueHandle_t xQueue;

//Functions Created
void blink_task(void *pvParameters);

//TODO, Change to static void if there is a problem here
void vSenderTask(void *pvParameters);
void vReceiverTask(void *pvParameters);

//Creating variables
typedef enum
{
	eSender1,
	eSender2
} DataSource_t;

typedef struct
{
	uint8_t ucValue;
	DataSource_t eDataSource;
} Data_t;

static const Data_t xStructToSend[2] =
{
		{100, eSender1},
		{200, eSender2}
};

//DONE, Change the Project Name in Makefile
//TODO, Test this with ESP32
void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    xQueue = xQueueCreate(3, sizeof(Data_t));

    if(xQueue != NULL)
    {
    	// Create the tasks here, Sender and Receiver tasks
    	xTaskCreate(vSenderTask, "Sender1", 2048, (void *) &(xStructToSend[0]), 5, NULL);
    	xTaskCreate(vSenderTask, "Sender2", 2048, (void *) &(xStructToSend[1]), 5, NULL);

    	xTaskCreate(vReceiverTask, "Receiver", 2048, NULL, 4, NULL);
    }
    else
    {
    	printf("Queue not created\n");
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

void vSenderTask(void *pvParameters)
{
	BaseType_t xStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

	while(1)
	{
		xStatus = xQueueSendToBack(xQueue, pvParameters, xTicksToWait);

		if(xStatus != pdPASS)
		{
			printf("Could not send data to the queue\n");
		}
	}

	vTaskDelete(NULL);
}

void vReceiverTask(void *pvParameters)
{
	BaseType_t xStatus;
	Data_t xReceivedStructure;

	while(1)
	{
		if(uxQueueMessagesWaiting(xQueue) != 3)
		{
			printf("Queue should have been full\n");
		}

		xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);

		if(xStatus == pdPASS)
		{
			printf("From Sender %d: %d\n", xReceivedStructure.eDataSource, xReceivedStructure.ucValue);
		}
		else
		{
			printf("Data not received from queue\n");
		}
	}

	vTaskDelete(NULL);
}
