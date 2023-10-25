// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    int numero1, numero2, i, potencia;
    potencia = 1;

    scanf("%d %d", &numero1, &numero2);

    for (i = 0; i < numero2; i++) {
        potencia = potencia * numero1;
    }
    
    printf("%d\n", potencia);

    return 0;
}