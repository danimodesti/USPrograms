#include <stdio.h>
#include <stdlib.h>

#define INIT -1

int min_energy_cost(int curr_m, int *MEMO, int *heights, int mountain_amt);
void init_memo(int *MEMO, int *heights, int height_amt);
void print_array(int *array, int size);
int find_min(int a, int b);
void print_heights(int *heights, int h_amt);

int main() {
    int mountain_amt;
    scanf(" %d", &mountain_amt);

    // mountain_height[1] guarda h1, mountain_height[2] guarda h2,...
    int *mountain_height = (int *) malloc(sizeof(int) * (mountain_amt + 1));
    for (int i = 1; i <= mountain_amt; i++) {
        scanf(" %d", &mountain_height[i]);
    }

    // O Memo precisa de +1 de memoria para conter o numero max. de montanhas como indice.
    // Ex.: Se temos 6 montanhas, precisamos do indice 6.

    // IMPORTANTE: Para este exercicio, o MEMO representa a distancia da montanha i ate a 
    // ultima montanha que se deseja alcancar.
    int *MEMO = (int *) malloc(sizeof(int) * (mountain_amt + 1));
    init_memo(MEMO, mountain_height, mountain_amt);

    // "Pensar de tras pra frente" --> mandar a montanha 1 para que a f. chegue ate a 
    // ultima montanha e retorne o custo minimo de energia necessaria pro trajeto
    int answer = min_energy_cost(1, MEMO, mountain_height, mountain_amt);
    printf("%d\n", answer);

    free(mountain_height);
    free(MEMO);

    return EXIT_SUCCESS;
}

int min_energy_cost(int curr_m, int *MEMO, int *heights, int mountain_amt) {
    // Acabaram as montanhas
    if (curr_m > mountain_amt) {

        return __INT_MAX__ / 2; // Para nao ser o minimo e 'perder a eleicao'
    }
    
    // Verifica se essa distancia ja foi computada
    if (MEMO[curr_m] != INIT) {

        return MEMO[curr_m]; // Retorna a distancia
    }

    // Precisa calcular uma distancia 'acumulada' de qual caminho escolher
    int way_1 = abs(heights[curr_m] - heights[curr_m + 1]) + min_energy_cost(curr_m + 1, MEMO, heights, mountain_amt);
    int way_2 = abs(heights[curr_m] - heights[curr_m + 2]) + min_energy_cost(curr_m + 2, MEMO, heights, mountain_amt);

    int min = find_min(way_1, way_2);

    MEMO[curr_m] = min;

    return MEMO[curr_m];
}

int find_min(int a, int b) {
    if (a <= b) {
        return a;
    }

    return b;
}

// Coloca -1 como forma de inicializar os valores do memo, ja que nenhuma distancia pode
// realmente ser -1 (fora do dominio do problema).
//
// Alem disso, tambem inicializa a ultima e a penultima posicao, pois seus valores sao
// faceis de encontrar.
void init_memo(int *MEMO, int *heights, int height_amt) {
    for (int i = 0; i <= height_amt; i++) {
        MEMO[i] = INIT;
    }

    // A distancia da ultima posicao ate ela mesma eh zero
    MEMO[height_amt] = 0;

    // So ha como pular da penultima montanha pra ultima
    MEMO[height_amt - 1] = abs(heights[height_amt] - heights[height_amt - 1]);
}

void print_heights(int *heights, int h_amt) {
    printf("Alturas das montanhas:\n");
    for (int i = 1; i <= h_amt; i++) {
        printf("Altura da montanha %d: ", i);
        printf("%d\n", heights[i]);
    }

    printf("\n");
}

void print_array(int *array, int size) {
    for (int i = 1; i <= size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}