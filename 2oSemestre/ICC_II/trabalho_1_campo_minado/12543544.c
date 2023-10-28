/*
 * Nome: Danielle Modesti
 * No USP: 12543544
 * Codigo do curso: SCC0201
 * Disciplina: Introducao a Ciencia da Computacao - 2° semestre de 2021
 * Trabalho 01: Campo Minado
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY '.'
#define HIDDEN 'X'
#define MINE '*'

typedef struct Matrix {
    char **data;
    bool **aux;
    int row_amt;
    int col_amt;
} matrix_t;

typedef enum Option {
    SHOW_BOARD = 1,
    SHOW_HINTS = 2,
    USER_CONTROL = 3
} option_t;

typedef struct Point {
    int row;
    int col;
} point_t;

char *read_line();
void read_board_line(FILE *stream, matrix_t *matrix);
void read_board(FILE *stream, matrix_t *matrix);
void fill_with_hints(matrix_t *matrix);
void hide_points(matrix_t *matrix, point_t *p);
void print_board(matrix_t *matrix);
bool **init_aux_matrix(matrix_t *matrix);
void reveal_surroundings(matrix_t *matrix, int p_row, int p_col);
void check_point(matrix_t *matrix, point_t *p);
void free_memory(matrix_t *matrix, char *file_name);

int main() {
    int option;
    scanf("%d ", &option);

    char *board_name = read_line();

    FILE *initial_board = NULL;
    initial_board = fopen(board_name, "r");

    if(initial_board == NULL) {
        printf("Arquivo nao existe ou eh ilegivel =(\n");
        return EXIT_FAILURE;
    }

    matrix_t board;
    board.aux = NULL;
    board.row_amt = 0;
    board.col_amt = 0;

    read_board(initial_board, &board);

    point_t p;

    switch((option_t)option) {
        case SHOW_BOARD:
            break;
        case SHOW_HINTS:
            fill_with_hints(&board);
            break;
        case USER_CONTROL:
            fill_with_hints(&board);
            scanf("%d%d", &p.row, &p.col);
            check_point(&board, &p);
            break;
    }

    print_board(&board);

    fclose(initial_board);
    free_memory(&board, board_name);

    return EXIT_SUCCESS;
}

/*
 * read_line
 * Funcao para ler o nome do arquivo 'board' do campo minado e alocar
 * isso na memoria Heap, retornando a string toda
 * 
 * A funcao nao tem parametros de entrada
 * @Return:
 *      char *: a saida da f. eh o endereco da primeira posicao na Heap contendo
 *       a string alocada
 * 
 */

char *read_line() {
    char *line = NULL;
    char curr_char;
    int line_size = 0;

    do {
        curr_char = getchar();
        line_size++;

        line = (char *) realloc(line, sizeof(char) * line_size);

        if(curr_char != '\n') {
            line[line_size - 1] = curr_char;
        }
        else {
            line[line_size - 1] = '\0';
        }
    } while(curr_char != '\n');

    return line;
}

/*
 * read_board_line
 * Funcao para ler CADA LINHA do arquivo 'board' do campo minado e alocar
 * isso na memoria Heap
 * 
 * @Parametros:
 *      FILE *stream: endereco da primeira posicao na Heap contendo
 *                     os dados do arquivo do tipo board
 *      matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz
 *
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void read_board_line(FILE *stream, matrix_t *matrix) {
    matrix->data[matrix->row_amt] = NULL;
    char curr_char;

    matrix->col_amt = 0;

    do {
        curr_char = fgetc(stream);

        if (curr_char != '\n' && curr_char != EOF) {
            (matrix->col_amt)++;
            int row = matrix->row_amt;
            matrix->data[row] = (char *) realloc(matrix->data[row], sizeof(char) * (matrix->col_amt));
            matrix->data[row][matrix->col_amt - 1] = curr_char;
        }
    } while(curr_char != '\n' && curr_char != EOF);
}

/*
 * read_board
 * Funcao para ler todo o arquivo 'board' do campo minado e alocar
 * isso na memoria Heap. Esta funcao chama internamente uma leitura de linha
 * dinamica.
 * Preciso verificar se estou numa linha nova e nao precisarei alocar mais
 * espacos antes de executar nova alocacao e chamar read_board_line;
 * por isso, o while (verificar primeiro).
 * 
 * @Parametros:
 *      FILE *stream: endereco da primeira posicao na Heap contendo
 *                    os dados do arquivo do tipo board
 *      matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz
 * 
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void read_board(FILE *stream, matrix_t *matrix) {
    matrix->data = NULL;
    char curr_char;

    while ((curr_char = fgetc(stream)) != EOF) {
        ungetc(curr_char, stream);
        matrix->data = (char **) realloc(matrix->data, (matrix->row_amt + 1) * sizeof(char *));
        read_board_line(stream, matrix);
        (matrix->row_amt)++;
    }
}

/*
 * fill_with_hints
 * Funcao que localiza a quantidade de minas ao redor de uma celula.
 * Aqui, eu escolhi transformar os inteiros em chars para serem exibidos na 
 * tela. Testo todos os arredores, tomando cuidado para nao acessar posicoes
 * invalidas da board. Incremento um contador e so transformo '.' para outro
 * char se existem, de fato, minas por perto.
 * 
 * @Parametros:
 *      matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Uso o endereco porque
 *                        nao quero criar copias e consumir memoria sem 
 *                        necessidade.
 *
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void fill_with_hints(matrix_t *matrix) {
   for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            int count_mines_around = 0;

            if (i - 1 >= 0) {
                if (j - 1 >= 0 && matrix->data[i - 1][j - 1] == MINE) {
                    count_mines_around++;
                }
                if (matrix->data[i - 1][j] == MINE) {
                    count_mines_around++;
                }
                if (j + 1 < matrix->col_amt && matrix->data[i - 1][j + 1] == MINE) {
                    count_mines_around++;
                }
            }

            if (j - 1 >= 0 && matrix->data[i][j - 1] == MINE) {
                count_mines_around++;
            }
            if (j + 1 < matrix->col_amt && matrix->data[i][j + 1] == MINE) {
                count_mines_around++;
            }

            if (i + 1 < matrix->row_amt) {
                if (j - 1 >= 0 && matrix->data[i + 1][j - 1] == MINE) {
                    count_mines_around++;
                }
                if (matrix->data[i + 1][j] == MINE) {
                    count_mines_around++;
                }
                if (j + 1 < matrix->col_amt && matrix->data[i + 1][j + 1] == MINE) {
                    count_mines_around++;
                }
            }

            if (count_mines_around > 0 && matrix->data[i][j] == EMPTY) {
                matrix->data[i][j] = count_mines_around + '0';
            }
        }
    }
}

/*
 * hide_points
 * Funcao que trata quando, no caso 3, o usuario escolhe:
 * 1. uma dica (eu substituo
 * todos os pontos da matriz por X, deixando visivel apenas o ponto que contem
 * a dica) 
 * 
 * 2. um espaco vazio (eu substituo todos os pontos NAO DESCOBERTOS 
 * (ou varridos) da matriz por X, deixando visivel apenas os pontos descobertos. 
 * Isso foi controlado pela minha matrix auxiliar, por isso comparo o conteudo 
 * em cada celula dela para substituir a info na matrix original da board, 
 * 'data').
 * 
 * @Parametros: matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Uso o endereco porque
 *                        nao quero criar copias e consumir memoria sem 
 *                        necessidade.
 * 
 *              point_t *p: endereco da primeira posicao de memoria contendo
 *                          dados do ponto selecionado pelo usuario, que estao
 *                          organizados em uma struct de ponto, com campos de
 *                          coordenada linha e coluna
 * 
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void hide_points(matrix_t *matrix, point_t *p) {
    char copy_point = matrix->data[p->row][p->col];

    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            if (matrix->aux == NULL || matrix->aux[i][j] == false) {
                matrix->data[i][j] = HIDDEN;
            }
        }
    }

    matrix->data[p->row][p->col] = copy_point;
}

/*
 * print_board
 * Funcao para exibir o tabuleiro do minesweeper na tela
 * 
 * @Parametros:
 *      matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Mando o endereco porque
 *                        um ponteiro ocupa somente 8 bytes. Assim, nao preciso
 *                        fazer copias caso a board seja muito grande, evitando
 *                        gasto de memoria desnecessario.
 * 
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void print_board(matrix_t *matrix) {
    for (int i = 0; i < matrix->row_amt; i++) {
        for (int j = 0; j < matrix->col_amt; j++) {
            printf("%c", matrix->data[i][j]);
        }
        printf("\n");
    }
}

/*
 * init_aux_matrix
 * Funcao que aloca espaco dinamico na Heap para uma matrix auxiliar, que 
 * controlara pontos varridos pela recursao (funcao reveal_surroundings).
 * Inicializada com zeros por meio do calloc, indica, no inicio, que nenhum dos
 * pontos foi varrido pela recursao.
 * 
 * @Parametros: matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Uso o endereco porque
 *                        nao quero criar copias e consumir memoria sem 
 *                        necessidade.
 * 
 *              
 * @Return:     
 *      bool **: a saida da f. eh a matrix auxiliar criada. Controla, com zeros
 * ou false, que nao passou por determinadas celulas - portanto, elas serao
 * escondidas com 'X'. Caso o programa siga pelo caminho de recursao em 
 * reveal_surroundings, o valor logico de algumas celulas se tornara true.
 * 
 */
bool **init_aux_matrix(matrix_t *matrix) {
    bool **aux;

    aux = (bool **) calloc(matrix->row_amt, sizeof(bool *));

    for (int i = 0; i < matrix->row_amt; i++) {
        aux[i] = (bool *) calloc(matrix->col_amt, sizeof(bool));
    }

    return aux;
}

/*
 * Funcao que, recursivamente, revela os arredores de um ponto selecionado
 * ate chegar numa borda ou numa dica.
 * 
 * - Casos-base (condicoes de parada): ultrapassar limites da matriz ou ser uma 
 * dica. Alem disso, o programa tem uma logica na qual eh preciso saber se ja 
 * passei antes por aquele ponto acessado. Assim, usamos uma matrix auxiliar
 * para controlar com valores booleanos se a recursao varreu aquele espaco. Se 
 * varreu, nao o faz novamente.
 * Ao final, tenho o controle de onde passei e de onde nao passei.
 * 
 * - Passo recursivo: A funcao chama a si mesma para preencher vizinhos do 
 * ponto, sendo estes os oito ao redor (pontos  * cardeais e diagonais) =)

 * @Parametros: matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Mando o endereco porque
 *                        um ponteiro ocupa somente 8 bytes. Assim, nao preciso
 *                        fazer copias caso a board seja muito grande, evitando
 *                        gasto de memoria desnecessario.
 *
 *             int p_row: coordenada da linha do ponto atual de uma celula a ser
 *                        acessada no campo minado. Necessaria para perscrutar
 *                        os arredores dessa celula.
 *  
 *             int p_col: coordenada da coluna do ponto atual de uma celula a 
 *                        ser acessada no campo minado. Necessaria para 
 *                        perscrutar os arredores dessa celula.
 *
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void reveal_surroundings(matrix_t *matrix, int p_row, int p_col) {
    bool is_swept = true;
    if (matrix->aux[p_row][p_col] == is_swept) {
        
        return;
    }

    matrix->aux[p_row][p_col] = is_swept; 

    if (matrix->data[p_row][p_col] > '0' && matrix->data[p_row][p_col] < '9') {

        return;
    }

    if ((p_row - 1) >= 0 && (p_col - 1) >= 0) {
        reveal_surroundings(matrix, p_row - 1, p_col - 1);
    }

    if ((p_row - 1) >= 0) {
        reveal_surroundings(matrix, p_row - 1, p_col);
    }

    if ((p_row - 1) >= 0 && (p_col + 1) < matrix->col_amt) {
        reveal_surroundings(matrix, p_row - 1, p_col + 1);
    }

    if ((p_col - 1) >= 0) {
        reveal_surroundings(matrix, p_row, p_col - 1);
    }

    if ((p_col + 1) < matrix->col_amt) {
        reveal_surroundings(matrix, p_row, p_col + 1);
    }

    if ((p_row + 1) < matrix->row_amt && (p_col - 1) >= 0) {
        reveal_surroundings(matrix, p_row + 1, p_col - 1);
    }

    if ((p_row + 1) < matrix->row_amt) {
        reveal_surroundings(matrix, p_row + 1, p_col);
    }
    if ((p_row + 1) < matrix->row_amt && (p_col + 1) < matrix->col_amt) {
        reveal_surroundings(matrix, p_row + 1, p_col + 1);
    }
}

/*
 * check_point
 * Funcao que controla o campo minado com base na escolha de ponto do usuario.
 * - Se o usuario escolhe um ponto na board que corresponde a uma mina, acaba
 *   o jogo e o tabuleiro eh mostrado com as dicas - nao preciso tratar, eh
 *   como no comando 2. Assim, aqui eu so trato quando o ponto eh diferente
 *   de uma mina.
 * 
 * - Se o usuario escolhe uma dica, o tabuleiro deve mostrar so o que ha nessa
 *   celula. Chamo uma funcao interna para esconder os demais pontos, 
 *   hide_points.
 *   obs.: Se eh dica - tem 1 ate 8 bombas ao redor - o ponto pode assumir esses
 *   valores, portanto.
 * 
 * - Se o usuario escolhe um espaco vazio, ou seja, um ponto, devemos chamar
 * uma recursao para descobrir os arredores ate chegar numa dica ou numa borda
 * de tabuleiro -> chamar reveal_surroundings. Antes, precisamos de uma
 * matrix auxiliar a ser melhor explicada na funcao recursiva, que a utiliza.
 * Ao final, esconder os pontos nao descobertos com hide_points.
 * 
 * @Parametros: matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Uso o endereco porque
 *                        nao quero criar copias e consumir memoria sem 
 *                        necessidade.
 * 
 *              point_t *p: endereco da primeira posicao de memoria contendo
 *                          dados do ponto selecionado pelo usuario, que estao
 *                          organizados em uma struct de ponto, com campos de
 *                          coordenada linha e coluna
 * 
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void check_point(matrix_t *matrix, point_t *p) {
    if (matrix->data[p->row][p->col] != MINE) {
        if (matrix->data[p->row][p->col] == EMPTY) {
            matrix->aux = init_aux_matrix(matrix);
            reveal_surroundings(matrix, p->row, p->col);
        }

        hide_points(matrix, p);
    }
}

/*
 * free_memory
 * Funcao para liberar memoria referente as matrizes dinamicamente alocadas na 
 * Heap. Liberar primeiro todo o conteudo nas linhas (ou seja, os dados nas
 * colunas). Depois, liberar os vetores das linhas que compoem a matrix em si.
 * [Cada vetor de linha aponta para outro vetor das colunas]
 * 
 * @Parametros:
 *      matrix_t *matrix: endereco da primeira posicao na Heap contendo
 *                        os dados da board, essencialmente organizados
 *                        na estrutura de uma matriz. Mando o endereco para
 *                        liberar, de fato, todos os dados, nao a copia do 
 *                        endereco. Esses dados foram alocados anteriormente
 *                        na funcao read_board.
 *                        Alem disso, essa estrutura contem a matrix auxiliar 
 *                        tambem, caso ela tenha sido necessaria (!= NULL)
 *      char *file_name: endereco da primeira posicao na Heap contendo a string 
 *                       alocada
 *
 * 
 * A funcao nao tem retorno [saida implicita void] - so processa
 * 
 */

void free_memory(matrix_t *matrix, char *file_name) {
    for (int i = 0; i < matrix->row_amt; i++) {
        free(matrix->data[i]);
        if (matrix->aux != NULL) {
            free(matrix->aux[i]);
        }
    }

    free(matrix->data);

    if (matrix->aux != NULL) { 
        free(matrix->aux); 
    }

    free(file_name);
}