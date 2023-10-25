/*
 * Danielle Modesti
 * No USP: 12543544
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Para usar isalnum() - verificar se um char eh alfanumerico
#include <stdbool.h>

#define SLASH '/'
#define SPACE ' '

char *read_line();
bool check_palindrome(int first_char, int last_char, char *string_to_check);
bool decide_between_palindromes(int first_char, int last_char, char *string_to_check);
int string_length(char *generic_string);

int main() {
    // Receber mensagem de Danny, mas so considerar caracteres alfanumericos, 
    // barra e espaco.
    char *message = read_line();

    // Eh importante saber o primeiro e o ultimo chars para ir comparando um a um
    int crescent_char_index = 0;
    int decrescent_char_index = string_length(message) - 1; // Porque o C conta a partir do zero

    bool is_palindrome = check_palindrome(crescent_char_index, decrescent_char_index, message);

    if (is_palindrome == false) {
        printf("Nao eh um palindromo\n");
    }
    else {
        bool is_indirect = decide_between_palindromes(crescent_char_index, decrescent_char_index, message);

        if (is_indirect == true) {
            printf("Palindromo indireto\n");
        }
        else {
            printf("Palindromo direto\n");
        }
    }

    free(message);

    return EXIT_SUCCESS;
}

/* Receber a mensagem, ja considerando apenas os caracteres alfanumericos
 * alem do espaco e da barra.
 * Alem disso, decidi converter todos os caracteres para minusculo, ja que 
 * eh preciso considera-los equivalentes. Assim, poderei compara-los mais
 * facilmente.
 */ 

char *read_line() {
    char *line = NULL; 
    char curr_char; 
    int line_size = 0; 

    do { 
        curr_char = getchar();

        // Alocar espacos somente se satisfizer essas condicoes
        if (curr_char == '\n' || isalnum(curr_char) || curr_char == SPACE || curr_char == SLASH) {
            line_size++; 
            line = (char *) realloc(line, sizeof(char) * line_size); 
        }

        if (curr_char != '\n' && (isalnum(curr_char) || curr_char == SPACE || curr_char == SLASH)) {
            line[line_size - 1] = tolower(curr_char); 
        }
        else if (curr_char == '\n') {
            line[line_size - 1] = '\0'; 
        }
    } while (curr_char != '\n'); 

    return line;
}

/*
 * Na checagem de caracteres iguais para palindromo, caso o caractere 'crescente', que
 * representa o que comeca no primeiro da string, for maior que o caractere 'decrescente (ocorre com qtd char par), 
 * que representa o que começa no ultimo da string, isso significa que estamos checando
 * posicoes ja checadas antes e que ja sao iguais. 
 * 
 * Caso o indice do caractere 'crescente' for igual ao do 'decrescente' (ocorre com qtd char impar),
 * significa que eh palindromo, pois eles sao iguais!
 * 
 * Essas sao as condicoes de parada para a recursao.
 * 
 * Caso eu encontre caracteres diferentes, devo parar a recursao tambem. Nao terei um palindromo,
 * nao ha por que continuar checando.
 */

bool check_palindrome(int first_char, int last_char, char *string_to_check) {
    bool is_palindrome = true;

    // Checar se ja verifiquei os indices
    if (first_char >= last_char) {
        return is_palindrome;
    }
    
    else {
        // Pular as barras
        if (string_to_check[first_char] == SLASH || string_to_check[first_char] == SPACE) {
            return check_palindrome(first_char + 1, last_char, string_to_check); 
        }

        if (string_to_check[last_char] == SLASH || string_to_check[last_char] == SPACE) {
            return check_palindrome(first_char, last_char - 1, string_to_check); 
        }

        if (string_to_check[first_char] != string_to_check[last_char]) {
            return is_palindrome = false;
        }

        // Passo recursivo
        return check_palindrome(first_char + 1, last_char - 1, string_to_check); 
    }
}

int string_length(char *generic_string) {
    int length = 0;
    while (generic_string[length] != '\0') {
        length++;
    }

    return length;
}

/*
* Ja verifiquei anteriormente se eh um palindromo. Agora, basta decidir se
* o palindromo eh indireto ou direto. Caso os chars forem diferentes em algum
* momento, ja sei que o palindromo eh indireto.
* 
* Se todos os indices foram verificados e, em nenhum momento, os elementos forem
* diferentes, eh palindromo direto.
*/

bool decide_between_palindromes(int first_char, int last_char, char *string_to_check) {
    bool is_indirect = false;

    if (first_char >= last_char) {
        is_indirect = false;
    }
    else if (string_to_check[first_char] != string_to_check[last_char]) {
        is_indirect = true;
    }
    else if (string_to_check[first_char] == string_to_check[last_char]) {

        // Passo recursivo
        return decide_between_palindromes(first_char + 1, last_char - 1, string_to_check); 
    }
    
    return is_indirect;
}