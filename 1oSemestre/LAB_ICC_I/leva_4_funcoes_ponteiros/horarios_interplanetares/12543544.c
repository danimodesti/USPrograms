// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <string.h>

#define STRING_MAX_SIZE 9

typedef unsigned long long int integer;

void measure_time_spent(integer* travel_time, char finish_planet[STRING_MAX_SIZE], integer time_units[4]); 

int main() {
    integer travel_time; // Tempo em segundos gasto na viagem para o bandejao na Terra, em Marte, em Venus ou em Mercurio
    integer time_units[4]; // Guarde dias, horas, minutos e segundos

    scanf("%llu%*[ ]s", &travel_time); // Leia ignorando espaco. % - significa leia e salva na variavel %* - leia e ignore

    char planet[STRING_MAX_SIZE] = {};

    scanf("%s", planet);

    measure_time_spent(&travel_time, planet, time_units); // Passagem de parametros por referencia. Chame a funcao

    printf("%llu segundos no planeta %s equivalem a:\n", travel_time, planet);
    printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n", time_units[0], time_units[1], time_units[2], time_units[3]);

    return 0;
}

void measure_time_spent(integer* travel_time, char finish_planet[STRING_MAX_SIZE], integer time_units[4]) {
    integer copy = *travel_time; // Copia do valor inicial recebido em travel_time
    
    // Um calculo para cada tipo de planeta
    if (strcmp(finish_planet,"Terra") == 0) {
        time_units[0] = *travel_time / 86400; 
        *travel_time %= 86400; 
        time_units[1] = *travel_time / 3600;
        *travel_time %= 3600; 
        time_units[2] = *travel_time / 60; 
        *travel_time %= 60;
        time_units[3] = *travel_time;
        *travel_time = copy;
    }
    else if (strcmp(finish_planet,"Jupiter") == 0) {
        time_units[0] = *travel_time / 35760; 
        *travel_time %= 35760; 
        time_units[1] = *travel_time / 3600;
        *travel_time %= 3600; 
        time_units[2] = *travel_time / 60; 
        *travel_time %= 60;
        time_units[3] = *travel_time;
        *travel_time = copy;
    }
    else if (strcmp(finish_planet,"Venus") == 0) {
        time_units[0] = *travel_time / 20995200; 
        *travel_time %= 20995200; 
        time_units[1] = *travel_time / 3600;
        *travel_time %= 3600; 
        time_units[2] = *travel_time / 60; 
        *travel_time %= 60;
        time_units[3] = *travel_time;
        *travel_time = copy;
    }
    else {  // Mercurio
        time_units[0] = *travel_time / 5068800; 
        *travel_time %= 5068800; 
        time_units[1] = *travel_time / 3600;
        *travel_time %= 3600; 
        time_units[2] = *travel_time / 60; 
        *travel_time %= 60;
        time_units[3] = *travel_time;
        *travel_time = copy;
    }
}