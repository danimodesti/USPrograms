#include <iostream> // Bib. de entrada e saida
#include <limits.h> // Para usar INT_MAX
#include <cstring> // Para usar memset

using namespace std;

#define TICKET_TYPE 3

int day_covered_amt[TICKET_TYPE] = {1, 7, 30};
int ticket_prices[TICKET_TYPE] = {5, 10, 6};

void print_ticket_prices(int ticket_prices[TICKET_TYPE]);
void print_staying_days(int staying_days[], int day_amt);
int minimum_cost(int *stay_days, int day_amt, int *MEMO, int curr_day_idx);

int main() {
    // Ler entrada
    int day_amt;
    cin >> day_amt;

    for (int i = 0; i < TICKET_TYPE; i++) {
        cin >> ticket_prices[i];
    }

    int staying_days[day_amt];
    for (int i = 0; i < day_amt; i++) {
        cin >> staying_days[i];
    }

    // Como eh um exercicio de PD, vamos usar memoizacao para evitar calculos ja
    // computados e tornar nosso programa menos complexo, deixa-lo linear.
    // *** Neste exercicio, o MEMO representa, em cada indice, o custo daquele dia em diante
    // (veja os caso-base: se so tiver um dia especifico para cobrir, eh mais simples do que
    // ter 30 dias para cobrir, que eh o que queremos resolver no final).
    int MEMO[day_amt];
    memset(MEMO, -1, sizeof MEMO); // Inicializar o memo com -1 em todas as posicoes (valor fora do dominio)

    // Calcular custo minimo - mandar o indice do primeiro dia para o qual o cliente
    // quer ficar no resort.
    // A resposta que queremos eh o custo minimo a partir daquele dia.
    int answer = minimum_cost(staying_days, day_amt, MEMO, 0);

    // Retornar
    cout << answer << endl;

    return EXIT_SUCCESS;
}

// Nucleo do problema de 'quais' dias cobrir
int next_remaining_day_idx(int *staying_days, int day_amt, int curr_day_idx, int ticket_type) {
    // O tipo do ticket pode ser de 1, 7 ou 30 dias
    int next_uncovered_day = staying_days[curr_day_idx] + ticket_type;

    // Para os proximos dias que ainda nao calculamos,
    for (int i = curr_day_idx + 1; i < day_amt; i++) {
        // Se algum dia ainda nao foi coberto pelo intervalo do tipo do ticket
        if (staying_days[i] >= next_uncovered_day) {
            return i; // Continue a achar o custo minimo a partir dele (que nao foi coberto pelo intervalo)
        }
    }

    // Todos os dias selecionados para o problema foram cobertos
    // Ou seja, acabou o 'dominio' de dias. Retornamos esse indice, que nao existe (maximo = day_amt - 1)
    return day_amt; 
}

int minimum_cost(int *stay_days, int day_amt, int *MEMO, int curr_day_idx) {
    // *** Casos-base
    // Acabaram os dias a cobrir no vetor de dias (verificacao de indice valido), custo $0
    if (curr_day_idx >= day_amt)
        return 0;

    if (MEMO[curr_day_idx] != -1)
        return MEMO[curr_day_idx];

    // ------------------------------------------------------------------
    // *** Regra de recorrencia
    // Custo minimo atual - tratar como infinito, para "perder a eleicao"
    MEMO[curr_day_idx] = INT_MAX / 2;

    for (int i = 0; i < TICKET_TYPE; i++) { // Para cada tipo de ticket (1, 7 e 30-day)
        // Usar ticket de cada tipo para calcular novo dia nao coberto ainda
        int new_idx = next_remaining_day_idx(stay_days, day_amt, curr_day_idx, day_covered_amt[i]);

        // O custo minimo atual sera atualizado, comparando todas as combinacoes possiveis de
        // tickets e achando sempre o minimo caminho para cada intervalo calculado acima.
        // Use o ticket (gaste o respectivo dinheiro) e calcule, para o prox. dia ainda nao coberto, o minimo custo
        MEMO[curr_day_idx] = min(MEMO[curr_day_idx], ticket_prices[i] + minimum_cost(stay_days, day_amt, MEMO, new_idx));
    }

    return MEMO[curr_day_idx];
}

void print_ticket_prices(int ticket_prices[TICKET_TYPE]) {
    int tickets_match[TICKET_TYPE] = {1, 7, 30}; 
    for (int i = 0; i < TICKET_TYPE; i++) {
        cout << "Preco do ticket para " << tickets_match[i] << " dia(s): " << ticket_prices[i] << " dinheiros";
        cout << endl;
    }
    cout << endl;
}

void print_staying_days(int staying_days[], int day_amt) {
    cout << "Dias especificos da estadia:" << endl;
    for (int i = 0; i < day_amt; i++) {
        cout << staying_days[i] << endl;
    }

    cout << endl;
}