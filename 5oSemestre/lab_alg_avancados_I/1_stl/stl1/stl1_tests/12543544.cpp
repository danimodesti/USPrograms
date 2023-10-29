// Usar fila

#include <iostream>
#include <queue>

using namespace std;

void print_queue(queue <int> my_queue);
void print_prio_queue(priority_queue<int> my_queue);

int main() {
    int case_amt, job_amt, my_job_position, minute_counter;
    cin >> case_amt;
    bool is_job_out;

    for (int i = 0; i < case_amt; i++) { // Controle da qtd. de casos de teste
        queue<int> received_jobs;
        priority_queue<int> greatest_priority;
        minute_counter = 1;
        cin >> job_amt >> my_job_position;

        for (int j = 0; j < job_amt; j++) {
            int curr_job;
            cin >> curr_job;
            received_jobs.push(curr_job);
            greatest_priority.push(curr_job);
        }

        is_job_out = false;
        while (!is_job_out) {
            // Job na cabeca da fila para ser executado
            if (my_job_position == 0) {
                // Se eh maior prioridade
                if (received_jobs.front() == greatest_priority.top()) {
                    // Execute neste minuto e finalize
                    cout << minute_counter << '\n';
                    is_job_out = true;
                }

                else {
                    // O meu job vai para o fim da fila
                    int head_job = received_jobs.front();
                    received_jobs.pop();
                    received_jobs.push(head_job);
                    my_job_position = received_jobs.size() - 1;
                }
            }

            // Outro job que nao o meu esta no topo da fila
            else {
                // Job na head tem a maior prioridade de todas?
                if (received_jobs.front() == greatest_priority.top()) {
                    received_jobs.pop();
                    greatest_priority.pop();
                    minute_counter++;
                }

                else {
                    int head_job = received_jobs.front();
                    received_jobs.pop();
                    received_jobs.push(head_job);
                }

                // Job vai para frente na fila
                my_job_position--;
            }
        }

    }

    return EXIT_SUCCESS;
}

void print_queue(queue <int> my_queue) {
    queue<int> copy(my_queue);

    while (!copy.empty()) {
        cout << copy.front() << ' ';
        copy.pop();
    }

    cout << '\n';
}

void print_prio_queue(priority_queue<int> my_queue) {
    priority_queue<int> copy(my_queue);

    while (!copy.empty()) {
        cout << copy.top() << ' ';
        copy.pop();
    }

    cout << '\n';
}