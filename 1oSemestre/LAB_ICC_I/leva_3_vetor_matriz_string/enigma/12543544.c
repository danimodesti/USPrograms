// Danielle Modesti
// No USP: 12543544

#include <stdio.h>

// Funcao para rotacionar os valores nos rotores
// Void -> porque funcoes com vetores ocorrem por referencia, ja modificando a propria variavel, nao criando uma copia
void rotacao(int rotor_n[26]);

int main() {
    int rotor_1[26], rotor_2[26], rotor_3[26]; // Rotores com 26 posicoes -> para cada char do alfabeto (A-Z)
    char char_codificado;

    scanf("%*[^\r\n]s"); // Ignora tudo até o final da linha, pois nao vamos usar 'Rotores:'
    scanf("%*[\r\n]s"); // Ignora o pula linha, pois nao vamos usar '\n'

    // Preencher valores do primeiro rotor
    for (int i = 0; i < 26; i++) 
        scanf("%d", &rotor_1[i]);

    // Preencher valores do segundo rotor
    for (int i = 0; i < 26; i++)
        scanf("%d", &rotor_2[i]);
    
    // Preencher valores do terceiro rotor
    for (int i = 0; i < 26; i++) 
        scanf("%d", &rotor_3[i]);

    scanf("%*[\r\n]s"); // Ignora o pula linha, pois nao vamos usar '\n'
    scanf("%*[^\r\n]s"); // Ignora tudo até o final da linha, pois nao vamos usar 'Mensagem:'
    scanf("%*[\r\n]s"); // Ignora o pula linha, pois nao vamos usar '\n'

    // Ao receber a mensagem codificada:
    // Leia chars, decodifique, imprima; leia char, decofique, imprima: -> repita ate condicao de parada: EOF (end of file -> no terminal: ctrl + d)
    // Usar getchar ou scanf

    // Contar rotacoes
    int cont_rot_1 = 0;
    int cont_rot_2 = 0;
    int cont_rot_3 = 0;

    while (scanf("%c", &char_codificado) != EOF) {
        // Processe e decodifique o char lido
        // O que executar?
        // Verifique se eh maiuscula
        if (char_codificado >= 'A' && char_codificado <= 'Z') {
            char char_decodificado = rotor_3[rotor_2[rotor_1[char_codificado - 65]]] + 65; // pois A = 65 em ASCII (interpretacao do computador)
            printf("%c", char_decodificado); // Exibe o equivalente em char do int encontrado
            rotacao(rotor_1);
            cont_rot_1++;
            if (cont_rot_1 % 26 == 0) {
                rotacao(rotor_2);
                cont_rot_2++;
                if (cont_rot_2 % 26 == 0) {
                    rotacao(rotor_3);
                    cont_rot_3++;
                }
            }
        }
        // Verifique se eh minuscula
        else if (char_codificado >= 'a' && char_codificado <= 'z') {
            char char_decodificado = rotor_3[rotor_2[rotor_1[char_codificado - 97]]] + 97; // pois a = 97 em ASCII (interpretacao do computador)
            printf("%c", char_decodificado);
            rotacao(rotor_1);
            cont_rot_1++;
            if (cont_rot_1 % 26 == 0) {
                rotacao(rotor_2);
                cont_rot_2++;
                if (cont_rot_2 % 26 == 0) {
                    rotacao(rotor_3);
                    cont_rot_3++;
                }
            }
        }
        // Se for simbolo especial: . , ' ...
        else {
            printf("%c", char_codificado); // Nao passa pelos rotores
        }
    }

    return 0;
}

void rotacao(int rotor_n[26]) {
    int copia_indice_0 = rotor_n[0]; // Guardar uma copia desse valor

    for (int i = 0; i < 25; i++) 
        rotor_n[i] = rotor_n[i + 1];
    
    rotor_n[25] = copia_indice_0;
}