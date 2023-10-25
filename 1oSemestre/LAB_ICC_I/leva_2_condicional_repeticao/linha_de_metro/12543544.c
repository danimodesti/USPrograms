// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    // Entrada
    int start_station; // Estacao onde Pedro pega o metro; numero de 0 a 9

    scanf("%d", &start_station);

    // Processamento e saida
    switch (start_station) {
        case 0: 
            printf("* Morumbi\n|\n");
        case 1: 
            printf("* Butanta\n|\n");
        case 2: 
            printf("* Pinheiros\n|\n");
        case 3: 
            printf("* Faria Lima\n|\n");
        case 4: 
            printf("* Fradique Coutinho\n|\n");
        case 5: 
            printf("* Oscar Freire\n");
            break;
        case 6: 
            printf("* Paulista\n|\n");
        case 7: 
            printf("* Higienopolis-Mackenzie\n|\n");
        case 8: 
            printf("* Republica\n|\n");
        case 9: 
            printf("* Luz\n");
            break;
        default: 
            printf("Estacao invalida\n");
            break;
    }

    return 0;
}