// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

#define MATRIX_ROWS 32
#define MATRIX_COLUMNS 64

#define CEMENT '@'
#define AIR ' '
#define WATER '~'
#define SAND '#'

char simulation_state[MATRIX_ROWS][MATRIX_COLUMNS];

// Onde tiver IS_AIR(i, j), entenda que o elemento da matriz eh ' '
#define IS_AIR(i, j) (simulation_state[i][j] == AIR)
#define IS_WATER(i, j) (simulation_state[i][j] == WATER)
#define IS_SAND(i, j) (simulation_state[i][j] == SAND)

void apply_physics();

int main() {
    // Inicializar a matriz com ar em todas as posicoes
    for (int i = 0; i < MATRIX_ROWS; i++) 
        for (int j = 0; j < MATRIX_COLUMNS; j++) 
            simulation_state[i][j] = AIR;

    // Quantidade de vezes que imprimimos a matriz do estado da simulacao de particulas
    int frame_amount;
    scanf("%d", &frame_amount);

    int count = 0;
    while (count < frame_amount) {
        int current_frame, x_coordinate, y_coordinate;
        char new_particle;
        int read_input = scanf(" %d: %d %d %c", &current_frame, &x_coordinate, &y_coordinate, &new_particle);

        if (read_input == EOF) 
            current_frame = frame_amount; 
        
        /* Calcula todos os frames ate o proximo frame onde queremos criar uma particula.
        Queremos parar neste frame current_frame e mudar a matriz, adicionando a nova particula
        Roda um determinado numero de frames ate chegar no frame em que quero adicionar a particula*/
        while (count < current_frame) {
            printf("frame: %d\n", count + 1);
            for (int i = 0; i < MATRIX_ROWS; i++) {
                for (int j = 0; j < MATRIX_COLUMNS; j++)
                    printf("%c", simulation_state[i][j]);
                printf("\n");
            }
            apply_physics();
            count++;
        }
        // Se achamos no scanf uma particula a ser criada, crie ela.
        if (read_input != EOF)   
            simulation_state[y_coordinate][x_coordinate] = new_particle;
    }

    return 0;
}

// Atualize regras da areia, com trocas diretas
void swap_sand(char copy_frame[MATRIX_ROWS][MATRIX_COLUMNS], int i, int j) {
    if (i + 1 < MATRIX_ROWS && (IS_WATER(i + 1, j) || IS_AIR(i + 1, j))) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i + 1][j];
        copy_frame[i + 1][j] = tmp;
    }
    else if (i + 1 < MATRIX_ROWS && j - 1 >= 0 && (IS_WATER(i + 1, j - 1) || IS_AIR(i + 1, j - 1))) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i + 1][j - 1];
        copy_frame[i + 1][j - 1] = tmp;
    }
    else if (i + 1 < MATRIX_ROWS && j + 1 < MATRIX_COLUMNS && (IS_WATER(i + 1, j + 1) || IS_AIR(i + 1, j + 1))) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i + 1][j + 1];
        copy_frame[i + 1][j + 1] = tmp;
    }
}

// Atualize regras da agua, com trocas diretas
void swap_water(char copy_frame[MATRIX_ROWS][MATRIX_COLUMNS], int i, int j) {
    if (i + 1 < MATRIX_ROWS && IS_AIR(i + 1, j)) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i + 1][j];
        copy_frame[i + 1][j] = tmp;
    }
    else if (i + 1 < MATRIX_ROWS && j - 1 >= 0 && IS_AIR(i + 1, j - 1)) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i + 1][j - 1];
        copy_frame[i + 1][j - 1] = tmp;
    }
    else if (i + 1 < MATRIX_ROWS && j + 1 < MATRIX_COLUMNS && IS_AIR(i + 1, j + 1)) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i + 1][j + 1];
        copy_frame[i + 1][j + 1] = tmp;
    }
    else if (j - 1 >= 0 && IS_AIR(i, j - 1)) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i][j - 1];
        copy_frame[i][j - 1] = tmp;
    }
    else if (j + 1 < MATRIX_COLUMNS && IS_AIR(i, j + 1)) {
        char tmp = copy_frame[i][j]; 
        copy_frame[i][j] = copy_frame[i][j + 1];
        copy_frame[i][j + 1] = tmp;
    }
}

/* A atualizacao de fisica deve ser feita em 1 loop. Verificamos as regras da areia e da agua dentro dele
Alterar apenas a matriz de copia
Verificar apenas na matriz original -> isso eh necessario para nao verificar coisas ja atualizadas. 
Essa matriz esta em 'previous state' */
void apply_physics() {
    char copy_previous_frame[MATRIX_ROWS][MATRIX_COLUMNS];
    for (int i = 0; i < MATRIX_ROWS; i++) 
        for (int j = 0; j < MATRIX_COLUMNS; j++) 
            copy_previous_frame[i][j] = simulation_state[i][j];

    /* Percorra a matriz de copia do topo para baixo apenas uma vez, da esquerda para a direita. 
    Atualize de uma vez todas as part., de acordo com as suas regras, na matriz de copia
    Para o proximo frame, atualize a matriz simulation_state com o conteudo de copia :)*/
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLUMNS; j++) {
            /* Verificacao sempre feita no estado atual do simulador de particulas original. 
            O estado atual atualiza o prox., que esta em copia */
            if (IS_SAND(i, j)) 
                swap_sand(copy_previous_frame, i, j);
            else if (IS_WATER(i, j))
                swap_water(copy_previous_frame, i, j);
        }
    }
    // Copie o conteudo da matriz de copia de volta para a matriz do estado de simulacao
    for (int i = 0; i < MATRIX_ROWS; i++) 
        for (int j = 0; j < MATRIX_COLUMNS; j++) 
            simulation_state[i][j] = copy_previous_frame[i][j];
}