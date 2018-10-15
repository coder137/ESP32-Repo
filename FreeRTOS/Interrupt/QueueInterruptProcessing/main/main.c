#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "freertos/semphr.h"
#include "freertos/queue.h"

// #include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2
#define INTR_GPIO 4
#define ESP_INTR_FLAG_DEFAULT 0

//Constants used
const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

QueueHandle_t xIntegerQueue, xStringQueue;

//Functions Created
void configureInterrupt();

void blink_task(void *pvParameters);
void vInterruptHandler(void * pvParameters);

static void IRAM_ATTR interrupt_task(void *arg);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
	xIntegerQueue = xQueueCreate(10, sizeof(uint32_t));
	xStringQueue = xQueueCreate(10, sizeof(char * ));

	// * Configure the interrupt here
	configureInterrupt();

	// * This task triggers the interrupt
	xTaskCreate(&blink_task, "interrupt_trigger", 2048, NULL, 1, NULL);

	// * This task receives the data queue from the interrupt
	xTaskCreate(&vInterruptHandler, "stringPrinter", 2048, NULL, 2, NULL);
}

void configureInterrupt()
{
	// * interrupt configured at positive edge (RISING)
	gpio_config_t intrconfig;
	intrconfig.pin_bit_mask = (1 << INTR_GPIO);
	intrconfig.mode = GPIO_MODE_INPUT;
	intrconfig.pull_up_en = GPIO_PULLUP_ENABLE;
	intrconfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	intrconfig.intr_type = GPIO_PIN_INTR_POSEDGE;
	gpio_config(&intrconfig);

	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	gpio_isr_handler_add(INTR_GPIO, interrupt_task, NULL);
}

void blink_task(void *pvParameters)
{
	// * configure the blink register here
	gpio_config_t blinkconfig;
	blinkconfig.pin_bit_mask = (1 << BLINK_GPIO);
	blinkconfig.mode = GPIO_MODE_OUTPUT;
	blinkconfig.pull_up_en = GPIO_PULLUP_DISABLE;
	blinkconfig.pull_up_en = GPIO_PULLDOWN_DISABLE;
	blinkconfig.intr_type = GPIO_INTR_DISABLE;

	// Set the pin configs here
	gpio_config(&blinkconfig);

	// * Send data to the queue
	uint32_t ulValueToSend = 0;
	BaseType_t i;
	const TickType_t xDontBlock = 0;

    while(1)
    {
		// * Send to queue here
		for(i = 0; i < 4; i++)
		{
			xQueueSendToBack(xIntegerQueue, &ulValueToSend, xDontBlock);
			ulValueToSend++;
		}
		printf("ulValueToSend: %" PRIu32 "\n", ulValueToSend);

		// * This triggers the interrupt
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(xDelay1000ms);

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
	uint32_t ulReceivedValue;
	BaseType_t xHigherPriorityTaskWoken;

	static const char * pcString[] = 
	{
		"String 0\r\n",
		"String 1\r\n",
		"String 2\r\n",
		"String 3\r\n",
	};
	xHigherPriorityTaskWoken = pdFALSE;

	// * Receive Queue from ISR
	while( xQueueReceiveFromISR(xIntegerQueue, &ulReceivedValue, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY)
	{
		// We only want the last 2 bits
		ulReceivedValue &= 0x03;
		xQueueSendFromISR(xStringQueue, &pcString[ulReceivedValue], &xHigherPriorityTaskWoken);
	}
	
	//CHECK, Not correlating with FreeRTOS Example
	portYIELD_FROM_ISR();
}

/*
 * This function is used since we are deferring the `interrupt_task` to a FreeRTOS task
 * Do some processing task inside this function
 */
void vInterruptHandler(void *pvParameters)
{
	char * pcString;

	while(1)
	{
		xQueueReceive(xStringQueue, &pcString, portMAX_DELAY);

		printf("%s", pcString);
	}
}
