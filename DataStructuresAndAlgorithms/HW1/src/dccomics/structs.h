#include<stdbool.h>
#include<stdio.h>

typedef struct cancion{
    int id;
    int disco_id;
    int largo;
    int valoracion;
    bool disponible;
    bool flag;
} Cancion;

typedef struct disco{
    int id;
    int largo;
    Cancion** canciones;
} Disco;

Cancion* cancion_init(int id, int disco_id, int largo, int valoracion);
Disco* disco_init(int id, int largo);
void eliminar_cancion(Cancion* cancion);
void imprimir_disco(Disco* disco, FILE *output_file);
void imprimir_cancion(Cancion* cancion, FILE *output_file);

typedef struct nodo{

    Cancion* cancion;
    struct nodo* siguiente;

} Nodo;

typedef struct playlist{

    int id;
    bool disponible;
    Nodo* inicio;

} Playlist;

Nodo* init_nodo(Cancion* cancion);
Playlist* init_playlist(int id);
void agregar_cancion(Playlist* playlist, Cancion* cancion);
bool eliminar_cancion_playlist(Playlist* playlist, int disk_id, int song_id);
int agregar_disco(Playlist* playlist, Disco* disco);
void imprimir_playlist(Playlist* playlist, FILE *output_file);
double rating_playlist(Playlist* playlist);
int eliminar_playlist(Playlist* playlist);
void unir_playlist(Playlist* playlist1, Playlist* playlist2);
void separar_playlist(Playlist* playlist1, Playlist* playlist2, int position);
int purgar_playlist(Playlist* playlist, int rating);
void ordenar_playlist(Playlist* playlist, FILE *output_file);