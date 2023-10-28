/*
 * Nome: Danielle Modesti
 * No USP: 12543544
 * Disciplina: Lab. ICC II - 2° semestre de 2021
 * UberSort - aplicacao - exercicio modulo II
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

typedef enum PivotChoice {
    THREE_MEDIAN = 1,
    RANDOMIC = 2
} pivot_t;

void print_vector(int *vector, int size);
void insertion_sort(int *vector, int start, int end);
int pivot_choice_estrategy(int *vector, int start, int end, int choice_flag);
void swap(int *first_element, int *second_element);
void partition(int *vector, int start, int end, int pivot, int *L1_iterator, int *L3_iterator);
void my_sorting(int *vector, int start, int end, int pivot_choice);

int main() {
    // Receber entrada
    int array_size;
    scanf("%d", &array_size);

    int pivot_choice;
    scanf("%d", &pivot_choice);

    // Setando a seed
    if (pivot_choice == RANDOMIC) {
        srand(42);
    }

    // Alocando espaco
    int *data = (int *) malloc(array_size * sizeof(int));

    for (int i = 0; i < array_size; i++) {
        scanf("%d", &data[i]);
    }

    // Ordenando
    my_sorting(data, 0, array_size - 1, pivot_choice);

    print_vector(data, array_size);

    // Desalocando memoria
    free(data);

    return EXIT_SUCCESS;
}

void print_vector(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", vector[i]);
    }
}

void insertion_sort(int *vector, int start, int end) {
    int i = start + 1;

    while (i <= end) {
        int key = vector[i];
        int j = i - 1;

        while (j >= start && key < vector[j]) {
            vector[j + 1] = vector[j];
            j--;
        }

        vector[j + 1] = key;
        i++;
    }
}

// Funcao de estrategia de escolha de pivo para Quick Sort (retorna indice do pivo)
int pivot_choice_estrategy(int *vector, int start, int end, int choice_flag) {
    // Resolver piores casos do qsort: vetor ordenado ou reverso (evitar listas
    // vazias)
    if (choice_flag == THREE_MEDIAN) {
        // Calculando centro
        int center = (int)((start + end) / 2);

        // Comparando ordenacao de valores
        if (vector[start] < vector[end]) {
            if (vector[center] < vector[end]) {
                if (vector[center] < vector[start]) {
                    return start;
                }

                return center;
            }

            return end;
        }

        // Elemento do inicio eh maior ou igual ao do fim
        else {
            if (vector[center] < vector[start]) {
                if (vector[center] < vector[end]) {
                    return end;
                }

                return center;
            }

            return start;
        }
    }

    // Chances de pior caso mais esparsas desta maneira
    else if (choice_flag == RANDOMIC) {
        return (int)(rand() % (end - start + 1) + start);
    }

   return ERROR; 
}

void swap(int *first_element, int *second_element) {
    int tmp = *first_element;
    *first_element = *second_element;
    *second_element = tmp;
}

/* 
* Funcao que particiona o vetor em 3 listas:
* 
* [--- L1 ---] < [--- L2 ---] < [--- L3 ---]
* 
* sendo os elementos da L1 < p, os elementos da L2 == p e os elementos da L3 > p
* - percorrer elementos == pivo
* - percorre o inicio do vetor para garantir < pivo
* - percorre o fim do vetor para garantir > pivo 
*/
void partition(int *vector, int start, int end, int pivot, int *L1_iterator, int *L3_iterator) {
    *L1_iterator = start; // percorre L1 < p (segue ++)

    // Percorrer vetor procurando por elementos iguais ao pivo, a fim de formar a L2
    int equal_amt = 1; // No minimo, apenas o pivo
    while (*L1_iterator <= end - equal_amt) {
        if (vector[*L1_iterator] == vector[pivot]) {
            // Pular posicoes com mesmo conteudo, olhando posicoes anteriores no vetor
                // Tambem nao contar elementos se o indice for o mesmo
            while (*L1_iterator != end - equal_amt && vector[*L1_iterator] == vector[end - equal_amt]) {
                equal_amt++;
            }

            // Enviar o elemento igual ao pivo para o fim do vetor
            if (*L1_iterator != end - equal_amt) {
                swap(&vector[*L1_iterator], &vector[end - equal_amt]);
            }

            equal_amt++;
        }

        (*L1_iterator)++;
    }

    // Agora, temos a L2, com elementos iguais a P, no fim do vetor.

    // -------------------------------------------------------------------------
    // Percorrer novamente o vetor, formando L1 e L3 [acao do Quick Sort costumeiro]
    *L1_iterator = start;

    // Desconsiderar parte do vetor com elementos iguais ao pivo, ja percorrida.
    *L3_iterator = end - equal_amt;   // percorre L2 > p  (segue --)

    while (*L1_iterator <= *L3_iterator) {
        // L1
        while (*L1_iterator <= end && vector[*L1_iterator] < vector[pivot]) {
            (*L1_iterator)++; 
        }

        // L3
        while (vector[*L3_iterator] > vector[pivot]) {
            (*L3_iterator)--; // Pivo demarca o inicio
        }

        // i e j sao candidatos a troca
        if (*L3_iterator > *L1_iterator) {
            swap(&vector[*L1_iterator], &vector[*L3_iterator]);
        }
    }

    // Enviar os elementos da L2 para o meio da lista, encaixando os na posicao correta.
    for (int k = 0; k < equal_amt; k++) {
        if (vector[*L1_iterator] != vector[end - k]) {
            swap(&vector[*L1_iterator], &vector[end - k]);
        }

        (*L1_iterator)++;
    }
}

// Criacao do meu Uber Sort - Quick Sort com os aprimoramentos
void my_sorting(int *vector, int start, int end, int pivot_choice) {
    // 1 - Caso base de ja ordenacao (vetores de tamanho 0 ou 1)
    if (start >= end) {
        return;
    }

    // 2 - Caso base de array com ate 10 elementos - limiar de transicao para insertion
    if ((end - start + 1) <= 10) { 
        insertion_sort(vector, start, end);
        return;
    }

    // 3 - Particao ao redor de um *pivo* [depende da Estrategia de Escolha do Pivo (pivot_choice_estrategy)]
    int pivot = pivot_choice_estrategy(vector, start, end, pivot_choice);

    // Troca pivo com a ultima posicao
    swap(&vector[pivot], &vector[end]);
    pivot = end;

    // Iteradores L1 e L3, respectivamente, obtidos por referencia da funcao de particao
    int i = 0;
    int j = 0;
    partition(vector, start, end, pivot, &i, &j);
    
    // 4 - Chamadas recursivas so para L1 e L3
    my_sorting(vector, start, j, pivot_choice);
    my_sorting(vector, i, end, pivot_choice);
}