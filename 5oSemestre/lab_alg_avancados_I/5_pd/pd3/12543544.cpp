#include <iostream>
#include <vector>
#include <cstring> // Memset

#define EMPTY_CELL '.'
#define TRAP '*'
#define MAX_DIMENSION 1000
#define NONE -1
#define MOD 1000000007

using namespace std;

typedef vector<vector<char>> matrix_t;

// Guarda quantos caminhos tem para chegar ao fim partindo de determinada celula da matriz
int MEMO[MAX_DIMENSION][MAX_DIMENSION];

matrix_t create_matrix(int grid_dim);
void print_matrix(matrix_t& matrix, int grid_dim);
int possible_path_amt(matrix_t &matrix, int grid_dim, int curr_i, int curr_j);

int main() {
    int grid_dim;
    cin >> grid_dim;

    matrix_t my_grid = create_matrix(grid_dim);


    // Inicializando o MEMO com valor fora do dominio
    memset(MEMO, NONE, sizeof MEMO);

    int answer = possible_path_amt(my_grid, grid_dim, 0, 0);
    cout << answer << '\n';

    return EXIT_SUCCESS;
}

matrix_t create_matrix(int grid_dim) {
    // Inicializar vetor de vetores ao tamanho apropriado antes de acessar elementos.
    // Criando vetor de row_amt de tamanho vetor col_amt, preenchido com 0
    matrix_t new_matrix(grid_dim, vector<char>(grid_dim));

    for (int i = 0; i < grid_dim; i++) {
        for (int j = 0; j < grid_dim; j++) {
            cin >> new_matrix[i][j];
        }
    }

    return new_matrix;
}

void print_matrix(matrix_t& matrix, int grid_dim) {
    for (int i = 0; i < grid_dim; i++) {
        for (int j = 0; j < grid_dim; j++) {
            cout << matrix[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}

int possible_path_amt(matrix_t &matrix, int grid_dim, int curr_i, int curr_j) {
    // Para celulas fora do limite do grid, nao existem caminhos
    if (curr_i > grid_dim - 1 or curr_j > grid_dim - 1) {
        return 0;
    }

    if (MEMO[curr_i][curr_j] != NONE) { // Checar se ja nao calculou a qtd de caminhos a partir daquela celula ate o fim
        return MEMO[curr_i][curr_j];
    }

    // Para celulas que sao bomba, nao existem caminhos
    if (matrix[curr_i][curr_j] == TRAP) {
        MEMO[curr_i][curr_j] = 0;

        return 0;
    }
    
    // Caso-base: estou na ultima celula. Ha somente um caminho para chegar a
    // ultima celula estando nela.
    if (curr_i == grid_dim - 1 and curr_j == grid_dim - 1) {
        MEMO[curr_i][curr_j] = 1;

        return 1;
    }

    // Chamar para duas direcoes (para direita e para baixo)
    MEMO[curr_i][curr_j] = (possible_path_amt(matrix, grid_dim, curr_i, curr_j + 1) + possible_path_amt(matrix, grid_dim, curr_i + 1, curr_j)) % MOD;
    
    return MEMO[curr_i][curr_j];
}