// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    long int a1, r, n, i, an, sn;

    // Em um caso teste, o resultado extrapola o numero de bytes
    // portanto, sn deve ser long int e, como fazemos operacoes com as outras
    // variaveis tambem, e preciso dar um casting nos seus tipos de dado

    scanf("%ld %ld %ld", &a1, &r, &n);

    for (i = 0; i < n; i++) { 
        an = a1 + r * i;
        sn = (a1 + an) * (i + 1) / 2;
    }
    
    printf("%ld\n%ld\n", an, sn);

    return 0;
}