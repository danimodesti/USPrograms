#include <stdio.h>
#include <stdlib.h>

void read_array(long int *array, long int arr_len);
long int *read_entry(long int *arr_len);
void print_array(long int *array, long int arr_start, long int arr_end);
long int sort_and_count(long int *array, long int start, long int end);

int main() {
    int case_amt = 0;
    scanf(" %d", &case_amt);

    for (int i = 0; i < case_amt; i++) { // Testando so 1 caso
        long int array_len = 0;
        long int *array = read_entry(&array_len);

        long int total_crossing_amt = 0;
        total_crossing_amt = sort_and_count(array, 0, array_len - 1);
        printf("%ld\n", total_crossing_amt);

        free(array);
    }

    return EXIT_SUCCESS;
}

void read_array(long int *array, long int arr_len) {
    for (int i = 0; i < arr_len; i++) {
        long int tmp;
        scanf(" %ld", &tmp);
        array[i] = tmp - 1; // Para comecar contando do zero
    }
}

long int *read_entry(long int *arr_len) {
    scanf(" %ld", arr_len);
    long int *array = (long int *) malloc(sizeof(long int) * (*arr_len));
    read_array(array, *arr_len);

    return array;
}

void print_array(long int *array, long int arr_start, long int arr_end) {
    for (int i = arr_start; i <= arr_end; i++) {
        printf("%ld ", array[i]);
    }

    printf("\n");
} 

// Intercalando subvetores
long int merge_and_count(long int *array, long int start, long int end) {
    long int crossing_amt = 0;
    long int *aux = (long int *) malloc((end - start + 1) * sizeof(long int));

    long int center = (start + end) / 2;
    long int i = start; // Iterador subvetor esquerdo
    long int j = center + 1; // Iterador subvetor direito
    long int k = 0; // Iterador vetor auxiliar

    // Enquanto houver elementos das duas listas para serem comparados, faca-o
    while (i <= center && j <= end) {
        if (array[i] < array[j]) {
            aux[k] = array[i];
            i++;
        }

        // Se arr[i] > arr[j], tem inversao/crossing!
        // Se arr[i] == arr[j], tambem tem um cruzamento! Deixar para tratar
        // aqui
        else {
            crossing_amt += center - i + 1; // Contar qtos elementos estao no lugar errado (à esquerda)
            aux[k] = array[j];
            j++;
        }

        k++;
    }

    // Terminar de preencher -> apenas um dos dois loops abaixo ocorre
    while (i <= center) {
        aux[k] = array[i];
        i++;
        k++;
    }

    while (j <= end) {
        aux[k] = array[j];
        j++;
        k++;
    }

    for (i = start, k = 0; i <= end; i++, k++) {
        array[i] = aux[k];
    }

    free(aux);

    // Numero de crossings nessa execucao
    return crossing_amt;
}

// Usa estrutura do merge sort, mas retorna o numero de inversoes a serem feitas.
long int sort_and_count(long int *array, long int start, long int end) {
    if (start >= end) { // Ja dividiu todos os subvetores (gerando lista de 1 elemento)
        
        return 0; // Ha 0 cruzamentos em uma lista de 1 elemento
    }

    long int center = (start + end) / 2;

    long int left_array_crossing = sort_and_count(array, start, center);

    long int right_array_crossing = sort_and_count(array, center + 1, end);

    long int total_crossing_amt = merge_and_count(array, start, end);
    total_crossing_amt += left_array_crossing + right_array_crossing;

    return total_crossing_amt;
}