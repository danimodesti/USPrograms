#include <iostream>
#include <unordered_map> // Alunos se ligam a projeto
#include <vector> // Para ordenar elementos do map por int e depois por string
#include <algorithm> // sort

#define INPUT_END "0"
#define TEST_END "1"
#define BLACKLISTED "-1" // Alunos ja removidos e que nao podem aparecer
                        // novamente em nenhum projeto.

using namespace std;

typedef unordered_map<string, string> student_project_map;
typedef unordered_map<string, int> project_studentamt_map;
typedef pair<string, int> si;

void solve_case(string& input);

istream& read_line(istream& stream, string& str);

int main() {
    string input;
    read_line(cin, input); // Primeiro nome de projeto
    
    do {
        solve_case(input); // Resolve cada caso (ate ler "1")
        read_line(cin, input); // Checar se proxima linha termina a entrada ou se eh outro teste
    } while (input != INPUT_END); // Fim dos casos

    return EXIT_SUCCESS;
}

// Implementacao de getline, mas trata \r\n (Windows format)
istream& read_line(istream& stream, string& str) {
    char c;
    str.clear(); // Garantir string vazia no inicio
    while (stream.get(c) && c != '\n') {
        if (c != '\r') {
            str.push_back(c);
        }
    }

    return stream;
}

bool comparator(si& a, si& b) {
    if (a.second > b.second) {
        return true;
    }

    if (a.second == b.second && a.first < b.first) {
        return true;
    }

    return false;
}

void print_psa_map(project_studentamt_map& psa) {
    vector<si> v;
    for (project_studentamt_map::iterator it = psa.begin(); it != psa.end(); it++) {
        si p;
        p.first = it->first; p.second = it->second;
        v.push_back(p);
    }

    sort(v.begin(), v.end(), comparator);

    for (si p : v) { // for p in v
        cout << p.first << ' ' << p.second << '\n';
    }
}

void print_sp_map(student_project_map& sp) {
    cout << "\nMAPA STUDENT-PROJECT\n";
    for (student_project_map::iterator it = sp.begin(); it != sp.end(); it++) {
        cout << it->first << ' ' << it->second << '\n';
    }

    cout << '\n';
}

bool student_has_project(string& student_user, student_project_map& sp) {
    return (sp[student_user] != "");
}

// Controle da leitura do teste/caso e marcacao dos alunos (que se inscrevem em mais de um proj ou nao)
void set_data(string& input, student_project_map& sp, project_studentamt_map& psa) {
    string curr_project = input;
    psa[curr_project] = 0; // Nenhum aluno ao inicializar projeto

    // Ler usernames de alunos, se houver
    do {
        read_line(cin, input);
        if (islower(input[0])) { // Eh realmente aluno
            string prev_project = sp[input];
            if (prev_project != "") {
                if (prev_project != BLACKLISTED && prev_project != curr_project) {
                    sp[input] = BLACKLISTED;
                } 

                // Projeto invalido ou mesmo projeto -> ignorar
            }

            else {
                sp[input] = curr_project;
            }
        }
    } while (islower(input[0]));
}

// Resolve o caso teste --> ate ler "1"
void solve_case(string& input) {
    // Estruturas de armazenamento do problema:
    //   Mapa com relacoes aluno-projeto (cada aluno so pode ter um projeto, 
    // mas um projeto pode conter varios alunos).
    student_project_map sp;

    //   Mapa com relacoes projeto-numero_alunos (para exibir no final).
    project_studentamt_map psa;

    // Logica de leitura e armazenamento de dados
    do {
        set_data(input, sp, psa);
    } while (input != TEST_END); // Ate finalizar caso de teste atual

    
    // Contabilizar alunos nos projetos validos
    for (auto &s : sp) {
        if (s.second != BLACKLISTED) {
            psa[s.second]++;
        }
    }
    
    print_psa_map(psa);
}