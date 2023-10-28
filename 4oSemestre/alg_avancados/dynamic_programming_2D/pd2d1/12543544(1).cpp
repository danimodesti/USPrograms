#include <bits/stdc++.h>

using namespace std;

const long MOD = 1000000007;

bool is_valid_cell(vector<vector<char>>& matrix, int row_amt, int col_amt, int i, int j);
void read_matrix(vector<vector<char>>& matrix, int row_amt, int col_amt);
void print_matrix(vector<vector<char>>& matrix, int row_amt, int col_amt);

int main() {
    int row_amt, col_amt; 
    cin >> row_amt >> col_amt; 

    vector<vector<long>> NumWays; //declare the NumWays matrix
    vector<vector<char>> Labrinth; 

    NumWays.resize(row_amt);
    Labrinth.resize(row_amt);

    for (int i = 0; i < row_amt; i++) {
        NumWays[i].resize(col_amt);
        NumWays[i].assign(col_amt, 0);

        Labrinth[i].resize(col_amt);
    }

    read_matrix(Labrinth, row_amt, col_amt);

    NumWays[0][0] = 1;
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            if (is_valid_cell(Labrinth, row_amt, col_amt, i - 1, j)) {
                NumWays[i][j] = (NumWays[i - 1][j] + NumWays[i][j]) % MOD;
            }

            if (is_valid_cell(Labrinth, row_amt, col_amt, i, j - 1)) {
                NumWays[i][j] = (NumWays[i][j - 1] + NumWays[i][j]) % MOD;
            }
        }
    }

    cout << NumWays[row_amt - 1][col_amt - 1] << "\n";

    return EXIT_SUCCESS;
}

bool is_valid_cell(vector<vector<char>>& matrix, int row_amt, int col_amt, int i, int j) {
    if (i < 0 || i >= row_amt) {
        return false;
    }

    if (j < 0 || j >= col_amt) {
        return false;
    }

    if (matrix[i][j] == '#') {
        return false;
    }

    return true;
}

void read_matrix(vector<vector<char>>& matrix, int row_amt, int col_amt) {
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            cin >> matrix[i][j];
        }
    }
}

void print_matrix(vector<vector<char>>& matrix, int row_amt, int col_amt) {
    for (int i = 0; i < row_amt; i++) {
        for (int j = 0; j < col_amt; j++) {
            cout << matrix[i][j];
        }
        cout << "\n";
    }

    cout << "\n";
}