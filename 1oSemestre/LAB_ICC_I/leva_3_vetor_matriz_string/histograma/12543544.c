//  Danielle Modesti
// No USP: 12543544

#include <stdio.h>

#define PIXEL_AMOUNT 25 // Se eu quiser alterar a dimensao da imagem, fica mais facil

#define COLOR_AMOUNT 5

int maximo(int color_1, int color_2, int color_3, int color_4, int color_5);

int main() {
    int image[PIXEL_AMOUNT];

    int count_0 = 0;
    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;

    for (int i = 0; i < PIXEL_AMOUNT; i++) {
        scanf("%d", &image[i]);

        if (image[i] == 0) 
            count_0++;
        else if (image[i] == 1) 
            count_1++;
        else if (image[i] == 2) 
            count_2++;
        else if (image[i] == 3) 
            count_3++;
        else
            count_4++;
    }

    int histogram[COLOR_AMOUNT] = {count_0, count_1, count_2, count_3, count_4}; 

    for (int i = 0; i < COLOR_AMOUNT; i++) {
        printf("%d: |", i);

        for (int j = 0; j < histogram[i]; j++) 
            printf("#");
        
        printf("\n");
    }

    int mode = maximo(count_0, count_1, count_2, count_3, count_4);

    // Encontre o indice do vetor histograma que tenha o valor de moda
    int index_moda;
    for (index_moda = 0; index_moda < COLOR_AMOUNT; index_moda++) {
        if (histogram[index_moda] == mode)
        break;
    }

    for (int i = 0; i < PIXEL_AMOUNT; i++) {
        if (image[i] == index_moda) // Se o numero no vetor imagem for igual à cor mais incrementada, que pode ser 0, 1, 2, 3 ou 4, printe o indice do image
            printf("%d\n", i);
    }

    return 0;
}

int maximo(int color_1, int color_2, int color_3, int color_4, int color_5) {
    int result_1_2, result_3_4, result_1_2_3_4, result;

    if (color_1 > color_2)
        result_1_2 = color_1;
    else 
        result_1_2 = color_2;

    if (color_3 > color_4)
        result_3_4 = color_3;
    else
        result_3_4 = color_4;

    if (result_1_2 > result_3_4)
        result_1_2_3_4 = result_1_2;
    else
        result_1_2_3_4 = result_3_4;

    if (result_1_2_3_4 > color_5)
        result = result_1_2_3_4;
    else
        result = color_5;

    return result;
}