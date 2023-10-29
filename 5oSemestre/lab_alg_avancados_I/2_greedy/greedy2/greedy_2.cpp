#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Task task_t;

struct Task {
    int id;
    int time_needed;
    int fine; // Representa a prioridade (qto maior, mais prioridade)
};

void solve_case();

int main() {
    int case_amt;
    cin >> case_amt;

    for (int i = 0; i < case_amt; i++) {
        solve_case();

        if (i < case_amt - 1) {
            cout << '\n';
        }
    }

    return EXIT_SUCCESS;
}

/* 
    Dar preferencia a tasks que:
    1. tem valor de multa diaria maior
    2. levam menos tempo em dias para completar

    Entao, se consideramos a razao multa / tempo, teremos a prioridade de maior multa em menor tempo
    executando primeiro, diminuindo a taxa no total.
*/
bool comparator(task_t& t1, task_t& t2) {
    // Precisa converter para double senao da divisao inteira (int / int = int)
    if (((double)t1.fine / t1.time_needed) > ((double)t2.fine / t2.time_needed)) {
        return true; // elemento 1 vem antes do 2
    }

    // Se a razao eh a mesma, exibir na ordem lexicografica
    if (((double)t1.fine / t1.time_needed) == ((double)t2.fine / t2.time_needed) && t1.id < t2.id) {
        return true;
    }

    return false;
}

task_t read_task(int curr_id) {
    task_t t;
    t.id = curr_id;
    cin >> t.time_needed >> t.fine;

    return t;
}

void print_tasks(vector<task_t>& tasks) {
    for (auto it = tasks.begin(); it != tasks.end(); it++) {
        cout << it->id << ' ';
    }

    cout << '\n';
}

void solve_case() {
    int task_amt;
    cin >> task_amt;

    vector<task_t> tasks;

    for (int i = 1; i <= task_amt; i++) {
        task_t t = read_task(i);
        tasks.push_back(t);
    }

    sort(tasks.begin(), tasks.end(), comparator);
    print_tasks(tasks);
}