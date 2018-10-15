#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLINK_GPIO 2
const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);

void blink_task(void *pvParameter);

void app_main()
{
    xTaskCreate(&blink_task, "blink_task", 2048, NULL, 1, NULL);
}

void blink_task(void *pvParameter)
{
    gpio_config_t blinkconfig = 
    {
        .pin_bit_mask = (1 << BLINK_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

	//Set the pin configs here
	gpio_config(&blinkconfig);

    while(1) 
    {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(xDelay1000ms);

        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(xDelay1000ms);
    }

    vTaskDelete(NULL);
}

