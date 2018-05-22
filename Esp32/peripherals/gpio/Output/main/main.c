#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//Definitions
#define BLINK_GPIO 2 //GPIO 2

const TickType_t xDelay500ms = pdMS_TO_TICKS(500); //converts ms to ticks for freeRTOS

//Functions Created
void gpio_output(void *pvParameters);

//TODO, Change the Project Name in Makefile
//TODO, Test this with ESP32
void app_main()
{
    xTaskCreate(&gpio_output, "gpio_output", 2048, NULL, 5, NULL);
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
        gpio_set_level(BLINK_GPIO, 0);
        printf("Off\n");
        vTaskDelay(xDelay500ms);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        printf("On\n");
        vTaskDelay(xDelay500ms);
    }

    vTaskDelete(NULL);
}
