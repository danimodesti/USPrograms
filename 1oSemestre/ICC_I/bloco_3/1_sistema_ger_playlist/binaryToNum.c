#include <stdio.h>

// Soma polinomial que interpreta o valor binário como um valor numérico.
// Quanto mais próximo o valor de retorno, mais próximo seu binário está do ideal.
// Não há necessidade de entender o funcionamento dessa função.
//
// Parâmetros: Nome do arquivo (binFilename: char *)
// Retorno: Nada (void)
void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}
