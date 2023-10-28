#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define DELIMITER 0

// Problemas de teoria dos numeros frequentemente trabalham com numeros grande
typedef long long ll;
typedef vector<ll> vll;

vll numbers_to_test_gcd();
ll number_that_leaves_same_remainder(vll& numbers);
void print_vector(vll& numbers);

int main() {
    vll numbers;

    do {
        numbers = numbers_to_test_gcd();

        if (!numbers.empty()) {
            ll answer = number_that_leaves_same_remainder(numbers);
            cout << answer << '\n';
        }    
    } while (!numbers.empty());

    return EXIT_SUCCESS;
}

vll numbers_to_test_gcd() {
    ll new_number;
    vll numbers;

    while (cin >> new_number && new_number != DELIMITER) { // Enqt for possivel ler um numero
        if (new_number != DELIMITER) {
            numbers.push_back(new_number);
        }
    }

    return numbers;
}

void compute_differences(vll& numbers) {
    for (ll i = numbers.size() - 1; i > 0; i--) {
        numbers[i] -= numbers[i - 1];
    }
}

// Algoritmo de Euclides para MDC
ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }

    else {
        return gcd(b, a % b);
    }
}

ll number_that_leaves_same_remainder(vll& numbers) {
    // Os numeros devem ser ordenados
    sort(numbers.begin(), numbers.end());

    // Para o mesmo resto de divisao, importa a diferenca entre o numero seguinte e o atual (idx 0 ignorado)
    compute_differences(numbers);

    ll mdc = gcd(numbers[1], numbers[2]);

    for (int i = 3; i < (int)numbers.size(); i++) {
        // Pegar o Maximo Divisor Comum pensando em todos os numeros do caso de teste
        mdc = gcd(mdc, numbers[i]);
    }

    return mdc;
}

void print_vector(vll& numbers) {
    for (int i = 0; i < (int)numbers.size(); i++) {
        cout << numbers[i] << ' ';
    }

    cout << '\n';
}