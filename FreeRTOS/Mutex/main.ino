
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

void pvrSetupHardware(void);
void vPrintString(const char *pcString);

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

SemaphoreHandle_t xMutex;
const TickType_t xMaxBlockTimeTicks = 500;

void pvrSetupHardware(void) {
    Serial.begin(115200);
}
void vPrintString(const char *pcString) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    {
        Serial.println((char*)pcString);
    }
    xSemaphoreGive(xMutex);
}

void vTask1(void *pvParameters) {
    const char *pcTaskName = "[Task 1] runing...";

    for ( ;; ) {
        vPrintString(pcTaskName);
        vTaskDelay(rand() % xMaxBlockTimeTicks);
    }
}


void vTask2(void *pvParameters) {
    const char *pcTaskName = "[Task 2] runing...";
    volatile uint32_t ul;

    for ( ;; ) {
        vPrintString(pcTaskName);
        vTaskDelay(rand() % xMaxBlockTimeTicks);
    }
}

void setup() {
    pvrSetupHardware();

    xMutex = xSemaphoreCreateMutex();
    if (xMutex != NULL) {
        xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    }
}

void loop() {}