/*
 * Nome: Danielle Modesti
 * No USP: 12543544
 * Codigo do Curso: SCC0201
 * Disciplina: Introducao a Ciencia da Computacao II - 2° Semestre de 2021
 * [E02 - 02.1] Exercicio Modulo 2 - Compressao de Imagens com Quad Tree
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    int **data;
    int order;
} matrix_t;

bool allocate_data(matrix_t **image_to_compress, int square_matrix_size);
void read_data(matrix_t *image_to_compress);
bool check_values_equality(matrix_t *image_to_compress, int start_row, int end_row, int start_col, int end_col);
void recursive_checking(matrix_t *image_to_compress, int start_row, int end_row, int start_col, int end_col);
void free_data(matrix_t **image_to_compress);

int main() {
    // Receber entrada
    matrix_t *image_to_compress = NULL;
    int row_amt, col_amt;
    scanf("%d %d", &row_amt, &col_amt);

    bool is_valid_alloc = allocate_data(&image_to_compress, row_amt);
    if (!is_valid_alloc) {
        return EXIT_FAILURE;
    }

    read_data(image_to_compress);

    // Fazer quad tree
    recursive_checking(image_to_compress, 0, row_amt - 1, 0, col_amt - 1);
    printf("\n");

    free_data(&image_to_compress);

    return EXIT_SUCCESS;
}

// Alocar memoria dinamicamente
bool allocate_data(matrix_t **image_to_compress, int square_matrix_size) {
    *image_to_compress = (matrix_t *) malloc(sizeof(matrix_t));

    if (!(*image_to_compress)) {
        return false;
    }

    (*image_to_compress)->order = square_matrix_size;

    // Alocar linhas
    (*image_to_compress)->data = (int **) malloc((*image_to_compress)->order * sizeof(int *));

    if (!(*image_to_compress)->data) {
        return false;
    }

    // Alocar colunas
    for (int i = 0; i < (*image_to_compress)->order; i++) {
        (*image_to_compress)->data[i] = (int *) malloc((*image_to_compress)->order * sizeof(int));
    }

    return true;
}

// Ler conteudo da matriz
void read_data(matrix_t *image_to_compress) {
    for (int i = 0; i < image_to_compress->order; i++) {
        for (int j = 0; j < image_to_compress->order; j++) {
            scanf("%d", &image_to_compress->data[i][j]);
        }
    }
}

// Checar se todos os valores da regiao percorrida sao iguais. 
bool check_values_equality(matrix_t *image_to_compress, int start_row, int end_row, int start_col, int end_col) {
    // Supor que os valores sao os mesmos
    bool are_equal = true;

    int value_to_cmp = image_to_compress->data[start_row][start_col];

    // Percorrer o quadrante e conferir se so temos valores iguais
    int i = start_row;
    int j = start_col + 1;
    while (i <= end_row && are_equal) {
        while (j <= end_col && are_equal) {
            are_equal = (image_to_compress->data[i][j] == value_to_cmp);
            j++;
        }

        j = start_col;
        i++;
    }

    return are_equal;
}

// Se os valores checados nao forem iguais, diminuir a area de busca ate
// conseguir tal condicao ou ate ter apenas um unico valor na area de busca.
void recursive_checking(matrix_t *image_to_compress, int start_row, int end_row, int start_col, int end_col) {
    // Caso base
    if (check_values_equality(image_to_compress, start_row, end_row, start_col, end_col)) {
        // Mostre o no folha
        printf("%d ", image_to_compress->data[start_row][start_col]);
    }

    else {
        // Criar nova raiz
        printf("-1 ");

        // Quanto houve de variacao?
        // Cuidado para somar o ponto inicial, que nao eh necessariamente a posicao de index zero.
        int n = end_row - start_row + 1;

        // Chamar novos quatro quadrantes

        // 1o quadrante
        recursive_checking(image_to_compress, start_row, start_row + n/2 - 1, start_col, start_col + n/2 - 1);
        
        // 2o quadrante
        recursive_checking(image_to_compress, start_row, start_row + n/2 - 1, start_col + n/2, end_col);
        
        // 3o quadrante
        recursive_checking(image_to_compress, start_row + n/2, end_row, start_col, start_col + n/2 - 1);
        
        // 4o quadrante
        recursive_checking(image_to_compress, start_row + n/2, end_row, start_col + n/2, end_col);
    }
}

// Liberar  memoria dinamicamente alocada
void free_data(matrix_t **image_to_compress) {
    if (*image_to_compress) {
        if ((*image_to_compress)->data) {
            for (int i = 0; i < (*image_to_compress)->order; i++) {
                free((*image_to_compress)->data[i]);
            }
            free((*image_to_compress)->data);
        }
        free(*image_to_compress);
        *image_to_compress = NULL;
    }
}