#include <iostream>
#include <vector>
#include <bitset>
#include <map>

#define MAX 10000000 // 10 ^ 7

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
// Mapa do numero a ser fatorado em fatores primos
typedef map<ll, int> mli; // Mapeia fator long long para quantos fatores tem dele.

bitset<MAX + 5> sieve; // Crivo --> perguntar se o numero eh primo ou nao
vll primes; // Guarda os fatores primos --> iterar sobre numeros primos (guardar quais sao - passaram no teste)

void create_sieve();
mli factor_number(ll number);
void print_factor_decomposition(mli& factors); // Imprime na forma 'fator' - 'qtd de vezes em que aparece'
int factor_amt_in_factorial(ll factor, ll n);
bool divides_the_factorial(ll n, ll possible_divisor);

int main() {
    ll n, possible_divisor;
    
    create_sieve(); // Guardar um vetor de primos ate MAX

    while (cin >> n >> possible_divisor) {
        if (divides_the_factorial(n, possible_divisor)) {
            cout << possible_divisor << " divides " << n << "!\n";
        }

        else {
            cout << possible_divisor << " does not divide " << n << "!\n";
        }
    }

    return EXIT_SUCCESS;
}

void create_sieve() {
    // Cada elemento eh um bit (0 ou 1)
    sieve.set(); // Inicializar com 1 em todas as posicoes (supor todos primos)

    // 0 e 1 nao sao primos - remover do crivo
    sieve[0] = 0;
    sieve[1] = 0;

    for (ll i = 2; i <= MAX; i++) { // Para cada um dos numeros do crivo
        // Se o numero for primo (sieve[i] == 1)
        if (sieve[i]) {
            primes.push_back(i); // Guarda-lo no vetor de primo

            // Remover multiplos do fator primo.
            // Inicializar do i * i porque: se i = 2, remover 4, depois remover 4 + i(2), depois 6 + i(2), ...
            // quando i = 3, nao passa pelo 6, mas direto para o 9 --> j comeca em i * i -> 9 (maior eficiencia)
            for (ll j = i * i; j <= MAX; j += i) {
                sieve[j] = 0;
            }
        }
    }
}

mli factor_number(ll number) {
    ll idx = 0;
    ll prime_factor = primes[idx];
    mli factors; // Guardar number decomposto em fatores primos

    while (prime_factor * prime_factor <= number) { // Iterar ate que o fator primo seja <= a raiz do numero a ser fatorado eh suficiente
        // Enquanto for possivel fatorar para aquele fator primo
        while (number % prime_factor == 0) {
            // Fazer processo de fatoracao
            factors[prime_factor]++; 
            number /= prime_factor;
        }

        // Quando nao der mais para dividir por aquele fator primo, passar para o proximo fator primo guardado
        prime_factor = primes[++idx];
    }

    // Se passou por todos os possiveis fatores primos e nao conseguiu decompor, significa que o numero
    // em questao eh primo, entao, ele so eh divisivel por 1 e por ele mesmo
    if (number != 1) {
        factors[number]++; // Contabilizar ele mesmo como fator
    }

    return factors; 
}

void print_factor_decomposition(mli& factors) { // Passar mapa criado para um determinado numero a ser decomposto
    for (mli::iterator it = factors.begin(); it != factors.end(); it++) {
        cout << it->first << " - " << it->second << "\n";
    }
}

// Quantos fatores 'factor' existem/cabem no n!
int factor_amt_in_factorial(ll factor, ll n) {
    int factor_amt = 0;

    for (int power = factor; power <= n; power *= factor) {
        factor_amt += n / power;
    }

    return factor_amt;
}

bool divides_the_factorial(ll n, ll possible_divisor) {
    // 0 nao pode ser divisor
    if (possible_divisor == 0) {
        return false; 
    }

    // ex.: possible_divisor = 73 e n = 100,
    // --> 100! = 100 . 99 . ... . 73 . ... . 1 --> isso eh divisivel por 73
    if (possible_divisor <= n) {
        return true;
    }

    // Fatorando o divisor
    mli divisor_factors = factor_number(possible_divisor);

    for (mli::iterator it = divisor_factors.begin(); it != divisor_factors.end(); it++) {
        ll factor = it->first;
        int factor_amt_in_divisor = it->second;
        
        // Se tiver mais fatores no divisor do que no dividendo (n!), nao divide
        if (factor_amt_in_divisor > factor_amt_in_factorial(factor, n)) {
            return false;
        }
    }

    // Deu tudo certo (dividiu n!)
    return true;
}