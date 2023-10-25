// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    int n_linhas = 0;
    int n_palavras = 0;
    int n_chars = 0;
    char char_lido;
    int eh_palavra = 0; // Variavel de controle. Verifica se esta percorrendo uma palavra. 0 = nao; 1 = sim

    while (scanf("%c", &char_lido) != EOF) { // Pare de ler quando encontrar EOF

        // Conte pula linhas
        if (char_lido == '\n') {
            n_linhas++;
        }

        // Conte palavras. 
        if (char_lido == ' ' || char_lido == '\t' || char_lido == '\n' || char_lido == '\r') {
            eh_palavra = 0; // Nao percorre palavra
        }
        else if (eh_palavra == 0) { // Se nao rodou a condicao anterior, eh uma parte de palavra. Porem, o char anterior nao era parte de string, ja q ehpalavra == 0 nesse ponto
            eh_palavra = 1; // Se nao rodou a condicao do primeiro if, eh um char que constitui a string, entao uma palavra eh percorrida
            n_palavras++; // Se uma palavra eh percorrida, incremente o numero de palavras. Precisa fazer assim pq ha casos teste que nao terminam em ehpalavra == 0, nao ha char especial como \n no final, p. ex.
        }

        // Conte caracteres
        n_chars++;
    }

    printf("Linhas\tPalav.\tCarac.\n");
    printf("%d\t%d\t%d\n", n_linhas, n_palavras, n_chars);

    return 0;
}