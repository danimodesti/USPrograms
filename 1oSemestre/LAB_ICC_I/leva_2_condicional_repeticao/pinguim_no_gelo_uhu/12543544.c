// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    int n; // Numero maximo de rodadas
    int m; // Numero de jogadores
    int p; // Posicao de Pingu na ordem de rodadas.
    //int count_pinguim; // contadores da lista

    scanf("%d %d %d", &n, &m, &p); // Valores para o jogo

    int read_statement = 1; // Contador de leituras de frases
    int current_round = 1; // Comece no round 1
    while (current_round <= n) { // Repetir o processo ate o numero maximo de rodadas

        // Usar i para repetir os statements se necessario, quantas vezes precisar
        // Pingu esta falando o que esta no current_round % m == (p % m)
        // p % m trata todos os casos, pois se p < m pega o resto e se p = m pega zero 
        for (int i = 0; i < read_statement; i++) {
            if (current_round % m == (p % m) && current_round <= n) { // Nao esquecer de testar se ja nao acabou a qtd maxima de rodadas
                if (current_round == 1) printf("%d pinguim\n", read_statement);
                else printf("%d pinguins\n", read_statement);
            }
            current_round++; // Va pro prox round
        }
        for (int i = 0; i < read_statement; i++) {
            if (current_round % m == (p % m) && current_round <= n) {
                printf("no gelo\n");
            }
            current_round++; // Va pro prox round
        }
        for (int i = 0; i < read_statement; i++) {
            if (current_round % m == (p %m) && current_round <= n) {
                printf("uhuu!\n");
            }  
            current_round++; // Va pro prox round
        }   
        read_statement++; // Na proxima iteracao, repete mais uma vez cada statement
    }
    
    return 0;
}