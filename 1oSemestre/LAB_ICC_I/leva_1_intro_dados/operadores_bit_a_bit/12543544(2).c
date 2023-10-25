#include <stdio.h>

int main() {
    unsigned int a, b;
    int and, or, xor, complement_a, complement_b, a_rightshift, b_rightshift;

    scanf("%d", &a); // long unsigned int
    scanf("%d", &b);

    // Operadores bit a bit - bitwise - são usados para manipular bits de numeros int
    // Manipularemos a codificação binária de a e b
    // Comparação com &, |, ^

    and = a & b;
    printf("%d\n", and);

    or = a | b;
    printf("%d\n", or);

    xor = a ^ b; // Cuidado para não confundir com símbolo usualmente associado à potência. Temos a biblioteca da math.h e o pow()
    printf("%d\n", xor);

    complement_a = ~a; // Inversão de todos os bits de a
    printf("%d\n", complement_a);

    complement_b = ~b;
    printf("%d\n", complement_b);

    a_rightshift = a >> 2; // Mudar os bits do primeiro operando, com o segundo operando decidindo o numero de posiçoes modificado
    printf("%d\n", a_rightshift);

    b_rightshift = b << 2;
    printf("%d\n", b_rightshift); 

    return 0;
}