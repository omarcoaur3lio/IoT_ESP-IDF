#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "WiFi.h"
#include "WiFiMulti.h"
#include "HTTPClient.h"
#include "geniotHTTPS_ESP32.h"

void prvSetupHardware(void);
void vTask1(void *pvParameters);

#define CORE_0 0
#define CORE_1 1

#define WIFISSID "your_ssid"
#define PASSWORD "your_pass"

#define TOKEN_GENIOT "your_token"
#define TEMPERATURA "S00"
#define UMIDADE "S01"

#define DEBUG true

Geniot client((char *)TOKEN_GENIOT);

void prvSetupHardware() {
    Serial.begin(115200);
loop: 
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }
    if(!(client.wifiConnection((char *)WIFISSID, (char *)PASSWORD))) {
        goto loop;
    }
}

void vTask1(void *pvParameters) {
    float value;
    char text[100];
    client.vPrintString("[TASK1] STARTED\n");

    for ( ;; ) {
        client.add(TEMPERATURA, random(300), (char *)"Test message");
        client.add(UMIDADE, random(100), (char *)"New message");
        
        if(client.send()) {
            client.vPrintString((char *)"Send success!");
        }

        if (client.read((char *)TEMPERATURA)) {
            client.vPrintStringAndFloat((char *) "Value: ", client.geniotValue);
            client.vPrintTwoStrings((char *) "Message: ", client.geniotText);
        }

        if (client.read((char *)UMIDADE)) {
            client.vPrintStringAndFloat((char *) "Value: ", client.geniotValue);
            client.vPrintTwoStrings((char *) "Message: ", client.geniotText);
        }
        vTaskDelay(60000 / portTICK_PERIOD_MS);
    }
}

void setup() {
    prvSetupHardware();
    xTaskCreatePinnedToCore(vTask1, "Task 1", configMINIMAL_STACK_SIZE + 10000, NULL, 2, NULL, CORE_0);
}
void loop() {
    vTaskDelay(100 / portTICK_PERIOD_MS);
}