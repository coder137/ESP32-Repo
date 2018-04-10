#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

//constants
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

QueueHandle_t xPointerQueue;

//Functions Created
void blink_task(void *pvParameters);
void vSenderTask(void *pvParameters);
void vReceiverTask(void *pvParameters);

//TODO, Change the Project Name in Makefile
//TODO, Test this with ESP32
void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    xPointerQueue = xQueueCreate(5, sizeof(char *));

    if(xPointerQueue != NULL)
    {
    	//Queue Created
    	xTaskCreate(vSenderTask, "Sender", 2048, NULL, 5, NULL);

    	xTaskCreate(vReceiverTask, "Receiver", 2048, NULL, 4, NULL);
    }
    else
    {
    	//Queue not created
    	printf("Queue has not been created\n");
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
	char *pcStringToSend;
	const size_t xMaxStringLength = 50;
	BaseType_t xStringNumber = 0;

	BaseType_t xStatus;

	while(1)
	{
		//Note, Allocate it here
		pcStringToSend = (char *) pvPortMalloc(xMaxStringLength*sizeof(char));

		snprintf(pcStringToSend, xMaxStringLength, "String Number %d\n", xStringNumber);
		xStringNumber++;

		//You have to send the pointer to the String
		xStatus = xQueueSendToBack(xPointerQueue, &pcStringToSend, portMAX_DELAY);

		if(xStatus == pdPASS)
		{
			printf("Sent to queue: %s\n", pcStringToSend);
		}
	}

	vTaskDelete(NULL);
}

void vReceiverTask(void *pvParameters)
{
	char *pcStringReceived;
	BaseType_t xStatus;


	while(1)
	{
		xStatus = xQueueReceive(xPointerQueue, &pcStringReceived, portMAX_DELAY);

		if(xStatus == pdPASS)
		{
			printf("Data Received: %s\n", pcStringReceived);

			//Note, we have to de allocate the memory here
			vPortFree(pcStringReceived);
		}
		else
		{
			printf("Data not present inside buffer\n");
		}
	}

	vTaskDelete(NULL);
}
