// Danielle Modesti
// No USP: 12543544

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ADD_SONG_TO_PLAYLIST = 1,
    VIEW_SONGS_IN_PLAYLIST = 2,
    GOTO_NEXT_SONG = 3,
    GOTO_PREVIOUS_SONG = 4,
    FINISH_PROGRAM = 5
} manager_option;

typedef struct song {
    char* name;
    char* artist;
    unsigned int duration;
} song;

typedef struct playlist {
    char* name;
    int song_amount;
    song* song_set;  
} playlist;

// Funcoes
char* readLine();
song readSong();
void insertInPlaylist(playlist* current_playlist, song current_song);

int main() {
    // Criando a playlist, a qual tem caracteristicas intrinsecas
    playlist current_playlist;

    // Ponteiro vazio, nao aponta para nenhum endereco por enquanto
    current_playlist.song_set = NULL; 
    song* playing_song = NULL;

    // No comeco da execucao: sera dado o nome da playlist, a qual comeca vazia
    current_playlist.name = readLine();
    current_playlist.song_amount = 0; 

    int music_manager;
    // Comeca a tocar na primeira musica
    int now_playing = 0; 

    // Funcionalidades do gerenciador - controle seus comandos
    do {
        scanf("%d", &music_manager);
        getchar();

        switch(music_manager) {
            case ADD_SONG_TO_PLAYLIST:
                if (current_playlist.song_amount < 15) {
                    song current_song = readSong();
                    current_playlist.song_amount++;
                    insertInPlaylist(&current_playlist, current_song);
                    playing_song = current_playlist.song_set + now_playing;
                    printf("Musica %s de %s adicionada com sucesso.\n", current_song.name, current_song.artist);
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
            case FINISH_PROGRAM:
                break;
            default: 
                printf("Opcao invalida\n");
                break;
        }
    } while (music_manager != FINISH_PROGRAM);


    // Liberar a memoria alocada dinamicamente
    free(current_playlist.name);

    for (int i = 0; i < current_playlist.song_amount; i++) {
        free(current_playlist.song_set[i].name);
        free(current_playlist.song_set[i].artist);
    }
    
    free(current_playlist.song_set);

    return 0;
}

// Para ler e alocar strings
char* readLine() {
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
song readSong() {
    song song_info; 

    song_info.name = readLine();
    song_info.artist = readLine();
    scanf("%u", &song_info.duration);   

    return song_info; 
}

// Receber a playlist e inserir as musicas nela, alterando seu tamanho
void insertInPlaylist(playlist* current_playlist, song current_song) {
    // Alocar espacos para as musicas
    current_playlist->song_set = (song*) realloc(current_playlist->song_set, sizeof(song) * current_playlist->song_amount); 
    
    // Inserir a musica atual
    current_playlist->song_set[current_playlist->song_amount - 1] = current_song;
}