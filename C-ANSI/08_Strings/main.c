#include <stdio.h>

/* Esse tipo de abordagem não é recomendada, pois estaremos duplicando o valor de message */
void printPorCopia(char message[]){
    printf("%s \n", message); // imprimir o valor
    printf("%d \n", message); // imprimir o endereço
    printf("%d \n", &message[0]); // & -> Resgata o endereço inicial do vetor
}

void printPorReferencia(char * message){
    printf("%s \n", message); // imprimir o valor
    printf("%d \n", message); // imprimir o endereço
}

int main() {
    char message[] = "Bom dia";

    printPorReferencia(message);

    return 0;
}