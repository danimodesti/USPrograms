#include <iostream>
#include <cstring>

using namespace std;

#define MAX 10000 // Maior tamanho de array possivel

int MEMO[MAX]; // Guardar maior subsequencia crescente (LIS) contendo cada indice do vetor

int max_increasing_subsequence(int *arr, int arr_len, int idx, int *max_lis);
void print_arr(int *arr, int arr_len);

int main() {
    // Leitura
    int arr_len;
    cin >> arr_len;

    int arr[arr_len];
    for (int i = 0; i < arr_len; i++) {
        cin >> arr[i];
    }

    // Processamento
    // Achar maior subsequencia/cadeia crescente (LIS) dentro do vetor
    
    memset(MEMO, -1, sizeof MEMO); // Inicializando o MEMO

    // LIS ate o valor que esta no em arr[arr_len - 1] (ultimo indice do arr)
    int max_l = 1;
    max_increasing_subsequence(arr, arr_len, arr_len - 1, &max_l); 
    
    // Essa eh a maior LIS do vetor inteiro
    int answer = max_l;

    // Retorno
    cout << answer << endl;

    return EXIT_SUCCESS;
}

// Retorna LIS para o idx passado
int max_increasing_subsequence(int *arr, int arr_len, int idx, int *max_lis) {
    // Se a sequencia tem tamanho 1, olhando pro indice idx, o tamanho da maior subsequencia eh 1
    if (idx == 0) {
        MEMO[0] = 1; // A LIS ate o indice 0 (de um so elemento) eh 1

        return 1;
    }

    // Verificar se o resultado ja foi computado
    if(MEMO[idx] != -1) {
        return MEMO[idx]; // Nao calcule a LIS ate aquele indice novamente
    }

    int curr_LIS = 1; // Nunca sera 1, esta englobado no caso base (valor min. possivel)
    for (int j = idx - 1; j >= 0; j--) {
        // Calcule o maximo LIS para todos os anteriores - chame a recursao para todos os 
        // valores anteriores ao de arr[i]
        int value = max_increasing_subsequence(arr, arr_len, j, max_lis) + 1; // +1 p/ incluir o elemento do ind. idx

        if (arr[idx] > arr[j]) { // Somente sequencia crescente eh valida
            curr_LIS = max(value, curr_LIS);
        }
    }

    // curr_LIS guarda a maior LIS contendo o elemento do ultimo indice considerado
    // max_lis guarda a maior LIS em quaqluer ponto do vetor todo, que eh o que queremos
    if (*max_lis < curr_LIS) {
        *max_lis = curr_LIS;
    }

    // Neste ponto, ja calculei todas as subsequencias, olhando todos os indices anteriores. Ja
    // sei qual eh a maior LIS ate ali com certeza.
    MEMO[idx] = curr_LIS;

    return curr_LIS;
}

void print_arr(int *arr, int arr_len) {
    for (int i = 0; i < arr_len; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}