// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

#define DATA_AMOUNT 10

// Fazer funcoes distintas para cada calculo
int maximum(int vetor[DATA_AMOUNT]);

int minimum(int vetor[DATA_AMOUNT]);

double average(int vetor[DATA_AMOUNT]); // Usar double para uma maior precisao

int mode(int vetor[DATA_AMOUNT]);

int main() {
    int data[DATA_AMOUNT];

    for (int i = 0; i < DATA_AMOUNT; i++) 
        scanf("%d", &data[i]);
    
    int max_data = maximum(data);
    int min_data = minimum(data);
    double avg_data = average(data);
    int mode_data = mode(data);

    printf("%d %d %.2lf %d\n", max_data, min_data, avg_data, mode_data);

    return 0;
}

int maximum(int vetor[DATA_AMOUNT]) {
    int result_max = vetor[0]; // Comeca com o maximo sendo o primeiro lido
    for (int i = 1; i < DATA_AMOUNT; i++) {
        if (vetor[i] > result_max)
            result_max = vetor[i];
    }

    return result_max;
}

int minimum(int vetor[DATA_AMOUNT]) {
    int result_min = vetor[0]; // Comeca com o minimo sendo o primeiro lido
    for (int i = 1; i < DATA_AMOUNT; i++) {
        if (vetor[i] < result_min)
            result_min = vetor[i];
    }

    return result_min;
}

double average(int vetor[DATA_AMOUNT]) {
    double adding_elements = 0;
    double result_avg;

    for (int i = 0; i < DATA_AMOUNT; i++) 
        adding_elements += vetor[i];
    
    result_avg = adding_elements / DATA_AMOUNT;

    return result_avg;
}

int mode(int vetor[DATA_AMOUNT]) {
    int cmp_value_1 = 0; 
    int cmp_value_2 = 0;
    int count_frequency_1 = 0;
    int count_frequency_2 = 0;
    int result_mode = vetor[0]; // Supor o primeiro elemento como aquele que mais se repete 
    int keep_most_frequent = count_frequency_1;
    
    for (int i = 0; i < DATA_AMOUNT - 1; i++) {
        cmp_value_1 = vetor[i]; 
        cmp_value_2 = vetor[i + 1]; 
    
        for (int j = 0; j < DATA_AMOUNT; j++) {
            if (vetor[j] == cmp_value_1) 
                count_frequency_1++; 
            else if (vetor[j] == cmp_value_2) 
                count_frequency_2++; 
        }
        if (count_frequency_2 > count_frequency_1) {
            // Certo, mas falta comparar com um valor armazenado na moda anteriormente caso um dos comparados seja maior que o outro
            if (count_frequency_2 > keep_most_frequent) { //  Somente se a frequencia comparada nesta iteracao especifica for maior que a armazenada, altere a moda
                keep_most_frequent = count_frequency_2;
                result_mode = cmp_value_2;
            }
        }
        count_frequency_1 = 0;
        count_frequency_2 = 0;
    }

    return result_mode;
}