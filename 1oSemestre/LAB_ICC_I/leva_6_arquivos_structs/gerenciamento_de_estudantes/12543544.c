/*
 * Danielle Modesti
 * No USP: 12543544
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum Operation {
    FIND_STUDENT_ID = 1,
    FIND_STUDENT_COURSE = 2,
    FIND_ALL_STUDENTS = 3,
    FINISH_OPERATIONS = -1
} operation_t;

typedef struct StudentRegister {
    int id;
    char *name;
    char *course;
    int age;
} student_register_t;

char *read_line();
int string_length(char *generic_string);
bool is_string_match(char *string_1, char *string_2);
void print_student_info(student_register_t *student_register_list, int index);
void free_memory(student_register_t *student_register_list, int student_amt);

int main() {
    // Criar lista guardando registros de varios estudantes
    student_register_t *all_registers = NULL;
    int student_amt = 0;

    int command;
    scanf("%d\n", &command);
    
    while (command != -1) {
        all_registers = (student_register_t *) realloc(all_registers, (student_amt + 1) * sizeof(student_register_t));

        all_registers[student_amt].id = command;
        all_registers[student_amt].name = read_line();
        all_registers[student_amt].course = read_line();
        scanf("%d", &all_registers[student_amt].age); 
        student_amt++; 

        scanf("%d\n", &command);
    }

    // Agora, faca operacoes com a lista de estudantes armazenada 
    int searched_id;
    char *searched_course;
    int choose_operation;
    do {
        scanf("%d", &choose_operation);
        switch (choose_operation) {
            case FIND_STUDENT_ID:
                scanf("%d", &searched_id);

                int searched_index = 0;
                while (all_registers[searched_index].id != searched_id && searched_index < (student_amt - 1)) {
                    searched_index++;
                }

                if (all_registers[searched_index].id == searched_id) {
                    print_student_info(all_registers, searched_index);
                }
                else {
                    printf("Aluno nao cadastrado\n");
                }
                break;
            case FIND_STUDENT_COURSE:
                searched_course = read_line();

                searched_index = 0;
                while (searched_index < (student_amt - 1)) {
                    int match = is_string_match(all_registers[searched_index].course, searched_course);
                    if (match) {
                        print_student_info(all_registers, searched_index);
                    }
                    searched_index++;
                }
                free(searched_course);
                break;
            case FIND_ALL_STUDENTS:
                for (int i = 0; i < student_amt; i++) {
                    print_student_info(all_registers, i);
                }
                break;
            case FINISH_OPERATIONS:
                break;
            default:
                printf("Operacao invalida! =(\n");
                break;
        }
    } while (choose_operation != FINISH_OPERATIONS);

    // Liberar memoria dinamicamente alocada
    free_memory(all_registers, student_amt);

    return 0;
}

char *read_line() {
    char *line = NULL; 
    char current_char; 
    int line_size = 0; 

    do { 
        current_char = getchar();
        line_size++; 

        // Usar realloc para alocar novos espacos a cada iteracao do loop
        line = (char *) realloc(line, sizeof(char) * line_size); 

        if (current_char != '\n')
            line[line_size - 1] = current_char; 
        else
            line[line_size - 1] = '\0'; 
    } while (current_char != '\n'); 

    return line;
}

// Para comparar as strings
bool is_string_match(char *string_1, char *string_2) {
    int string_1_len = string_length(string_1);
    int string_2_len = string_length(string_2);
    bool match = false;

    if (string_1_len != string_2_len) {
        return match;
    }
    else {
        int i = 0;
        int char_amt = string_1_len;
        while (string_1[i] == string_2[i] && i < char_amt) {
            i++;
        }
        if (i == char_amt) {
            match = true;
        }
    }

    return match;
}

int string_length(char *generic_string) {
    int length = 0;
    while (generic_string[length] != '\0') {
        length++;
    }

    return length;
}

void print_student_info(student_register_t *student_register_list, int index) {
    printf("Nome: %s\n", student_register_list[index].name);
    printf("Curso: %s\n", student_register_list[index].course);
    printf("N USP: %d\n", student_register_list[index].id);
    printf("IDADE: %d\n\n", student_register_list[index].age);
}

void free_memory(student_register_t *student_register_list, int student_amt) {
    for (int i = 0; i < student_amt; i++) {
        free(student_register_list[i].name);
        free(student_register_list[i].course);
    }
    free(student_register_list);
}