// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {

    int selected_day, day_of_month;

    scanf("%d", &selected_day);

    // cabecalho do calendario
    printf("         Abril 2021         \n");
    printf(" Do  Se  Te  Qu  Qu  Se  Sa \n");

    // espacamento primeira linha de abril
    for (int space_count = 0; space_count < 16; space_count++) {
        printf(" ");
    }
    for(day_of_month = 1; day_of_month < 4; day_of_month++) {
        // Teste se é o dia selecionado
        if (day_of_month == selected_day) printf("(%2d)", day_of_month);
        // Quando esse não é o dia selecionado
        else printf(" %2d ", day_of_month);
    }
    printf("\n");
    for(day_of_month = 4; day_of_month < 11; day_of_month++) {
        // Teste se é o dia selecionado
        if (day_of_month == selected_day) printf("(%2d)", day_of_month);
        // Quando esse não é o dia selecionado
        else printf(" %2d ", day_of_month);
    }
    printf("\n");
    for(day_of_month = 11; day_of_month < 18; day_of_month++) {
        // Teste se é o dia selecionado
        if (day_of_month == selected_day) printf("(%2d)", day_of_month);
        // Quando esse não é o dia selecionado
        else printf(" %2d ", day_of_month);
    }
    printf("\n");
    for(day_of_month = 18; day_of_month < 25; day_of_month++) {
        // Teste se é o dia selecionado
        if (day_of_month == selected_day) printf("(%2d)", day_of_month);
        // Quando esse não é o dia selecionado
        else printf(" %2d ", day_of_month);
    }
    printf("\n");
    for(day_of_month = 25; day_of_month < 31; day_of_month++) {
        // Teste se é o dia selecionado
        if (day_of_month == selected_day) printf("(%2d)", day_of_month);
        // Quando esse não é o dia selecionado
        else printf(" %2d ", day_of_month);
    }
    printf("\n");

    return 0;
}