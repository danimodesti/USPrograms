// Danielle Modesti
// No USP: 12543544

#include <stdio.h> 
#include <math.h> // Biblio com funcoes matematicas, como sqrt, da qual eu preciso. 
#include <stdlib.h> // Biblio padrao, com funcao de valor absoluto, abs(), da qual eu preciso

// Funcoes
double distance_Euclides(int x1, int x2, int y1, int y2, int id) {
    double result_Euclides;

    if (id == -1 || id == 1) 
        result_Euclides = sqrt(pow(((double)x2 - (double)x1), 2) + pow(((double)y2 - (double)y1), 2));
    else
        result_Euclides = (double)(abs(x2 - x1) + abs(y2 - y1));

    return result_Euclides;
}

double distance_Hermann(int x1, int x2, int y1, int y2, int id) { 
    double result_Hermann;

    if (id == 0 || id == 1)
        result_Hermann = (double)(abs(x2 - x1) + abs(y2 - y1));
    else
        result_Hermann = sqrt(pow(((double)x2 - (double)x1), 2) + pow(((double)y2 - (double)y1), 2));

    return result_Hermann;
}

int main() {
    int N; 

    scanf("%d", &N);

    // Trate as restricoes
    if (N <= 0) {
        printf("Falha no processamento dos dados.\n");
        return 0;
    }

    // Crie matriz para guardar toda a info dos pontos visitados
    // Sempre teremos N linhas e 3 colunas (primeira coluna tem info do x, segunda tem info do y, terceira tem info do i)
    int visited_point[N][3];
  
    int count_wasteland = 0; 
    int count_home = 0;
    int count_park = 0;

    // Preencha os valores de estabelecimentos/pontos visitados
    for (int i = 0; i < N; i++) { 
        scanf("%d %d %d", &visited_point[i][0], &visited_point[i][1], &visited_point[i][2]); 

            // Incremente os tipos de terreno (verifique a qtd de cada id)
            if (visited_point[i][2] == -1) {
                count_wasteland++;
            }
            else if (visited_point[i][2] == 0) {
                count_home++;
            }
            else if (visited_point[i][2] == 1) {
                count_park++;
            }
            else { // Trate restricoes
                printf("Falha no processamento dos dados.\n");
                return 0;
            }
    }

    double totaldistance_Euclides = 0;
    double totaldistance_Hermann = 0;

    for (int i = 1; i <= N - 1; i++) {
        totaldistance_Euclides += distance_Euclides(visited_point[i - 1][0], visited_point[i][0], visited_point[i - 1][1], visited_point[i][1], visited_point[i - 1][2]);
        totaldistance_Hermann += distance_Hermann(visited_point[i - 1][0], visited_point[i][0], visited_point[i - 1][1], visited_point[i][1], visited_point[i - 1][2]);
    }

    totaldistance_Euclides = totaldistance_Euclides + distance_Euclides(visited_point[N - 1][0], visited_point[0][0], visited_point[N - 1][1], visited_point[0][1], visited_point[N - 1][2]);
    totaldistance_Hermann = totaldistance_Hermann + distance_Hermann(visited_point[N - 1][0], visited_point[0][0], visited_point[N - 1][1], visited_point[0][1], visited_point[N - 1][2]);

    double delta_distance = fabs(totaldistance_Euclides - totaldistance_Hermann); 

    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\nA diferenca total de distancia percorrida foi de %.2lf metros.\n", count_wasteland, count_home, count_park, delta_distance);

    return 0;
}