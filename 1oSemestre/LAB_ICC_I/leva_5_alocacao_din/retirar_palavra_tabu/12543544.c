// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_phrase();
void count_taboo(char *generic_phrase, char *taboo_word, int phrase_elements_amt);
char* remove_taboo(char *generic_phrase, char *taboo_word, int taboo_size, int *phrase_elements_amt);

int main() {
    // A palavra tabu pode ser alocada estaticamente
    // + 1 espaco para o '\0'
    // Ler dessa maneira a palavra tabu para ignorar o \n que resta
    char taboo[21];
    scanf("%s\n", taboo);
    int taboo_size = strlen(taboo);

    // Ler a frase dinamicamente
    char *phrase = read_phrase();

    // Qual eh o tamanho da frase? Agora que eu aloquei, eu tenho essa info
    // Adicione 1 para o '\0'
    int phrase_size = strlen(phrase) + 1;
    //Procure pela palavra tabu e conte suas ocorrencias

    // Printe o resultado
    count_taboo(phrase, taboo, phrase_size);
    phrase = remove_taboo(phrase, taboo, taboo_size, &phrase_size);

    // Desalocar a frase dinamicamente alocada
    free(phrase);

    return 0;
}

char* read_phrase() {
    char* phrase = NULL; 
    char current_char; 
    int phrase_size = 0; 

    do { 
        scanf("%c", &current_char); 
        phrase_size++; 

        phrase = (char*)realloc(phrase, sizeof(char) * phrase_size); 

        if (current_char != '$')
            phrase[phrase_size - 1] = current_char; 
        else
            phrase[phrase_size - 1] = '\0'; 
    } while (current_char != '$'); 

    return phrase;
}
void count_taboo(char *generic_phrase, char *taboo_word, int phrase_elements_amt) {
    int match = 0; 
    int count_match = 0; 

    for (int i = 0; i < phrase_elements_amt; i++) {
        int j = 0; 
        match = 1; 
        while (taboo_word[j] != '\0') {
            if (generic_phrase[i + j] != taboo_word[j] || i + j >= phrase_elements_amt) {
                match = 0;
                break; 
            }
            j++;
        }
        count_match += match; 
    } 

    printf("A palavra tabu foi encontrada %d vezes\n", count_match);
}

char* remove_taboo(char *generic_phrase, char *taboo_word, int taboo_size, int *phrase_elements_amt) {
    int match = 0; 
    int i = 0; 

    while (generic_phrase[i] != '\0') {
        int j = 0; 
        match = 1;
        while (taboo_word[j] != '\0') {
            if (generic_phrase[i + j] != taboo_word[j] || i + j >= (*phrase_elements_amt)) {
                match = 0;
                break; 
            }
            j++;
        }
        if (match == 1) {
            for (int j = i; generic_phrase[j + taboo_size] != '\0'; j++) {
                generic_phrase[j] = generic_phrase[j + taboo_size];
            }
            *phrase_elements_amt -= taboo_size;
            generic_phrase = (char*)realloc(generic_phrase, sizeof(char) * (*phrase_elements_amt));
            generic_phrase[*phrase_elements_amt - 1] = '\0';
        }
        else if (match == 0) {
            i++;
        }
    } 

    printf("Frase: %s", generic_phrase);

    return generic_phrase;
}