//incluir biblio para comandos de entrada e saida como scanf e printf
#include <stdio.h>

//funçao principal
int main() {
    //declarar variaveis; no caso, as temperaturas
    float fahrenheit;
    float celsius;

    //leia o valor digitado em fahrenheit
    scanf("%f", &fahrenheit);
    //converta para celsius
    celsius = 5*(fahrenheit - 32)/9;
    //imprima valor convertido para celsius
    printf("%.2f\n", celsius);
    //fim do programa, retorne 0
    return 0;
}