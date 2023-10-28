#include <iostream>

using namespace std;

void string_game(string& s);

int main() {
    int case_amt;
    cin >> case_amt;

    string s;

    for (int i = 0; i < case_amt; i++) {
        cin >> s;
        
        string_game(s);
        cout << s << '\n';
    }


    return EXIT_SUCCESS;
}

void string_game(string& s) {
    int str_size = s.size();

    for (int i = 0; i < str_size; i++) {
        // Vez de Alice
        if (i % 2 == 0) {
            if (s[i] == 'a') { // Precisa trocar por uma letra diferente
                s[i] = 'b'; // Porque queremos a 'menor' letra possivel no alfabeto
            }

            else { // Se antes nao era 'a'
                s[i] = 'a'; // Troque por 'a', a 'menor' letra possivel
            }
        }

        // Vez de Bob
        else {
            if (s[i] == 'z') { // Precisa trocar por uma letra diferente
                s[i] = 'y'; // Porque queremos a 'maior' letra possivel no alfabeto
            }

            else { // Se antes nao era 'z'
                s[i] = 'z'; // Troque por 'z', a 'maior' letra possivel
            }
        }
    }
}