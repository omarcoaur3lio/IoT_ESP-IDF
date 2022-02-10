#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "esp_adc_cal.h"

#include <Wire.h>
#include "SSD1306.h"
SSD1306 display(0x3C, 5, 4);

#define V_REF 1100

void prvSetupHardware(void);
void prvPrintString(const char *pcString);
uint32_t adcRead(void);
void vTask_OLED(void *pvParameters);
void vTask_ADC(void *pvParameters);

SemaphoreHandle_t xMutex, xMutex_oled;

TaskHandle_t Task_OLED_Handle = NULL, Task_ADC_Handle = NULL;

char buffer[50];

void prvSetupHardware(void) {
    Serial.begin(115200);
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
}

void prvPrintString(const char *pcString) {
    xSemaphoreTake(xMutex, portMAX_DELAY);
    {
        Serial.println((char *)pcString);
    }
    xSemaphoreGive(xMutex);
}

void vTask_OLED(void *pvParameters) {
    char *pcTaskName;
    pcTaskName = (char *)pvParameters;
    vPrintString(pcTaskName);

    for ( ;; ) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait for a notification to be received 
        xSemaphoreTake(xMutex_oled, portMAX_DELAY);
        {
            display.clear();
            display.drawString(0, 0, buffer);
            display.display();
        }
        xSemaphoreGive(xMutex_oled);

        vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}

void vTask_ADC(void *pvParameters) {
    const char amostras = 10;
    volatile long adc_result = 0;
    volatile int count = 0;

    char *pcTaskName;
    pcTaskName = (char *)pvParameters;
    vPrintString(pcTaskName);

    for ( ;; ) {
        adc_result += adcRead();
        count++;
        if (count >= amostras) {
            sprintf(buffer, "ADC: %2.f", adc_result / (amostras * 1.0));
            count = adc_result = 0;

            xTaskNotifyGive(Task_OLED_Handle); // Notifies that the variable has been modified
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

uint32_t adcRead(void) {
    uint32_t adc_result = 0;
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_11db);
    esp_adc_cal_characteristics_t characteristics;
    esp_adc_cal_get_characteristics(V_REF, ADC_ATTEN_11db, ADC_WIDTH_12Bit, &characteristics);
    adc_result = adc1_to_voltage(ADC1_CHANNEL_0, &characteristics);

    return adc_result;
}

void setup() {
    prvSetupHardware();

    xMutex = xSemaphoreCreateMutex();
    xMutex_oled = xSemaphoreCreateMutex();
    if (xMutex != NULL && xMutex_oled != NULL) {
        xTaskCreate(vTask_OLED, "OLED Task", configMINIMAL_STACK_SIZE, (char *)"[OLED Task] initializing...", 2, &Task_OLED_Handle);
        xTaskCreate(vTask_ADC, "ADC Task", configMINIMAL_STACK_SIZE, (char *)"[ADC Task] initializing...", 2, &Task_ADC_Handle);
    }
}

void loop() {
    vTaskDelay( 100 / portTICK_PERIOD_MS);
}
