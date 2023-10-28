#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_DIMENSION 8 // Sempre sera um tabuleiro de xadrez 8x8

// Variavel global para auxiliar no backtracking
// Cada uma das colunas do tabuleiro contem uma rainha. Inicializamos com -1 para
// sinalizar que nenhuma rainha ocupa aquela coluna.
// Indice = id da rainha 
// O id da rainha tambem eh dado pelo numero da linha do tabuleiro
int columns[BOARD_DIMENSION] = {-1,
                                -1,
                                -1,
                                -1,
                                -1,
                                -1,
                                -1,
                                -1
                               };

int max_possible_score = -1;

int **read_board();
void free_memory(int *board[BOARD_DIMENSION]);
void print_board_info(int **board);
int sum_points(int **board);
bool is_safe_spot(int queen, int potential_col);
void search_max_score(int **board, int queen);

int main() {
    int chessboard_amt;    
    scanf(" %d", &chessboard_amt);

    for (int i = 0; i < chessboard_amt; i++) { // O segundo caso so tem 1 board
        int **board = read_board(board);
        search_max_score(board, 0);
        printf("%5d\n", max_possible_score);

        max_possible_score = -1; // Resetar pontuacao para proxima board
        free_memory(board);
    }

    return EXIT_SUCCESS;
}

void search_max_score(int **board, int queen) {
    // Ja acabaram as rainhas a serem posicionadas
    if (queen == BOARD_DIMENSION) {
        // A maior pontuacao eh a encontrada atualmente ou a que esta armazenada?
        int curr_score = sum_points(board);
        if (curr_score > max_possible_score) {
            max_possible_score = curr_score;
        }
    }

    // Ainda nao acabaram as rainhas a serem posicionadas
    for (int col = 0; col < BOARD_DIMENSION; col++) {
        if (is_safe_spot(queen, col)) {
            columns[queen] = col; // Posicione a rainha nesta coluna
            search_max_score(board, queen + 1); // Posicione as proximas rainhas
        }
    }
}

bool is_safe_spot(int queen, int potential_col) {
    // Sempre seguro (primeira rainha - sem conflitos)
    if (queen == 0) {
        return true;
    }
    
    // Curr_row = rainha atacante
    for (int curr_row = 0; curr_row < queen; curr_row++) {
        // Conflito de colunas
        if (potential_col == columns[curr_row]) {
            return false;
        }

        // Conflito pelas diagonais
        int line_diff = queen - curr_row;

        // Para a linha na qual a 'queen' sera colocada, em qual(is) coluna(s)
        // ha ataque de outras rainhas?

        // Diagonal a esquerda
        if (potential_col == columns[curr_row] - line_diff) {
            return false;
        }

        // Diagonal a direita
        if (potential_col == columns[curr_row] + line_diff) {
            return false;
        }
    }

    return true;
}

int sum_points(int **board) {
    int total_points = 0;

    for (int i = 0; i < BOARD_DIMENSION; i++) {
        // Linha do board: indica a rainha
        // Coluna do board: o vetor global guarda, no indice, a rainha. O seu valor naquele indice
        // eh a coluna ocupada pela rainha i
        total_points += board[i][columns[i]];
    }

    return total_points;
}

int **read_board() {
    int **board = (int **) malloc(sizeof(int *) * BOARD_DIMENSION);
    
    for (int i = 0; i < BOARD_DIMENSION; i++) {
        board[i] = (int *) malloc(sizeof(int) * BOARD_DIMENSION);
    }

    for (int i = 0; i < BOARD_DIMENSION; i++) {
        for (int j = 0; j < BOARD_DIMENSION; j++) {
            scanf(" %d", &board[i][j]);
        }
    }

    return board;
}

void free_memory(int **board) {
    for (int i = 0; i < BOARD_DIMENSION; i++) {
        free(board[i]);
    }

    free(board);
}

void print_board_info(int **board) {
    printf("-- tabuleiro --\n");
    for (int i = 0; i < BOARD_DIMENSION; i++) {
        for (int j = 0; j < BOARD_DIMENSION; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}