#include <stdio.h>

int main() {  
    // A entrada começa com um no inteiro n - altura do triângulo
    int altura_triangulo;
    scanf("%d\n", &altura_triangulo);
    
    // Caractere de formação do triângulo
    char simbolo;
    scanf("%c", &simbolo); // Colocamos espaço %c para que o teclado não leia nosso enter após o primeiro scanf
   
    if(altura_triangulo <= 0 || altura_triangulo > 25) {
        printf("Altura invalida\n");
        return 0; // Caso isso aconteça, encerra o programa aqui. Caso o inteiro seja > 0 && <= 25, continua com o for
    }

    // Esse for está imprimindo uma qtd de linhas = ao inteiro digitado - 1; depois, qtd_linhas varia -> usamos isso pra controlar os outros for dependentes desse
    for(int qtd_linhas = 0; qtd_linhas < altura_triangulo; qtd_linhas++) { 
        
        for(int qtd_espacos = altura_triangulo - qtd_linhas - 1; qtd_espacos > 0; qtd_espacos--) { // Precisa repetir n-1 vezes, depois n -1 -1 vezes, depois n-1-1-1 vezes...
            printf(" ");
        }

        for(int qtd_simbolos = 0; qtd_simbolos < qtd_linhas * 2 + 1; qtd_simbolos++) { // Precisa fazer 1 vez, depois 1+2 vezes, depois 3+2 vezes, depois 5+2 vezes...
            printf("%c", simbolo);
        }

        printf("\n");
    }
        
    return 0;
}