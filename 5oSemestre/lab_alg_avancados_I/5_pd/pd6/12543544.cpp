#include <iostream>
#include <cstring>

#define MAX_STRING_LENGTH 3000
#define NONE -1

using namespace std;

int pattern_len, text_len;
string pattern, text;
int MEMO[MAX_STRING_LENGTH][MAX_STRING_LENGTH];

int LCS(int i, int j);

int main() {
    string str1, str2;
    cin >> str1 >> str2;

    if (str1.length() <= str2.length()) {
        pattern = str1;
        text = str2;
    }

    else {
        pattern = str2;
        text = str1;
    }

    pattern_len = pattern.length();
    text_len = text.length();
    memset(MEMO, NONE, sizeof MEMO);
    LCS(0, 0);

    int i = 0, j = 0;
    while (i < pattern_len) {
        if (pattern[i] == text[j]) {
            cout << pattern[i];
            i++; j++;
        }

        // Houve matching no prox caractere da str pattern
        else if (MEMO[i + 1][j] >= MEMO[i][j + 1]) {
            i++;
        }

        // Sem matching proximo, percorrer mais um caractere da str text (maior)
        else {
            j++;
        }
    }

    cout << '\n';

    return EXIT_SUCCESS;
}

int LCS(int i, int j) {
    // Calculo ja foi realizado
    if (MEMO[i][j] != NONE) {
        return MEMO[i][j];
    }

    // Acabou uma das strings
    if (i == pattern_len or j == text_len) {
        MEMO[i][j] = 0;

        return 0;
    }

    // Deu matching
    if (pattern[i] == text[j]) {        
        MEMO[i][j] = 1 + LCS(i + 1, j + 1);

        return MEMO[i][j];
    }

    // Nao deu matching. Continue procurando...
    MEMO[i][j] = max(LCS(i + 1, j), LCS(i, j + 1));

    return MEMO[i][j];
}