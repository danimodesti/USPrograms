#include <stdio.h>

int main() {

    int ano;

    // Leia um ano
    scanf("%d", &ano);

    // Verificar se o ano e bissexto, ou seja, divisivel por 4
    if (ano % 4 == 0) printf("SIM\n");
    else printf("NAO\n");

    return 0;
}