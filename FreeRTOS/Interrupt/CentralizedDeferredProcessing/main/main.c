#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "freertos/semphr.h"
#include "freertos/timers.h"

// #include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2
#define INTR_GPIO 4
#define ESP_INTR_FLAG_DEFAULT 0

//Constants used
const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

//Functions Created
void blink_task(void *pvParameters);
static void IRAM_ATTR interrupt_task(void *arg);
void vInterruptHandler(void *pvParameter1, uint32_t ulParameter2);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
	const UBaseType_t ulPeriodicTaskPriority = configTIMER_TASK_PRIORITY - 1;
	printf("ulPeriodicTaskPriority: %u\n", ulPeriodicTaskPriority);

	gpio_config_t intrconfig;
	intrconfig.pin_bit_mask = (1 << INTR_GPIO);
	intrconfig.mode = GPIO_MODE_INPUT;
	intrconfig.pull_up_en = GPIO_PULLUP_ENABLE;
	intrconfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	intrconfig.intr_type = GPIO_PIN_INTR_POSEDGE;
	gpio_config(&intrconfig);

	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	gpio_isr_handler_add(INTR_GPIO, interrupt_task, NULL);

	// ? This task triggers the interrupt
	xTaskCreate(&blink_task, "blink_task", 2048, NULL, ulPeriodicTaskPriority, NULL);
}

void blink_task(void *pvParameters)
{
	gpio_config_t blinkconfig;
	blinkconfig.pin_bit_mask = (1 << BLINK_GPIO);
	blinkconfig.mode = GPIO_MODE_OUTPUT;
	blinkconfig.pull_up_en = GPIO_PULLUP_DISABLE;
	blinkconfig.pull_up_en = GPIO_PULLDOWN_DISABLE;
	blinkconfig.intr_type = GPIO_INTR_DISABLE;

	//Set the pin configs here
	gpio_config(&blinkconfig);

    while(1)
    {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(xDelay1000ms);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(xDelay1000ms);
    }

    vTaskDelete(NULL);
}

/*
 * This a ESP32 interrupt which defers its data to FreeRTOS `vInterruptHandler` task
 * // ! You cannot print stuff inside interrupts
 */
static void IRAM_ATTR interrupt_task(void *arg)
{
	static uint32_t ulParameterValue = 0;
	BaseType_t xHigherPriorityTaskWoken;

	xHigherPriorityTaskWoken = pdFALSE;
	
	xTimerPendFunctionCallFromISR(vInterruptHandler, NULL, ulParameterValue, &xHigherPriorityTaskWoken);
	ulParameterValue++;

	//CHECK, Not correlating with FreeRTOS Example
	portYIELD_FROM_ISR();
}

/*
 * This function is used since we are deferring the `interrupt_task` to a FreeRTOS task
 * Do some processing task inside this function
 */
void vInterruptHandler(void *pvParameter1, uint32_t ulParameter2)
{
	printf("ulParameter: %u\n", ulParameter2);
}
