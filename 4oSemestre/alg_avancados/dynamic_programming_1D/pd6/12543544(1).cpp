#include <iostream>
#include <cstring>

using namespace std;

#define MAX_LEN 2000
#define DELTA 1 // Custo de inserir letra (se o gap for na str1) ou remover letra (se o gap for na str2) - referencia eh str1
#define MIN(a,b,c) min(min(a,b),c)

string str1;
string str2;

int MEMO[MAX_LEN + 1][MAX_LEN + 1];

int alpha(int i, int j);
int min_operation_amt(int i, int j); // i, j comecam em 1 (0 = str vazia)

int main() {
    int test_cases;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        cin >> str1;
        cin >> str2;

        memset(MEMO, -1, sizeof MEMO);

        int answer = min_operation_amt(str1.size(), str2.size());
        cout << answer << '\n';
    }

    return EXIT_SUCCESS;
}

// Calculo do custo do matching 
int alpha(int i, int j) {
    if (str1[i - 1] == str2[j - 1]) {
        return 0;
    }

    return 1; // Custo de trocar letra se elas forem diferentes
}

int min_operation_amt(int i, int j) {
    // Memoizacao
    if (MEMO[i][j] != -1) {
        return MEMO[i][j]; // Menor numero de operacoes para transformar string1 ate indice i na string2 ate
                           // indice j
    }

    // Casos-base ---
    if (i == 0) { // Acabou a str1
        MEMO[0][j] = j * DELTA;
        return j * DELTA; // Custo do que sobrou da str2 em gap
    }

    if (j == 0) { // Acabou a str2
        MEMO[i][0] = i * DELTA;
        return i * DELTA;
    }

    // Ha um matching entre str1[i] e str2[j] ou de str1[i] com algum str2[j - k]
    // ou de str2[j] com algum str1[i - k], k >= 1.
    // Continuar o processo para os caracteres anteriores
    MEMO[i][j] =  MIN(
        alpha(i, j) + min_operation_amt(i - 1, j - 1),
        DELTA + min_operation_amt(i - 1, j),
        DELTA + min_operation_amt(i, j - 1)
    ); 

    return MEMO[i][j];
}