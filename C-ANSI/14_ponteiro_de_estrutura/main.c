#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char txt[100];
} Buffer_t;

typedef struct {
    unsigned char comPort;
    unsigned int baudRate;
    Buffer_t buffer;
} Serial_t;

void copiar_struct(Serial_t * uart) {
    //(*uart).baudRate = 115200;
    // ou com a notação ->
    uart->baudRate = 115200;
    printf("MSG: %s", uart->buffer.txt);
    printf("BaudRate: %d\n", uart->baudRate);
}

int main(void) {

    Serial_t Uart = {
        .baudRate = 9600,
        .comPort = 0,
        // .buffer = {
        //     .txt = "Bom dia, Maria"
        // }
    };
    snprintf(Uart.buffer.txt, sizeof(Uart.buffer.txt), "%s", "Serial COM XPTO");
    copiar_struct(&Uart); // Esta sendo passado o endereço da estrutura
    return 0;
}