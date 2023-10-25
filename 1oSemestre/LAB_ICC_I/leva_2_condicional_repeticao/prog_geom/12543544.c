// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    float a1, q, an, sn, potencia; // Primeiro termo e razao
    int n, i; // Numero total de termos


    scanf("%f %f %d", &a1, &q, &n);

    // Preciso calcular pot = q elevado a (n-1)
    potencia = 1;
    for (i = 0; i < (n - 1); i++) {
        potencia = potencia * q;
        an = a1 * potencia;
    }

    // Preciso calcular pot = q elevado a n
    potencia = 1;
    for (i = 0; i < n; i++) {
        potencia = potencia * q;
        sn = a1 * (potencia - 1) / (q - 1);
    }

    printf("%.2f\n%.2f\n", an, sn);

    return 0;
}