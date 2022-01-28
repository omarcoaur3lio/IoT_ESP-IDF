#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include "cJSON.h"

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

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;

const char *pcTextForTask1 = "Task 1 is runing\n";
const char *pcTextForTask2 = "Task 2 is runing\n";

QueueHandle_t xQueue;

void prvSetupHardware(void) {
    Serial.begin(115200);
    for (uint8_t t = 3; t > 0; t--) {
        Serial.printf("[SETUP] SETUP WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
    
    // Criação da fila
    xQueue = xQueueCreate(5, sizeof(float));
    if (xQueue == NULL) {
        while (1) {
            vPrintString("ERROR...");
        }
    }
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
    vPrintString("Task 1 Init...");

    BaseType_t xStatus;
    float value;
    
    for ( ;; ) {
        if (wifiMulti.run() == WL_CONNECTED) { 
            HTTPClient http;
            vPrintString("[HTTP] POST...");
            http.begin("https://www.geniot.com.br/things/services/api/v1/variables/S00/value/?token=c1df1092d086d42f84346f9409fc0f84", ca);
            http.addHeader("Content-Type", "application/json");
            http.addHeader("HOST", "geniot.com.br");
            http.addHeader("Connection", "close");

            int httpCodeResponse = http.POST("{\"value\": 96.6}");

            if (httpCodeResponse > 0) {
                vPrintStringAndNumber("[HTTP] response code: ", httpCodeResponse);

                if (httpCodeResponse == HTTP_CODE_OK) {
                    String payload = http.getString();
                    if (DEBUG) {
                        vPrintString(payload.c_str());
                    }
                    if (vJsonConverter(payload, &value) == true) {
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
    vPrintString("Task 2 Init...\n");
    
    float lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(5000UL);

    for ( ;; ) {
        xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
        if (xStatus == pdPASS) {
            vPrintStringAndNumber("TASK2: Received: ", lReceivedValue);
        } else {
            if (DEBUG) {
                vPrintString("ERROR: Empty queue....");
            }
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
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

void setup() {
    prvSetupHardware();
    xTaskCreatePinnedToCore(vTask1, "Task 1", configMINIMAL_STACK_SIZE+8000, (void *)pcTextForTask1, 2, NULL, CORE_0);
    xTaskCreatePinnedToCore(vTask2, "Task 2", configMINIMAL_STACK_SIZE+5000, (void *)pcTextForTask2, 2, NULL, CORE_1);
}

void loop() {
    vTaskDelay(100/portTICK_PERIOD_MS);
}