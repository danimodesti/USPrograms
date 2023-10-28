/*
 * Nome: Danielle Modesti
 * No USP: 12543544
 * Disciplina: Lab. ICC II - 2° semestre de 2021
 * Ordenacao aconchegante - aplicacao - exercicio modulo I
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct shell {
    double vertical_diameter;
    char *color;
    char *texture;
} shell_t;

typedef struct list {
    shell_t **items;
    int shell_amt;
} list_t;

char *read_line();
shell_t *read_shell_info();
void print_shell_list(list_t *shell_list);
bool comparator(shell_t *shell_1, shell_t *shell_2);
void insertion_sort(list_t *shell_list, int gap, int sublist_number);
void my_sorting(list_t *shell_list);
void free_memory(list_t **shell_list);

int main() {
    list_t *shell_list = (list_t *) malloc(sizeof(list_t));

    scanf("%d", &shell_list->shell_amt);
    shell_list->items = (shell_t **) malloc(shell_list->shell_amt * sizeof(shell_t *));
    
    // Lendo as infos das conchas e colocando as numa lista
    for (int i = 0; i < shell_list->shell_amt; i++) {
        shell_t *new_shell = read_shell_info();
        shell_list->items[i] = new_shell;
    }
    my_sorting(shell_list); 
    print_shell_list(shell_list);
    free_memory(&shell_list);

    return EXIT_SUCCESS;
}

// Ler a linha ate achar um separador. No caso, usarei para obter informacoes
// das conchas, como cor e textura.
char *read_line() {
    char curr_char;
    int line_size = 0;
    char *line = NULL;

    do {
        curr_char = getchar();
    } while (curr_char == '\r' || curr_char == '\n' || curr_char == ' ');

    if (curr_char != EOF) {
        ungetc(curr_char, stdin);
    }

    do {
        curr_char = getchar();
        line_size++;
        line = (char *) realloc(line, line_size * sizeof(char));

        if (curr_char != ' ' && curr_char != '\r' && curr_char != '\n' && curr_char != EOF) {
            line[line_size - 1] = curr_char;
        }

        else {
            line[line_size - 1] = '\0';
        }

    } while (curr_char != ' ' && curr_char != '\r' && curr_char != '\n' && curr_char != EOF);

    return line;
}

// Obtendo as informacoes de cada concha
shell_t *read_shell_info() {
    shell_t* shell = (shell_t *) malloc(sizeof(shell_t));
    scanf("%lf", &shell->vertical_diameter);
    shell->color = read_line();
    shell->texture = read_line();

    return shell;
}

void print_shell_list(list_t *shell_list) {
    for (int i = 0; i < shell_list->shell_amt; i++) {
        printf("%.3lf ", shell_list->items[i]->vertical_diameter);
        printf("%s ", shell_list->items[i]->color);
        printf("%s\n", shell_list->items[i]->texture);
    }
}

// Criterio para ordenacao
bool comparator(shell_t *shell_1, shell_t *shell_2) {
    return shell_1->vertical_diameter < shell_2->vertical_diameter; 
}

// Metodo de ordenacao adaptado para a situacao de conchas
void insertion_sort(list_t *shell_list, int gap, int sublist_number) {
    int i = sublist_number + gap;
	while (i < shell_list->shell_amt) {	
		shell_t *key = shell_list->items[i]; 
		int j = i - gap; 

        // j >= k -> vou comecar daqui, nao preciso olhar desde 0.
		while (j >= sublist_number && comparator(key, shell_list->items[j])) {
			shell_list->items[j + gap] = shell_list->items[j]; 
			j -= gap; 
		}
        // Insere elemento (chave) na posicao correta
		shell_list->items[j + gap] = key;

		i += gap;
	}
}

// Minha versao de shell sort! Divide em sublistas virtuais e depois ordena com 
// insertion, visto que o 'grande problema' do insertion eh o gap de 1 em 1, o 
// que o faz ir muito longe para fazer comparacoes, originalmente.
void my_sorting(list_t *shell_list) {
    int sublist_amt = shell_list->shell_amt / 2;
    while (sublist_amt >= 1) {
        for (int j = 0; j < sublist_amt; j++) {
            insertion_sort(shell_list, sublist_amt, j);
        }
        sublist_amt /= 2;
    }
}

// Liberar memoria dinamicamente alocada
void free_memory(list_t **shell_list) {
    if (*shell_list) {
        if ((*shell_list)->items) {
            for (int i = 0; i < (*shell_list)->shell_amt; i++) {
                // Liberar info da concha
                if ((*shell_list)->items[i]->color) {
                    free((*shell_list)->items[i]->color);
                }

                if ((*shell_list)->items[i]->texture) {
                    free((*shell_list)->items[i]->texture);
                }
                // Liberar cada concha
                if ((*shell_list)->items[i]) {
                    free((*shell_list)->items[i]);
                }
            }
    
            // Liberar itens da lista de conchas [o ponteiro]
            free((*shell_list)->items);
        }

        // Liberar lista de conchas [o ponteiro]
        free((*shell_list));
    }

    *shell_list = NULL;
}