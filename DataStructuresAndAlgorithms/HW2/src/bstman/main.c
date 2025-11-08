#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structs.h"


/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2){
  	return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv){
  	
	if(argc != 3){
    	printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    	printf("Donde:\n");
    	printf("\tINPUT es la ruta del archivo de input\n");
    	printf("\tOUTPUT es la ruta del archivo de output\n");
    	exit(1);
  	}

  	return true;
}


int main(int argc, char** argv){
  
  	check_arguments(argc, argv);

  	FILE* input_file = fopen(argv[1], "r");
  	FILE* output_file = fopen(argv[2], "w");

  	int node_count;
  	int query_count;

  	fscanf(input_file, "%d", &node_count);

  	/* leemos Cada nodo */
  	int k;
	fscanf(input_file, "%d", &k);
    //printf("%d ", k);
	Nodo* raiz = init_nodo(k);

  	for(int i = 1; i<node_count; i++){
    	fscanf(input_file, "%d", &k);
    	//printf("%d ", k);
		Nodo* nuevo_nodo = init_nodo(k);
		insert_nodo(raiz, nuevo_nodo);
  	}
  	//printf("\n");

  	fscanf(input_file, "%d", &query_count);
  	/* leemos las consultas */
  	char command[32];
  	int value;
  	for(int i = 0; i<query_count; i++){
    	fscanf(input_file, "%s %d", command, &value);
    	//printf("%s %d\n", command, value);
    	/* completar la revision de comando y ejecucion de los mismos */
		if(string_equals(command, "PATH") == true){
			get_path(raiz, value, output_file);
		}
		else if(string_equals(command, "DEEP") == true){
			get_deep(raiz, value, 0, output_file);
		}
		else if(string_equals(command, "ORDER") == true){
			get_order(raiz, output_file);
			fprintf(output_file, "\n");
		}
		else if(string_equals(command, "SUBTREE") == true){
			
			fscanf(input_file, "%d", &k);
			Nodo* subraiz = init_nodo(k);

  			for(int i = 1; i<value; i++){
    			fscanf(input_file, "%d", &k);
				Nodo* nuevo_nodo = init_nodo(k);
				insert_nodo(subraiz, nuevo_nodo);
  			}

			if(check_subtree(raiz, subraiz) == true){
				fprintf(output_file, "1\n");
			}
			else{
				fprintf(output_file, "0\n");
			}
			limpiar(subraiz);
		}
  	}

	limpiar(raiz);

  	fclose(input_file);
  	fclose(output_file);
  	
	return 0;
}
