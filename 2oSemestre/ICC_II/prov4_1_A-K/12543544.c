/*
 * Nome: Danielle Modesti
 * No USP: 12543544
 * Codigo do curso: SCC0201
 * Disciplina: Introducao a Ciencia da Computacao - 2° semestre de 2021
 * Avaliacao 1 - contagem de operacoes e eficiencia
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int** alloc_matrix(int m);
void print_matrix(int **matrix, int line_size);
void the_best_algorithm_in_the_world(int **matrix, int line_size);
void free_memory(int **matrix, int line_size);

int main() {
    int line_size;
    scanf("%d", &line_size);
    int **my_matrix = alloc_matrix(line_size);
    the_best_algorithm_in_the_world(my_matrix, line_size);
    print_matrix(my_matrix, line_size);
    free_memory(my_matrix, line_size);

    return EXIT_SUCCESS;
}

// Funcao dada pelo professor
int** alloc_matrix(int m) {
	int **mat = malloc(sizeof(int*)*m);
	srand(m);
	
	int in = 0;
	// aloca matriz ordenada
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(sizeof(int)*m);
	    	for (int j = 0; j < m; j++) {
			if (i == j) in+= (rand()%3)+1;
			else in += rand()%3;
			mat[i][j] = in;
		}
	}
	// desordena matriz triangular superior
	for (int i = 0; i < m-2; i++) {
	    	for (int j = i+1; j < m-1; j++) {
			int swaps = (int)((m-j)/2.0)+1;
			for (int t = 1; t <= swaps; t++) {
				int a = (rand()%(m-j))+j;
				int b = (rand()%(m-j))+j;
				int tmp = mat[i][a];
				mat[i][a] = mat[i][b];
				mat[i][b] = tmp;
			}
		}

	}
	return mat;
}

void print_matrix(int **matrix, int line_size) {
    for (int i = 0; i < line_size; i++) {
        for (int j = 0; j < line_size; j++) {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_memory(int **matrix, int line_size) {
    for (int i = 0; i < line_size; i++) {
            free(matrix[i]);
    }

    free(matrix);
}

void the_best_algorithm_in_the_world(int **matrix, int line_size) {
    int aux;

    for (int i = 0; i < line_size - 2; i++) { // Nao preciso olhar as ultimas linhas, ja estao ordenadas
        for (int k = 0; k < line_size - 2 - i; k++) {
            for (int j = i + 1; j < line_size - 1; j++) {
                if (j + 1 < line_size && matrix[i][j] > matrix[i][j + 1]) {
                    aux = matrix[i][j];
                    matrix[i][j] = matrix[i][j + 1];
                    matrix[i][j + 1] = aux;
                }
            }
        }
    }
}