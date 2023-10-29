#include <iostream>
#include <limits.h> // INT_MAX
#include <cstring> // Memset

#define COIN_SET_SIZE 500
#define MAX_VALUE 1000
#define NONE -1

using namespace std;

// -- Variaveis globais
int coin_set[COIN_SET_SIZE];
int coin_type_amt;

int MEMO[MAX_VALUE + 1];

int min_coin_amt(int coin_change);

int main() {
    int test_amt, coin_change;
    cin >> test_amt;

    for (int i = 0; i < test_amt; i++) {
        cin >> coin_change >> coin_type_amt;

        for (int j = 0; j < coin_type_amt; j++) {
            cin >> coin_set[j];
        }

        // Inicializando o MEMO com valor fora do dominio
        memset(MEMO, NONE, sizeof MEMO);

        MEMO[0] = 0;
        MEMO[1] = 1;

        int answer = min_coin_amt(coin_change);
        cout << answer << '\n';
    }

    return EXIT_SUCCESS;
}

void print_MEMO() {
    for (int i = 0; i < MAX_VALUE; i++) {
        cout << MEMO[i] << ' ';
    }

    cout << '\n';
}

int min_coin_amt(int coin_change) {
    if (coin_change == 0) {
        return MEMO[0];
    }

    // Se ja calculei, nao preciso calcular novamente
    if (MEMO[coin_change] != NONE) {
        return MEMO[coin_change];
    }

    int min_amt = INT_MAX / 2;

    int i = 0;

    // Considerar apenas valores de moedas validos
    while (i < coin_type_amt and coin_change >= coin_set[i]) {
        int new_min = min(min_amt, min_coin_amt(coin_change - coin_set[i++]) + 1);

        if (new_min < min_amt) {
            min_amt = new_min;
        }

        MEMO[coin_change] = min_amt;
    }

    return MEMO[coin_change];
}