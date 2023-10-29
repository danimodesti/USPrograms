#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> vi; // Guardar ocorrencias do padrao

vi create_lps_table(string pattern);
vi kmp(string text, string pattern, vi lps_table);

int main() {
    string pattern, text;
    cin >> text >> pattern;

    vi lps = create_lps_table(pattern);
    vi occurrences = kmp(text, pattern, lps);
    cout << (int) occurrences.size() << '\n';

    return EXIT_SUCCESS;
}

// A LPS serve para nao precisar voltar no texto (abordagem 'naive').
// O 'texto' nao importa, apenas o padrao/pattern.
// Criar 'memoria' de ate onde ja foi conferido e a partir de qual
// indice eh preciso testar (nao reconferir quando nao necessario).
vi create_lps_table(string pattern) {
    int pattern_len = pattern.length();
    vi lps_table(pattern_len);
    lps_table[0] = 0; // Nao tem onde voltar

    int j = 0; // Comparar prefixos
    for (int i = 1; i < pattern_len; i++) { // Comparar em tudo (str do comeco ao fim)        
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps_table[j - 1];
        }

        // Se as letras coincidirem, mova i (ja feito no for) e j
        if (pattern[i] == pattern[j]) {
            j++; // Acumular prefixo
        }

        // Para saber onde voltar no prefixo (para qual 'indice + 1')
        lps_table[i] = j;
    }

    return lps_table;
}

vi kmp(string text, string pattern, vi lps_table) {
    int pattern_len = pattern.length();
    int text_len = text.length();
    vi occurrences; // Nao se sabe quantas

    int j = 0; 
    for (int i = 0; i < text_len; i++) { // Parsing. i nunca retrocede (ganha eficiencia)
        
        while (j > 0 && text[i] != pattern[j]) {
            j = lps_table[j - 1];
        }

        // Se as letras coincidirem, mova i (ja feito no for) e j
        if (text[i] == pattern[j]) {
            j++; // Acumular prefixo
        }

        // Encontrou o padrao
        if (j == pattern_len) {
            // i --> esta no ultimo indice da ocorrencia do padrao
            // subtrair pattern_len para voltar para o indice anterior ao do inicio do padrao
            // + 1 para ir para o primeiro indice da ocorrencia
            // + 1 para corrigir a interpretacao (no problema, o indice comeca em 1, nao em 0)
            occurrences.push_back(i - pattern_len + 2);

            j = lps_table[j - 1]; // Voltar no prefixo onde estava acumulado para que 'i' nao precise retroceder
        }
    }

    return occurrences;
}