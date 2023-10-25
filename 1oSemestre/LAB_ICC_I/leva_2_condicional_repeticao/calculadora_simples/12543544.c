#include <stdio.h>

int main() {
    float a, b, resultado_op; 
    char op; // Operador

    scanf("%f %c %f", &a, &op, &b);

    // Determinar qual operacao realizar dependendo da leitura de op
    switch(op) {
        case '+': 
            resultado_op = a + b;
            printf("%.6f\n", resultado_op);
            break;
        case '-':
            resultado_op = a - b;
            printf("%.6f\n", resultado_op);
            break;
        case '*':
            resultado_op = a * b;
            printf("%.6f\n", resultado_op);
            break;
        case '/':
            if (b == 0) { 
                printf("Operacao invalida\n");
                return 0;
            }
            else {
            resultado_op = a / b;
            printf("%.6f\n", resultado_op);
            }
            break;
        case '%':
            if (b == 0) { 
                printf("Operacao invalida\n");
                return 0;
            }
            else {
            resultado_op = (a * 100) / b; 
            printf("%.6f\n", resultado_op);
            }
            break;
        default:
            printf("Operacao invalida\n");
            break;
    }

    return 0;
}