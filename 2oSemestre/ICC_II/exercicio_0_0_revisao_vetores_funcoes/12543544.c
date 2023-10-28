/*
 * Revisando Vetores e Funcoes
 * Danielle Modesti
 * No USP: 12543544
 * 
 * > programa que, recebendo uma sequencia de numeros, imprime-os em ordem
 * crescente e mostra quantas vezes eles ocorrem
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int allocate_vector(int **vector);
int *keep_only_unique_elements(int *all_elements, int all_amt, int *unique_amt);
int count_frequency_of_element(int *vector, int number_amt, int value);
void print_data(int unique_amt, int *unique_elements, int all_amt, int *all_elements);

int main() {
    int *all_elements = NULL;
    int all_amt = allocate_vector(&all_elements);

    int unique_amt = 0;
    int *unique_elements = keep_only_unique_elements(all_elements, all_amt, &unique_amt);

    print_data(unique_amt, unique_elements, all_amt, all_elements);
    free(all_elements);
    free(unique_elements);

    return EXIT_SUCCESS;
}

int allocate_vector(int **vector) {
    int curr_element;
    int number_amt = 0;

    while ((scanf("%d", &curr_element)) != EOF) {
        *vector = (int *) realloc(*vector, sizeof(int) * (number_amt + 1));
        (*vector)[number_amt++] = curr_element;
    } 

    return number_amt;
}

/*
 * A logica desta funcao eh a seguinte:
 * 1. Anteriormente, recebi todos os numeros e os salvei em um all_elements
 * 2. Agora, criarei um vetor que so tera os unique_elements
 * 3. para CADA valor do all_elements, compara com TODAS as posiçoes do 
 * unique_elements
 * 4. se, depois de comparar todos os elementos, o booleano continuar valendo 1,
 * eu aloco espaço e salvo na ultima posiçao do unique_elements. Eu o usarei 
 * para printar cada elemento distinto apenas uma vez no final.
 *
 */

int *keep_only_unique_elements(int *all_elements, int all_amt, int *unique_amt) {
    int *unique_elements = NULL;
    unique_elements = (int *) malloc(sizeof(int));

    unique_elements[0] = all_elements[0];
    *unique_amt = 1;
    
    int i = 1;
    while (i < all_amt) {
        bool is_unique_value = true;
        int j = 0;
        while (j < *unique_amt && is_unique_value) {
            if (all_elements[i] != unique_elements[j]) {
                j++;
            }
            else {
                is_unique_value = false;
            }
        }

        if (is_unique_value) {
            (*unique_amt)++;
            unique_elements = (int *) realloc(unique_elements, sizeof(int) * (*unique_amt));
            unique_elements[j] = all_elements[i];
        }
        i++;
    }

    return unique_elements;
}

/*
 * Utilizarei, neste codigo, a seguinte funcao para comparar cada elemento do
 * vetor com todos os elementos com cada valor especifico do vetor de elementos 
 * distintos. Assim, com cada valor unico (value), conto suas ocorrencias totais
 * recebidas inicialmente como entrada (armazenadas em vector)
 *
 */

int count_frequency_of_element(int *vector, int number_amt, int value) {
    int frequency = 0;

    for (int i = 0; i < number_amt; i++) {
        if (vector[i] == value) {
            frequency++;
        }
    }

    return frequency;
}

void print_data(int unique_amt, int *unique_elements, int all_amt, int *all_elements) {
    for (int i = 0; i < unique_amt; i++) {
        printf("%d (%d) ", unique_elements[i], count_frequency_of_element(all_elements, all_amt, unique_elements[i]));    
        printf("\n");
    }
}