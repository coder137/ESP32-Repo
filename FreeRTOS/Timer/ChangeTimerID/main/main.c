#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2
#define mainONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS(333)
#define mainAUTO_RELOAD_TIMER_PERIOD pdMS_TO_TICKS(500)

//Constants used
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

static TimerHandle_t xAutoReloadTimer, xOneShotTimer;

//Functions Created
void blink_task(void *pvParameters);
static void prvTimerCallback(TimerHandle_t xTimer);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
	BaseType_t xOneShotTimerStarted, xAutoReloadTimerStarted;

    xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    xOneShotTimer = xTimerCreate("OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0, prvTimerCallback);
    xAutoReloadTimer = xTimerCreate("AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0, prvTimerCallback);

    if( (xOneShotTimer != NULL) && (xAutoReloadTimer != NULL))
    {
    	xOneShotTimerStarted = xTimerStart(xOneShotTimer, 0);
    	xAutoReloadTimerStarted = xTimerStart(xAutoReloadTimer, 0);

    	if( (xOneShotTimerStarted == pdPASS) && (xAutoReloadTimerStarted == pdPASS))
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

static void prvTimerCallback(TimerHandle_t xTimer)
{
	TickType_t xTimeNow;
	uint32_t ulExecutionCount;

	//Set the ID of the Timer here
	ulExecutionCount = (uint32_t) pvTimerGetTimerID(xTimer);
	ulExecutionCount++;
	vTimerSetTimerID(xTimer, (void *) ulExecutionCount);

	xTimeNow = xTaskGetTickCount();

	if(xTimer == xOneShotTimer)
	{
		printf("One Shot Timer Callback executing: %d\n", xTimeNow);
	}
	else
	{
		printf("Auto Reload Timer Callback executing: %d\n", xTimeNow);

		if(ulExecutionCount == 5)
		{
			xTimerStop(xTimer, 0); // Stop the timer immediately
		}
	}
}

