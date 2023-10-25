/*
 * Danielle Modesti
 * No USP: 12543544
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Filler {
    char color;
    int row;
    int col;
} filler_t;

typedef struct Matrix {
    char **data;
    int row_amt;
    int col_amt;
} matrix_t;

char *read_line();
void read_art(FILE *stream, matrix_t *matrix);
void read_matrix_line(FILE *stream, matrix_t *matrix, bool *is_EOF);
void print_art(matrix_t matrix);
void fill_art(matrix_t *matrix, char color, int pixel_row, int pixel_col, char prev_color);
void enquadra_arte(char *nome_do_arquivo_da_arte, int altura_do_quadro, int largura_do_quadro);
void free_memory(matrix_t *matrix, char *file_name, filler_t *filler_info);

int main() {
    // 1 - Ler a partir do arquivo da arte e colocar a arte numa matriz dinamica
    char *art_name = read_line();
    FILE *initial_art = NULL;

    initial_art = fopen(art_name, "r");

    if (initial_art == NULL) {
        printf("Arquivo nao existe =(\n");
        return 0;
    }

    matrix_t art;

    art.row_amt = 0;
    art.col_amt = 0;    

    // 2 - Alocar matriz dinamica
    read_art(initial_art, &art);

    printf("Arte inicial: \n");
    print_art(art);
    fclose(initial_art);

    int filler_amount;
    scanf("%d", &filler_amount);

    filler_t *filler_info = (filler_t *) malloc(filler_amount * sizeof(filler_t));

    // 3 - Fazer a recursao
    for (int i = 0; i < filler_amount; i++) {
        scanf(" %c %d %d", &filler_info[i].color, &filler_info[i].row, &filler_info[i].col);
        printf("\nArte apos a etapa %d:\n", i);

        char prev_color = art.data[filler_info[i].row][filler_info[i].col];
        fill_art(&art, filler_info[i].color, filler_info[i].row, filler_info[i].col, prev_color);
        print_art(art);
    }
    
    // Realizar escrita no arquivo com a arte preenchida 
    // Usar fputc porque preciso adicionar quebras de linha, que sao caracteres
    initial_art = fopen(art_name, "w");

    for (int i = 0; i < art.row_amt; i++) {
        for (int j = 0; j < art.col_amt; j++) {
            fputc(art.data[i][j], initial_art);
        }
        if (i < (art.row_amt - 1)) {
            fputc('\n', initial_art);
        }
    }
    fclose(initial_art);

    // 4 - Mostre a arte enquadrada
    printf("\nArte enquadrada:\n");
    enquadra_arte(art_name, art.row_amt, art.col_amt);

    // Liberar memoria alocada dinamicamente
    free_memory(&art, art_name, filler_info);

    return EXIT_SUCCESS;
}

// Para ler o nome do arquivo ASCII
char *read_line() {
    char *line = NULL; 
    char current_char; 
    int line_size = 0; 

    do { 
        current_char = getchar();
        line_size++; 

        // Usar realloc para alocar novos espacos a cada iteracao do loop
        line = (char *) realloc(line, sizeof(char) * line_size); 

        if (current_char != '\n') {
            line[line_size - 1] = current_char; 
        }
        else {
            line[line_size - 1] = '\0'; 
        } 
    } while (current_char != '\n'); 

    return line;
}

void read_matrix_line(FILE *stream, matrix_t *matrix, bool *is_EOF) {
    matrix->data[matrix->row_amt] = NULL; 
    char current_char; 

    matrix->col_amt = 0;
    do { 
        current_char = fgetc(stream);
        
        // Usar realloc para alocar novos espacos a cada iteracao do loop
        if (current_char != '\n' && current_char != EOF) {
            (matrix->col_amt)++; 
            int row = matrix->row_amt;
            matrix->data[row] = (char *) realloc(matrix->data[row], sizeof(char) * (matrix->col_amt)); 
            matrix->data[row][matrix->col_amt - 1] = current_char; 
        }
    } while (current_char != '\n' && current_char != EOF);

    if (current_char == EOF) {
        *is_EOF = true;
    }
}

void read_art(FILE *stream, matrix_t *matrix) {
    // Para dar o realloc, precisa configurar a matriz com ponteiro NULL
    matrix->data = NULL;
    bool is_EOF = false;
    
    do {
        matrix->data = (char **) realloc(matrix->data, (matrix->row_amt + 1) * sizeof(char *));
        read_matrix_line(stream, matrix, &is_EOF);
        (matrix->row_amt)++;
    } while (!is_EOF); 

}

void print_art(matrix_t matrix) {
    for (int i = 0; i < matrix.row_amt; i++) {
        for (int j = 0; j < matrix.col_amt; j++) {
            printf("%c", matrix.data[i][j]);
        }
        printf("\n");
    }
}

// Funcao recursiva para preenchimento da arte com cores
/*
 * Condicao de parada: ultrapassar os limites da matriz e/ou a cor da posicao ser diferente da cor inicial do pixel 
 * inicial.
 *
 * Passo recursivo: a funcao chama a si mesma para preencher vizinhos do pixel,
 * sendo eles os dois horizontais e os dois verticais
 * 
 * Preencher apenas pixels com a mesma cor inicial do pixel escolhido
 * 
*/
void fill_art(matrix_t *matrix, char color, int pixel_row, int pixel_col, char prev_color) {
    // So pintar se o pixel nao fizer parte do desenho ou se ja estiver pintado - parada
    if (matrix->data[pixel_row][pixel_col] != prev_color) {
        return;
    }
    
    matrix->data[pixel_row][pixel_col] = color;

    // Modificar uma coisa por vez: primeiro as linhas acima e abaixo, depois as colunas anteriores e posteriores
    if ((pixel_row - 1) >= 0) {
        fill_art(matrix, color, pixel_row - 1, pixel_col, prev_color);
    }

    if ((pixel_row + 1) < matrix->row_amt) {
        fill_art(matrix, color, pixel_row + 1, pixel_col, prev_color);
    }

    if ((pixel_col - 1) >= 0) {
        fill_art(matrix, color, pixel_row, pixel_col - 1, prev_color);
    }

    if ((pixel_col + 1) < matrix->col_amt) {
        fill_art(matrix, color, pixel_row, pixel_col + 1, prev_color);
    }    
}

// Funcao auxiliar fornecida - nao modificar!
void enquadra_arte(char *nome_do_arquivo_da_arte, int  altura_do_quadro, int  largura_do_quadro) {
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}

void free_memory(matrix_t *matrix, char *file_name, filler_t *filler_info) {
    free(file_name);
    for (int i = 0; i < matrix->row_amt; i++) {
        free(matrix->data[i]);
    } 
    free(matrix->data);
    free(filler_info);
}