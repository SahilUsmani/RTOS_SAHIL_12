/*
@file:          Question_02.c

@author:        Sahil Usmani

@date:          02-Feb-2023

@description:   "RTOS Module Exam Question 01"

@Question:      "Create 3 real-time tasks each with the periodicity T1 = 1000ms, T2 = 2000ms, T3 = 5000ms.
                Also create two additional task T4 and T5 where T4 sends integer data to T5 using Message Queues.
                The priorities of the tasks T1, T2, T3, T4, T5 are 5, 6, 7, 8, 9 respectively."
*/



#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"

#define QUEUE_LENGTH 5
#define QUEUE_ITEM_SIZE sizeof(int)


TaskHandle_t    task01_handle, task02_handle, task03_handle, task04_handle, task05_handle;
QueueHandle_t   q_handle;
static int      taskcore = 1;


/*  Task 01    */
void task_01(void *data)
{
    printf("Task 01 : Started\n");
    vTaskDelay( pdMS_TO_TICKS(1000));
    printf("Task 01 : Deleted\n");
    vTaskDelete(NULL);                                  // Deleting Task 01
}

/*  Task 02    */
void task_02(void *data)
{
    printf("Task 02 : Started\n");
    vTaskDelay( pdMS_TO_TICKS(2000));
    printf("Task 02 : Deleted\n");
    vTaskDelete(NULL);                                  // Deleting Task 02
}

/*  Task 03    */
void task_03(void *data)
{
    printf("Task 03 : Started\n");
    vTaskDelay( pdMS_TO_TICKS(5000));
    printf("Task 03 : Deleted\n");
    vTaskDelete(NULL);                                  // Deleting Task 03
}

/*  Task 04    */
void task_04(void *data)
{
    BaseType_t sendrt;
    int data_4 = 1;
    printf("Task 04 : Started\n");

    while(data_4 < 10) {

    sendrt = xQueueSend(q_handle, &data_4, pdMS_TO_TICKS(1000)); // Sending Data
        if(sendrt != pdPASS) {
            printf("Queue : Nothing was sent\n");
        }
        else {
            printf("Task 04 : Data Sent = %d\n", data_4);
        }
        data_4++;
    }
    printf("Task 04 : Deleted\n");
    vTaskDelay( pdMS_TO_TICKS(500));
    vTaskDelete(NULL);                                  // Deleting Task 04
}

/*  Task 05    */
void task_05(void *data)
{
    BaseType_t rec_rt;
    int buffer = 0;
    printf("Task 05 : Started\n");
    
    for(int i = 0; i < 9; i++) {
        rec_rt = xQueueReceive(q_handle, &buffer, pdMS_TO_TICKS(3000));  // Receiving Data
        if(rec_rt != pdPASS) {
            printf("Queue : Nothing was recieved\n");
        }
        else {
            printf("Task 05 : Data Received = %d\n", buffer);
        }
    }
    vTaskDelay( pdMS_TO_TICKS(500));
    printf("Task 05 : Deleted\n");
    vTaskDelete(NULL);                                  // Deleting Task 05
}

/*  Main Task   */
void app_main(void)
{
    BaseType_t res;

    /*  Creating Message Queue  */
    q_handle = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    if(q_handle == NULL) {
        printf("Queue : Could not be created\n");
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

    /*  Creating Task 04  */
    res = xTaskCreatePinnedToCore(task_04, "task04", 2048, NULL, 8, &task04_handle, taskcore);
    if(res != pdPASS) {
        printf("Task 04 : Could not be Created\n");
    }

    /*  Creating Task 05  */
    res = xTaskCreatePinnedToCore(task_05, "task05", 2048, NULL, 9, &task05_handle, taskcore);
    if(res != pdPASS) {
        printf("Task 05 : Could not be Created\n");
    }

}
