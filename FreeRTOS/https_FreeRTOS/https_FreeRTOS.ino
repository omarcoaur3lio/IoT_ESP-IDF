#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>

// Certificado necessário para conexão SSL
const char *ca =
    "-----BEGIN CERTIFICATE-----\n" \
    "    YOUR_CERTIFICATE_HERE"       \
    "-----END CERTIFICATE-----\n";

WiFiMulti wifiMulti;

#define WIFI_SSID "your_SSID"
#define WIFI_PASSWORD "your_PASSWORD"

portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;
#define CORE_0 0
#define CORE_1 1

void pvrSetupHardware(void);
void vPrintString(const char *pcString);
void vPrintStringAndNumber(const char *pcString, uint32_t uLValue);
void vPrintTwoStrings(const char *pcString, const char *pcString1);

static uint32_t ulIdleCycleCount = 0UL;

const char *pcTextForTask1 = "Task 1 está rodando\n";
const char *pcTextForTask2 = "Task 2 está rodando\n";

void prvSetupHardware(void) {
    Serial.begin(115200);
    for (uint8_t t = 3; t > 0; t--) {
        Serial.printf("[SETUP] SETUP WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
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
        sprintf(buffer, "%s %lu\r\n", pcString, ulValue);
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

    // Verifica quantos bytes estão livres. NULL refere-se a própria task (pode ser alterado pelo handle de outra task)
    UBaseType_t uxHighWaterMark;
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    vPrintStringAndNumber("Size 1: ", uxHighWaterMark);

    vPrintString("Task 1 Init...");
    volatile uint32_t test = 123;
    for ( ;; ) {
        if (wifiMulti.run() == WL_CONNECTED) { 
            HTTPClient http;

            vPrintString("[HTTP] POST...");
            http.begin("https://www.geniot.com.br/things/services/api/v1/variables/S00/value/?token=c1df1092d086d42f84346f9409fc0f84", ca);
            http.addHeader("Content-Type", "application/json");
            http.addHeader("HOST", "geniot.com.br");
            http.addHeader("Connection", "close");

            int httpCodeResponse = http.POST("{\"value\": 86.6}");

            if (httpCodeResponse > 0) {
                vPrintStringAndNumber("[HTTP] response code: \n", httpCodeResponse);

                if (httpCodeResponse == HTTP_CODE_OK) {
                    String payload = http.getString();
                    vPrintString(payload.c_str());
                }
            } else {
                vPrintTwoStrings("[HTTP] POST... Error: \n", http.errorToString(httpCodeResponse).c_str());
            }

            http.end();
        }
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        vPrintStringAndNumber("Size 2: ", uxHighWaterMark);

        vTaskDelay(61000 / portTICK_PERIOD_MS);
    }
}

void vTask2(void *pvParameters) {
    char *pcTaskName;
    pcTaskName = (char*) pvParameters;
    volatile uint32_t ul;

    vPrintString("Task 2 Init...\n");

    for ( ;; ) {
        vPrintString(pcTaskName);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void setup() {
    prvSetupHardware();
    xTaskCreatePinnedToCore(vTask1, "Task 1", configMINIMAL_STACK_SIZE+5000, (void *)pcTextForTask1, 1, NULL, CORE_0);
    xTaskCreatePinnedToCore(vTask2, "Task 2", configMINIMAL_STACK_SIZE+5000, (void *)pcTextForTask2, 1, NULL, CORE_1);
}

void loop() {
    vTaskDelay(100/portTICK_PERIOD_MS); // Evita que a função loop do arduino impeça a mudança de contexto no core
}