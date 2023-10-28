#include <iostream>
#include <vector>
#include <stack>

#define DELIMITER '#'
#define MAX_DIGITS_AMT 10000

using namespace std;

typedef vector<int> vi;

int prime = 131071; // Nenhum valor passa desse

// Guardar potencias de dois ate 2 ^ 10 000 mod prime
vi powers_of_two_mod(MAX_DIGITS_AMT);

void compute_powers_of_two();
vi read_number();
int compute_module(vi& bin_number);

int main() {
    compute_powers_of_two(); // Ja no espaco Z_prime

    vi bin_number;

    do {
        bin_number = read_number();

        if (!bin_number.empty()) {
            int module = compute_module(bin_number);

            if (module == 0) { // Numero eh divisivel por 131071
                cout << "YES\n";
            }

            else {
                cout << "NO\n";
            }
        }
    } while (!bin_number.empty());

    return EXIT_SUCCESS;
}

void compute_powers_of_two() {
    int power = 1;

    for (int i = 0; i <= MAX_DIGITS_AMT; i++) {
        powers_of_two_mod[i] = power;

        power = (power * 2) % prime; // Para caber na variavel (espaco em modulo)
    }
}

vi read_number() {
    stack<int> bin_digits; // Para ler os digitos do LSB ate o MSB

    char digit;
    while (cin >> digit && digit != DELIMITER) {
        if (digit == '0') {
            bin_digits.push(0);
        }

        else if (digit == '1') { // Cuidado com digitos '\n' (numero pode continuar em outra linha)
            bin_digits.push(1);
        }
    }

    // Armazenando na ordem correta os digitos binarios
    vi bin_number;
    while (!bin_digits.empty()) {
        digit = bin_digits.top(); bin_digits.pop();
        bin_number.push_back(digit);
    }

    return bin_number;
}

int compute_module(vi& bin_number) {
    int module = 0; 

    for (int i = 0; i < (int)bin_number.size(); i++) { // Para cada digito do numero binario
        if (bin_number[i] == 1) { // Digitos validos
            module = (module + powers_of_two_mod[i]) % prime;
        }
    }

    return module; // Numero dado na entrada no espaco Z_prime
}