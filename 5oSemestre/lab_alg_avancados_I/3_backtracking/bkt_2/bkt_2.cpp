#include <iostream>

using namespace std;

string find_maximum_number(string& original, string& maximum, int swaps_left, int curr_idx);

int main() {
    string big_num;
    int max_swap_amt;

    cin >> big_num >> max_swap_amt;
    do {
        string max_num(big_num);
        string answer = find_maximum_number(big_num, max_num, max_swap_amt, 0);
        cout << answer << '\n';
    } while (cin >> big_num >> max_swap_amt);

    return EXIT_SUCCESS;
}

// Encontrar maior digito que o atual, olhando apenas a partir deste
int idx_of_greatest_number_in_range(string max_num, int idx_start, int idx_end) {
    int idx_of_greatest_n = idx_start;
    // Somente olhar posicoes que nao sofreram troca ainda para potencialmente trocarem com idx atual
    for (int i = idx_start + 1; i <= idx_end; i++) {
        if (max_num[i] > max_num[idx_of_greatest_n]) {
            idx_of_greatest_n = i; // Sempre acha maior numero ainda nao trocado de posicao 
        }
    }

    return idx_of_greatest_n;
}

string find_maximum_number(string& original, string& maximum, int swaps_left, int curr_idx) {
    // Fim das trocas quando: 
    // 1. passou do maximo de trocas estabelecido
    // 2. numero ja nao cresce mais

    if (swaps_left <= 0) {
        return maximum;
    }

    // Maior numero deve ser colocado sempre mais a esquerda... (alg. mais significativo)
    // Mas considerar digitos ainda nao trocados
    int idx_of_greatest_n = idx_of_greatest_number_in_range(maximum, curr_idx, maximum.size() - 1);
    
    if (idx_of_greatest_n != curr_idx) { // Pode ser que os digitos sejam iguais
        swaps_left--; // Fazer a troca para produzir numero maior
    }

    // Procure o maximo local entre o restante
    for (int i = (int)original.size() - 1; i >= curr_idx; i--) {
        // Maior digito esta como algarismo menos significativo, entao fazer ele ser mais significativo.
        // Isso evita com que troquemos o maior digito primeiro em uma posicao onde ele tem mais significancia
        // (se fizermos isso, reduzimos o valor do numero)
        if (original[i] == original[idx_of_greatest_n]) {
            swap(original[curr_idx], original[i]); // Pode ocorrer troca entre mesmos digitos (inaltera)

            // Numero atual ('original') eh maior que o maximo ate agora
            if (original.compare(maximum) > 0) { // Pode ser que a troca de digitos nao mude nada (digito igual)
                // Novo maximo
                maximum = original;
            }

            // Recursao para outras trocas, considerando prox idx
            find_maximum_number(original, maximum, swaps_left, curr_idx + 1);

            // Backtrack --> desfazer a troca no numero 'original' p/ testar outras poss. como forca bruta (mas mantendo 'maximum'!)
            swap(original[curr_idx], original[i]); 
        }
    }

    return maximum;
}