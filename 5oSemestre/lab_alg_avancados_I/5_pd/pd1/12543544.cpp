#include <iostream>
#include <cstring> // Memset
#include <limits.h> // INT_MAX

using namespace std;

#define TICKET_TYPE 3
#define MAX_DAY_AMT_TO_STAY 300
#define INFINITY 1e8

#define NONE -1

// -- Variaveis globais -- 

/*
 * Guarda os precos dos tickets de 1, 7 e 30 dias
 * ticket_prices[0] = 1 dia
 * ticket_prices[1] = 7 dias
 * ticket_prices[2] = 30 dias
*/
int ticket_intervals[TICKET_TYPE] = {1, 7, 30};
int ticket_prices[TICKET_TYPE];

// Guarda os dias especificos em que o cliente fica no resort
int specific_staying_days[MAX_DAY_AMT_TO_STAY];

/* 
 * Como eh um exercicio de PD, vamos usar memoizacao para evitar calculos ja
 * computados e tornar nosso programa menos complexo, deixa-lo linear.
 * *** Neste exercicio, o MEMO representa, em cada indice, o custo daquele dia em diante
 * (veja os caso-base: se so tiver um dia especifico para cobrir, eh mais simples do que
 * ter 30 dias para cobrir, que eh o que queremos resolver no final).
 * 
*/
int MEMO[MAX_DAY_AMT_TO_STAY];

int min_money_amt_spent(int days_stayed, int day_amt);

int main() {
    int staying_days_amt;
    cin >> staying_days_amt;

    for (int i = 0; i < TICKET_TYPE; i++) {
        cin >> ticket_prices[i];
    }

    for (int i = 0; i < staying_days_amt; i++) {
        cin >> specific_staying_days[i];
    }

    // Inicializando o MEMO com valor fora do dominio
    memset(MEMO, NONE, sizeof MEMO);

    int answer = min_money_amt_spent(0, specific_staying_days[staying_days_amt - 1]);
    cout << answer;

    return EXIT_SUCCESS;
}

int next_remaining_day_idx(int day_amt, int curr_day_idx, int ticket_type) {
    // O ticket pode cobrir 1, 7 ou 30 dias
    int next_uncovered_day = specific_staying_days[curr_day_idx] + ticket_type;

    // Para os proximos dias que ainda nao calculamos,
    for (int i = curr_day_idx + 1; i < day_amt; i++) {
        // Se algum dia nao foi coberto pelo intervalo do tipo de ticket
        if (specific_staying_days[i] >= next_uncovered_day) {
            return i; // Continue a achar o custo minimo a partir deste dia (nao coberto pelo intervalo)
        }
    }

    // Todos os dias foram cobertos e o programa deve finalizar. Dia maximo a cobrir tem o indice day_amt - 1.
    return day_amt;
}

// Testar minha cobertura de intervalo e meu gasto em relacao a ela
int min_money_amt_spent(int curr_days_stayed_idx, int day_amt) {
    // Acabaram os dias que gostaria de ficar (fiquei o ultimo dia)
    if (curr_days_stayed_idx >= day_amt) {
        return 0; // O custo a mais
    }

    // Se ja calculei, nao preciso processar de novo. Basta retornar o valor
    if (MEMO[curr_days_stayed_idx] != NONE) {
        return MEMO[curr_days_stayed_idx];
    }

    // Custo minimo atual ainda nao existe e eh tratado como infinito para 'perder eleicao'
    MEMO[curr_days_stayed_idx] = INT_MAX / 2;

    for (int i = 0; i < TICKET_TYPE; i++) { // Para cada tipo de ticket
        // Usar o ticket para calcular novo dia nao coberto por ele ainda
        int new_idx = next_remaining_day_idx(day_amt, curr_days_stayed_idx, ticket_intervals[i]);

        MEMO[curr_days_stayed_idx] = min(MEMO[curr_days_stayed_idx], ticket_prices[i] + min_money_amt_spent(new_idx, day_amt));
    }

    return MEMO[curr_days_stayed_idx];
}