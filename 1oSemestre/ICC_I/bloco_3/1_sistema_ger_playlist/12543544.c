/**
 * Nome: Danielle Modesti
 * No USP: 12543544
**/

#include <stdio.h>
#include <stdlib.h>

typedef enum ManagerOperation {
    ADD_SONG_TO_PLAYLIST = 1,
    VIEW_SONGS_IN_PLAYLIST = 2,
    GOTO_NEXT_SONG = 3,
    GOTO_PREVIOUS_SONG = 4,
    SAVE_CURRENT_PLAYLIST = 5,
    LOAD_SAVED_PLAYLIST = 6,
    FINISH_PROGRAM = 7
} manager_operation_t;

typedef struct Song {
    char *name;
    char *artist;
    unsigned int duration;
} song_t;

typedef struct Playlist {
    char *name;
    int song_amount;
    song_t *song_set;  
} playlist_t;

char *read_line();
song_t read_song();
void add_song(playlist_t *playlist);
void insert_in_playlist(playlist_t *playlist, song_t current_song);
void binary_to_num(char *bin_filename);
int string_length(char *generic_string);
void free_playlist_info(playlist_t *playlist);

int main() {
    playlist_t current_playlist;

    current_playlist.song_set = NULL; 

    // Muda onde esta o now playing
    song_t *playing_song = NULL;

    // No comeco da execucao: sera dado o nome da playlist, a qual comeca vazia
    current_playlist.name = read_line();
    current_playlist.song_amount = 0; 

    int music_manager;
    
    // Comeca a tocar na primeira musica
    int now_playing = 0; 

    // Funcionalidades do gerenciador - controle seus comandos
    do {
        // Criando um arquivo
        FILE *playlist_file = NULL;

        // Para ler o nome do arquivo
        char *playlist_file_name;

        // Guardar tamanhos de dados da musica
        int song_name_length, song_artist_length;

        scanf("%d", &music_manager);
        getchar();

        switch(music_manager) {
            case ADD_SONG_TO_PLAYLIST:
                if (current_playlist.song_amount < 15) {
                    add_song(&current_playlist);
                    playing_song = current_playlist.song_set + now_playing;
                }
                else 
                    printf("Playlist cheia!\n");
                break;
            case VIEW_SONGS_IN_PLAYLIST:
                printf("---- Playlist: %s ----\n", current_playlist.name);
                printf("Total de musicas: %d\n\n", current_playlist.song_amount);

                for (int i = 0; i < current_playlist.song_amount; i++) {
                    if (playing_song == &current_playlist.song_set[i])
                        printf("=== NOW PLAYING ===\n");
                    printf("(%d). '%s'\n", i + 1, current_playlist.song_set[i].name);
                    printf("Artista: %s\n", current_playlist.song_set[i].artist);
                    printf("Duracao: %u segundos\n\n", current_playlist.song_set[i].duration);
                }
                break;
            case GOTO_NEXT_SONG:
                now_playing = (now_playing + 1) % current_playlist.song_amount;
                playing_song = current_playlist.song_set + now_playing;
                break;
            case GOTO_PREVIOUS_SONG:
                now_playing = (now_playing - 1 + current_playlist.song_amount) % current_playlist.song_amount;
                playing_song = current_playlist.song_set + now_playing;
                break;
            case SAVE_CURRENT_PLAYLIST:

                // Agora, o ponteiro aponta para esse arquivo
                playlist_file_name = read_line();
                playlist_file = fopen(playlist_file_name, "wb");

                // Escrever no arquivo
                // Cabecalho de um arquivo de playlist
                int playlist_name_length = string_length(current_playlist.name);
                fwrite(&playlist_name_length, sizeof(int), 1, playlist_file);
                fwrite(current_playlist.name, sizeof(char), playlist_name_length, playlist_file);
                fwrite(&current_playlist.song_amount, sizeof(int), 1, playlist_file);

                // Estrutura de um registro de musica no arquivo de playlist
                // Fazer o mesmo processo para todas as musicas
                for (int i = 0; i < current_playlist.song_amount; i++) {
                    song_name_length = string_length(current_playlist.song_set[i].name);
                    fwrite(&song_name_length, sizeof(int), 1, playlist_file);
                    fwrite(current_playlist.song_set[i].name, sizeof(char), song_name_length, playlist_file);

                    song_artist_length = string_length(current_playlist.song_set[i].artist);
                    fwrite(&song_artist_length, sizeof(int), 1, playlist_file);
                    fwrite(current_playlist.song_set[i].artist, sizeof(char), song_artist_length, playlist_file);
                    fwrite(&current_playlist.song_set[i].duration, sizeof(unsigned int), 1, playlist_file);
                }

                // Fechar o arquivo
                fclose(playlist_file);

                // Chamar binary_to_num
                printf("Playlist %s salva com sucesso.\n", playlist_file_name);
                binary_to_num(playlist_file_name);
                free(playlist_file_name);
                break; 
            case LOAD_SAVED_PLAYLIST:
                // Ha uma playlist carregada na RAM? Descarte ela
                free_playlist_info(&current_playlist);

                // Carregar a playlist 
                playlist_file_name = read_line();

                playlist_file = fopen(playlist_file_name, "rb");
                
                if (playlist_file == NULL) {
                    printf("Arquivo %s nao existe.\n", playlist_file_name);
                    free(playlist_file_name);
                    exit(0);
                }

                // Ler o cabecalho do arquivo de playlist
                // Cabecalho de um arquivo de playlist
                fread(&playlist_name_length, sizeof(int), 1, playlist_file);
                // printf("Tamanho do nome da Playlist: %d\n", playlist_name_length);

                // Alocar memoria para o nome da playlist
                current_playlist.name = (char *) malloc(sizeof(char) * (playlist_name_length + 1));
                fread(current_playlist.name, sizeof(char), playlist_name_length, playlist_file);
                current_playlist.name[playlist_name_length] = '\0';
                // printf("Nome da Playlist: %s\n", current_playlist.name);

                fread(&current_playlist.song_amount, sizeof(int), 1, playlist_file);
                // printf("Qtd de musicas na Playlist: %d\n", current_playlist.song_amount);
                
                // Alocar memoria para o conjunto de musicas
                current_playlist.song_set = (song_t *) malloc(sizeof(song_t) * current_playlist.song_amount);

                for (int i = 0; i < current_playlist.song_amount; i++) {
                    // Alocar memoria para o nome da musica e para o artista em cada indice
                    fread(&song_name_length, sizeof(int), 1, playlist_file);
                    current_playlist.song_set[i].name = (char *) malloc(sizeof(char) * (song_name_length + 1));
                    fread(current_playlist.song_set[i].name, sizeof(char), song_name_length, playlist_file);
                    current_playlist.song_set[i].name[song_name_length] = '\0';

                    fread(&song_artist_length, sizeof(int), 1, playlist_file);
                    current_playlist.song_set[i].artist = (char *) malloc(sizeof(char) * (song_artist_length + 1));
                    current_playlist.song_set[i].artist[song_artist_length] = '\0';

                    fread(current_playlist.song_set[i].artist, sizeof(char), song_artist_length, playlist_file);
                    fread(&current_playlist.song_set[i].duration, sizeof(unsigned int), 1, playlist_file);
                }

                // O NOW PLAYING deve aparecer na primeira musica
                now_playing = 0;
                playing_song = current_playlist.song_set;

                // Fechar o arquivo
                fclose(playlist_file);

                // Chamar binary_to_num
                printf("Playlist %s carregada com sucesso.\n", playlist_file_name);
                binary_to_num(playlist_file_name);
                free(playlist_file_name);
                break;
            case FINISH_PROGRAM:
                // Liberar a memoria alocada dinamicamente
                free_playlist_info(&current_playlist);
                break;
            default: 
                printf("Opcao invalida\n");
                break;
        }
    } while (music_manager != FINISH_PROGRAM);

    return EXIT_SUCCESS;
}

// Para ler e alocar strings
char* read_line() {
    char* line = NULL; 
    char current_char; 
    int line_size = 0; 

    do { 
        current_char = getchar();
        line_size++; 

        line = (char*) realloc(line, sizeof(char) * line_size); 

        if (current_char != '\n')
            line[line_size - 1] = current_char; 
        else
            line[line_size - 1] = '\0'; 
    } while (current_char != '\n'); 

    return line; 
}

// Dados da musica para inserir na playlist
song_t read_song() {
    song_t song_info; 

    song_info.name = read_line();
    song_info.artist = read_line();
    scanf("%u", &song_info.duration);   

    return song_info; 
}

void add_song(playlist_t *playlist) {
    song_t current_song = read_song();
    (*playlist).song_amount++;
    insert_in_playlist(playlist, current_song);
    printf("Musica %s de %s adicionada com sucesso.\n", current_song.name, current_song.artist);
}

// Receber a playlist e inserir as musicas nela, alterando seu tamanho
void insert_in_playlist(playlist_t* playlist, song_t current_song) {
    // Alocar espacos para as musicas
    playlist->song_set = (song_t*) realloc(playlist->song_set, sizeof(song_t) * playlist->song_amount); 
    
    // Inserir a musica atual
    playlist->song_set[playlist->song_amount - 1] = current_song;
}

// Soma polinomial que interpreta o valor binário como um valor numérico.
// Quanto mais próximo o valor de retorno, mais próximo seu binário está do ideal.
//
// Parâmetros: Nome do arquivo (bin_filename: char *)
// Retorno: Nada (void)
void binary_to_num(char *bin_filename) {
    FILE *fp = fopen(bin_filename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}

int string_length(char *generic_string) {
    int length = 0;
    while (generic_string[length] != '\0') {
        length++;
    }

    return length;
}

// Liberar a memoria alocada dinamicamente
void free_playlist_info(playlist_t *playlist) {
    free((*playlist).name);

    for (int i = 0; i < (*playlist).song_amount; i++) {
        free((*playlist).song_set[i].name);
        free((*playlist).song_set[i].artist);
    }
    
    free((*playlist).song_set);
}