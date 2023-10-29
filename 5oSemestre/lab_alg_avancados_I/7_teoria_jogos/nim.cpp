#include <iostream>
#include <vector>

using namespace std;

bool second_player_starts_winning(int pile_amt, vector<long> stone_amt);
void print_vector(int size, vector<long> vec);

int main() {
    int case_amt;
    cin >> case_amt;

    int pile_amt;
    vector<long> stone_amt; 
    long curr_stone_amt;
    for (int i = 0; i < case_amt; i++) {
        cin >> pile_amt;

        for (int j = 0; j < pile_amt; j++) {
            cin >> curr_stone_amt;

            // Ver quantas pedras vai tirar - 1, 2, 3
            stone_amt.push_back(curr_stone_amt % 4);
        }
        
        if (second_player_starts_winning(pile_amt, stone_amt)) {
            // Se o primeiro jogador (trapaceiro) comeca em 'estado perdedor',
            // todo movimento que ele fizer o leva a um 'estado ganhador' (as xors != 0).
            // Por outro lado, existe algum movimento do segundo jogador que pode fazer
            // o primeiro jogador voltar ao 'estado perdedor'.
            cout << "second\n"; // Como qualquer movimento vale, basta mover 1 pedra
        }

        else {
            cout << "first\n"; // O trapaceiro ja comecou em estado vencedor
        }

        stone_amt.clear(); // Limpar elementos do vetor
    }

    return EXIT_SUCCESS;
}

bool second_player_starts_winning(int pile_amt, vector<long> stone_amt) {
    long long X_value = stone_amt[0];

    for (int i = 1; i < pile_amt; i++) {
        X_value = X_value ^ stone_amt[i]; // s_0 xor s_1 xor s_2 ... xor s_pile_amt-1
    }


    // Pode ser provado que se X = 0, o segundo jogador sempre pode achar
    // uma maneira de ganhar (ambos jogam de forma optima) - 'estado vencedor'
    return (X_value == 0);
}

void print_vector(int size, vector<long> vec) {
    for (int i = 0; i < size; i++) {
        cout << vec[i] << ' ';
    }

    cout << '\n';
}