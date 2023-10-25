#include <stdio.h>
#include <math.h>

int main() {
    float a, b, potencia;

    // Leitura da entrada padrão - teclado
    scanf("%f", &a);
    scanf(" %f", &b);

    // Processamento de dados
    potencia = pow(a, b); // Fazendo potência com a math.h

    // Impressão na saída padrão - monitor
    printf("%.4f\n", potencia);



    return 0;
}
