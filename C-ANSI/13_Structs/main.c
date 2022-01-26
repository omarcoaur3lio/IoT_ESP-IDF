#include <stdio.h>
#include <stdlib.h>

/*
* Declaração de structs

typedef struct {
    unsigned char comPort;
    unsigned int baudRate;
} Serial_t;

int main(void) {
    Serial_t Uart;
    Uart.comPort = 1;
    Uart.baudRate = 9800;

    printf("Com: %d \nBaudRate: %d", Uart.comPort, Uart.baudRate);
    return 0;
}

*/

/* 
* Inicialização de structs 

typedef struct {
    const char *comPort;
    unsigned int baudRate;
} Serial_t;

int main(void) {
    //Serial_t Uart = { "COM2", 115200}; // Inicialização direta
    
    Serial_t Uart2 = {
        .comPort = "COM1",
        .baudRate = 9800
    };

    // printf("Com: %s \nBaudRate: %d", Uart.comPort, Uart.baudRate);
    // printf(" \n");
    printf("Com: %s \nBaudRate: %d", Uart2.comPort, Uart2.baudRate);
    return 0;
}
*/

/* Aninhamento de structs 

typedef struct {
    char buffer[200];
} Buff_t;

typedef struct {
    const char *comPort;
    unsigned int baudRate;
    Buff_t config;
} Serial_t;


int main(void) {
    Serial_t Uart = {
        .comPort = "COM4",
        .baudRate = 9800,
        .config = {
            .buffer = "Porta de cimunicação serial\n",
        }
    };

    printf("%s", Uart.config.buffer);
    return 0;

}
*/

/* Alinhamento de structs */

#pragma pack(1) // Irá alinhar as informações salvas na estrutura
typedef struct {
    const char comPort;
    unsigned int baudRate;
} Serial_t;


int main(void) {
    Serial_t Uart;
    printf("%d", sizeof(Uart));
    return 0;
}