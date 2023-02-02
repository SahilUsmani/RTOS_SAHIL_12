/*
@file:          Question_02.c

@author:        Sahil Usmani

@date:          02-Feb-2023

@description:   "RTOS Module Exam Question 02"

@Question:      "Create 3 real-time tasks each with the periodicity T1 = 1000ms, T2 = 2000ms, T3 = 5000ms.
                Also create oneshot software timer to trigger a callback function from T# after 10000ms.
                The priorities of the tasks T1, T2, T3 are 5, 6, 7 respectively."
*/


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t    task01_handle, task02_handle, task03_handle;
TimerHandle_t   timer_handle;
static int      taskcore = 1;

/*  Timer Callback Function    */
void callback_task3(TimerHandle_t timer_handle)
{
    printf("Oneshot Timer : Fired\n");
}

/*  Task 01    */
void task_01(void *data)
{
    printf("Task 01 : Started\n");
    vTaskDelay( pdMS_TO_TICKS(1000));
    printf("Task 01 : Deleted\n");
    vTaskDelete(NULL);                  // Deleting Task 01
}

/*  Task 02    */
void task_02(void *data)
{
    printf("Task 02 : Started\n");
    vTaskDelay( pdMS_TO_TICKS(2000));
    printf("Task 02 : Deleted\n");
    vTaskDelete(NULL);                  // Deleting Task 02
}

/*  Task 03    */
void task_03(void *data)
{
    BaseType_t tres;
    printf("Task 03 : Started\n");
    vTaskDelay( pdMS_TO_TICKS(5000));

    /*  Starts the Callback function */
    tres = xTimerStart(timer_handle, pdMS_TO_TICKS(10000));
    if(tres == pdPASS) {
        printf("Oneshot Timer : Started Successfully\n");
    }
    printf("Task 03 : Deleted\n");
    vTaskDelete(NULL);                   // Deleting Task 03
}

/*  Main Task  */
void app_main(void)
{
    BaseType_t res;

    /*  Creating One-shot Timer   */
    timer_handle = xTimerCreate("Oneshot_timer", pdMS_TO_TICKS(5000), pdFALSE, NULL, callback_task3);
    if(timer_handle == NULL) {
        printf("Oneshot Timer : Could not be created\n");
    }

    /*  Creating Task 01  */
    res = xTaskCreatePinnedToCore(task_01, "task01", 2048, NULL, 5, &task01_handle, taskcore);
    if(res != pdPASS) {
        printf("Task 01 : Could not be Created\n");
    }

    /*  Creating Task 02  */
    res = xTaskCreatePinnedToCore(task_02, "task02", 2048, NULL, 6, &task02_handle, taskcore);
    if(res != pdPASS) {
        printf("Task 02 : Could not be Created\n");
    }

    /*  Creating Task 03  */
    res = xTaskCreatePinnedToCore(task_03, "task03", 2048, NULL, 7, &task03_handle, taskcore);
    if(res != pdPASS) {
        printf("Task 03 : Could not be Created\n");
    }

}
