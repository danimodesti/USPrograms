// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    double a, b, c, d, media; 
    // Variaveis double tem mais bits e conseguem, portanto, representar numeros
    // com maior precisao que float

    // Entrada
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    // Processamento
    if (a <= b && a <= c && a <= d) {
        media = (b + c + d) / 3;
    }
    else if (b <= a && b <= c && b <= d) {
        media = (a + c + d) / 3;
    }
    else if (c <= a && c <= b && c <= d) {
        media = (a + b + d) / 3;
    }
    else {
        media = (a + b + c) / 3;
    }

    // Saida
    printf("%.4lf\n", media);

    return 0;
}