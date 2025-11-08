#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/* Retorna true si ambos string so iguales */
bool string_equals(char *string1, char *string2){
  	return !strcmp(string1, string2);
}

/* Función encargada de chequear los argumentos ingresados */
bool check_arguments(int argc, char **argv){
  	if(argc != 3){
    	printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    	printf("Donde:\n");
    	printf("\tINPUT es la ruta del archivo de input\n");
    	printf("\tOUTPUT es la ruta del archivo de output\n");
    	return false;
  	}
  	return true;
}

int main(int argc, char **argv){

  	/////////////////////////
  	//        Input        //
  	/////////////////////////
  	/* Si los parámetros del programa son inválidos */
  	if(!check_arguments(argc, argv)){
    /* Salimos del programa indicando que no terminó correctamente */
    	return 1;
  	}

  	/* Abrimos el archivo de input */
  	FILE *input_file = fopen(argv[1], "r");

  	/* Abrimos el archivo de output */
  	FILE *output_file = fopen(argv[2], "w");

  	/* String que usaremos para guardar la instrucción actual*/
  	char command[32];

  	// Lectura del número de batiplaylists
  	int N_BATIPLAYLISTS;
  	fscanf(input_file, "%d", &N_BATIPLAYLISTS);


  	// Lectura del número de discos
  	int N_DISCS;
  	fscanf(input_file, "%d", &N_DISCS);

  	/* Leemos la primera instrucción */
  	fscanf(input_file, "%s", command);

	Playlist* playlists[N_BATIPLAYLISTS];
	Disco* discos[N_DISCS];

	for(int i = 0; i<N_BATIPLAYLISTS; i++){
		playlists[i] = NULL;
	}
	for(int i = 0; i<N_DISCS; i++){
		discos[i] = NULL;
	}

	int act_disc = 0;

  	/* Mientras la instrucción sea distinta a FIN */
  	while(!string_equals(command, "FIN")){

    	/////////////////////////
    	//       Parte A       //
    	/////////////////////////

    	if(string_equals(command, "CREAR-DISCO")){
      		/* Obtenemos la información del disco */
      		int capacity, length, rating;
      		fscanf(input_file, "%d", &capacity);

      		/* COMPLETAR */
			discos[act_disc] = disco_init(act_disc, capacity);
			for(int i = 0; i<capacity; i++){
				fscanf(input_file, "%d %d", &length, &rating);
				discos[act_disc]->canciones[i] = cancion_init(i, act_disc, length, rating);
				fprintf(output_file, "CANCION AGREGADA %i %i\n", i, act_disc);
			}
			act_disc = act_disc + 1;
    	}
    	else if(string_equals(command, "ELIMINAR-CANCION")){
      		/* Obtenemos la información de la canción */
      		int disc_id, song_id;
      		fscanf(input_file, "%d %d", &disc_id, &song_id);
			/* COMPLETAR */
      		eliminar_cancion(discos[disc_id]->canciones[song_id]);
			fprintf(output_file, "ELIMINADO %i %i\n", disc_id, song_id);
    	}
    	else if(string_equals(command, "IMPRIMIR-DISCO")){
      		/* Obtenemos la información correspondiente */
      		int disc_id;
      		fscanf(input_file, "%d", &disc_id);

      		/* COMPLETAR */
			imprimir_disco(discos[disc_id], output_file);
    	}
    	else if(string_equals(command, "IMPRIMIR-CANCION")){
      		/* Obtenemos la información correspondiente */
      		int disc_id, song_id;
      		fscanf(input_file, "%d %d", &disc_id, &song_id);

      		/* COMPLETAR */
			imprimir_cancion(discos[disc_id]->canciones[song_id], output_file);
    	}

    	/////////////////////////
    	//       Parte B       //
    	/////////////////////////

    	else if(string_equals(command, "CREAR-BATIPLAYLIST")){
      		/* Obtenemos la información correspondiente */
      		int playlist_id;
      		fscanf(input_file, "%d", &playlist_id);

      		/* COMPLETAR */
			playlists[playlist_id] = init_playlist(playlist_id);
			fprintf(output_file, "BATIPLAYLIST CREATED %i\n", playlist_id);
    	}
		else if(string_equals(command, "AGREGAR-CANCION-BATIPLAYLIST")){
      		int playlist_id, disc_id, song_id;
      		fscanf(input_file, "%d %d %d", &playlist_id, &disc_id, &song_id);

      		/* COMPLETAR */
			if(disc_id >= act_disc || song_id >= discos[disc_id] -> largo || discos[disc_id] -> canciones[song_id] -> disponible == false){
				fprintf(output_file, "SONG NOT FOUND\n");
			}
			else{
				agregar_cancion(playlists[playlist_id], discos[disc_id]->canciones[song_id]);
				fprintf(output_file, "NEW SONG ADDED %i %i %i\n", song_id, disc_id, playlist_id);
			}
    	}
		else if(string_equals(command, "ELIMINAR-CANCION-BATIPLAYLIST")){
      		int playlist_id, disk_id, song_id;
      		fscanf(input_file, "%d %d %d", &playlist_id, &disk_id, &song_id);

		    /* COMPLETAR */
			if(eliminar_cancion_playlist(playlists[playlist_id], disk_id, song_id) == true){
				fprintf(output_file, "ELIMINADO %i %i %i\n", song_id, disk_id, playlist_id);
			}
			else{
				fprintf(output_file, "SONG NOT FOUND ON PLAYLIST\n");
			}
    	}
    	else if(string_equals(command, "AGREGAR-DISCO-BATIPLAYLIST")){
      		int playlist_id, disk_id;
      		fscanf(input_file, "%d %d", &playlist_id, &disk_id);

      		/* COMPLETAR */
			int N_SONGS = agregar_disco(playlists[playlist_id], discos[disk_id]);
			fprintf(output_file, "AGREGADO %i %i %i\n", N_SONGS, disk_id, playlist_id);
    	}
		else if(string_equals(command, "PLAY-BATIPLAYLIST")){
      		int playlist_id;
      		fscanf(input_file, "%d", &playlist_id);

      		/* COMPLETAR */
			imprimir_playlist(playlists[playlist_id], output_file);
    	}
		else if(string_equals(command, "RATE-BATIPLAYLIST")){
      		int playlist_id;
      		fscanf(input_file, "%d", &playlist_id);

      		/* COMPLETAR */
			float promedio = rating_playlist(playlists[playlist_id]);
			fprintf(output_file, "BATIPLAYLIST %i: %.2f\n", playlist_id, promedio);
    	}

    	/////////////////////////
    	//       Parte C       //
    	/////////////////////////

    	else if(string_equals(command, "ELIMINAR-BATIPLAYLIST")){
      		int playlist_id;
      		fscanf(input_file, "%d", &playlist_id);

      		/* COMPLETAR */
			int N = eliminar_playlist(playlists[playlist_id]);
			fprintf(output_file, "BATIPLAYLIST DELETED %i %i\n", playlist_id, N);
    	}
		else if(string_equals(command, "UNIR-BATIPLAYLIST")){
      		int playlist_id1, playlist_id2;
      		fscanf(input_file, "%d %d", &playlist_id1, &playlist_id2);

      		/* COMPLETAR */
			unir_playlist(playlists[playlist_id1], playlists[playlist_id2]);
			fprintf(output_file, "JOINED %i AND %i\n", playlist_id1, playlist_id2);
    	}
		else if(string_equals(command, "SPLIT-BATIPLAYLIST")){
      		int playlist_id, new_playlist_id, position;
      		fscanf(input_file, "%d %d %d", &playlist_id, &new_playlist_id, &position);

      		/* COMPLETAR */
			playlists[new_playlist_id] = init_playlist(new_playlist_id);
			separar_playlist(playlists[playlist_id], playlists[new_playlist_id], position);
    	}
		else if(string_equals(command, "ORDENAR-BATIPLAYLIST")){
      		int playlist_id;
      		fscanf(input_file, "%d", &playlist_id);

      		/* COMPLETAR */
			ordenar_playlist(playlists[playlist_id], output_file);
    	}
		else if(string_equals(command, "PURGAR-BATIPLAYLIST")){
      		int playlist_id, rating;
      		fscanf(input_file, "%d %d", &playlist_id, &rating);

      		/* COMPLETAR */
			int N = purgar_playlist(playlists[playlist_id], rating);
			fprintf(output_file, "BATIPLAYLIST PURGED %i %i\n", playlist_id, N);
    	}

    	/* Leemos la siguiente instrucción */
    	fscanf(input_file, "%s", command);
  	}

  	///////////////////////////////////
  	//     Liberamos memoria         //
  	///////////////////////////////////

	for(int i = 0; i<N_DISCS; i++){
		if(discos[i] == NULL){
			continue;
		}
		for(int j = 0; j<discos[i] -> largo; j++){
			free(discos[i]->canciones[j]);
		}
		free(discos[i] -> canciones);
		free(discos[i]);
	}

	for(int i = 0; i<N_BATIPLAYLISTS; i++){
		
		if(playlists[i] == NULL){
			continue;
		}

		if(playlists[i] -> disponible == false){
			free(playlists[i]);
			continue;
		}

		Nodo* head = playlists[i] -> inicio;
		while(head != NULL){
			Nodo* nodo_eliminado = head;
			head = head -> siguiente;
			free(nodo_eliminado);
		}

		free(playlists[i]);
	}

	/////////////////////////////////////
  	//        Cerramos archivos        //
  	////////////////////////////////////

	fclose(input_file);
  	fclose(output_file);

  	return 0;
}