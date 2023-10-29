// Guloso
#include <iostream>
#include <queue>

using namespace std;

typedef struct Person person_t;

struct Person {
    int age;

    // Define MENOR prioridade ao retornar true (ensinar a comparar)
    bool operator< (const Person &other) const { // Sobrecarga
        if (age > other.age) { // Ordenar do mais novo pro mais velho
            return true;
        }

        return false;
    }
};

person_t read_person();
void read_people(priority_queue<person_t>& bachelors, int spinsters, int b_amt, int s_amt);

int main() {
    int bachelor_amt, spinster_amt, curr_case = 1, left_aside_amt, spinsters = 0; // Nao preciso armazenar spinsters

    cin >> bachelor_amt >> spinster_amt;
    do {
        priority_queue<person_t> bachelors; // Ja ordenar do mais novo pro mais velho

        read_people(bachelors, spinsters, bachelor_amt, spinster_amt);

        left_aside_amt = 0; // Referente aos bachelors
        if (bachelor_amt - spinster_amt >= 0) {
            left_aside_amt = bachelor_amt - spinster_amt;
        }

        cout << "Case " << curr_case++ << ": " << left_aside_amt;

        if (left_aside_amt > 0) {
            cout << ' ' << bachelors.top().age; // O mais novo eh o que fica sem match
        }

        cout << '\n';

        cin >> bachelor_amt >> spinster_amt;
    } while (!(bachelor_amt == 0 && spinster_amt == 0)); 


    return EXIT_SUCCESS;
}

person_t read_person() {
    person_t curr_person;
    cin >> curr_person.age;

    return curr_person;
}

void read_people(priority_queue<person_t>& bachelors, int spinsters, int b_amt, int s_amt) {
    for (int i = 0; i < b_amt; i++) {
            person_t p = read_person();
            bachelors.push(p);
    }

    for (int i = 0; i < s_amt; i++) {
        cin >> spinsters; // Spinsters nao precisam ser armazenadas, apenas lidas e ignoradas
    }
}