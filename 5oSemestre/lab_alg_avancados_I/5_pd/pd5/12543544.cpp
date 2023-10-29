#include <iostream>
#include <cstring> // Para usar memset

using namespace std;

#define NONE -1

#define MAX_STRING_LENGTH 5000

// Custo de inserir ou remover letra de uma str
#define DELTA 1 

#define MIN(a, b, c) min(min(a, b), c) // Apenas para facilitar no codigo

// Somar 1 para considerar str vazia.
// Este MEMO guarda o menor numero de operacoes para transformar
// str1 ate indice i na str2 ate o indice j
int MEMO[MAX_STRING_LENGTH + 1][MAX_STRING_LENGTH + 1];

// Strings globais para facilitar manipulacao no problema
string to_edit_str, to_be_obtained_str;

int min_editing_amt(int i, int j);
void print_MEMO();

int main() {
    cin >> to_edit_str >> to_be_obtained_str;

    // Inicializando MEMO
    memset(MEMO, NONE, sizeof MEMO);

    // Comecar processo a partir do fim das strings e chegar ate o comeco
    cout << min_editing_amt(to_edit_str.size(), to_be_obtained_str.size()) << '\n';

    return EXIT_SUCCESS;
}

// Calculo do custo do matching (trocar/atualizar letra se for diferente entre a str 1 e a str 2)
int alpha(int i, int j) {
    // Se os caracteres forem iguais, nao troca letra
    if (to_edit_str[i - 1] == to_be_obtained_str[j - 1]) {
        return 0;
    }

    // Trocar letra se elas sao diferentes entre strings
    return 1;
}

// i --> idx que acompanha str 1
// j --> idx que acompanha str 2
int min_editing_amt(int i, int j) {
    // Usando calculos ja feitos para diminuir complexidade
    if (MEMO[i][j] != NONE) {
        return MEMO[i][j];
    }

    // Casos-base ---
    if (i == 0) { // Chegou ao fim da str1
        MEMO[0][j] = j * DELTA;

        return j * DELTA; // Precisa inserir essa qtd. de caracteres na str1 para chegar na str2
    }

    if (j == 0) { // Chegou ao fim da str2
        MEMO[i][0] = i * DELTA;

        return i * DELTA; // Precisa remover essa qtd. de caracteres na str1 para chegar na str2
    }

    // Ainda nao acabou nenhuma string.
    // Deve haver um matching entre str1[i] e str2[j] ou de str1[i] com algum str2[j - k]
    // ou de str2[j] com algum str1[i - k], k >= 1.
    // Continue a testar para os caracteres anteriores...

    // Minimo custo para 3 possibilidades listadas acima...
    MEMO[i][j] = MIN(
        alpha(i, j) + min_editing_amt(i - 1, j - 1),
        DELTA + min_editing_amt(i - 1, j),
        DELTA + min_editing_amt(i, j - 1)
    );

    // Custo minimo para igualar as duas strings totalmente...
    return MEMO[i][j];
}

void print_MEMO() {
    int str1_len = to_edit_str.size();
    int str2_len = to_be_obtained_str.size();

    for (int i = 0; i < str1_len; i++) {
        for (int j = 0; j < str2_len; j++) {
            cout << MEMO[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';
}