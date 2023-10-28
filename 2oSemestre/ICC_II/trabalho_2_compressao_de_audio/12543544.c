/*
 * Nome: Danielle Modesti
 * No USP: 12543544
 * Codigo do Curso: SCC0201
 * Disciplina: Introducao a Ciencia da Computacao II - 2° Semestre de 2021
 * Trabalho 02: Compressao de Audio
 * 
 */

#include <complex.h> // Para operar com a DFT
#include <math.h>    // Para a magnitude
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

// Para cada coeficiente
typedef struct CoefficientInfo {
    double complex data;
    int original_index;
} coef_t;

// Flag para ordenacao do vetor de coeficientes
typedef enum SortFlag {
    MAGNITUDE = 1,
    INDEX = 2
} sort_flag_t;

char *read_line();
unsigned char *read_wav_data(char *file_name, int *max_coefficient_amt, unsigned char header[44]);
coef_t *DFT(unsigned char *audio, int length);
double magnitude(double complex element);
bool comparator(coef_t element_1, coef_t element_2, sort_flag_t f);
void intercalate(coef_t *vector, int start, int end, sort_flag_t f);
void merge_sort(coef_t *vector, int start, int end, sort_flag_t f);
void put_zeros(coef_t *vector, int size, int coefficient_to_keep_amt);
unsigned char *IDFT(coef_t *coef, int length);
bool save_wav_data(unsigned char *my_audio, int length, unsigned char header[44]);
void less_or_equal_zero_amt(coef_t *vector, int size);
void print_most_important_magnitudes(coef_t *vector, int compressed_amt);
void free_memory(char **file_name, unsigned char **sample_vector, coef_t **coefficient);

int main() {
    // Receber entrada
    char *file_name = read_line();
    int compressed_amt;
    scanf("%d", &compressed_amt);

    // Criar vetor de unsigned char de samples, o qual sera dinamicamente alocado
    unsigned char *sample = NULL;
    int max_coefficient_amt;
    unsigned char header[44];

    // Manipular arquivo recebido
    sample = read_wav_data(file_name, &max_coefficient_amt, header);
    printf("%d\n", max_coefficient_amt); 

    if (!sample) {
        printf("Arquivo invalido ou nao pode ser aberto, ou problema na alocacao! =(\n");

        return EXIT_FAILURE;
    }

    // A DFT gera um vetor de coeficientes complexos
    coef_t *coefficient = DFT(sample, max_coefficient_amt);
    
    // Limpando a informacao desse vetor para reutiliza lo na IDFT
    free(sample);

    if (!coefficient) {
        printf("Problema na alocacao! =(\n");

        return EXIT_FAILURE;
    }

    // Contagem de coeficientes <= 0 entre todas as samples do audio original
    less_or_equal_zero_amt(coefficient, max_coefficient_amt);

    // Ordenando os coeficientes por magnitude, da mais relevante para a menos
    merge_sort(coefficient, 0, max_coefficient_amt - 1, MAGNITUDE);
    print_most_important_magnitudes(coefficient, compressed_amt);

    // Atribuindo 0 aos coeficientes de posicoes posteriores as dos que serao 
    // utilizados na compressao, ou seja, aos coeficientes menos relevantes
    put_zeros(coefficient, max_coefficient_amt, compressed_amt);

    // Voltar coeficientes para posicao original, de antes da ordenacao pelas 
    // magnitudes mais notaveis. Ou seja, ordenar pelos indices originais 
    // armazenados, do menor ao maior
    merge_sort(coefficient, 0, max_coefficient_amt - 1, INDEX);

    // Aplicar a transformada inversa
    sample = IDFT(coefficient, max_coefficient_amt);

    // Salvar o resultado da transformada em um arquivo binario de audio
    bool is_valid_saving = save_wav_data(sample, max_coefficient_amt, header);

    if (!is_valid_saving) {
        printf("Nao conseguiu salvar no arquivo! =(\n");
        return EXIT_FAILURE;
    }

    // Liberar memoria dinamicamente alocada
    free_memory(&file_name, &sample, &coefficient);

    return EXIT_SUCCESS;
}

char *read_line() {
    char curr_char;
    char *line = NULL;
    int line_size = 0;

    // Consumir chars possivelmente restantes no buffer
    do {
        curr_char = getchar();
    } while (curr_char == '\r' || curr_char == '\n');

    // Devolver char se valido
    if (curr_char != EOF) {
        ungetc(curr_char, stdin);
    }

    line = (char *) malloc(BUFFER_SIZE * sizeof(char));

    do {
        curr_char = getchar();
        line_size++;

        if (curr_char != '\r' && curr_char != '\n' && curr_char != EOF) {
            // Teste do buffer
            if (line_size % BUFFER_SIZE == 0) {
                line = (char *) realloc(line, ((line_size / BUFFER_SIZE + 1) * BUFFER_SIZE) * sizeof(char));
            }

            line[line_size - 1] = curr_char;
        }
        else {
            line[line_size - 1] = '\0';
        }

    } while (curr_char != '\r' && curr_char != '\n' && curr_char != EOF);

    // Corrigir a alocacao
    line = (char *) realloc(line, line_size * sizeof(char));

    return line;
}

// Funcao fornecida para ler dados do arquivo binario de audio
unsigned char *read_wav_data(char *file_name, int *max_coefficient_amt, unsigned char header[44]) {
    FILE *audio_file = NULL;

    audio_file = fopen(file_name, "rb");

    if (!audio_file) {
        return NULL;
    }

    unsigned char buf4[4];

    // --- Leitura de cabecalho --- 

    // Copiar o cabecalho de 44 bytes para poder salvar no meu arquivo de audio
    fread(header, sizeof(unsigned char), 44, audio_file); 
    
    // Chegar na posicao de leitura da quantidade de dados do audio
    fseek(audio_file, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, audio_file);

    // Shifting para ler little endian
    int data_size = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    // Salvar quantidade maxima de coeficientes que serao gerados
    *max_coefficient_amt = data_size;

    // Alocacao dinamica do vetor de samples
    unsigned char *data = malloc(data_size * sizeof(*data));
    
    int i = 0;
    while (i < data_size) {
        fread(&data[i++], sizeof(unsigned char), 1, audio_file);
    }

    fclose(audio_file);

    // data == samples
    return data;
}

// Funcao fornecida para aplicar DFT no vetor de samples:
// os audios sao curtos pois eh uma funcao com complexidade n² (tipico de for 
// dentro de for percorrendo length toda)
coef_t *DFT(unsigned char *audio, int length) {
    coef_t *coefficient = (coef_t *) calloc(length, sizeof(coef_t));

    for (int k = 0; k < length; k++) {
        // n eh o indice do somatorio
        for (int n = 0; n < length; n++) {
            coefficient[k].data += audio[n] * cexp((-2.0 * M_PI * (((k + 1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }

        // Guardar posicao original dos coeficientes, para os proximos passos
        coefficient[k].original_index = k;
    }

    return coefficient;
}

// -------------------- Funcoes Para Ordenacao por Merge_sort ------------------

double magnitude(double complex element) {
    // Medida pela distancia euclidiana ou modulo do numero complexo
    return sqrt(pow(creal(element), 2) + pow(cimag(element), 2));
}

// Criterios para ordenacao: ha duas possiveis flags. Primeiro, precisamos ordenar
// por magnitude. Depois, por indices.
bool comparator(coef_t element_1, coef_t element_2, sort_flag_t f) {
    switch(f) {
        case MAGNITUDE:
            return magnitude(element_1.data) > magnitude(element_2.data);
        case INDEX:
            return element_1.original_index < element_2.original_index;
    }

    return false;
}

// Conquistar
void intercalate(coef_t *vector, int start, int end, sort_flag_t f) {
    coef_t *aux = (coef_t *) malloc((end - start + 1) * sizeof(coef_t));

    // Recalculo do centro
    int center = (start + end) / 2;  

    // Valores iniciais dos iteradores

    // iterador no subvetor esquerdo
    int i = start;    

    // iterador no subvertor direito
    int j = center + 1;  

    // iterador no vetor auxiliar
    int k = 0;      

    // Enquanto ainda houver elementos das duas listas para serem comparados, 
    // faremo-lo
    while (i <= center && j <= end) {
        if (comparator(vector[i], vector[j], f)) {
            aux[k].data = vector[i].data;
            aux[k].original_index = vector[i].original_index;
            i++;
        } 

        else {
            aux[k].data = vector[j].data;
            aux[k].original_index = vector[j].original_index;
            j++;
        }

        k++;
    }

    // Terminar de preencher - Apenas um dos 2 próximos loops ocorre
    while (i <= center) {
        aux[k].data = vector[i].data;
        aux[k].original_index = vector[i].original_index;
        i++;
        k++;
    }

    while (j <= end) {
        aux[k].data = vector[j].data;
        aux[k].original_index = vector[j].original_index;
        j++;
        k++;
    }

    // Copiar vetor ordenado para o vetor original
    for (i = start, k = 0; i <= end; i++, k++) {
        vector[i].data = aux[k].data;
        vector[i].original_index = aux[k].original_index;
    }

    free(aux);
}

// Dividir
void merge_sort(coef_t *vector, int start, int end, sort_flag_t f) {
    //  Caso base - conquistar
    if (start == end) {
        return;
    }

    // Dividir
    int center = (start + end) / 2;

    merge_sort(vector, start, center, f);      // 1a metade
    merge_sort(vector, center + 1, end, f);    // 2a metade

    intercalate(vector, start, end, f);
}

// ----------------------------------------------------------------------------


// Colocar zeros aos coeficientes que ocupam posicoes fora das samples que 
// desejamos manter
void put_zeros(coef_t *vector, int size, int coefficient_to_keep_amt) {
    for (int i = coefficient_to_keep_amt; i < size; i++) {
        vector[i].data = 0;
    }
}

// A Inversa gera o audio comprimido para salvar num arquivo.
// Ela reconstitui o audio original sem os valores esparsos - nulos ou proximos
// de zero -, mantendo os coeficientes mais importantes.
unsigned char *IDFT(coef_t *coef, int length) {
    unsigned char *audio = (unsigned char *) calloc(length, sizeof(unsigned char));

    for (int n = 0; n < length; n++) {
        // Complexo auxiliar para o somatorio
        double complex c = 0.0;

        // k eh o indice do somatorio
        for (int k = 0; k < length; k++) {
            c += coef[k].data * cexp((2.0 * M_PI * (((k + 1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }

        // Conversao para inteiro
        audio[n] = (int)(creal(c) / (length * 1.0));
    }

    return audio;
}

// Salvar dados no arquivo binario de audio
bool save_wav_data(unsigned char *my_audio, int length, unsigned char header[44]) {
    FILE *my_audio_file = fopen("my_audio_file.wav", "wb");
    
    if (!my_audio_file) {
        return false;
    }

    fwrite(header, sizeof(unsigned char), 44, my_audio_file);
    fwrite(my_audio, sizeof(unsigned char), length, my_audio_file);
    fclose(my_audio_file);

    return true;
}

// Contar e exibir numero de valores menores ou iguais a zero tanto na parte
// real como na imaginaria
void less_or_equal_zero_amt(coef_t *vector, int size) {
    int counter = 0;
    for (int i = 0; i < size; i++) {
        if (creal(vector[i].data) <= 0 && cimag(vector[i].data) <= 0) {
            counter++;
        }
    }

    printf("%d\n", counter);
}

// Imprimir so os coeficientes mais relevantes
// Conversao para int dos elementos
void print_most_important_magnitudes(coef_t *vector, int compressed_amt) {
    for (int i = 0; i < compressed_amt; i++) {
        printf("%d\n", (int)magnitude(vector[i].data));
    }
}

// Liberar memoria dinamicamente alocada
void free_memory(char **file_name, unsigned char **sample_vector, coef_t **coefficient) {
    if (*file_name) {
        free(*file_name);
        *file_name = NULL;
    }

    if (*sample_vector) {
        free(*sample_vector);
        *sample_vector = NULL;
    }

    if (*coefficient) {
        free(*coefficient);
        *coefficient = NULL;
    }
}