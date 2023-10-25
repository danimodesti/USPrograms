// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h> // Funcoes como malloc() e free() dependem dessa biblio


char* readLine(); // Essa funcao retorna um ponteiro/endereco de char

int main() {
    int line_amount; 

    scanf("%d\n", &line_amount);

    char *single_line[line_amount]; // Aqui, eu crio um vetor de vetores de char (ou um vetor de strings)
    
    for (int i = 0; i < line_amount; i++) {
        single_line[i] = readLine(); // Salvando cada linha em um indice do vetor de strings
    }

    int valid_line;

    scanf("%d\n", &valid_line); // Quantas linhas sao validas?

    for (int i = 0; i < valid_line; i++) {
        int index;
        scanf("%d", &index); 
        printf("%s\n", single_line[index]);
    }

    // Liberar a memoria alocada na Heap - valores em cada indice de single_line
    for (int i = 0; i < line_amount; i++) 
        free(single_line[i]);

    return 0;
}

char* readLine() {
    char* line = NULL; 
    char current_char; 
    int line_size = 0; 

    do { 
        current_char = getchar();
        line_size++; 

        // Usar realloc para alocar novos espacos a cada iteracao do loop
        line = (char*) realloc(line, sizeof(char) * line_size); 

        if (current_char != '\n')
            line[line_size - 1] = current_char; 
        else
            line[line_size - 1] = '\0'; 
    } while (current_char != '\n'); 

    return line;
}