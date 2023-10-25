// Biblioteca para comandos de entrada e saída, como printf e scanf
#include <stdio.h>

// Funçao principal do programa
int main() {
    // Peça para ler um número inteiro num dado pelo usuário, armazene na variável 
    int num;
    scanf("%d", &num);

    // Variável que conta a quantidade de divisores de num, entre 11, 13 e 19
    int cont = 0;

    if (num % 11 == 0) 
        cont++;

    if (num % 13 == 0) 
        cont++;

    if (num % 19 == 0) 
        cont++;

    // A partir do valor de cont,
    
    // Se o número não é divisível por nenhum dos 3 divisores, retornar o valor do número 
    if (cont == 0)
        printf("%d", num);

    // Se o número é divisível por um dos 3 divisores, retornar Ba no início
    if(cont == 1)
        printf("Ba");

    // Se o número for divisível por 11, retornar Ba
    if(num % 11 == 0)
        printf("Ba");

    // Se o número é divisível por dois dos 3 divisores, retornar Dum no meio
    if(cont == 2)
        printf("Dum");

    // Se o número for divisível por 13, retornar Dum
    if(num % 13 == 0)
        printf("Dum");

    // Se o número é divisível por três dos 3 divisores, retornar Tss no fim
    if(cont == 3)
        printf("Tss");

    // Se o número é divisível por 19, retornar Tss 
    if(num % 19 == 0)
        printf("Tss");

    printf("\n");

    return 0;
}