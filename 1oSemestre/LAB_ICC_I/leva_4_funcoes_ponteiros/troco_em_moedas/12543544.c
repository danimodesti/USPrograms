// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

#define CENT_TYPE 6 // 100 cent (1 real), 50 cent, 25 cent, 10 cent, 5 cent, 1 cent

void coin_change(int* payment, int coin_amount[CENT_TYPE]); // Passa &coin_amount[0] -> referencia. Nao tem retorno pois queremos alterar os valores nos proprios enderecos

int main() {
    int payment; // Valor dado para que se retorne o troco em centavos deste

    scanf("%d", &payment);

    int coin_amount[CENT_TYPE] = {}; // Supor que nao precisa de troco primeiro

    coin_change(&payment, coin_amount); // Passagem de parametros por referencia

    for (int i = 0; i < CENT_TYPE; i++) {
        printf("O valor consiste em ");
        if (i == 0)
            printf("%d moedas de 1 real\n", coin_amount[i]);
        else if (i == 1)
            printf("%d moedas de 50 centavos\n", coin_amount[i]);
        else if (i == 2)
            printf("%d moedas de 25 centavos\n", coin_amount[i]);
        else if (i == 3)
            printf("%d moedas de 10 centavos\n", coin_amount[i]);
        else if (i == 4)
            printf("%d moedas de 5 centavos\n", coin_amount[i]);
        else
            printf("%d moedas de 1 centavo\n", coin_amount[i]);
    }

    return 0;
}

void coin_change(int* payment, int coin_amount[CENT_TYPE]) {
    coin_amount[0] = *payment / 100;
    *payment %= 100; 
    coin_amount[1] = *payment / 50;
    *payment %= 50; 
    coin_amount[2] = *payment / 25; 
    *payment %= 25;
    coin_amount[3] = *payment / 10;
    *payment %= 10; 
    coin_amount[4] = *payment / 5; 
    *payment %= 5;
    coin_amount[5] = *payment;  
}