#include <iostream>
#include <cstring>

using namespace std;

#define MAX_LEN 2000
#define ALPHABET_SIZE 26
#define DELTA 0
#define MAX(a,b,c) max(max(a,b),c)

char str1[MAX_LEN];
char str2[MAX_LEN];
int letter_prices[ALPHABET_SIZE];

int MEMO[MAX_LEN + 1][MAX_LEN + 1];

void print_str(char str[], int size);
void print_letter_costs(int arr[], int size);
int alpha(int i, int j);
int common_subseq_max_cost(int i, int j);

int main() {
    int len1, len2;
    cin >> len1 >> len2;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        cin >> letter_prices[i];
    }

    for (int i = 0; i < len1; i++) {
        cin >> str1[i];
    }

    for (int i = 0; i < len2; i++) {
        cin >> str2[i];
    }

    memset(MEMO, -1, sizeof MEMO);

    int answer = common_subseq_max_cost(len1, len2);
    cout << answer << '\n';

    return EXIT_SUCCESS;
}

void print_str(char str[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c", str[i]);
    }

    printf("\n");
}

void print_letter_costs(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

// Calculo do custo do matching
int alpha(int i, int j) {
    if (str1[i - 1] == str2[j - 1]) {
        return letter_prices[str1[i - 1] - 'a'];
    }

    return 0;
}

int common_subseq_max_cost(int i, int j) {
    // Memoizacao
    if (MEMO[i][j] != -1) {
        return MEMO[i][j]; // Maior custo da maior subsequencia para a str1 considerando o indice i para tras 
                            // e a str2 considerando o indice j para tras
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
    MEMO[i][j] =  MAX(
        alpha(i, j) + common_subseq_max_cost(i - 1, j - 1),
        DELTA + common_subseq_max_cost(i - 1, j),
        DELTA + common_subseq_max_cost(i, j - 1)
    ); 

    return MEMO[i][j];
}