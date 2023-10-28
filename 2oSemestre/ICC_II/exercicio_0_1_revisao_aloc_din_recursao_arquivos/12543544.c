/*
 * Danielle Modesti
 * No USP: 12543544
 * Revisando Alocacao Dinamica, Recursao e Arquivos
 * > percorre um labirinto recursivamente ate a saida
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCKED '#'
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
int count_people(matrix_t *matrix);
int count_available_paths(int people_amt, matrix_t *matrix);
bool is_BLOCKED(matrix_t *matrix, point_t *p);
bool is_walked(matrix_t *matrix, point_t *p);
bool is_free_way(matrix_t *matrix, point_t *p);
bool cross_maze(matrix_t *matrix, point_t *start, int *route);
double exploration_percentage(int path_amt, int visited_amt);
void print_matrix(matrix_t *matrix, int ppl_amt, int paths, int route, double explored);
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
    point_t start;

    fscanf(labrinth_info," %d %d ", &labrinth.row_amt, &labrinth.col_amt);
    
    fscanf(labrinth_info," %d %d ", &start.row, &start.col);

    allocate_matrix(&labrinth, labrinth_info);

    fclose(labrinth_info);

    int people_amt;
    people_amt = count_people(&labrinth);

    int available_paths;
    available_paths = count_available_paths(people_amt, &labrinth);


    int route = 0;
    cross_maze(&labrinth, &start, &route);

    double exploration;
    exploration = exploration_percentage(available_paths, route);

    print_matrix(&labrinth, people_amt, available_paths, route, exploration);

    free_memory(labrinth_name, &labrinth);

    return EXIT_SUCCESS;
}

/*
* Para este exercicio, o nome do arquivo termina com EOF.
* 
*/

char *read_file_name() {
    char *file_name = NULL;
    char curr_char;
    int file_name_size = 0;

    do {
        curr_char = getchar();
        file_name_size++;

        file_name = (char *) realloc(file_name, sizeof(char) * file_name_size);

        if (curr_char != '\n' && curr_char != EOF) {
            file_name[file_name_size - 1] = curr_char;
        }

        else {
            file_name[file_name_size - 1] = '\0';
        }

    } while (curr_char != '\n' && curr_char != EOF);

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

int count_people(matrix_t *matrix) {
    int people_amt = 0;

    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            if (matrix->data[i][j] == BLOCKED) {
                people_amt++;
            }
        }
    }
    return people_amt;
}

int count_available_paths(int people_amt, matrix_t *matrix) {
    int matrix_size = matrix->row_amt * matrix->col_amt;
    int path_amount = matrix_size - people_amt;

    return path_amount;
}

/*
 * Funcao recursiva para caminhar pelo labirinto. Sai da funcao caso o ponto 
 * final seja percorrido (condicao de parada);
 * Em casos de bifurcacao, eh necessario desempilhar as recursoes da Stack, 
 * ate que haja outro caminho a se seguir, pois, ao desempilhar, o programa 
 * procura o proximo if depois do que acabou de leva lo a um beco sem saida. 
 * Isso continua em passo recursivo ate que se chegue ao fim do labirinto 
 * ('reached the end' = true)   =)
 * se NÃO (!) chegou ao final (reach_end) = true
 * ou seja, !reach_end = true (nao chegou ao final)
 * 
 * Testar os limites da matriz - voce conseguiu escapar se chegar em umas das
 * 4 extremidades - linha inicial, linha final; coluna inicial, coluna final.
 * 
 * 
*/

bool cross_maze(matrix_t *matrix, point_t *start, int *route) {
    matrix->data[start->row][start->col] = WALKED;
    (*route)++;

    if (matrix->data[0][start->col] == WALKED) {
        return true;
    }

    if (matrix->data[matrix->row_amt - 1][start->col] == WALKED) {
        return true;
    }

    if (matrix->data[start->row][0] == WALKED) {
        return true;
    }

    if (matrix->data[start->row][matrix->col_amt - 1] == WALKED) {
        return true;
    }

    point_t next;

    bool reach_end = false;

    next.row = start->row - 1;
    next.col = start->col;
    if (is_free_way(matrix, &next) && !reach_end) {
        reach_end = cross_maze(matrix, &next, route);
    }

    next.row = start->row;
    next.col = start->col + 1;
    if (is_free_way(matrix, &next) && !reach_end) {
        reach_end = cross_maze(matrix, &next, route);
    }

    next.row = start->row + 1;
    next.col = start->col;
    if (is_free_way(matrix, &next) && !reach_end) {
        reach_end = cross_maze(matrix, &next, route);
    }

    next.row = start->row;
    next.col = start->col - 1;
    if (is_free_way(matrix, &next) && !reach_end) {
        reach_end = cross_maze(matrix, &next, route);
    }

    return reach_end;
}

bool is_BLOCKED(matrix_t *matrix, point_t *p) {
    return matrix->data[p->row][p->col] == BLOCKED;
}

bool is_walked(matrix_t *matrix, point_t *p) {
    return matrix->data[p->row][p->col] == WALKED;
}

bool is_free_way(matrix_t *matrix, point_t *p) {
    return !is_BLOCKED(matrix, p) && !is_walked(matrix, p);
}

/* Atencao, este calculo considera o resultado de uma divisao inteira, apesar
* de seu resultado ser armazenado em uma variavel double.
*
*/

double exploration_percentage(int path_amt, int visited_amt) {
    double explored_percentage = (visited_amt * 100 / path_amt);

    return explored_percentage;
}

void print_matrix(matrix_t *matrix, int ppl_amt, int paths, int route, double explored) {
    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            printf("%c", matrix->data[i][j]);
        }
        printf("\n");
    }

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", ppl_amt);
    printf("----Numero total de caminhos validos:   %d\n", paths);
    printf("----Numero total de caminhos visitados: %d\n", route);
    printf("----Exploracao total do labirinto: %.1lf%%\n", explored);
}

void free_memory(char *file_name, matrix_t *matrix) {
    free(file_name);

    for (int i = 0; i < matrix->row_amt; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}