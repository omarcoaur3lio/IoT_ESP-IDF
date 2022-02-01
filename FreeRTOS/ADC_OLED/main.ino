#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include "cJSON.h"

#include <Wire.h>
#include "SSD1306.h"
SSD1306 display(0x3C, 5, 4);

// Certificado necessário para conexão SSL
const char *ca =
    "-----BEGIN CERTIFICATE-----\n" \
    "    YOUR_CERTIFICATE_HERE"       \
    "-----END CERTIFICATE-----\n";

WiFiMulti wifiMulti;

#define WIFI_SSID "your_SSID"
#define WIFI_PASSWORD "your_PASSWORD"

#define DEBUG 0
#define CORE_0 0
#define CORE_1 1

void pvrSetupHardware(void);
void vPrintString(const char *pcString);
void vPrintStringAndNumber(const char *pcString, uint32_t uLValue);
void vPrintTwoStrings(const char *pcString, const char *pcString1);
bool vJsonConverter(String payload, float *result);

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);
void vTask3(void *pvParameters);

portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;

QueueHandle_t xQueue, xQueue_adc;

void prvSetupHardware(void) {
    Serial.begin(115200);
    for (uint8_t t = 3; t > 0; t--) {
        Serial.printf("[SETUP] SETUP WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello, world!");
}

void vPrintString(const char *pcString) {
    taskENTER_CRITICAL(&myMutex);
    {
        Serial.println((char*)pcString);
    }
    taskEXIT_CRITICAL(&myMutex);
}

void vPrintStringAndNumber(const char *pcString, uint32_t ulValue) {
    taskENTER_CRITICAL(&myMutex);
    {
        char buffer[50];
        sprintf(buffer, "%s %u\r\n", pcString, ulValue);
        Serial.println((char*)buffer);
    }
    taskEXIT_CRITICAL(&myMutex);
}

vPrintStringAndInteger((const char *pcString, int value) {
    taskENTER_CRITICAL(&myMutex);
    {
        char buffer[50];
        sprintf(buffer, "%s %d\r\n", pcString, value);
        Serial.println((char*)buffer);
    }
    taskEXIT_CRITICAL(&myMutex);
}

void vPrintTwoStrings(const char *pcString, const char *pcString1) {
    taskENTER_CRITICAL(&myMutex);
    {
        char buffer[50];
        sprintf(buffer, "%s %s\r\n", pcString, pcString1);
        Serial.println((char*)buffer);
    }
    taskEXIT_CRITICAL(&myMutex);
}

void vTask1(void *pvParameters) {
    if (DEBUG) {
        vPrintString("Task 1 Init...");
    }

    float value;
    int adc_result;
    BaseType_t xStatus;
    
    for ( ;; ) {

        xStatus = xQueueReceive(xQueue_adc, &adc_result, 0);
        if (xStatus != pdPASS) {
            continue;
        }

        if (wifiMulti.run() == WL_CONNECTED) { 
            HTTPClient http;
    
            http.begin("https://www.geniot.com.br/things/services/api/v1/variables/S00/value/?token=c1df1092d086d42f84346f9409fc0f84", ca);
            http.addHeader("Content-Type", "application/json");
            http.addHeader("HOST", "geniot.com.br");
            http.addHeader("Connection", "close");

            String data = String(adc_result);

            int httpCodeResponse = http.POST("{\"value\":" + data +"}");

            if (httpCodeResponse > 0) {
                if (DEBUG) {
                    vPrintStringAndInteger("[HTTP] response code: ", httpCodeResponse);
                }

                if (httpCodeResponse == HTTP_CODE_OK) {
                    String payload = http.getString();
                    if (DEBUG) {
                        vPrintString(payload.c_str());
                    }
                    if (vJsonConverter(payload, &value) != -1) {
                        xStatus = xQueueSendToBack(xQueue, &value, portMAX_DELAY);
                        if (xStatus != pdPASS) {
                            if (DEBUG) {
                              vPrintString("ERROR: The queue is full. \r\n");
                            }
                        }
                    }
                }
            } else {
                if (DEBUG) {
                    vPrintTwoStrings("[HTTP] POST... Error: \n", http.errorToString(httpCodeResponse).c_str());
                }
            }

            http.end();
        }
        vTaskDelay(61000 / portTICK_PERIOD_MS);
    }
}

void vTask2(void *pvParameters) {
    if (DEBUG) {
        vPrintString("Task 2 Init...\n");
    }
    for ( ;; ) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void vTask3(void *pvParameters) {
    float lReceivedValue;
    BaseType_t xStatus;
    if (DEBUG) {
        vPrintString("Task3 init...");
    }
    for ( ;; ) {
        xStatus = xQueueReceive(xQueue, &lReceivedValue, portMAX_DELAY);
        if (xStatus == pdPASS) {
            display.clear();
            display.drawString(0, 0, String(lReceivedValue));
            display.display();
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void vTask4(void *pvParameters) {
    if (DEBUG) {
        vPrintString("Task4 Init...");
    }
    BaseType_t xStatus;
    int value;
    for ( ;; ) {
        // Leitura do ADC
        adc1_config_width(ADC_WIDTH_12Bit);
        adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_0db);
        value = adc1_get_voltage(ADC1_CHANNEL_0);
        vPrintStringAndInteger("Task 4 ADC: ", value);

        xStatus = xQueueSendToBack(xQueue_adc, &value, portMAX_DELAY);
        if (xStatus != pdPASS) {
            if (DEBUG) {
                vPrintString("ERROR: Empty queue.");
            }
        }
        vTaskDelay( 2000 / portTICK_PERIOD_MS);
    }
}

bool vJsonConverter(String payload, float *result) {
    bool back = false;
    cJSON *json = cJSON_Parse(payload.c_str());

    if (json != NULL) {
        const cJSON *name = NULL;
        name = cJSON_GetObjectItem(json, "name");
        if ((name->valuestring != NULL)) {
            if (DEBUG) {
                vPrintTwoStrings("Variable: ", name->valuestring);
            }
        }

        const cJSON *lastValue = NULL;
        lastValue = cJSON_GetObjectItem(json, "last_value");
        if ((lastValue->valuestring != NULL)) {
            if (DEBUG) {
                vPrintTwoStrings("Last Value: ", lastValue->valuestring);
            }
            cJSON *json_value = cJSON_Parse(lastValue->valuestring);
            if (json_value != NULL) {
                const cJSON *value = NULL;
                value = cJSON_GetObjectItem(json_value, "value");
                if ((value->valuedouble != NULL)) {
                    *result = value->valuedouble;
                    back = true;
                }
                cJSON_Delete(json_value);
            }
        }
        cJSON_Delete(json);
    } else { 
        back = false; 
    }
    return back;
}

void drawFontFaceDemo() {
    // for more fonts: http://oleddisplay.squix.ch
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(0, 0, "Hello, World");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Hello, World");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello, World");
}

void setup() {
    prvSetupHardware();
    
    xQueue = xQueueCreate(5, sizeof(float));
    if (xQueue == NULL) {
        while (1) {
            vPrintString("Queue ERROR...");
        }
    }    
    
    xQueue_adc = xQueueCreate(1, sizeof(int));
    if (xQueue_adc == NULL) {
        while (1) {
            vPrintString("Queue_adc ERROR...");
        }
    }    
    
    xTaskCreatePinnedToCore(vTask1, "Task 1", configMINIMAL_STACK_SIZE+8000, NULL, 2, NULL, CORE_0);
    xTaskCreatePinnedToCore(vTask2, "Task 2", configMINIMAL_STACK_SIZE+5000, NULL, 2, NULL, CORE_1);
    xTaskCreatePinnedToCore(vTask3, "Task 3", configMINIMAL_STACK_SIZE+1000, NULL, 2, NULL, CORE_1);
    xTaskCreatePinnedToCore(vTask4, "Task 4", configMINIMAL_STACK_SIZE+1000, NULL, 2, NULL, CORE_1);
}

void loop() {
    vTaskDelay(100/portTICK_PERIOD_MS);
}