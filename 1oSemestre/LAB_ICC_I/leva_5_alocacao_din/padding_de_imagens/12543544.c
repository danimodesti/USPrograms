// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int amt_rows, int amt_columns);
void free_matrix(int **matrix, int amt_rows);
void show_padding(int padding_size, int width, int *padding_row);

int main() {
    // Receba dados
    int image_width, image_height;
    scanf("%d %d", &image_width, &image_height);

    // Crie a matriz dinamica
    int **image_dimension;
    image_dimension = allocate_matrix(image_height, image_width);

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            scanf("%d", &image_dimension[i][j]);
        }
    }

    // Tamanho do padding
    int padding;
    scanf("%d", &padding);

    // Criar um vetor de padding
    int *padding_row = calloc(image_width, sizeof(int));

    show_padding(padding, image_width, padding_row);

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < padding; j++) {
            printf("0 ");
        }
        for (int j = 0; j < image_width; j++) {
            printf("%d ", image_dimension[i][j]);
        }
        for (int j = 0; j < padding; j++) {
            printf("0 ");
        }
        printf("\n");
    }

    show_padding(padding, image_width, padding_row);
    free(padding_row);

    printf("\n");
    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {
            printf("%d ", image_dimension[i][j]);
        }
        printf("\n");
    }    
    free_matrix(image_dimension, image_height);

    return 0;
}

int **allocate_matrix(int amt_rows, int amt_columns) {
    // Alocando a matriz na Heap
    int **matrix = (int**)malloc(amt_rows * sizeof(int*));

    for (int i = 0; i < amt_rows; i++) {
        matrix[i] = (int*)malloc(amt_columns * sizeof(int));
    }
    
    return matrix;
}
void free_matrix(int **matrix, int amt_rows) {
    for (int i = 0; i < amt_rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void show_padding(int padding_size, int width, int *padding_row) {
    for (int i = 0; i < padding_size; i++) {
        for (int j = 0; j < padding_size; j++) {
            printf("0 ");
        }
        for (int j = 0; j < width; j++) {
            printf("%d ", padding_row[j]);
        }
        for (int j = 0; j < padding_size; j++) {
            printf("0 ");
        }
        printf("\n");
    }
}
