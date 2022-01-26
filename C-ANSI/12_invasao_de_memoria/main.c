#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char txt[6];
    // txt = "HELLO"; // resultará em um erro
    // sprintf(txt, "%s", "HELLO");

    // snprintf evita a invasão de endereços ao copiar valores para dentro de um vetor
    snprintf(txt, sizeof(txt),"%s", "HELLOMUNDO"); 
    printf("%.*s", sizeof(txt), txt); // .* força que seja necessário informar o tamanho do que se deseja imprimir
    return 0;
}