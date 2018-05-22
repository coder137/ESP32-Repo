#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

//Constants used
TickType_t xHealthyDelay = pdMS_TO_TICKS(1000);
TickType_t xErrorDelay = pdMS_TO_TICKS(100);

BaseType_t xErrorValue = 0;
TickType_t xVariableDelay = pdMS_TO_TICKS(1000);

static TimerHandle_t xAutoReloadTimer;

//Functions Created
void blink_task(void *pvParameters);
static void prvCheckErrorCallback(TimerHandle_t xTimer);
void vSimulateError(void *ignore);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
    xTaskCreate(blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
    xTaskCreate(vSimulateError, "simulateError", 2048, NULL, 5, NULL);

    xAutoReloadTimer = xTimerCreate("AutoReload", xHealthyDelay, pdTRUE, 0, prvCheckErrorCallback);
    BaseType_t xTimerStarted = xTimerStart(xAutoReloadTimer, 0);

    if(xTimerStarted == pdPASS)
    {
    	printf("Timer has started\n");
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
        vTaskDelay(xVariableDelay);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(xVariableDelay);
    }

    vTaskDelete(NULL);
}

static void prvCheckErrorCallback(TimerHandle_t xTimer)
{
	if(xErrorValue == 0)
	{
		printf("No Error Detected: %d\n", xTaskGetTickCount());
		xTimerChangePeriod(xTimer, xHealthyDelay, 0);
		xVariableDelay = xHealthyDelay;
	}
	else if(xErrorValue == 1)
	{
		printf("Error Detected: %d\n", xTaskGetTickCount());
		xTimerChangePeriod(xTimer, xErrorDelay, 0); // Do not block
		xVariableDelay = xErrorDelay;
	}
}

void vSimulateError(void *ignore)
{
	TickType_t xDelay10s = pdMS_TO_TICKS(10000); // 10 seconds delay
	while(1)
	{
		xErrorValue = 0;
		printf("vSimulateError Task: %d\n", xErrorValue);
		vTaskDelay(xDelay10s);

		xErrorValue = 1;
		printf("vSimulateError Task: %d\n", xErrorValue);
		vTaskDelay(xDelay10s);
	}
	vTaskDelete(NULL);
}

