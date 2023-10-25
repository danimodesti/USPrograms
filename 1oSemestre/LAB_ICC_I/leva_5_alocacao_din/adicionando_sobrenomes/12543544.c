// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

char *read_full_name(int *is_last_name);
int find_last_name_beginning(char *name_to_copy);
char *get_last_name(char *last_name_to_copy, int begin_last_name);
char *make_new_last_name(char *renamed_person, char *new_last_name);
int string_length(char *generic_string);
char *string_append(char *first_string, char *second_string);

int main() {
    // Criar uma lista (a qual tem um ponteiro para indicar seu inicio)
    // com varios nomes completos (cada nome tem um ponteiro para o inicio do nome)
    // Inicia sem nomes
    char **list_of_full_names = NULL;

    // Leia um nome completo e guarde na lista
    int index_curr_name = 0;
    int is_last_name = 0;
    while (is_last_name == 0) {
        list_of_full_names = (char **) realloc(list_of_full_names, (index_curr_name + 1) * sizeof(char *));
        list_of_full_names[index_curr_name] = read_full_name(&is_last_name); 
        index_curr_name++;
    }

    // Armazene e replique o sobrenome 
    int beginning_last_name;
    for (int i = 1; i < index_curr_name; i += 2) {
        beginning_last_name = find_last_name_beginning(list_of_full_names[i - 1]);
        char *hold_last_name = get_last_name(list_of_full_names[i - 1], beginning_last_name);
        list_of_full_names[i] = make_new_last_name(list_of_full_names[i], hold_last_name);
        free(hold_last_name);
    }

    for (int i = 0; i < index_curr_name; i++) {
        printf("%s\n", list_of_full_names[i]);
    }

    // Liberando a memoria dinamicamente alocada
    // Do mais especifico para o mais geral
    for (int i = 0; i < index_curr_name; i++) {
        free(list_of_full_names[i]);
    }
    free(list_of_full_names);

    return 0;
}

char *read_full_name(int *is_last_name) {
    char *full_name = NULL; 
    char curr_char; 
    int full_name_size = 0; 

    do { 
        scanf("%c", &curr_char); 
        full_name_size++; 

        full_name = (char *) realloc(full_name, sizeof(char) * full_name_size); 

        if (curr_char != '\n' && curr_char != '$') {
            full_name[full_name_size - 1] = curr_char; 
        }
        else {
            full_name[full_name_size - 1] = '\0'; 
        }
    } while (curr_char != '\n' && curr_char != '$'); 

    // A main enxerga que chegou ao ultimo nome quando passamos essa variavel
    // por referencia pra essa funcao
    if (curr_char == '$') {
        *is_last_name = 1;
    }

    return full_name;
}

int find_last_name_beginning(char *name_to_copy) {
    // Farei uma varredura no nome, procurando o '\0' 
    // de fim de string e voltando ate encontrar um espaco, que indica
    // que ali comeca o ultimo sobrenome
    int curr_char_index = 0;
    while(name_to_copy[curr_char_index] != '\0') {
        curr_char_index++;
    }

    while(name_to_copy[curr_char_index] != ' ') {
        curr_char_index--;
    }

    return curr_char_index;
}

char *get_last_name(char *last_name_to_copy, int begin_last_name) {
    char *last_name = NULL; 
    int last_name_size = 0; 

    // Como eu sei o comeco do sobrenome, copio a partir desse ponto
    // para, posteriormente, 'colar' no proximo elemento da lista de nomes 
    do { 
        last_name_size++; 
        last_name = (char *) realloc(last_name, sizeof(char) * (last_name_size + 1)); 

        if (last_name_to_copy[begin_last_name] != '\0') {
            last_name[last_name_size - 1] = last_name_to_copy[begin_last_name]; 
        }
        else {
            last_name[last_name_size - 1] = '\0'; 
        }
    } while (last_name_to_copy[begin_last_name++] != '\0'); 

    return last_name;
}

char *make_new_last_name(char *renamed_person, char *new_last_name) {
    int renamed_person_size = string_length(renamed_person) + string_length(new_last_name) + 1;
    renamed_person = (char *) realloc(renamed_person, sizeof(char) * renamed_person_size);

    renamed_person = string_append(renamed_person, new_last_name);

    return renamed_person;
}

int string_length(char *generic_string) {
    int length = 0;
    while (generic_string[length] != '\0') {
        length++;
    }

    return length;
}

char *string_append(char *original_string, char *appendix_string) {
    int original_length = string_length(original_string);
    int appendix_length = string_length(appendix_string);

    int concatenated_length = original_length + appendix_length + 1;
    char *concatenated_string = (char *) realloc(original_string, concatenated_length * sizeof(char));

    for (int i = original_length, j = 0; j <= appendix_length; i++, j++) {
        concatenated_string[i] = appendix_string[j];
    }

    return concatenated_string;
}