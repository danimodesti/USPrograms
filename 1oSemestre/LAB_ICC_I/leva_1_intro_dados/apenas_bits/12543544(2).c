#include <stdio.h>

int main() {
    int number; // Lembrando que um int tem 4 bytes de tamanho
    char shift_bits1, shift_bits2, shift_bits3, shift_bits4; // o char lê apenas um byte, ou seja, 8 bits - e os oito primeiros, menos significativos

    scanf("%d", &number); // Ler um número inteiro

    // Rotacionar os bits e ler os oito menos significativos, me aproveitando das características de um char
    shift_bits1 = number >> 24; // Descarte os 24 bits menos significativos
    shift_bits2 = number >> 16; // Guarde a segunda sequência de oito bits
    shift_bits3 = number >> 8; // Guarde a terceira sequência de oito bits
    shift_bits4 = number; // Guarde a última sequência de oito bits

    // Exiba os caracteres
    printf("%c%c%c%c", shift_bits1, shift_bits2, shift_bits3, shift_bits4);

    return 0;
}


