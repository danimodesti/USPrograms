#include <stdio.h>
#include <stdlib.h> // Para gerar números inteiros pseudoaleatórios, nesse caso

int main() {
    int row_a, column_a, row_b, column_b; // Indices
    
    // Entrada
    scanf("%d %d\n", &row_a, &column_a);
    scanf("%d %d\n", &row_b, &column_b);

    // Condicoes para nao multiplicacao: column_a != row_b ou ter row_a, row_b,
    // column_a, column_b <= 0
    // column_a = row_b, então só precisa checar row_b, se passou pela primeira
    // verificação de column_a = row_b
    if (column_a != row_b || row_a <= 0 || row_b <= 0 || column_b <= 0) { 
        printf("Valores invalidos para a multiplicacao.\n");
        return 0;
    }

    int seed;
    scanf("%d", &seed); // Com base nessa seed, geraremos elementos aleatórios nas matrizes A e B

    // Processamento
    // Definicao da seed de aleatoriedade
    srand(seed);

    // Caso nao de nenhum problema, leia a seed e as declare as matrizes
    int matrix_A[row_a][column_a];
    // Preenchendo a matriz A   
    for (int i = 0; i < row_a; i++) {
        for (int j = 0; j < column_a; j++) {
            matrix_A[i][j] = rand() % 50 - 25;     // Gera um numero aleatorio e armazena na posicao (i, j) da matriz
            // printf("%d ", matrix_A[i][j]);
        }
        // printf("\n");
    }

    // Preenchendo a matriz B   
    int matrix_B[row_b][column_b];
    for (int i = 0; i < row_b; i++) {
        for (int j = 0; j < column_b; j++) {
            matrix_B[i][j] = rand() % 50 - 25;     // Gera um numero aleatorio e armazena na posicao (i, j) da matriz
            // printf("%d ", matrix_B[i][j]);
        }
        // printf("\n");
    }
    
    // Matriz C
    int matrix_C[row_a][column_b];
    for (int i = 0; i < row_a; i++) {
        printf("Linha %d: ", i);
        
        for (int j = 0; j < column_b; j++) {
            matrix_C[i][j] = 0; 
            // Poderia colocar row_b também, pois temos Ap,n x Bn,q = Cp,q
            for (int k = 0; k < column_a; k++) { // Percorrer os elementos da linha de A e da coluna de B
                matrix_C[i][j] = matrix_A[i][k] * matrix_B[k][j] + matrix_C[i][j];
            }
            printf("%d ", matrix_C[i][j]);              
        }
        printf("\n");
    }

    return 0;
}