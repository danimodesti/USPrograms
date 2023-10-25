// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

float** allocate_attack_table(int amt_rows, int amt_columns);
void get_attack_table(int amt_rows, int amt_columns, float **matrix);
void maximum(float *vector, int vector_size);

int main() {
    int matrix_dimension;
    scanf("%d", &matrix_dimension);

    float **battle_table = allocate_attack_table(matrix_dimension, matrix_dimension);

    get_attack_table(matrix_dimension, matrix_dimension, battle_table);

    // Dando malloc de 4 bytes porque precisamos de pelo menos 1 atq
    // Alocacao para um ataque completo
    int **attack_information = (int**)malloc(1 * sizeof(int*));
    attack_information[0] = (int*)malloc(2 * sizeof(int));

    /* 
    Realoque caso haja menos ataques
    A quantidade de ataques nunca passa uma qtd = matrix_dimension 
    Porem, nao ha garantia de haver menos ataques que essa qtd
    Linhas -> qtd = matrix_dimension ou menos - pode precisar realocar
    Colunas -> sempre 2 - o ataque sempre tem 2 infos
    */
    
    int attack_amt = 0;
    do {
        for (int j = 0; j < 2; j++) {
            if (attack_amt > 0 && j == 0) {
                attack_information = (int**)realloc(attack_information, (attack_amt + 1) * sizeof(int*));
                attack_information[attack_amt] = (int*)malloc(1 * sizeof(int));
            }
            scanf("%d", &attack_information[attack_amt][j]);
            if (attack_information[attack_amt][0] == -1) {
                break;
            }
            else if (attack_amt > 0) {
                attack_information[attack_amt] = (int*)realloc(attack_information[attack_amt], 2 * sizeof(int));
            }
        }
        attack_amt++;
    } while (attack_information[attack_amt - 1][0] != -1 && attack_amt < matrix_dimension);

    // Lidando com o -1
    int is_attack_finished;
    scanf("%d", &is_attack_finished);

    int opponent_attack_type;
    if (is_attack_finished == -1) {
        scanf("%d", &opponent_attack_type);
    }
    else {
        opponent_attack_type = is_attack_finished;
    }

    // Usar o tipo do ataque do oponente para ver o melhor ataque do usuario
    float *attack_power = (float*)malloc((attack_amt + 1) * sizeof(float));
    for (int i = 0; i < attack_amt; i++) {
        attack_power[i] = attack_information[i][0] * battle_table[i][opponent_attack_type];
    }

    // Encontre o maior ataque
    maximum(attack_power, attack_amt);

    // Desalocando memoria dinamica
    for (int i = 0; i < matrix_dimension; i++) {
        free(battle_table[i]);
    }
    free(battle_table);
    for (int i = 0; i < attack_amt; i++) {
        free(attack_information[i]);
    }
    free(attack_information);
    free(attack_power);

    return 0;
}

void maximum(float *vector, int vector_size) {
    float result_max = vector[0]; // Comeca com o maximo sendo o primeiro lido
    int index = 0;
    for (int i = 1; i < vector_size; i++) {
        if (vector[i] > result_max) {
            result_max = vector[i];
            index = i;
        }
    }

    printf("O melhor ataque possui indice %d e dano %.2f\n", index, result_max);
}

float** allocate_attack_table(int amt_rows, int amt_columns) {
    float **matrix = (float**)malloc(amt_rows * sizeof(float*));
    for (int i = 0; i < amt_rows; i++) {
        matrix[i] = (float*)malloc(amt_columns * sizeof(float));
    }
    
    return matrix;
}
void get_attack_table(int amt_rows, int amt_columns, float** matrix) {
    for (int i = 0; i < amt_rows; i++) {
        for (int j = 0; j < amt_columns; j++) {
            scanf("%f", &matrix[i][j]);
        }
    }
}