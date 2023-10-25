// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

#define ADD '+'
#define SUBTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'
#define SPACE ' '

double do_operation(char operation, double operand_1, double operand_2);

int main() {
    // Vetor alocado dinamicamente, armazena os valores da pilha
    double *stack_data = (double *) malloc(sizeof(double));
    
    int element_on_top_index = 0; 
    char curr_char;
    while ((curr_char = getchar()) != EOF) {
        if (curr_char == ADD || curr_char == SUBTRACT || curr_char == MULTIPLY || curr_char == DIVIDE) {
            stack_data[element_on_top_index - 2] = do_operation(curr_char, stack_data[element_on_top_index - 2], stack_data[element_on_top_index - 1]);
            // Falta desempilhar o valor no topo da stack - posso jogar ele fora com o realloc
            element_on_top_index--;
            stack_data = (double *) realloc(stack_data, sizeof(double) * element_on_top_index);
        }
        else if (curr_char != SPACE) {
            if (element_on_top_index > 0) {
                stack_data = (double *) realloc(stack_data, sizeof(double) * (element_on_top_index + 1));
            }
            ungetc(curr_char, stdin);
            scanf("%lf", &stack_data[element_on_top_index]);
            element_on_top_index++;
        }
    }

    // Saida
    printf("Resultado: %.6lf\n", stack_data[element_on_top_index - 1]); 

    // Liberar a memoria dinamicamente alocada
    free(stack_data);

    return 0;
}

double do_operation(char operation, double operand_1, double operand_2) {
    double operation_result;
    switch(operation) {
        case ADD:
            operation_result = operand_1 + operand_2;
            break;
        case SUBTRACT:
            operation_result = operand_1 - operand_2;
            break;
        case MULTIPLY:
            operation_result = operand_1 * operand_2;
            break;
        case DIVIDE:
            operation_result = operand_1 / operand_2;
            break;
    }

    return operation_result;
}