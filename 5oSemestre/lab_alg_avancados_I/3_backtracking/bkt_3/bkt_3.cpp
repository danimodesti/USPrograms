#include <iostream>
#include <vector>
#include <queue>

#define MINED 0
#define INFINITY -1

using namespace std;

typedef vector<vector<int>> matrix;
typedef vector<vector<bool>> b_matrix;

typedef struct Cell {
    int i;
    int j;
    int distance;        
} cell_t;

matrix read_board(int row_amt, int col_amt);
void pre_process_board(matrix& board, int row_amt, int col_amt);
void print_board(matrix& board, int row_amt, int col_amt);
int bfs(matrix& board, b_matrix& visited, int row_amt, int col_amt, int i_src);

int main() {
    int row_amt, col_amt;
    cin >> row_amt >> col_amt;

    matrix board = read_board(row_amt, col_amt);
    pre_process_board(board, row_amt, col_amt);

    b_matrix visited(row_amt, vector<bool>(col_amt));

    int min_distance = INFINITY;
    for (int i = 0; i < row_amt; i++) {
        int curr_distance = bfs(board, visited, row_amt, col_amt, i);
        
        if (min_distance == INFINITY or (curr_distance != INFINITY and curr_distance < min_distance)) {
            min_distance = curr_distance;
        }
    }

    if (min_distance == INFINITY) {
        cout << "Nao ha caminho valido\n";
    }

    else {
        cout << "Comprimento da rota = " << min_distance << '\n';
    }

    return EXIT_SUCCESS;
}


// Como nao posso passar por celulas adjacentes em N, S, L e O a mina, transformo-as em minas
void pre_process_board(matrix& board, int row_amt, int col_amt) {
    matrix copy = board;
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            if (board[i][j] == MINED) {
                // Checagem de integridade de celulas (limites do tabuleiro)
                if (i - 1 >= 0) {
                    copy[i - 1][j] = MINED;
                }

                if (j + 1 < col_amt) {
                    copy[i][j + 1] = MINED;
                }

                if (i + 1 < row_amt) {
                    copy[i + 1][j] = MINED;
                }

                if (j - 1 >= 0) {
                    copy[i][j - 1] = MINED;
                }
            }
        }
    }

    board = copy;
}

matrix read_board(int row_amt, int col_amt) {
    // Inicializar vetor de vetores ao tamanho apropriado antes de acessar elementos.
    // Criando vetor de row_amt de tamanho vetor col_amt, preenchido com 0
    matrix board(row_amt, vector<int>(col_amt));
    
    int curr_cell;
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            cin >> curr_cell;
            board[i][j] = curr_cell;
        }
    }

    return board;
}

void print_board(matrix& board, int row_amt, int col_amt) {
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';
}

cell_t create_cell(int i, int j, int distance) {
    cell_t c;
    c.i = i;
    c.j = j;
    c.distance = distance;

    return c;
}

void unvisit_all(b_matrix& visited, int row_amt, int col_amt) {
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            visited[i][j] = false;
        }
    }
}

bool is_cell_valid(matrix& board, b_matrix& visited, int i, int j, int row_amt, int col_amt) {
    // Limites do tabuleiro
    if (i < 0 or j < 0) {
        return false;
    }

    if (i >= row_amt or j >= col_amt) {
        return false;
    }

    // Nao pode visitar
    if (board[i][j] == MINED) {
        return false;
    }

    // Ja foi visitado
    if (visited[i][j]) {
        return false;
    }

    return true;
}

int bfs(matrix& board, b_matrix& visited, int row_amt, int col_amt, int i_src) {
    unvisit_all(visited, row_amt, col_amt);
    
    queue<cell_t> cq;

    if (is_cell_valid(board, visited, i_src, 0, row_amt, col_amt)) {
        cq.push(create_cell(i_src, 0, 0));
        visited[i_src][0] = true; // Visitando primeira celula
    }

    while (!cq.empty()) {
        cell_t u = cq.front();
        cq.pop();

        // Chegou na saida (ultima coluna)
        if (u.j == col_amt - 1) {
            return u.distance;
        }

        // Testar caminhos possiveis
        if (is_cell_valid(board, visited, u.i - 1, u.j, row_amt, col_amt)) {
            visited[u.i - 1][u.j] = true;
            cq.push(create_cell(u.i - 1, u.j, u.distance + 1));
        }

        if (is_cell_valid(board, visited, u.i, u.j + 1, row_amt, col_amt)) {
            visited[u.i][u.j + 1] = true;
            cq.push(create_cell(u.i, u.j + 1, u.distance + 1));
        }

        if (is_cell_valid(board, visited, u.i + 1, u.j, row_amt, col_amt)) {
            visited[u.i + 1][u.j] = true;
            cq.push(create_cell(u.i + 1, u.j, u.distance + 1));
        }
    }

    return INFINITY;
}