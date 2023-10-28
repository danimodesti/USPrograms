#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

#define FOUND 1
#define NOT_FOUND 0

#define NOT_VISITED 0
#define VISITED 1

// Variavel global apenas para controle das direcoes do movimento no tabuleiro
// Coluna 0: referente as linhas
// Coluna 1: referente as colunas
char moves[4][2] = {{0, 1}, // Direita
                    {1, 0}, // Baixo
                    {0, -1}, // Esquerda
                    {-1, 0} // Cima
                    };

typedef struct Cell {
    char value;
    int is_visited;
} cell_t;

typedef struct Board {
    int row_amt;
    int col_amt;
    cell_t **matrix;
    int curr_row;
    int curr_col;
} board_t;

typedef struct Word {
    char *searched;
    int length;
} word_t;

void read_board(board_t *board);
void print_board_info(board_t *board);
void free_memory(board_t *board, char *word);
char *read_line();
void reset_board(board_t *b);
int look_through_board(board_t *b, word_t *word);
int word_search(board_t *board, word_t *word, int word_idx);

int main() {
    board_t my_board;
    read_board(&my_board);

    word_t my_word;
    scanf("%d", &my_word.length);
    my_word.searched = read_line();

    int final_answer = look_through_board(&my_board, &my_word);

    if (final_answer == FOUND) {
        printf("Yes\n");
    }

    else {
        printf("No\n");
    }

    free_memory(&my_board, my_word.searched);

    return EXIT_SUCCESS;
}

void read_board(board_t *board) {
    scanf(" %d %d", &board->row_amt, &board->col_amt);
    board->matrix = (cell_t **) malloc(sizeof(cell_t *) * board->row_amt);
    
    for (int i = 0; i < board->row_amt; i++) {
        board->matrix[i] = (cell_t *) malloc(sizeof(cell_t) * board->col_amt);
    }

    for (int i = 0; i < board->row_amt; i++) {
        for (int j = 0; j < board->col_amt; j++) {
            scanf(" %c", &board->matrix[i][j].value);
            board->matrix[i][j].is_visited = NOT_VISITED;
        }
    }

    board->curr_row = 0;
    board->curr_col = 0;
}

void print_board_info(board_t *board) {
    printf("qtd. linhas: %d\n", board->row_amt);
    printf("qtd. colunas: %d\n\n", board->col_amt);
    printf("-- tabuleiro --\n");
    for (int i = 0; i < board->row_amt; i++) {
        for (int j = 0; j < board->col_amt; j++) {
            printf("%c", board->matrix[i][j].value);
        }
        printf("\n");
    }

    printf("\n");
}

void free_memory(board_t *board, char *word) {
    for (int i = 0; i < board->row_amt; i++) {
        free(board->matrix[i]);
    }

    free(board->matrix);

    // Liberar palavra
    free(word);
}

char *read_line() {
    char curr_char;
    int str_len = 0;
    char *str = NULL;

    // Consumir chars possivelmente restantes no buffer
    do {
        curr_char = getchar();
    } while (curr_char == '\r' || curr_char == '\n' || curr_char == ' ');

    // Devolver char se valido
    if (curr_char != EOF) {
        ungetc(curr_char, stdin);
    }

    str = (char *) malloc(BUFFER_SIZE * sizeof(char));

    do {
        curr_char = getchar();
        str_len++;

        if (curr_char != '\r' && curr_char != '\n' && curr_char != EOF) {
            // Teste do buffer
            if (str_len % BUFFER_SIZE == 0) {
                str = (char *) realloc(str, ((str_len / BUFFER_SIZE+1) * BUFFER_SIZE) * sizeof(char));
            }

            str[str_len - 1] = curr_char;
        }

        else {
            str[str_len - 1] = '\0';
        }

    } while (curr_char != '\r' && curr_char != '\n' && curr_char != EOF);

    if (!str) {
        return NULL;
    } 

    // Corrigir a alocacao
    str = (char *) realloc(str, str_len * sizeof(char));

    return str;
}

int look_through_board(board_t *b, word_t *word) {
    int curr_index = 0; // Indice a ser buscado na palavra
    
    // So chamar recursao se tivermos a primeira letra dando match no tabuleiro
    for (int i = 0; i < b->row_amt; i++) {
        for (int j = 0; j < b->col_amt; j++) {
            // Posicao em que iniciaremos a busca: [i][j]
            if (b->matrix[i][j].value == word->searched[curr_index]) {
                b->curr_row = i;
                b->curr_col = j;
                
                reset_board(b); // Desvisitar celulas
                if (word_search(b, word, curr_index) == FOUND) {
                    return FOUND;
                }
            }
        }
    } 

    return NOT_FOUND;
}

// Testando 'out of bounds'
int is_position_valid(board_t *b) {
    int limits = b->curr_row >= 0 && b->curr_row < b->row_amt && b->curr_col >= 0 && b->curr_col < b->col_amt;
    return limits && !(b->matrix[b->curr_row][b->curr_col].is_visited);
}

void reset_board(board_t *b) {
    for (int i = 0; i < b->row_amt; i++) {
        for (int j = 0; j < b->col_amt; j++) {
            b->matrix[i][j].is_visited = NOT_VISITED;
        }
    }
}

int word_search(board_t *board, word_t *word, int word_idx) {
    // Se a celula atual nao esta nos limites do tabuleiro, nao encontrou
    if (!is_position_valid(board)) {
        return NOT_FOUND;
    }

    // Visitar a celula
    board->matrix[board->curr_row][board->curr_col].is_visited = VISITED;

    // Se a celula nao tem a letra que estamos procurando, nao encontramos um match
    if (board->matrix[board->curr_row][board->curr_col].value != word->searched[word_idx]) {
        return NOT_FOUND;
    }

    // A letra do ultimo indice foi encontrada - palavra completa
    if (word_idx == word->length - 1) {
        return FOUND;
    }

    // Celula atual
    int curr_row = board->curr_row, curr_col = board->curr_col;

    // Caminhar pelo tabuleiro
    for (int i = 0; i < 4; i++) { // Direcoes possiveis
        board->curr_row = curr_row + moves[i][0];
        board->curr_col = curr_col + moves[i][1];

        // Procurar proximo indice/letra da palavra (novo estado)
        if (word_search(board, word, word_idx + 1) == FOUND) {

            return FOUND;
        }

        else if (is_position_valid(board)) {
            // Desvisitar a celula
            board->matrix[board->curr_row][board->curr_col].is_visited = NOT_VISITED;
        }
    }

    return NOT_FOUND;
}