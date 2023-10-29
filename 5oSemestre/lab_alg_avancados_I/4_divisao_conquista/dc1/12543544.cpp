#include <iostream>
#include <vector>
#include <cmath>

#define MAX 100000 // referente ao tamanho do vetor de N inteiros

// como os indices da coluna se tratam do expoente do tamanho do bloco, log2 MAX - 16, ... eh suficiente para guardar os dados
int lookup_table[MAX][17];

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

void fill_lookup_table(vi& numbers);
void print_table(vi& numbers);
int answer_query(ii query);

int main() {
    int number_amt, query_amt;
    cin >> number_amt;

    vi numbers(number_amt);
    for (int i = 0; i < number_amt; i++) {
       cin >> numbers[i];
    }

    // Construir tabela com O(n log n)
    fill_lookup_table(numbers);

    cin >> query_amt;

    // Retornar o indice do vetor com o menor valor neste intervalo,
    // com complexidade O(1).
    for (int i = 0; i < query_amt; i++) {
       ii curr;
       cin >> curr.first >> curr.second;
       
       cout << answer_query(curr) << '\n';
    }


    return EXIT_SUCCESS;
}

/*
 * Usar bitwise com shift left para fazer potencia. Cada shift left multiplica por 2.
 * Funciona assim:
 * 1 << 0 significa 2⁰ = 1 [1 vai para a esquerda 0 vezes, o que resulta em 1]
 * 1 << 1 significa 2¹ = 2 [1 vai para a esquerda 1 vez, o que resulta em 2 (01 vira 10 que eh 2 em binario)]
 * 1 << 5 significa 2⁵ = 32 [1 vai para a esquerda 5 vezes, o que resulta em 32 (01 vira 100000 que eh 32 em binario)]
*/
int power_of_two(int exponent) { 
    return (1 << exponent);
}

/*
 * Na matriz de consulta, preenchida para posteriormente responder as queries, temos a forma M[i][j].
 * i --> este indice representa onde comeca (inicio) a analise do intervalo para encontrar o valor minimo ali guardado
 * j --> este indice representa o expoente na forma 2^j. O 2^j trata do tamanho do intervalo analisado 
 *   ou seja, pode haver intervalos de 2^0 = 1 elemento, 2¹ = 2 elementos, 2² = 4 elementos, ... onde acharemos o qual tem 
 *   valor minimo.
 * 
 * O valor guardado em M[i][j] sera sempre o minimo naquele intervalo analisado.
*/
void fill_lookup_table(vi& numbers) {
    int number_amt = numbers.size();


    // A primeira coluna deve ser preenchida primeiro para servir de base para as proximas.
    // Ela guardara intervalos de 1 elemento, ou seja, 'qual eh o minimo no intervalo que comeca em i e tem 2⁰ = 1 de comprimento?'
    // R: sera o proprio elemento (minimo entre ele e ele mesmo).
    for (int i = 0; i < number_amt; i++) {
        lookup_table[i][0] = numbers[i];
    }

    /*
     * Nas proximas colunas, para exemplificar:
     * i = 0, j = 1 --> guarda intervalos de 2¹ = 2 elementos comecando no elemento que esta no indice 0
     * i = 1, j = 1 --> guarda intervalos de 2 elementos comecando no elemento que esta no indice 1
     * 
     * i = 3, j = 3 --> guarda intervalos de 2³ = 8 elementos comecando no elemento que esta no indice 3
    */

    for (int j = 1; power_of_two(j) <= number_amt; j++) { // Em um vetor com n elementos, posso dividir em intervalos de no max. 2^j = n
        /* Para a cond. de parada do i, eh preciso pensar nos limites dos blocos. 
        * Ex.: em um vet. de tamanho n = 10, se estou no j = 2, subdivido o vetor em dois blocos de 2² = 4 elementos (0 a 3 e 4 a 7).
        * Isso significa que quando i = 7, nao preencheremos, pois isso sairia dos limites do vetor (seria 7 + 4 - 1 = 10, idx inexistente).
        * O maior indice preenchido para um bloco de 4 elementos sera 6, pois 6 + 4 - 1 = 9, ultimo idx do vetor de 10 elem.
        */

        for (int i = 0; i + power_of_two(j) - 1 < number_amt; i++) { 
            // Para encontrar o minimo deste tamanho de intervalo, procure pelo minimo do tamanho de intervalo anterior.
            // Ex.: o minimo para um intervalo de j = 3, ie 2³ = 8 elementos corresponde ao minimo entre os dois sub-blocos
            // de j = 2 ie 2² = 4 elementos que o compoem.
            lookup_table[i][j] = min(lookup_table[i][j - 1], lookup_table[i + power_of_two(j - 1)][j - 1]); 
        }
    }
}

void print_table(vi& numbers) {
    int number_amt = numbers.size();
    for (int i = 0; i < number_amt; i++) {
        for (int j = 0; power_of_two(j) <= number_amt; j++) {
            if (i + power_of_two(j) - 1 >= number_amt) {
                cout << "x ";
            }

            else {
                cout << lookup_table[i][j] << ' ';
            }
        }

        cout << '\n';
    }
}

int get_greatest_interval_exponent(int interval_size) {
    int j = 0;

    while (power_of_two(j) <= interval_size) {
        j++;
    }

    return j - 1; // Maior expoente acerca do bloco que cabe
}

int answer_query(ii query) {
    int idx_start = query.first;
    int idx_end = query.second;

    int interval_size = (idx_end - idx_start + 1);

    /*
     * Como guardamos intervalos de potencia de base 2, queremos saber qual eh o maior bloco (de 1, de 2, de 4, de 8, ... elementos)
     * que podemos utilizar para responder a query com base na lookup table. Assim, se tivermos um intervalo de tamanho 5, por ex., 
     * para analisar, vamos unir intervalos de tamanho 4 (maior potencia de 2 na qual 5 esta contido eh 2² = 4) para encontrar a resposta.
    */
    int greatest_interval_exponent = get_greatest_interval_exponent(interval_size);

    return min(
        lookup_table[idx_start][greatest_interval_exponent], 
        lookup_table[idx_end - power_of_two(greatest_interval_exponent) + 1][greatest_interval_exponent]
    );
}