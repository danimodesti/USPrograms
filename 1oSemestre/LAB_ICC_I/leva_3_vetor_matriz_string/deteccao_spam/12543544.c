// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

// As strings tem tamanho variavel, mas terminam no '\0'

// Podemos escrever string[], pois o compilador sabe contar o tamanho de strings estaticas
int searching_string(char row[76], char searched_string[]); // Procurar string proibida na linha

int main() {
    char email[76]; // o vetor de char = a string para cada linha

    // Strings proibidas -> 5 tipos de comparacao: comparar 8 chars, 7 chars, 6 chars, 5 chars, 3 chars
    char prohibited_1[] = "gratuito"; // "" inserem \0 no vetor
    char prohibited_2[] = "limitado";
    char prohibited_3[] = "imediato";
    char prohibited_4[] = "dinheiro";

    char prohibited_5[] = "atencao";
    char prohibited_6[] = "urgente";
    char prohibited_7[] = "zoombie";

    char prohibited_8[] = "oferta";

    char prohibited_9[] = "renda";
    char prohibited_10[] = "fundo";
    char prohibited_11[] = "ajuda";

    char prohibited_12[] = "SOS";

    int current_index = 0; // Comecar na posicao 0 da string. Por linha, conte ate 76 - eh o maximo de chars para nao ser spam

    int count_prohibited = 0; // Se tiver 2 ou +, vai pro Spam 

    while(scanf("%c", &email[current_index]) != EOF) {

        if (email[current_index] == '\n') { // Sinaliza prox linha

            // Com os chars da linha completa, testar correspondencia com palavras proibidas na mesma linha
            count_prohibited += searching_string(email, prohibited_1);
            count_prohibited += searching_string(email, prohibited_2);
            count_prohibited += searching_string(email, prohibited_3);
            count_prohibited += searching_string(email, prohibited_4);
            count_prohibited += searching_string(email, prohibited_5);
            count_prohibited += searching_string(email, prohibited_6);
            count_prohibited += searching_string(email, prohibited_7);
            count_prohibited += searching_string(email, prohibited_8);
            count_prohibited += searching_string(email, prohibited_9);
            count_prohibited += searching_string(email, prohibited_10);
            count_prohibited += searching_string(email, prohibited_11);
            count_prohibited += searching_string(email, prohibited_12);

            current_index = 0; // Recomece a contagem para a prox linha
        }
        else {
            current_index++;
        }
        if (current_index > 76 || count_prohibited >= 2) {
            printf("Spam\n"); // Linha muito grande

            return 0; // Sai do loop e termina
        }
    }

    printf("Inbox\n");
    
    return 0;
}

int searching_string(char row[76], char searched_string[]) {
    int match = 0; // Nao ha compatibilidade do char lido na linha com o lido na string
    int count_match = 0; // Contar palavras proibidas encontradas na mesma linha

    for (int i = 0; i < 76; i++) {
        int j = 0; // Percorre a string
        match = 1; // Suponha que o valor no indice da string eh compativel com o valor lido na linha
        while (searched_string[j] != '\0') {
            if (row[i + j] != searched_string[j] || i + j >= 76) { // Se estiver no loop e i + j > = 76 -> palavra proibida nao chegou ao fim
                match = 0;
                break; // Nao precisa continuar procurando
            }
            j++;
        }
        count_match += match; // Contar palavras proibidas naquela linha
    }

    return count_match;
}