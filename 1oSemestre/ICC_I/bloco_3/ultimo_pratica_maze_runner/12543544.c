/*
 * Danielle Modesti
 * No USP: 12543544
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WALL '#'
#define WALKED '*'

typedef struct Matrix {
    char **data;
    int row_amt;
    int col_amt;
} matrix_t;

typedef struct Point {
    int row;
    int col;
} point_t;

char *read_file_name();
void allocate_matrix(matrix_t *matrix, FILE *stream);
bool is_wall(matrix_t *matrix, point_t p);
bool is_walked(matrix_t *matrix, point_t p);
bool is_free_way(matrix_t *matrix, point_t p);
bool cross_maze(matrix_t *matrix, point_t start, point_t end, int *steps);
void print_matrix(matrix_t *matrix, int steps);
void free_memory(char *file_name, matrix_t *matrix);

int main() {
    char *labrinth_name = read_file_name();
    
    FILE *labrinth_info = NULL;
    
    labrinth_info = fopen(labrinth_name, "r");

    if (labrinth_info == NULL) {
        printf("Falha na abertura do arquivo =(\n");
        exit(EXIT_FAILURE);
    }

    matrix_t labrinth;
    point_t start, end;

    fscanf(labrinth_info," %d %d ", &labrinth.row_amt, &labrinth.col_amt);
    fscanf(labrinth_info," %d %d ", &start.row, &start.col);
    fscanf(labrinth_info," %d %d ", &end.row, &end.col);

    allocate_matrix(&labrinth, labrinth_info);

    fclose(labrinth_info);

    int steps = 0;
    cross_maze(&labrinth, start, end, &steps);

    print_matrix(&labrinth, steps);

    free_memory(labrinth_name, &labrinth);

    return EXIT_SUCCESS;
}

char *read_file_name() {
    char *file_name = NULL;
    char curr_char;
    int file_name_size = 0;

    do {
        curr_char = getchar();
        file_name_size++;

        file_name = (char *) realloc(file_name, sizeof(char) * file_name_size);

        if (curr_char != '\n') {
            file_name[file_name_size - 1] = curr_char;
        }

        else {
            file_name[file_name_size - 1] = '\0';
        }

    } while (curr_char != '\n');

    return file_name;
}

void allocate_matrix(matrix_t *matrix, FILE *stream) {
    matrix->data = (char **) malloc(sizeof(char *) * matrix->row_amt);

    for (int i = 0; i < matrix->row_amt; i++) {
        matrix->data[i] = (char *) malloc(sizeof(char) * (matrix->col_amt));
    }

    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            fscanf(stream, "%c", &matrix->data[i][j]);
        }
        fscanf(stream, "\n");
    }
}

/*
 * Funcao recursiva para caminhar pelo labirinto. Sai da funcao caso o ponto 
 * final seja percorrido (condicao de parada);
 * Em casos de bifurcacao, eh necessario desempilhar as recursoes da Stack, 
 * ate que haja outro caminho a se seguir, pois, ao desempilhar, o programa 
 * procura o proximo if depois do que acabou de leva lo a um beco sem saida. 
 * Isso continua em passo recursivo ate que se chegue ao fim do labirinto 
 * ('reached the end' = true)   =)
 * 
*/
bool cross_maze(matrix_t *matrix, point_t start, point_t end, int *steps) {
    matrix->data[start.row][start.col] = WALKED;
    (*steps)++;

    if (matrix->data[end.row][end.col] == WALKED) {
        return true;
    }

    point_t next;

    bool reach_end = false;

    next.row = start.row;
    next.col = start.col - 1;
    if (is_free_way(matrix, next) && !reach_end) {
        reach_end = cross_maze(matrix, next, end, steps);
    }

    next.row = start.row + 1;
    next.col = start.col;
    if (is_free_way(matrix, next) && !reach_end) {
        reach_end = cross_maze(matrix, next, end, steps);
    }

    next.row = start.row;
    next.col = start.col + 1;
    if (is_free_way(matrix, next) && !reach_end) {
        reach_end = cross_maze(matrix, next, end, steps);
    }

    next.row = start.row - 1;
    next.col = start.col;
    if (is_free_way(matrix, next) && !reach_end) {
        reach_end = cross_maze(matrix, next, end, steps);
    }

    return reach_end;
}

bool is_wall(matrix_t *matrix, point_t p) {
    return matrix->data[p.row][p.col] == WALL;
}

bool is_walked(matrix_t *matrix, point_t p) {
    return matrix->data[p.row][p.col] == WALKED;
}

bool is_free_way(matrix_t *matrix, point_t p) {
    return !is_wall(matrix, p) && !is_walked(matrix, p);
}

void print_matrix(matrix_t *matrix, int steps) {
    printf("Caminho final: \n");
    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            printf("%c", matrix->data[i][j]);
        }
        printf("\n");
    }

    printf("Passos percorridos: %d\n", steps);
}

void free_memory(char *file_name, matrix_t *matrix) {
    free(file_name);

    for (int i = 0; i < matrix->row_amt; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}