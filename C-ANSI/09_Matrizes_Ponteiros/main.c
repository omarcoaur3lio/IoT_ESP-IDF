#include <stdio.h>

void print( char * txt ) { // o tipo na declaração definirá o tamanho do salto do ponteiro
    while( *txt != '0' ) {
        printf( "%c", *txt );
        txt++;
    }
}

int main( void ) {

    unsigned short count = 0xAABB;

    /*
    * Manipulação byte a byte

    unsigned char * ponteiro;
    ponteiro = &count; // Passa o endereço de 'count' para 'ponteiro'
    printf("%X", *ponteiro);
    ponteiro++;
    printf("%X", *ponteiro);
    */
   
    /* Manipulação de blocos de bytes */
    unsigned short * ponteiro;
    ponteiro = &count;
    printf("%X", *ponteiro);

    printf("\n-------------\n");

    /* Matrizes e ponteiros */
    char txt[] = {'A', 'B', 'C', 0}; // é o mesmo que "ABC" (uma string é uma sequencia de caracteres com o zero no final)
    print(txt);

    return 0;
}