
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "Wire.h"
#include "SSD1306.h"

SSD1306 display(0x3C, 5, 4);

void pvrSetupHardware(void);
void vPrintString(const char *pcString);

void vTask1(void *pvParameters);

SemaphoreHandle_t xMutex;
const TickType_t xMaxBlockTimeTicks = 500;

void pvrSetupHardware(void) {
    Serial.begin(115200);

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_24);
}

void vPrintString(const char *pcString) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    {
        Serial.println((char*)pcString);
    }
    xSemaphoreGive(xMutex);
}

void vTask1(void *pvParameters) {
    char *pcTaskName;
    pcTaskName = (char *)pvParameters;
    vPrintString(pcTaskName);

    for ( ;; ) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        {
            display.clear();
            display.drawString(0, 0, String(millis()));
            display.display();
        }
        xSemaphoreGive(xMutex);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void setup() {
    pvrSetupHardware();

    xMutex = xSemaphoreCreateMutex();
    if (xMutex != NULL) {
        // Both tasks will call the same function 
        xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, (char *)"[Task 1] Initialized", 2, NULL);
        xTaskCreate(vTask1, "Task 2", configMINIMAL_STACK_SIZE, (char *)"[Task 2] Initialized", 2, NULL);
    }
}

void loop() {
    vTaskDelay(100 / portTICK_PERIOD_MS);
}