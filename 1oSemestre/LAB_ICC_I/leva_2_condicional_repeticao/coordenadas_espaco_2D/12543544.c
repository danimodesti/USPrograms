// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    char displacement;
    int i; // Para controlar que o usuario digite algo 6 vezes
    int x = 0, y = 0; // Para controlar as coordenadas
   // x = 0;
    //y = 0;

   for (i = 0; i <= 5; i++) { // Loop 6 vezes para inserir 6 entradas 
        scanf("%c", &displacement); // Guarde o char na variavel displacement
        
        if (displacement == 'W') y++;
        else if (displacement == 'S') y--;
        else if (displacement == 'A') x--;
        else x++; // Caso displacement == 'D'
    }

    printf("%d %d\n", x, y);

    return 0;
}