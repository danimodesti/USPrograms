// Danielle Modesti
// No USP: 12543544
// Trabalho I: usar operadores, condicionais, loops e vetores

#include <stdio.h>

#define SIZE 512

#define HLT 0 // Se zero e lido como operacao, encerre a execucao
#define ADD 1 
#define MUL 2 
#define CLT 3 
#define CEQ 4 
#define JMP 5 
#define JEQ 6
#define CPY 7
#define PUT 8
#define PTN 9

int main() {
    int tape[SIZE]; // Fita percorrida   

    for (int address = 0; address < SIZE; address++) scanf("%d", &tape[address]);

    // Percorra a fita e realiza as operacoes
    printf("Saida do programa:\n");
    
    int address = 0;
    while (tape[address] != HLT) { // se entrar em HLT, encerre a leitura
        if (tape[address] == ADD) {
            // Declarei os tipos de dado assim porque so os uso nesses procedimentos
            int argument_1 = tape[address + 1];
            int argument_2 = tape[address + 2];
            int argument_3 = tape[address + 3];

            tape[argument_3] = tape[argument_1] + tape[argument_2];

            address = address + 4;
        }
        else if (tape[address] == MUL) {
            int argument_1 = tape[address + 1];
            int argument_2 = tape[address + 2];
            int argument_3 = tape[address + 3];

            tape[argument_3] = tape[argument_1] * tape[argument_2];

            address = address + 4;
        }
        else if (tape[address] == CLT) {
            int argument_1 = tape[address + 1];
            int argument_2 = tape[address + 2];
            int argument_3 = tape[address + 3];

            // Isso ja retorna 1 se tape[argument_1] < tape[argument_2]
            // e 0 se >=
            tape[argument_3] = (tape[argument_1] < tape[argument_2]);
            // if (tape[argument_1] < tape[argument_2]) tape[argument_3] = 1;
            // else tape[argument_3] = 0;

            address = address + 4;
        }
        else if (tape[address] == CEQ) {
            int argument_1 = tape[address + 1];
            int argument_2 = tape[address + 2];
            int argument_3 = tape[address + 3];

            // Isso ja retorna 1 se tape[argument_1] == tape[argument_2]
            // e 0 se !=
            tape[argument_3] = (tape[argument_1] == tape[argument_2]);
            // if (tape[argument_1] == tape[argument_2]) tape[argument_3] = 1;
            // else tape[argument_3] = 0;

            address = address + 4;
        }        
        else if (tape[address] == JMP) {
            int argument_1 = tape[address + 1];

            address = tape[argument_1];
        } 
        else if (tape[address] == JEQ) {
            int argument_1 = tape[address + 1]; 
            int argument_2 = tape[address + 2]; 

            if (tape[argument_1] != 0) address = tape[argument_2];
            else address = address + 3;
        }
        else if (tape[address] == CPY) {
            int argument_1 = tape[address + 1];
            int argument_2 = tape[address + 2];

            tape[argument_2] = tape[argument_1]; 

            address = address + 3;
        }
        else if (tape[address] == PUT) {
            int argument_1 = tape[address + 1]; 
 
            printf("%c", tape[argument_1]); 

            address = address + 2;
        }
        else if (tape[address] == PTN) {
            int argument_1 = tape[address + 1];

            printf("%d", tape[argument_1]);

            address = address + 2;
        }
    }

    printf("\nEstado final da fita:\n");
    for (int address = 0; address < SIZE; address++) printf("%d\n", tape[address]);

    return 0;
}