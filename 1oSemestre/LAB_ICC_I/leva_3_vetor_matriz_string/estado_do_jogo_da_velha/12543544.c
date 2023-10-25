#include <stdio.h>

int main() {
    char velha[3][3];

    // Percorra a matriz, testando casos de estado do jogo

    int count_diagonal_princip_x = 0; // Se a contagem der 3 nas condicoes do loop, x ganhou
    int count_diagonal_princip_o = 0; // Se a contagem der 3 nas condicoes do loop, o ganhou

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) 
            scanf(" %c", &velha[i][j]);   // Leia o estado do jogo da velha, coluna a coluna
    }

    int count_linha_x, count_linha_o, count_coluna_x, count_coluna_o;
    int count_hifen = 0;

    // Varra a matriz
    for (int i = 0; i < 3; i++) {

        count_linha_x = 0;
        count_linha_o = 0;
        
        count_coluna_x = 0;
        count_coluna_o = 0;

        for (int j = 0; j < 3; j++) {

            // Teste diagonal principal
            if (i == j) {
                if (velha[i][j] == 'x')
                    count_diagonal_princip_x++;
                else if (velha[i][j] == 'o')
                    count_diagonal_princip_o++;
            }

            // Teste linhas
            if (velha[i][j] == 'x')
                count_linha_x++;
            else if (velha[i][j] == 'o')
                count_linha_o++;

            // Teste colunas
            if (velha[j][i] == 'x')
                count_coluna_x++;
            else if (velha[j][i] == 'o')
                count_coluna_o++; 

            // Tem hifen? Se sim e nao cumpriu as outras condicoes, o jogo tah em andamento
            if (velha[i][j] == '-')
                count_hifen++;
        }
        
        if (count_linha_x == 3 || count_linha_o == 3)
            break;
        else if (count_coluna_x == 3 || count_coluna_o == 3)
            break;
    }
    
    // Teste diag secundaria
    int count_diagonal_secund_x = 0;
    int count_diagonal_secund_o = 0;
    int j = 2;

    for (int i = 0; i < 3; i++) {
        if (velha[i][j] == 'x') {
            count_diagonal_secund_x++;
            j--;
        }
        else if (velha[i][j] == 'o') {
            count_diagonal_secund_o++;
            j--;
        }
    }

    if (count_diagonal_princip_x == 3 || count_linha_x == 3 || count_coluna_x == 3 || count_diagonal_secund_x == 3)
        printf("x ganhou\n");
    else if (count_diagonal_princip_o == 3 || count_linha_o == 3 || count_coluna_o == 3 || count_diagonal_secund_o == 3)
        printf("o ganhou\n");
    else if (count_hifen > 0)
        printf("em jogo\n");
    else
        printf("empate\n");

    return 0;
}