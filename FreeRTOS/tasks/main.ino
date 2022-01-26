#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED; // variável para sincronização do acesso ao recurso
#define CORE_0 0
#define CORE_1 1

const char *pcTextForTask1 = "Task 2 está rodando\n";

void prvSetupHardware(void) { 
    Serial.begin(115200);  
}

void vPrintString(const char *pcString) {
    taskENTER_CRITICAL(&myMutex); // Evita que recursos sejam acessados de forma concorrente
    Serial.print((char*)pcString);
    taskEXIT_CRITICAL(&myMutex);
}

void vTask1(void *pvParameters) {
  const char *pcTaskName = "Task 1 is running\r\n";
  volatile uint32_t ul;
  for (;;) {
    vPrintString(pcTaskName);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void vTask2(void *pvParameters) {
  char *pcTaskName;
  pcTaskName = (char *)pvParameters;
  volatile uint32_t ul;
  for (;;) {
    vPrintString(pcTaskName);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  prvSetupHardware(); 
//   xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreatePinnedToCore(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL, CORE_0);
//   xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreatePinnedToCore(vTask2, "Task 2", configMINIMAL_STACK_SIZE, (void *)pcTextForTask1, 1, NULL, CORE_1); // Criação de task com passagem de parâmetro
}

void loop() {}
