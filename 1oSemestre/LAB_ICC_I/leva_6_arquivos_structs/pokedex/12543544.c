/*
 * Danielle Modesti
 * No USP: 12543544
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum Commands {
    FINISH_PROGRAM,
    REGISTER_POKEMON,
    ADD_ATTACK,
    PRINT_POKEMON_DATA,
    PRINT_POKEMON_ATTACK_DATA
} commands_t;

// Estruturas
typedef struct Attribute {
    int health_power;
    int attack;
    int defense;
    int special_attack;
    int special_defense;
    int speed;
} attribute_t;

typedef struct Attack {
    char name[21];
    int basic_power;
    float accuracy;
    char attack_class;
} attack_t;

typedef struct Pokemon {
    char name[51];
    char primary_type[21];
    char secondary_type[21];
    attribute_t attribute_set;
    attack_t attack_set[4]; // O pokemon pode ter 4 ataques, cada qual com suas caracteristicas intrinsecas
} pokemon_t;

typedef struct Pokedex {
    pokemon_t *list;
} pokedex_t;

int main() {
    // Criar a pokedex e inicializa-la
    pokedex_t my_pokedex;
    my_pokedex.list = NULL;
    int pokedex_index = 0;
    
    pokemon_t pokemon;
    int read_info_index;
    int attack_index;

    int command;
    do {
        scanf("%d", &command);
        getchar();

        switch (command) {
            case REGISTER_POKEMON: 
                scanf("%s\n", pokemon.name);
                scanf("%s\n", pokemon.primary_type);
                scanf("%s", pokemon.secondary_type);
                scanf("%d", &pokemon.attribute_set.health_power);
                scanf("%d", &pokemon.attribute_set.attack);
                scanf("%d", &pokemon.attribute_set.defense);
                scanf("%d", &pokemon.attribute_set.special_attack);
                scanf("%d", &pokemon.attribute_set.special_defense);
                scanf("%d", &pokemon.attribute_set.speed);

                my_pokedex.list = (pokemon_t *) realloc(my_pokedex.list, (pokedex_index + 1) * sizeof(pokemon_t));
                my_pokedex.list[pokedex_index] = pokemon;

                pokedex_index++;
                break;
            case ADD_ATTACK:
                scanf("%d", &read_info_index);
                scanf("%d", &attack_index);

                attack_t attack;
                scanf("%s", attack.name);
                scanf("%d", &attack.basic_power);
                scanf("%f\n", &attack.accuracy);
                scanf("%c", &attack.attack_class);

                my_pokedex.list[read_info_index].attack_set[attack_index] = attack;
                break;
            case PRINT_POKEMON_DATA:
                scanf("%d", &read_info_index);

                printf("Nome do Pokemon: %s\n", my_pokedex.list[read_info_index].name);
                printf("Tipo primario: %s\n", my_pokedex.list[read_info_index].primary_type);
                printf("Tipo secundario: %s\n", my_pokedex.list[read_info_index].secondary_type);
                printf("Status:\n");
                printf("\tHP: %d\n", my_pokedex.list[read_info_index].attribute_set.health_power);
                printf("\tAtaque: %d\n", my_pokedex.list[read_info_index].attribute_set.attack);
                printf("\tDefesa: %d\n", my_pokedex.list[read_info_index].attribute_set.defense);
                printf("\tAtaque Especial: %d\n", my_pokedex.list[read_info_index].attribute_set.special_attack);
                printf("\tDefesa Especial: %d\n", my_pokedex.list[read_info_index].attribute_set.special_defense);
                printf("\tVelocidade: %d\n\n", my_pokedex.list[read_info_index].attribute_set.speed);
                break;
            case PRINT_POKEMON_ATTACK_DATA:
                scanf("%d", &read_info_index);
                scanf("%d", &attack_index);

                printf("Nome do Ataque: %s\n", my_pokedex.list[read_info_index].attack_set[attack_index].name);
                printf("Poder base: %d\n", my_pokedex.list[read_info_index].attack_set[attack_index].basic_power);
                printf("Acuracia: %f\n", my_pokedex.list[read_info_index].attack_set[attack_index].accuracy);
                printf("Classe: %c\n\n", my_pokedex.list[read_info_index].attack_set[attack_index].attack_class);
                break;
            case FINISH_PROGRAM:
                break;
            default: 
                printf("Comando invalido! =(\n");
                break;
        } 
    } while (command != FINISH_PROGRAM);

    // Liberar a memoria dinamicamente alocada
    free(my_pokedex.list);

    return 0;
}