#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2
#define INTR_GPIO 4
#define ESP_INTR_FLAG_DEFAULT 0

//Constants used
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
static int i=0;

//Functions Created
void gpio_output(void *pvParameters);
static void IRAM_ATTR interrupt_task(void *arg);

//DONE, Change the Project Name in Makefile
//DONE, Test this with ESP32
void app_main()
{
	gpio_config_t intrconfig;
	intrconfig.pin_bit_mask = (1 << INTR_GPIO);
	intrconfig.mode = GPIO_MODE_INPUT;
	intrconfig.pull_up_en = GPIO_PULLUP_ENABLE;
	intrconfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	intrconfig.intr_type = GPIO_PIN_INTR_POSEDGE;
	gpio_config(&intrconfig);

	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	gpio_isr_handler_add(INTR_GPIO, interrupt_task, NULL);

	xTaskCreate(&gpio_output, "blink_task", 2048, NULL, 5, NULL);
	while(1)
	{
		printf("What is it: %d\n", i);
		vTaskDelay(xDelay250ms);
	}

}

void gpio_output(void *pvParameters)
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
    	printf("Off\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(xDelay250ms);

        /* Blink on (output high) */
        printf("On\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(xDelay250ms);
    }

    vTaskDelete(NULL);
}

static void IRAM_ATTR interrupt_task(void * arg)
{
	i++;
}
