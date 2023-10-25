// Danielle Modesti
// No USP 12543544

#include <stdio.h>

int main() {
    int amount_cat_plays_ball, amount_cat_bites_food;
    
    scanf("%d %d", &amount_cat_plays_ball, &amount_cat_bites_food);

    // Veja se o gato ganhou ou perdeu peso com base nas entradas
    /* Para que o gato reduza seu peso, deve haver reducao de pelo menos 30, 
    ou seja, <= -30*/
    if (amount_cat_bites_food * 3 - amount_cat_plays_ball * 5 <= -30) {
        printf("P\n");
    }
    else if (amount_cat_bites_food * 3 - amount_cat_plays_ball * 5 <= 0){
        printf("B\n");
    }
    else {
        printf("R\n");
    }

    return 0;
}