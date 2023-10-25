// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

#define LIVING_CELL 'x'
#define DEAD_CELL '.'
#define VON_NEUMANN_NEIGHBOURHOOD 'N'
#define MOORE_NEIGHBOURHOOD 'M'

char** allocate_matrix(int row_amount, int column_amount);
void free_matrix(char **matrix, int row_amount);
char **copy_previous_generation(int row_amount, int column_amount, char **original_matrix);
void apply_Moore(int row_amount, int column_amount, char **original_matrix);
void apply_von_Neumann(int row_amount, int column_amount, char **original_matrix);

int main() {
    int board_rows, board_columns, board_generation;
    char board_type;
    char **board_dimension;

    scanf("%d %d %d %c\n", &board_rows, &board_columns, &board_generation, &board_type);

    if (board_rows <= 0 || board_columns <= 0 || board_generation <= 0 || 
        (board_type != MOORE_NEIGHBOURHOOD && board_type != VON_NEUMANN_NEIGHBOURHOOD)) {
        printf("Dados de entrada apresentam erro.\n");
        return 0;
    }

    board_dimension = allocate_matrix(board_rows, board_columns);

    for (int i = 0; i < board_rows; i++) 
        for (int j = 0; j < board_columns + 1; j++) 
            scanf("%c", &board_dimension[i][j]);
        
    // Comecamos na geracao zero
    int count_generation = 0;

    while (count_generation < board_generation) {
        // Qual eh o metodo de checagem para a proxima geracao?
        if (board_type == MOORE_NEIGHBOURHOOD)
            apply_Moore(board_rows, board_columns, board_dimension);
        else if (board_type == VON_NEUMANN_NEIGHBOURHOOD)
            apply_von_Neumann(board_rows, board_columns, board_dimension); 

        count_generation++;
    }
    
    // Ver a matriz no frame final
    for (int i = 0; i < board_rows; i++) 
        for (int j = 0; j < board_columns + 1; j++)
            printf("%c", board_dimension[i][j]);

    free_matrix(board_dimension, board_rows);

    return 0;
}

char** allocate_matrix(int row_amount, int column_amount) {
    // Alocando a matriz na Heap
    char **matrix = (char**)malloc(row_amount * sizeof(char*));

    for (int i = 0; i < row_amount; i++)
        matrix[i] = (char*)malloc((column_amount + 1) * sizeof(char));
    
    return matrix;
}

void free_matrix(char **matrix, int row_amount) {
    for (int i = 0; i < row_amount; i++)
        free(matrix[i]);
    
    free(matrix);
}

char **copy_previous_generation(int row_amount, int column_amount, char **original_matrix) {
    // Criando uma matriz de copia, alocada dinamicamente
    char **copy_previous_generation;

    copy_previous_generation = allocate_matrix(row_amount, column_amount);

    for (int i = 0; i < row_amount; i++) 
        for (int j = 0; j < column_amount + 1; j++) 
            copy_previous_generation[i][j] = original_matrix[i][j];

    return copy_previous_generation;
}

void apply_Moore(int row_amount, int column_amount, char **original_matrix) {
    // Obtenha a matriz de copia
    char **copy_matrix = copy_previous_generation(row_amount, column_amount, original_matrix);
    // Faca a logica de vizinhanca de Moore
    for (int i = 0; i < row_amount; i++) {
        for (int j = 0; j < column_amount; j++) {
            // Checar os arredores
            int count_living_around = 0;

            if (original_matrix[(i - 1 + row_amount) % row_amount][(j - 1 + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i - 1 + row_amount) % row_amount][(j + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i - 1 + row_amount) % row_amount][(j + 1 + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + row_amount) % row_amount][(j - 1 + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + row_amount) % row_amount][(j + 1 + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + 1 + row_amount) % row_amount][(j - 1 + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + 1 + row_amount) % row_amount][(j + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + 1 + row_amount) % row_amount][(j + 1 + column_amount) % column_amount] 
                == LIVING_CELL)
                count_living_around++;
            /* Com base na quantidade de celulas vivas, se a celula nao morrer pelas condicoes seguintes,
            continue viva na proxima geracao */
            if (original_matrix[i][j] == LIVING_CELL) {
                if (count_living_around < 2 || count_living_around > 3)
                    copy_matrix[i][j] = DEAD_CELL;
            }

            // Para a celula morta
            else {
                if (count_living_around == 3)
                    copy_matrix[i][j] = LIVING_CELL;
            }
        }
    }
    // Copie o conteudo da matriz de copia de volta para a matriz do estado de simulacao
    for (int i = 0; i < row_amount; i++) 
        for (int j = 0; j < column_amount; j++) 
            original_matrix[i][j] = copy_matrix[i][j];

    free_matrix(copy_matrix, row_amount);
}

void apply_von_Neumann(int row_amount, int column_amount, char **original_matrix) {
    // Obtenha a matriz de copia
    char **copy_matrix = copy_previous_generation(row_amount, column_amount, original_matrix);
    // Faca a logica de vizinhanca de von Neumann
    for (int i = 0; i < row_amount; i++) {
        for (int j = 0; j < column_amount; j++) {
            // Checar os arredores
            int count_living_around = 0;

            if (original_matrix[(i - 2 + row_amount) % row_amount][j % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i - 1 + row_amount) % row_amount][j % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[i % row_amount][(j - 2 + column_amount) % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[i % row_amount][(j - 1 + column_amount) % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[i % row_amount][(j + 1 + column_amount) % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[i % row_amount][(j + 2 + column_amount) % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + 1 + row_amount) % row_amount][j % column_amount] == LIVING_CELL)
                count_living_around++;
            if (original_matrix[(i + 2 + row_amount) % row_amount][j % column_amount] == LIVING_CELL)
                count_living_around++;
            /* Com base na quantidade de celulas vivas, se a celula nao morrer pelas condicoes seguintes,
            continue viva na proxima geracao */
            if (original_matrix[i][j] == LIVING_CELL) {
                if (count_living_around < 2 || count_living_around > 3)
                    copy_matrix[i][j] = DEAD_CELL;
            }

            // Para a celula morta
            else {
                if (count_living_around == 3)
                    copy_matrix[i][j] = LIVING_CELL;
            }
        }
    }
    // Copie o conteudo da matriz de copia de volta para a matriz do estado de simulacao
    for (int i = 0; i < row_amount; i++) 
        for (int j = 0; j < column_amount; j++) 
            original_matrix[i][j] = copy_matrix[i][j];

    free_matrix(copy_matrix, row_amount);
}