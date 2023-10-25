/*
 * Danielle Modesti
 * No USP: 12543544
 * 
*/

#include <stdio.h>
#include <stdlib.h>

#define INCREMENT_INDEX_VALUE '+' 
#define DECREMENT_INDEX_VALUE '-' 
#define INCREMENT_INDEX '>' 
#define DECREMENT_INDEX '<' 
#define PRINT_INDEX_VALUE_AS_ASCII '.' 
#define START_LOOP '['
#define STOP_LOOP ']'

int main() {
    // Para o compilador JIT de BF
    // Abrir arquivo temporario com extensao .c com um nome qualquer
    FILE *brainfuck_file = NULL;

    // Modo w porque queremos escrever no arquivo criado
    brainfuck_file = fopen("jit_gerado.c", "w");
    fprintf(brainfuck_file, "#include <stdio.h>\n\nint main() {\nchar memory_BF[30000];\n");
    fprintf(brainfuck_file, "int i = 0;\nfor (int j = 0; j < 30000; j++) {\nmemory_BF[j] = 0;\n}\n ");

    // -------- Etapa 2 ------
    // Para cada operacao BF, escreva o codigo em C correspondente no arquivo temporario
    // Primeiro, converter isso. Depois, escrever no arquivo
    char operation;
    while ((operation = getchar()) != EOF) {
        switch(operation) {
            case INCREMENT_INDEX_VALUE:
                fprintf(brainfuck_file, "memory_BF[i]++;\n");
                break;
            case DECREMENT_INDEX_VALUE:
                fprintf(brainfuck_file, "memory_BF[i]--;\n");
                break;
            case INCREMENT_INDEX:
                fprintf(brainfuck_file, "i++;\n");
                break;
            case DECREMENT_INDEX:  
                fprintf(brainfuck_file, "i--;\n");
                break;
            case PRINT_INDEX_VALUE_AS_ASCII:
                fprintf(brainfuck_file, "putchar(memory_BF[i]);\n");
                break;
            case START_LOOP:
                fprintf(brainfuck_file, "while (memory_BF[i]) {\n");
                break;
            case STOP_LOOP:
                fprintf(brainfuck_file, "}\n");
                break;
        }
    }
    // Fim da traducao
    // --------- Etapa 3 -----
    // Imprimir valores nao nulos da memoria no final do programa
    fprintf(brainfuck_file, "printf(\"\\n\"); ");
    fprintf(brainfuck_file, "for (int j = 0; j < 30000; j++) {\n");
    fprintf(brainfuck_file, "if (memory_BF[j] != 0) {\nprintf(\"%%d \", memory_BF[j]);\n}\n");
    fprintf(brainfuck_file, "}\n printf(\"\\n\");\n");

    // --------- Etapa 4 -----
    // Fechar o arquivo temporario
    fprintf(brainfuck_file, "return 0;\n}");
    fclose(brainfuck_file);

    // Rodar comandos a partir do meu programa, como se fosse no terminal
    // Compilar o codigo gerado com gcc e rodar o binario gerado
    system("gcc jit_gerado.c -o jit");
    system("./jit");

    return 0;
}