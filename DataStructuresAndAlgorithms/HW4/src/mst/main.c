#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

	long long x[n];
	long long y[n];

	for(int i = 0; i<n; i++){
		fscanf(input_file, "%lld %lld", &x[i], &y[i]);
	}

	int minobj = 100000000;
	int finresx1[n-1];
	int finresx2[n-1];
	int finresy1[n-1];
	int finresy2[n-1];
	long long finres = 0;

	int Q = 10;
	
	for(int q = 1; q<Q; q++){

		bool visitado[n];
		int resx1[n-1];
		int resx2[n-1];
		int resy1[n-1];
		int resy2[n-1];
		long long res = 0;
		int degree[n];

		for(int i = 0; i<n; i++){
			visitado[i] = false;
			degree[i] = 0;
		}

		Tree* priority_queue = NULL;

		int nodo_inical = (n-1)/q;
		visitado[nodo_inical] = true;
		for(int i = 0; i<n; i++){
			if(visitado[i] == false){
				priority_queue = merge(priority_queue, init_tree(abs(x[nodo_inical] - x[i]) + abs(y[nodo_inical] - y[i]), nodo_inical, i));
			}
		}

		for(int i = 0; i<n-1; i++){
			long long valor = priority_queue -> value;
			int nodo1 = priority_queue -> nodo1;
			int nodo2 = priority_queue -> nodo2;
			Tree* basura = priority_queue;
			priority_queue = merge(priority_queue->left, priority_queue->right);
			free(basura);
			if(visitado[nodo2] == true){
				i--;
				continue;
			}
			for(int i = 0; i<n; i++){
				if(visitado[i] == true && abs(x[i] - x[nodo2]) + abs(y[i] - y[nodo2]) == valor && degree[i] <= degree[nodo1]){
					nodo1 = i;
				}
			}
			degree[nodo1] = degree[nodo1] + 1;
			degree[nodo2] = degree[nodo2] + 1;
			resx1[i] = x[nodo1];
			resx2[i] = x[nodo2];
			resy1[i] = y[nodo1];
			resy2[i] = y[nodo2];
			res = res + valor;
			visitado[nodo2] = true;
			for(int j = 0; j<n; j++){
				if(visitado[j] == false){
					priority_queue = merge(priority_queue, init_tree(abs(x[nodo2] - x[j]) + abs(y[nodo2] - y[j]), nodo2, j));
				}
			}
		}
	

		while(priority_queue != NULL){
			Tree* basura = priority_queue;
			priority_queue = merge(priority_queue->left, priority_queue->right);
			free(basura);
		}

		int contardegree[10];
		for(int i = 0; i<10; i++){
			contardegree[i] = 0;
		}
		for(int i = 0; i<n; i++){
			contardegree[degree[i]] = contardegree[degree[i]] + 1;
		}

		int obj = 0;
		for(int i = 0; i<10; i++){
			//printf("%d: %d\n", i, contardegree[i]);
			obj = obj + i*contardegree[i];
			if(i >= 4){
				obj = obj + (i-3)*contardegree[i];
			}
		}

		if(obj < minobj){
			for(int i = 0; i<n-1; i++){
				finresx1[i] = resx1[i];
				finresx2[i] = resx2[i];
				finresy1[i] = resy1[i];
				finresy2[i] = resy2[i];
			}
			finres = res;
			minobj = obj;
		}

	}

	printf("obj: %d\n", minobj);

	fprintf(output_file, "%lld\n", finres);

	for(int i = 0; i<n-1; i++){
		fprintf(output_file, "%d %d %d %d\n", finresx1[i], finresy1[i], finresx2[i], finresy2[i]);
	}

  	// Cerrar archivo de input
  	fclose(input_file);

  	// Cerrar archivo de output
  	fclose(output_file);

  	return 0;

}