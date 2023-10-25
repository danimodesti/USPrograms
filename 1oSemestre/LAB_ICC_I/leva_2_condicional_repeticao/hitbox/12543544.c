// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

int main() {
    long long int x_rectangle1, x_rectangle2, y_rectangle1, y_rectangle2, 
        width_rectangle1, width_rectangle2, height_rectangle1, 
        height_rectangle2, x_intersection, y_intersection, width_intersection, 
        height_intersection;

    scanf("%lld %lld %lld %lld", &x_rectangle1, & y_rectangle1, 
         &width_rectangle1, &height_rectangle1);
    scanf("%lld %lld %lld %lld", &x_rectangle2, &y_rectangle2, 
          &width_rectangle2, &height_rectangle2);

    // Comportamento do eixo x - teste se ha interseccao
    // Nos casos 1, 2, 3 -> x_rectangle1 < x_rectangle2
    // Retirei casos redundantes
    if (x_rectangle1 < x_rectangle2) {
        // Caso 1
        if ((x_rectangle1 + width_rectangle1) < x_rectangle2) {
            printf("MISS\n");
            return 0;
        }
        else if ((x_rectangle1 + width_rectangle1) == x_rectangle2) {
            x_intersection = x_rectangle2;
            width_intersection = (x_rectangle1 + width_rectangle1) - x_rectangle2; 
        }
        // Caso 2
        else if ((x_rectangle1 + width_rectangle1) < (x_rectangle2 + width_rectangle2)) {
            x_intersection = x_rectangle2;
            width_intersection = (x_rectangle1 + width_rectangle1) - x_rectangle2;
        }
        else if ((x_rectangle1 + width_rectangle1) == (x_rectangle2 + width_rectangle2)) {
            x_intersection = x_rectangle2;
            width_intersection = width_rectangle2;
        }
        // Caso 3
        else { 
            x_intersection = x_rectangle2;
            width_intersection = width_rectangle2;
        }
    }

    // -------------------------------------------------------------------------
    // Nos casos 4, 5, 6 -> x_rectangle2 < x_rectangle1
    // Perceba que o caso IV e identico ao I, o V ao II e o VI ao III
    // So trocar de ordem os retangulos

    else if (x_rectangle1 > x_rectangle2) {
        // Caso 4 = - Caso 1
        if ((x_rectangle2 + width_rectangle2) < x_rectangle1) {
            printf("MISS\n");
            return 0; 
        }
        else if ((x_rectangle2 + width_rectangle2) == x_rectangle1) {
            x_intersection = x_rectangle1;
            width_intersection = (x_rectangle2 + width_rectangle2) - x_rectangle1;
        }
        // Caso 5 = - Caso 2
        else if ((x_rectangle2 + width_rectangle2) < (x_rectangle1 + width_rectangle1)) {
            x_intersection = x_rectangle1;
            width_intersection = (x_rectangle2 + width_rectangle2) - x_rectangle1;
        }
        else if ((x_rectangle2 + width_rectangle2) == (x_rectangle1 + width_rectangle1)) {
            x_intersection = x_rectangle1;
            width_intersection = width_rectangle1;
        }
        // Caso 6 = - Caso 3
        else { 
            x_intersection = x_rectangle1;
            width_intersection = width_rectangle1;
        }
    }
    else { // x_rectangle1 = x_rectangle2 
        // do caso 2:
        if ((x_rectangle1 + width_rectangle1) == (x_rectangle2 + width_rectangle2)) {
            x_intersection = x_rectangle1;
            width_intersection = width_rectangle1;
        }
        else if ((x_rectangle1 + width_rectangle1) < (x_rectangle2 + width_rectangle2)) {
            x_intersection = x_rectangle1;
            width_intersection = (x_rectangle1 + width_rectangle1) - x_rectangle2;
        }
        // do caso 3:
        else if ((x_rectangle1 + width_rectangle1) > (x_rectangle2 + width_rectangle2)) {
            width_intersection = x_rectangle1;
            width_intersection = (x_rectangle1 + width_rectangle1) - (x_rectangle2 + width_rectangle2);
        }   
    }

    //--------------------------------------------------------------------------
    // Comportamento do eixo y - e similar ao do eixo x
    // Trocar w por h e x por y, apenas
    // Tem uma simetria muito bonita aqui

    if (y_rectangle1 < y_rectangle2) {
        // Caso 1
        if ((y_rectangle1 + height_rectangle1) < y_rectangle2) {
            printf("MISS\n");
            return 0; 
        }
        else if ((y_rectangle1 + height_rectangle1) == y_rectangle2) { 
            y_intersection = y_rectangle2;
            height_intersection = (height_rectangle1 + y_rectangle1) - y_rectangle2; 
        }
        // Caso 2
        else if ((y_rectangle1 + height_rectangle1) < (y_rectangle2 + height_rectangle2)){
            y_intersection = y_rectangle2;
            height_intersection = (y_rectangle1 + height_rectangle1) - y_rectangle2;
        }
        else if ((y_rectangle1 + height_rectangle1) == (y_rectangle2 + height_rectangle2)) {
            y_intersection = y_rectangle2;
            height_intersection = height_rectangle2;
        }
        // Caso 3
        else { 
            y_intersection = y_rectangle2;
            height_intersection = height_rectangle2;
        }
    }

    //--------------------------------------------------------------------------
    // Nos casos 4, 5, 6 -> y_rectangle2 < y_rectangle1
    // Perceba que o caso IV e identico ao I, o V ao II e o VI ao III
    // So trocar de ordem os retangulos

    else if (y_rectangle1 > y_rectangle2) {
        // Caso 4 = - Caso 1
        if ((y_rectangle2 +height_rectangle2) < y_rectangle1) {
            printf("MISS\n");
            return 0; 
        }
        else if ((y_rectangle2 + height_rectangle2) == y_rectangle1) {
            y_intersection = y_rectangle1;
            height_intersection = (y_rectangle2 + height_rectangle2) - y_rectangle1;
        }
        // Caso 5 = - Caso 2
        else if ((y_rectangle2 + height_rectangle2) < (y_rectangle1 + height_rectangle1)) {
            y_intersection = y_rectangle1;
            height_intersection = (y_rectangle2 + height_rectangle2) - y_rectangle1;
        }
        else if ((y_rectangle2 + height_rectangle2) == (y_rectangle1 + height_rectangle1)) {
            y_intersection = y_rectangle1;
            height_intersection = height_rectangle1;
        }
        // Caso 6 = - Caso 3
        else { 
            y_intersection = y_rectangle1;
            height_intersection = height_rectangle1;
        }
    }
    else { // y_rectangle1 = y_rectangle2
        // do caso 2:
        if ((y_rectangle1 + height_rectangle1) == (y_rectangle2 + height_rectangle2)) {
            y_intersection = y_rectangle1;
            height_intersection = height_rectangle1;
        }
        else if ((y_rectangle1 + height_rectangle1) < (y_rectangle2 + height_rectangle2)) {
            y_intersection = y_rectangle1;
            height_intersection = (y_rectangle1 + height_rectangle1) - y_rectangle2;
        }
        // do caso 3:
        else if ((y_rectangle1 + height_rectangle1) > (y_rectangle2 + height_rectangle2)) {
            y_intersection = y_rectangle1;
            height_intersection = (y_rectangle1 + height_rectangle1) - (y_rectangle2 + height_rectangle2);
        }
    }

    printf("HIT: %lld %lld %lld %lld\n", x_intersection, y_intersection, width_intersection, height_intersection);

    return 0;
}