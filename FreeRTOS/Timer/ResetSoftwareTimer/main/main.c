#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2

//Constants used
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
const TickType_t xDelay5s = pdMS_TO_TICKS(5000);

static TimerHandle_t xOneShotTimerHandle;

//Functions Created
void blink_task(void *pvParameters);
void vKeyHitTask(void *ignore);

static void prvBacklightOff(TimerHandle_t xTimerHandle);

//DONE, Change the Project Name in Makefile
//TODO, Test this with ESP32
void app_main()
{
     gpio_pad_select_gpio(BLINK_GPIO);
	/* Set the GPIO as a push/pull output */
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

	//NOTE, Creating Tasks and Timers here
	//xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
	xTaskCreate(&vKeyHitTask, "keyHit", 2048, NULL, 5, NULL);
    //Start a OneShot Timer to turn the back light off
    xOneShotTimerHandle = xTimerCreate("BacklightOff", xDelay5s, pdFALSE, 0, prvBacklightOff);

    BaseType_t timerStarted = xTimerStart(xOneShotTimerHandle, 0);
    if(timerStarted == pdPASS)
    {
    	printf("OneShotTimer has started\n");
    }

    printf("App Loop started\n");
}

//void blink_task(void *pvParameters)
//{
//    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
//       muxed to GPIO on reset already, but some default to other
//       functions and need to be switched to GPIO. Consult the
//       Technical Reference for a list of pads and their default
//       functions.)
//    */
//    gpio_pad_select_gpio(BLINK_GPIO);
//    /* Set the GPIO as a push/pull output */
//    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
//
//    while(1)
//    {
//        /* Blink off (output low) */
//        gpio_set_level(BLINK_GPIO, 0);
//        vTaskDelay(xDelay250ms);
//        /* Blink on (output high) */
//        gpio_set_level(BLINK_GPIO, 1);
//        vTaskDelay(xDelay250ms);
//    }
//
//    vTaskDelete(NULL);
//}

void vKeyHitTask(void *ignore)
{
	uint8_t data = 0;
	const TickType_t xShortDelay = pdMS_TO_TICKS(50);

	while(1)
	{
		scanf("%c", &data);
		//This is added for stability
		vTaskDelay(xShortDelay);

		if(data > 0)
		{
			printf("KeyPressed: %c\n", data);
			//Turn the back light on
			gpio_set_level(BLINK_GPIO, 1);

			//Reset the Timer
			xTimerReset(xOneShotTimerHandle, xShortDelay);
			printf("OneShot Timer has been reset\n");

			//Reset the input data
			data = 0;

			//Delay the task
			vTaskDelay(xDelay250ms);
		}
	}
}

static void prvBacklightOff(TimerHandle_t xTimerHandle)
{
	TickType_t xGetTime = xTaskGetTickCount();

	printf("Timer Expired, Turning back light off: %d\n", xGetTime);

	gpio_set_level(BLINK_GPIO, 0);
}
