// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

// A matriz sempre tem 32 linhas e 64 colunas. O que nao eh preenchido, eh espaco em branco
#define ROW 32

#define COLUMN 65 // 64 chars + \n

int main() {
    char conveyor[ROW][COLUMN];

    // De me uma esteira a percorrer
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            scanf("%c", &conveyor[i][j]);
        }
    }

    // Encontre o inicio da esteira - Plinio anda a partir de [
    int walking_Plinio_col = 0;

    for (int j = 0; j < COLUMN; j++) {
        if (conveyor[0][j] == '[') {
            walking_Plinio_col = j + 2; // Percorre so par. Comece 2 posicoes apos [
            break;
        }
    }

    // Plinio percorre a esteira a partir do indice conveyor[0][walking_Plinio_col]
    // Vamos percorrer a partir desse ponto e ir fazendo os comandos, substituindo valores qd necessario etc

    // So faz algo se for indice par, pois os impares tratam espacos
    
    int walking_Plinio_row = 0; // A row sempre comeca em zero

    // Preciso tratar o #, que nao se transforma em ponto. Alem disso, ele funciona como o comando imediatamente anterior a ele
    char do_same;
    
    // Eu nao sei quantas vezes isso sera executado. Tem condicoes especificas de parada, nao sei em que posicao se encontram esses casos
    // Para dar loop, precisa ser, simultaneamente, false para ']' E false para '.' E false para ' ' -> situacoes nas quais o Plinio para de percorrer, ou seja, para o loop
    while (conveyor[walking_Plinio_row][walking_Plinio_col] != ']' && conveyor[walking_Plinio_row][walking_Plinio_col] != '.' && conveyor[walking_Plinio_row][walking_Plinio_col] != ' ') { // Condicoes de parada: fim da esteira, ponto ja percorrido
            if (conveyor[walking_Plinio_row][walking_Plinio_col] != '#') 
                do_same = conveyor[walking_Plinio_row][walking_Plinio_col]; // Salve cada posicao pela qual Plinio passa, caso precise inserir como copia no #

            switch (conveyor[walking_Plinio_row][walking_Plinio_col]) { // O que Plinio faz para cada tipo de char?
                case '>':
                    conveyor[walking_Plinio_row][walking_Plinio_col] = '.';
                    walking_Plinio_col += 2;
                    break;
                case '<':
                    conveyor[walking_Plinio_row][walking_Plinio_col] = '.';
                    walking_Plinio_col -= 2;
                    break;
                case '^':
                    conveyor[walking_Plinio_row][walking_Plinio_col] = '.';
                    walking_Plinio_row--;
                    break;
                case 'v':
                    conveyor[walking_Plinio_row][walking_Plinio_col] = '.';
                    walking_Plinio_row++;
                    break;
                case '#': // Copia o comportamento do anterior e nao se altera
                    if (do_same == '>')
                        walking_Plinio_col += 2;
                    else if (do_same == '<')
                        walking_Plinio_col -= 2;
                    else if (do_same == '^')
                        walking_Plinio_row--;
                    else if (do_same == 'v') {
                        walking_Plinio_row++;
                    }
                    break;
                default:
                    break;
            }
    }
    
    // Plinio diz:
    if (conveyor[walking_Plinio_row][walking_Plinio_col] == '.')
        printf("Loop infinito.\n");
    else if (conveyor[walking_Plinio_row][walking_Plinio_col] == ']')
        printf("Ok.\n");
    else // Nao acha final nem da loop, ou seja, nao termina!
        printf("Falha na esteira.\n");

    // -------------------------------------------------------------------------
    // Mostre a esteira final
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%c", conveyor[i][j]);
        }
    }

    return 0;
}