#include <iostream>
#include <queue> // Usar fila de prioridade c/ dois parametros de comparacao

using namespace std;

typedef struct Register {
    int id;
    int period;
    int next_occurrence;

    // Define MENOR prioridade ao retornar true
    bool operator< (const Register &other) const { // Sobrecarga
        if (next_occurrence < other.next_occurrence) {
            return false;
        }

        if (next_occurrence == other.next_occurrence && id < other.id) {
            return false;
        }

        return true;
    }
} reg_t;

void print_queue(priority_queue<reg_t>& pq, int iteration_amt);

int main() {
    priority_queue<reg_t> pq;

    string input;
    cin >> input;
    while (input != "#") {
        reg_t curr_reg;
        cin >> curr_reg.id >> curr_reg.period;
        curr_reg.next_occurrence = curr_reg.period;
        pq.push(curr_reg);
        cin >> input;
    } 

    int query_amt;
    cin >> query_amt;

    print_queue(pq, query_amt);

    return EXIT_SUCCESS;
}

void print_full_queue(priority_queue<reg_t>& pq) {
    priority_queue<reg_t> aux = pq;
    while (!aux.empty()) {
        cout << aux.top().id << ' ' << aux.top().next_occurrence << ' ' << aux.top().period << '\n';
        aux.pop();
    }
} 

void print_queue(priority_queue<reg_t>& pq, int iteration_amt) {
    int i = 0;
    while (i < iteration_amt) {
        reg_t curr_head = pq.top();
        cout << curr_head.id << '\n';
        pq.pop(); // Tirar da fila
        curr_head.next_occurrence += curr_head.period; // Atualizar register
        pq.push(curr_head); // Colocar na fila de novo com nova prioridade
        i++;
    }
}