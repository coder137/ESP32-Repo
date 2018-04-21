#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

//constants

const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
const TickType_t xDelay200ms = pdMS_TO_TICKS(200);

QueueHandle_t xMailbox;

typedef struct
{
	TickType_t xTimeStamp;
	uint32_t ulData;
} Data_t;


//Functions Created
void blink_task(void *pvParameters);
void vUpdateMailbox(void *pvParameters);
void vReadMailbox(void *pvParameters);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    xMailbox = xQueueCreate(1, sizeof(Data_t));


    xTaskCreate(vUpdateMailbox, "UpdateMailbox", 2048, NULL, 5, NULL);
    xTaskCreate(vReadMailbox, "ReadMailbox", 2048, NULL, 5, NULL);

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

void vUpdateMailbox(void *pvParameters)
{
	Data_t xMailboxUpdateData;

	while(1)
	{
		static int i = 0;

		xMailboxUpdateData.ulData = i;
		xMailboxUpdateData.xTimeStamp = xTaskGetTickCount();
		xQueueOverwrite(xMailbox, &xMailboxUpdateData);

		i++;
		vTaskDelay(xDelay200ms);
	}

	vTaskDelete(NULL);
}

void vReadMailbox(void *pvParameters)
{
	Data_t xMailboxData;

	while(1)
	{
		xQueuePeek(xMailbox, &xMailboxData, portMAX_DELAY);

		printf("Time Stamp: %" PRIu32 "\n", xMailboxData.xTimeStamp);
		printf("Data: %" PRIu16 "\n\n", xMailboxData.ulData);

		vTaskDelay(xDelay200ms);
	}

	vTaskDelete(NULL);
}
