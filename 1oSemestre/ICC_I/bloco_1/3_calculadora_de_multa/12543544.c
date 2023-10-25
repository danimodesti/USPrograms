// Biblioteca para comandos de entrada e saída, como printf e scanf
#include <stdio.h>

// Função principal para o programa rodar
int main() {

    // Declara a velocidade do automovel
    float velocidade;
    // Usuário entra com dados de velocidade em km/h
    scanf("%f", &velocidade);

    // Caso a velocidade ultrapasse o limite de 80 km/h, 
    if (velocidade > 80) {
        float multa;
        // Cálculo da multa para o automovel
        multa = 2 * (velocidade - 80);
        printf("Limite de velocidade excedido! Multado no valor de R$%.2f!\n", multa);
    }
    // Caso o veiculo esteja na vel certa,
    else {
        printf("Velocidade dentro do limite permitido.\n");
    }

    return 0;
}