#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int main(int argc, char** argv){
  
  	if(argc != 3){
    	printf("Modo de uso: %s input output\nDonde:\n", argv[0]);
    	printf("\t\"input\" es la ruta al archivo de input\n");
    	printf("\t\"output\" es la ruta al archivo de output\n");
    	return 1;
  	}

  	// Abrimos el archivo de input
  	FILE* input_file = fopen(argv[1], "r");

  	// Abrimos el archivo de output
  	FILE* output_file = fopen(argv[2], "w");

  	// Si alguno de los dos archivos no se pudo abrir
  	if(!input_file){
    	printf("El archivo %s no existe o no se puede leer\n", argv[1]);
    	return 2;
  	}
  	if(!output_file){
    	printf("El archivo %s no se pudo crear o no se puede escribir\n", argv[2]);
    	printf("Recuerda que \"fopen\" no puede crear carpetas\n");
    	fclose(input_file);
    	return 3;
  	}

  	// [Aqui va tu tarea]

	int n;
	fscanf(input_file, "%d", &n);

	Lista* edges[n];

	for(int i = 0; i<n; i++){
		edges[i] = init_lista();
	}

	int inicio, fin;
	fscanf(input_file, "%d %d", &inicio, &fin);

	int m;
	fscanf(input_file, "%d", &m);

	for(int i = 0; i<m; i++){
		int a, b;
		long long w;
		fscanf(input_file, "%d %d %lld", &a, &b, &w);
		agregar_arista(edges[a], b, w);
		agregar_arista(edges[b], a, w);
	}

	long long d[n];
	for(int i = 0; i<n; i++){
		d[i] = 100000000000000000;
	}
	d[inicio] = 0;

	Tree* priority_queue = init_tree(0, inicio);
	while(priority_queue != NULL){
		
		long long valor = priority_queue -> value;
		int nodo = priority_queue -> nodo;
		Tree* basura = priority_queue;
		priority_queue = merge(priority_queue->left, priority_queue->right);
		free(basura);

		Arista* head = edges[nodo] -> inicio;
		while(head != NULL){
			if(valor + head -> largo < d[head->nodo]){
				d[head->nodo] = valor + head -> largo;
				priority_queue = merge(priority_queue, init_tree(valor + head -> largo, head -> nodo));
			} 
			head = head -> siguiente;
		}
	}

	fprintf(output_file, "%lld\n", d[fin]);

	for(int i = 0; i<n; i++){

		Arista* head = edges[i] -> inicio;
		while(head != NULL){
			Arista* arista_eliminada = head;
			head = head -> siguiente;
			free(arista_eliminada);
		}

		free(edges[i]);
	}

  	// Cerrar archivo de input
  	fclose(input_file);

  	// Cerrar archivo de output
  	fclose(output_file);

  	return 0;
}
