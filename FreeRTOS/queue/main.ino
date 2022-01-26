#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti;

xQueueHandle xQueue;

void setup() {
    Serial.begin(115200);

    xQueue = xQueueCreate(5, sizeof( long ));
    if (xQueue != NULL) {
        Serial.println("Fila criada corretamente");
    }
}

void vSendTask( void *pvParameters ) {
    long valueToSend;
    portBASE_TYPE xStatus;
    xStatus = xQueueSendToBack(xQueue, &valueToSend, 0);
}

void loop() {
    vTaskDelay(100/portTICK_PERIOD_MS);
}