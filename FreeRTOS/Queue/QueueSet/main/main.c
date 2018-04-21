#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

//Constants used
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;
static QueueSetHandle_t xQueueSet = NULL;

//Functions Created
void blink_task(void *pvParameters);

void vSenderTask1(void *pvParameters);
void vSenderTask2(void *pvParameters);

void vReceiverTask(void *pvParameters);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

   //Create the queues here
    xQueue1 = xQueueCreate(1, sizeof(char *));
    xQueue2 = xQueueCreate(1, sizeof(char *));

    //Create the queue set here and add the queues to the queue set
    xQueueSet = xQueueCreateSet(1*2); //2 queues needed
    xQueueAddToSet(xQueue1, xQueueSet);
    xQueueAddToSet(xQueue2, xQueueSet);

    //NOTE, We can add checks for xQueue1 and xQueue2 to see if it is NULL or no
    xTaskCreate(vSenderTask1, "Sender1", 2048, NULL, 5, NULL);
    xTaskCreate(vSenderTask2, "Sender2", 2048, NULL, 5, NULL);

    xTaskCreate(vReceiverTask, "Receiver", 2048, NULL, 6, NULL);
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

void vSenderTask1(void *pvParameters)
{
	const TickType_t xDelay = pdMS_TO_TICKS(100);
	const char * const pcMessage = "Sender Task 1";

	while(1)
	{
		vTaskDelay(xDelay);

		xQueueSend(xQueue1, &pcMessage, 0);
	}

	vTaskDelete(NULL);
}

void vSenderTask2(void *pvParameters)
{
	const TickType_t xDelay = pdMS_TO_TICKS(200);
	const char * const pcMessage = "Sender Task 2";

	while(1)
	{
		vTaskDelay(xDelay);

		xQueueSend(xQueue2, &pcMessage, 0);
	}

	vTaskDelete(NULL);
}

void vReceiverTask(void *pvParameters)
{
	QueueHandle_t xQueueContainsData;
	char *pcReceivedString;

	while(1)
	{
		xQueueContainsData = (QueueHandle_t) xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

		xQueueReceive(xQueueContainsData, &pcReceivedString, 0);

		printf("%s\n", pcReceivedString);
	}

	vTaskDelete(NULL);
}
