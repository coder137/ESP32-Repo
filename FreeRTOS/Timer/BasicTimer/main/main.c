#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

//Functions Created
void blink_task(void *pvParameters);
static void prvOneShotTimerCallback(TimerHandle_t xTimer);
static void prvAutoReloadTimerCallback(TimerHandle_t xTimer);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
	TimerHandle_t xAutoReloadTimer, xOneShotTimer;
	BaseType_t xAutoTimerStarted, xOneShotTimerStarted;

    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    xAutoReloadTimer = xTimerCreate("AutoReload", xDelay500ms, pdTRUE, 0, prvAutoReloadTimerCallback);
    xOneShotTimer = xTimerCreate("OneShotTimer", xDelay500ms, pdFALSE, 0, prvOneShotTimerCallback);

	if( (xAutoReloadTimer != NULL) && (xOneShotTimer != NULL))
	{
		printf("Starting Both the timers\n");

		xAutoTimerStarted = xTimerStart(xAutoReloadTimer, 0);
		xOneShotTimerStarted = xTimerStart(xOneShotTimer, 0);

		if((xAutoTimerStarted == pdTRUE) && (xOneShotTimerStarted == pdTRUE))
		{
			printf("Both the timers have started\n");
		}
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

static void prvAutoReloadTimerCallback(TimerHandle_t xTimer)
{
	static TickType_t xTimeNow;

	xTimeNow = xTaskGetTickCount();
	printf("AutoReloadTimer count: %" PRIu32 "\n", xTimeNow);
}

static void prvOneShotTimerCallback(TimerHandle_t xTimer)
{
	static TickType_t xTimeNow;

	xTimeNow = xTaskGetTickCount();
	printf("OneShotTimer count: %" PRIu32 "\n", xTimeNow);
}
