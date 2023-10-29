// Usar nth_element cpp
#include <iostream>
#include <vector>
#include <algorithm> // nth element

using namespace std;

int median(vector<long long> numbers);
void print_vector(vector<long long> numbers);

int main() {
    long long curr_number;
    vector<long long> numbers;

    while (cin >> curr_number) { // Para ler ate nao conseguir mais ler nada no arquivo
        numbers.push_back(curr_number);
        cout << median(numbers) << '\n';
    }

    return EXIT_SUCCESS;
}

int median(vector<long long> numbers) {
    // Nth_element trabalha com iteradores ("ponteiros")
    // Begin e End sao iteradores 
    // Queremos ordenar corretamente o elemento do meio, que sera a mediana
    nth_element(numbers.begin(), numbers.begin() + int(numbers.size() / 2), numbers.end());
    
    long long curr_median = numbers[numbers.size() / 2];

    // Calculos diferentes dependendo se a qtd de elementos no vetor eh par ou impar
    // Qtd impar --
        // Entao mediana eh o elemento que, ao ordenar o vetor, ficaria na posicao do meio dele.

    // Qtd par
        // Entao mediana eh dada pela media aritmetica dos elementos que, ao ordenar o vetor,
        // ficariam no meio dele
    if (numbers.size() % 2 == 0) { 
        // Chamar nth_element para ordenar o elemento do centro mais a esquerda, pois com a chamada previa à funcao
        // nao garantimos que os elementos a esquerda estejam ordenados, apenas que sao menores que o nth
        nth_element(numbers.begin(), numbers.begin() + int(numbers.size() / 2 - 1), numbers.end());

        long long other_centered = numbers[numbers.size() / 2 - 1]; // Mais a esquerda 
        curr_median = (curr_median + other_centered) / 2;
    }

    return curr_median;
}

void print_vector(vector<long long> numbers) {
    int size = numbers.size();

    for (int i = 0; i < size; i++) {
        cout << numbers[i] << ' ';
    }

    cout << '\n';
}