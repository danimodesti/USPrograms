#include <stdio.h>

int main() {
    // Entrada
    // Vetor dos caracteres do teclado. Ele terá 49 espaços a preencher
    char keyboard[49]; 

    // Preencher posições no vetor keyboard e gerar seus 49 caracteres
    for (int i = 0; i < 49; i++) {
        scanf("%c ", &keyboard[i]);
        // Quando chegar no último char, o programa ignora o \n (enter)
    }

    // Ler um inteiro com a quantidade de chars (codificados como inteiros) da
    // mensagem
    int amount_char;
    scanf("%d", &amount_char);

    // Receber a sequência com uma quantidade amount_char de inteiros
    int codificacao[amount_char];
    for (int i = 0; i < amount_char; i++) scanf("%d ", &codificacao[i]);

    // Saída
    // Fazer o mesmo processo para todos os [amount_char] espaços do vetor 
    // codificacao
    for (int i = 0; i < amount_char; i++) { 
        // Mas que processo fazer para traduzir?
        int translate = codificacao[i];
        if (keyboard[translate] == '_') printf(" ");
        else if (keyboard[translate] == 'E') printf("\n");
        else printf("%c", keyboard[translate]);
    }

    return 0;
}