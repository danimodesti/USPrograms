#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND 404

typedef struct Song {
    int id; // Para contar a partir do song 1
    int duration; // Em minutos
    int times_played; 
} song_t;

typedef struct Playlist {
    int song_amt;
    int liked_time_amt; // Qtd. de instantes de tempo (em minuto) nos quais gostou de uma musica
    int *liked_times; // Momentos de tempo nos quais gostou de uma musica
    song_t *songs;
} playlist_t;

void read_songs(playlist_t *p);
void read_liked_times(playlist_t *p);
void print_playlist_info(playlist_t *p);
int *time_tracking(playlist_t *p);
int binary_search(int *search_array, int key, int start, int end);

int main() {
    playlist_t eugeny_playlist;
    scanf(" %d %d", &eugeny_playlist.song_amt, &eugeny_playlist.liked_time_amt);
    read_songs(&eugeny_playlist);
    read_liked_times(&eugeny_playlist);

    int *time_spent = time_tracking(&eugeny_playlist);

    // Para cada momento em que Eugeny curtiu uma musica, encontre qual eh a musica
    // tocando naquele momento.
    for (int i = 0; i < eugeny_playlist.liked_time_amt; i++) {
        int key = eugeny_playlist.liked_times[i];
        int song_id = binary_search(time_spent, key, 0, eugeny_playlist.song_amt - 1);
        printf("%d\n", song_id + 1); // Song id + 1 para contar a partir do 1
    }

    free(eugeny_playlist.songs);
    free(eugeny_playlist.liked_times);
    free(time_spent);

    return EXIT_SUCCESS;
}

void print_song_info(song_t *s) {
    printf("# Dados da musica %d #\n", s->id);
    printf("Id (contando a partir do 1): %d\n", s->id);
    printf("Qtd de vezes em que musica foi tocada: %d\n", s->times_played);
    printf("Duracao da musica em minutos: %d\n\n", s->duration);
}

void read_songs(playlist_t *p) {
    p->songs = (song_t *) malloc(sizeof(song_t) * p->song_amt);
    for (int i = 0; i < p->song_amt; i++) {
        p->songs[i].id = i + 1; // Contar a partir do 1
        scanf(" %d %d", &p->songs[i].times_played, &p->songs[i].duration); 
    }
}

void read_liked_times(playlist_t *p) {
    p->liked_times = (int *) malloc(sizeof(int) * p->liked_time_amt);

    for (int i = 0; i < p->liked_time_amt; i++) {
        scanf(" %d", &p->liked_times[i]);
    }
}

void print_playlist_info(playlist_t *p) {
    printf("## Dados da Playlist ##\n\n");
    printf("Quantidade de musicas: %d\n", p->song_amt);
    printf("Quantidade de momentos (tempo) em que gostou de uma musica: %d\n", p->liked_time_amt);
    printf("Dados das musicas:\n\n");
    for (int i = 0; i < p->song_amt; i++) {
        print_song_info(&p->songs[i]);
    }

    printf("Momentos nos quais gostou de uma musica:\n\n");
    for (int i = 0; i < p->liked_time_amt; i++) {
        printf("%d\n", p->liked_times[i]);
    }
    printf("\n");
}

// Guarda, em cada indice, o tempo final da musica de id i + 1
int *time_tracking(playlist_t *p) {
    int *times = (int *) malloc(sizeof(int) * p->song_amt);

    times[0] = p->songs[0].times_played * p->songs[0].duration;

    for (int i = 1; i < p->song_amt; i++) {
        times[i] = p->songs[i].times_played * p->songs[i].duration + times[i - 1]; // Acumular
    }

    return times;
}

/* Busca binaria iterativa
   Assume que o vetor esta ordenado
   @param search_array vetor de inteiros para realizar a busca
   @param chave a ser buscada
   @param start posicao inicial do espaco de busca
   @param end posicao final do espaco de busca
   @return posicao em que a chave foi encontrada, ou NOT_FOUND caso contrario
*/
int binary_search(int *search_array, int key, int start, int end) {
    while (start <= end) { // Ainda nao procurou em todo o espaco de busca
		// Calcula ponto central e verifica se chave foi encontrada
		int center = (start + end) / 2;
		
        // Para center == 0, significa que chegamos a primeira musica (id center + 1). Tratamos
        // essa condicao aqui porque nao ha 'acumulacao' de minutos; acabou aqui a busca e 
        // sobrou apenas o elemento do indice zero.

        // Para key == search_array[center], significa que estamos procurando
        // exatamente o ultimo minuto em que a musica de id center + 1 esta tocando.
		if (key == search_array[center] || center == 0) {
            return center;
        }

		// Chave esta antes do centro, reduz a metade o espaco de busca
		if (key < search_array[center]) {
            // Se a chave (o instante de tempo) for maior que o de search_array[center - 1] e
            // menor que o de search_array[center], significa que a musica anterior, de id (center - 1) + 1,
            // ja acabou e a musica de id (center) + 1 comecou. Entao, ja estamos na musica de id (center).
            if (search_array[center - 1] < key) {
                
                return center;
            }

            // Pode ser que search_array[center - 1] == key, por ex. Isso entra nessa condicao da b.binaria
            end = center - 1;
        }

		// Chave esta depois do centro, reduz a metade o espaco de busca
		else if (key > search_array[center]) {
            start = center + 1; // Inicio do espaco de busca agora considera so o que esta depois do centro
        }
	}

    // Chave nao pode ser encontrada em todo o espaco de busca
	return NOT_FOUND; 
}