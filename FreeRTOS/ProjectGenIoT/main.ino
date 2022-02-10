#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "WiFi.h"
#include "WiFiMulti.h"
#include "HTTPClient.h"
#include "libs/geniotHTTPS_ESP32.h"

void prvSetupHardware(void);
void vTask1(void *pvParameters);

#define CORE_0 0
#define CORE_1 1

#define WIFISSID "your_SSID"
#define PASSWORD "wifi_password"

#define TOKEN_GENIOT "your_token"
#define TEMPERATURA "S00"
#define UMIDADE "S01"

#define DEBUG true

Geniot client((char *)TOKEN_GENIOT);

void prvSetupHardware() {
    Serial.begin(115200);
}

void setup() {}
void loop() {}