#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

Cancion* cancion_init(int id, int disco_id, int largo, int valoracion){

    Cancion* cancion = calloc(1, sizeof(Cancion));
    *cancion = (Cancion){
        .id = id,
        .disco_id = disco_id,
        .largo = largo,
        .valoracion = valoracion,
        .disponible = true,
        .flag = true,
    };

    return cancion;
}

Disco* disco_init(int id, int largo){

    Disco* disco = calloc(1, sizeof(Disco));
    *disco = (Disco){
        .id = id,
        .largo = largo,
        .canciones = calloc(largo, sizeof(Cancion*)),
    };

    return disco;
}

void eliminar_cancion(Cancion* cancion){
    cancion -> disponible = false;
    return;
}

void imprimir_disco(Disco* disco, FILE *output_file){

    int restantes = disco->largo;
    int max_rating = -1;
    int id_max_rating = -1;
    int min_rating = 1000000000;
    int id_min_rating = -1;
    int duracion_total = 0;

    for(int i = 0; i<disco -> largo; i++){
        if(disco->canciones[i]->disponible == false){
            restantes = restantes - 1;
            continue;
        }
        if(disco->canciones[i]->valoracion > max_rating){
            max_rating = disco->canciones[i]->valoracion;
            id_max_rating = i;
        }
        if(disco->canciones[i]->valoracion < min_rating){
            min_rating = disco->canciones[i]->valoracion;
            id_min_rating = i;
        }
        duracion_total = duracion_total + disco->canciones[i]->largo; 
    }

    fprintf(output_file, "ESTADO DISCO %i\n", disco -> id);
    fprintf(output_file, "\t%i\n", disco -> largo);
    fprintf(output_file, "\t%i %i\n", max_rating, id_max_rating);
    fprintf(output_file, "\t%i %i\n", min_rating, id_min_rating);
    fprintf(output_file, "\t%i\n", duracion_total);
    fprintf(output_file, "\tCANCIONES\n");
    for(int i = 0; i<disco -> largo; i++){
        if(disco->canciones[i]->disponible == true){
            fprintf(output_file, "\t\t%i\n", disco->canciones[i]->id);
        }
        else{
            fprintf(output_file, "\t\t-\n");
        }
    }
    fprintf(output_file, "FIN ESTADO\n");
    return;
}

void imprimir_cancion(Cancion* cancion, FILE *output_file){
    fprintf(output_file, "ESTADO CANCION %i\n", cancion->id);
    fprintf(output_file, "\t%i\n", cancion->largo);
    fprintf(output_file, "\t%i\n", cancion->valoracion);
    fprintf(output_file, "FIN ESTADO\n");
}

Nodo* init_nodo(Cancion* cancion){
    Nodo* nodo = calloc(1, sizeof(Nodo));
    *nodo = (Nodo){
        .siguiente = NULL,
        .cancion = cancion,
    };
    return nodo;
}

Playlist* init_playlist(int id){
    Playlist* playlist = calloc(1, sizeof(Playlist));
    *playlist = (Playlist){
        .id = id,
        .disponible = true,
        .inicio = NULL,
    };
    return playlist;
}

void agregar_cancion(Playlist* playlist, Cancion* cancion){
    
    if(playlist-> inicio == NULL){
        Nodo* new_nodo = init_nodo(cancion);
        playlist -> inicio = new_nodo;
        return;
    }

    Nodo* head = playlist -> inicio;
    while(head -> siguiente != NULL){
        if(head -> cancion == cancion){
            return;
        }
        head = head -> siguiente;
    }

    if(head -> cancion == cancion){
        return;
    }

    Nodo* new_nodo = init_nodo(cancion);
    head -> siguiente = new_nodo;

    return;
}

bool eliminar_cancion_playlist(Playlist* playlist, int disk_id, int song_id){

    if(playlist->inicio == NULL){
        return false;
    }

    if(playlist -> inicio -> cancion -> disco_id == disk_id && playlist -> inicio -> cancion -> id == song_id){
        Nodo* nodo_eliminado = playlist -> inicio;
        playlist -> inicio = playlist -> inicio -> siguiente;
        free(nodo_eliminado);
        return true;
    }

    Nodo* head = playlist -> inicio;

    while(head -> siguiente != NULL){
        if(head -> siguiente -> cancion -> disco_id == disk_id && head -> siguiente -> cancion -> id == song_id){
            Nodo* nodo_eliminado = head -> siguiente;
            head -> siguiente = head -> siguiente -> siguiente;
            free(nodo_eliminado);
            return true;
        }
        head = head -> siguiente;
    }

    return false;
}

int agregar_disco(Playlist* playlist, Disco* disco){

    int N_SONGS = 0;

    for(int i = 0; i<disco -> largo; i++){
        disco -> canciones[i] -> flag = true;
    }

    Nodo* head = playlist -> inicio;

    while(head != NULL){
        if(head -> cancion -> disco_id == disco -> id){
            disco -> canciones[head -> cancion -> id] -> flag = false;
        }
        head = head -> siguiente;
    }

    for(int i = 0; i<disco -> largo; i++){
        if(disco -> canciones[i] -> flag == true && disco -> canciones[i] -> disponible == true){
            agregar_cancion(playlist, disco -> canciones[i]);
            N_SONGS = N_SONGS + 1;
        }
    }

    return N_SONGS;
}

void imprimir_playlist(Playlist* playlist, FILE *output_file){

    fprintf(output_file, "ESTADO BATIPLAYLIST %i\n", playlist -> id);
    
    int N = 0;
    Nodo* head = playlist -> inicio;

    while(head != NULL){
        N = N + 1;
        head = head -> siguiente;
    }

    fprintf(output_file, "\t%i\n", N);
    fprintf(output_file, "\tCANCIONES\n");

    head = playlist -> inicio;

    while(head != NULL){
        fprintf(output_file, "\t\t%i %i\n", head -> cancion -> id, head -> cancion -> disco_id);
        head = head -> siguiente;
    }

    fprintf(output_file, "FIN ESTADO\n");

    return;
}

double rating_playlist(Playlist* playlist){

    double rating = 0;
    double N = 0;

    Nodo* head = playlist -> inicio;

    while(head != NULL){
        rating = rating + head -> cancion -> valoracion;
        N = N + 1;
        head = head -> siguiente;
    }

    return rating/N;
}

int eliminar_playlist(Playlist* playlist){

    int N = 0;

    Nodo* head = playlist -> inicio;

    while(head != NULL){
        Nodo* nodo_eliminado = head;
        head = head -> siguiente;
        free(nodo_eliminado);
        N = N + 1;
    }

    playlist -> disponible = false;

    return N;
}

void unir_playlist(Playlist* playlist1, Playlist* playlist2){
    
    if(playlist1 -> inicio == NULL){
        playlist1 -> inicio = playlist2 -> inicio;
        playlist2 -> disponible = false;
        return;
    }

    Nodo* head2 = playlist2 -> inicio;

    while(head2 != NULL){

        agregar_cancion(playlist1, head2 -> cancion);
        Nodo* eliminado = head2;
        head2 = head2 -> siguiente;
        free(eliminado);
    }

    playlist2 -> disponible = false;

    return;
}

void separar_playlist(Playlist* playlist1, Playlist* playlist2, int position){

    if(position == 0){
        playlist2 -> inicio = playlist1 -> inicio;
        playlist1 -> inicio = NULL;
        return;
    }

    Nodo* head = playlist1 -> inicio;

    for(int i = 0; i<position - 1; i++){
        head = head -> siguiente;
    }

    playlist2 -> inicio = head -> siguiente;
    head -> siguiente = NULL;

    return;
}

void ordenar_playlist(Playlist* playlist, FILE *output_file){

    Nodo* miniarg_before = playlist -> inicio;
    int mini = playlist -> inicio -> cancion -> largo;

    Nodo* head = playlist -> inicio;
    while(head -> siguiente != NULL){
        if(head -> siguiente -> cancion -> largo < mini){
            mini = head -> siguiente -> cancion -> largo;
            miniarg_before = head;
        }
        head = head -> siguiente;
    }

    if(mini < playlist -> inicio -> cancion -> largo){
        Nodo* miniarg = miniarg_before -> siguiente;
        miniarg_before -> siguiente = miniarg_before -> siguiente -> siguiente;
        miniarg -> siguiente = playlist -> inicio;
        playlist -> inicio = miniarg;
    }

    Nodo* last_sorted = playlist -> inicio;
    while(last_sorted -> siguiente != NULL){
        miniarg_before = last_sorted -> siguiente;
        mini = last_sorted -> siguiente -> cancion -> largo;
        head = last_sorted;
        while(head -> siguiente != NULL){
            if(head -> siguiente -> cancion -> largo < mini){
                mini = head -> siguiente -> cancion -> largo;
                miniarg_before = head;
            }
            head = head -> siguiente;
        }

        if(mini < last_sorted -> siguiente -> cancion -> largo){
            Nodo* miniarg = miniarg_before -> siguiente;
            miniarg_before -> siguiente = miniarg_before -> siguiente -> siguiente;
            miniarg -> siguiente = last_sorted -> siguiente;
            last_sorted -> siguiente = miniarg;
        }

        last_sorted = last_sorted -> siguiente;

    }

    fprintf(output_file, "SORTED BATIPLAYLIST %i\n", playlist -> id);
    
    head = playlist -> inicio;
    
    while(head != NULL){
        fprintf(output_file, "\tCANCION %i %i\n", head -> cancion -> id, head -> cancion -> disco_id);
        head = head -> siguiente;
    }
    
    fprintf(output_file, "END SORTED\n");

    return;
}

int purgar_playlist(Playlist* playlist, int rating){

    int N = 0;

    while(playlist -> inicio != NULL && playlist -> inicio -> cancion -> valoracion < rating){
        Nodo* nodo_eliminado = playlist -> inicio;
        playlist -> inicio = playlist -> inicio -> siguiente;
        free(nodo_eliminado);
        N = N + 1;
    }

    Nodo* head = playlist -> inicio;
    while(head!= NULL){
        while(head -> siguiente != NULL && head -> siguiente -> cancion -> valoracion < rating){
            Nodo* nodo_eliminado = head -> siguiente;
            head -> siguiente = head -> siguiente -> siguiente;
            free(nodo_eliminado);
            N = N + 1;
        }
        if(head == NULL){
            break;
        }
        head = head -> siguiente;
    }

    return N;
}