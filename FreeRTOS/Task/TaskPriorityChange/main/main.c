#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

//Variables used
TaskHandle_t xTask2Handle;

///These are important
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void app_main()
{
    //xTaskCreate(&blink_task, "blink_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);

    //Adding the Parameter here
    xTaskCreate(&vTask1, "print_task 1", 2048, NULL, 5, NULL);
    xTaskCreate(&vTask2, "print_task 2", 2048, NULL, 4, &xTask2Handle); //This task has a lesser priority
}

void vTask1(void *pvParameters)
{
	UBaseType_t uxPriority;
	uxPriority = uxTaskPriorityGet(NULL); //get priority of current task

	while(1)
	{
		printf("Task 1 is running\n");
		printf("Raising the Priority of Task 2: %u\n\n", uxPriority);
		vTaskPrioritySet(xTask2Handle, (uxPriority+1)); //Task2 ---> 6
	}
}

void vTask2(void *pvParameters)
{
	UBaseType_t uxPriority;

	uxPriority = uxTaskPriorityGet(NULL); //get from current function
	while(1)
	{
		printf("Task 2 is running\n");
		printf("Lowering Task 2 priority: %u\n\n", uxPriority);
		vTaskPrioritySet(NULL, (uxPriority - 1)); //
	}
}


