#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char** argv){
	
	clock_t start = clock();

  	FILE* input_file = fopen(argv[1], "r");
  	FILE* output_file = fopen(argv[2], "w");
	setvbuf(output_file, NULL, _IOFBF, 0);

	int n;
	fscanf(input_file, "%d", &n);

	int logn = 1;
	int aux = 1;

	while(aux*2 < n){
		logn++;
		aux *= 2;
	}

	int P = 2;
	int p[logn];
	p[0] = P;
	for(int i = 1; i<logn; i++){
		p[i] = p[i-1]*p[i-1];
	}

	int (*hash)[logn];
	hash = malloc((n+1)*sizeof(*hash));
	char* input = malloc((2*n+1)*sizeof(char));
	fgets(input, 2*n+1, input_file);
	for(int i = 1; i<=n; i++){
		hash[i][0] = input[2*i-1] - '0';
	}

	for(int i = n; i>=1; i--){
		if(2*i > n){
			for(int j = logn-1; j>=1; j--){
				hash[i][j] = -1;
			}
		}
		else{
			for(int j = logn-1; j>=1; j--){
				if(hash[2*i][j-1] == -1){
					hash[i][j] = -1;
				}
				else{
					hash[i][j] = hash[2*i][j-1]*p[j] + hash[2*i+1][j-1]*p[0] + hash[i][0];
				}
			}
		}
	}

	int q;
	fscanf(input_file, "%d", &q);
	int* countx = malloc((n+1)*sizeof(int));
	int* hashx = malloc((n+1)*sizeof(int));

	while(q--){

		int nx;
		fscanf(input_file, "%d", &nx);
		fgets(input, 2*nx+1, input_file);

		int lognx = 0;
		aux = 1;
		while(aux*2 < nx){
			lognx++;
			aux = aux*2;
		}

		for(int i = nx/2+1; i<=nx; i++){
			hashx[i] = input[2*i-1] - '0';
			countx[i] = 0;
		}

		for(int i = nx/2; i>=1; i--){
			countx[i] = countx[2*i] + 1;
			hashx[i] = hashx[2*i]*p[countx[i]] + hashx[2*i+1]*p[0] + input[2*i-1] - '0';
		}

		bool encontrado = false;
		int cota = (2*n)/nx;

		for(int i = 1; i<cota; i++){
			if(hash[i][lognx] == hashx[1]){
				encontrado = true;
				fprintf(output_file, "%d ", i);
			}
		}

		if(encontrado == false){
			fprintf(output_file, "-1\n");
		}
		else{
			fprintf(output_file, "\n");
		}
	}

	free(hash);
	free(input);
	free(countx);
	free(hashx);

  	// Cerrar archivo de input
  	fclose(input_file);

  	// Cerrar archivo de output
  	fclose(output_file);

	clock_t end = clock();
  	double elapsed = ((double)end - (double)start) / CLOCKS_PER_SEC;
  	printf("Tiempo en que tomó procesar: %lf segundos\n", elapsed);

  	return 0;

}