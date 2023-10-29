#include <iostream>

using namespace std;

void generate_words(string& original, string& new_word, int curr_idx);

int main() {
    string curr_str = "";
    while (getline(cin, curr_str)) {
        string s = "";
        generate_words(curr_str, s, 0);
        cout << '\n';
    }


    return EXIT_SUCCESS;
}

// Funcao de backtracking
void generate_words(string& original, string& new_word, int curr_idx) {
    if (curr_idx >= (int)original.size()) {
        cout << new_word << '\n';

        return;
    }

    // New word representa a string a ser gerada em sua forma atual
    string spaceless_new_word(new_word);
    spaceless_new_word.push_back(original[curr_idx]);
    generate_words(original, spaceless_new_word, curr_idx + 1);

    if (curr_idx != 0) { // Adicionar espacos em branco a esquerda de cada letra (exceto da primeira)
        string spaced_new_word(new_word);
        spaced_new_word.push_back(' ');
        spaced_new_word.push_back(original[curr_idx]);
        generate_words(original, spaced_new_word, curr_idx + 1);
    }
}