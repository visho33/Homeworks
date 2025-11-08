#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>
#include<mpi.h>
using namespace std;

int main(){

	MPI_Init(NULL,NULL);

	int world_size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Soy el procesador número %d con nombre %s\n", rank, processor_name);

    ifstream file;

    file.open("matrix.txt");
    int N, M;
    file>>N>>M;

    int row[world_size];
    int szrow[world_size];
    bool raiz = (rank == 0);

    int ITERS;
    if(raiz){
        cerr<<"Ingrese el número de iteraciones: ";
        cin>>ITERS;
        for(int p = 1; p<world_size; p++){
            MPI_Send(&ITERS, 1, MPI_INT, p, rank, MPI_COMM_WORLD);
        }
    }
    else{
        MPI_Recv(&ITERS, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for(int p = 0; p<world_size; p++){
        row[p] = (N/world_size)*p + max(0, N%world_size - (world_size - p));
        szrow[p] = (N/world_size) + int((world_size - p) <= N%world_size);
    }

    double *A = new double [szrow[rank]*M];
    double tmp;

    for(int i = 0; i<row[rank]*M; i++){
        file>>tmp;
    }
    for(int i = 0; i<szrow[rank]*M; i++){
        file>>A[i];
    }
    file.close();

    /*if(raiz){
        ofstream fileaux("vector.txt", std::ios::trunc);
        fileaux.close();
    }*/

    double b[szrow[world_size - 1]];
    for(int i = 0; i<szrow[rank]; i++){
        b[i] = double(1);
    }

    int iter = 0;
    while(true){

        double norm = 0;
        for(int i = 0; i<szrow[rank]; i++){
            norm = norm + b[i]*b[i];
        }

        if(raiz){
            double rnorm;
            double gnorm = norm;
            for(int p = 1; p<world_size; p++){
                MPI_Recv(&rnorm, 1, MPI_DOUBLE, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                gnorm += rnorm;
            }
            gnorm = sqrt(gnorm);
            for(int p = 1; p<world_size; p++){
                MPI_Send(&gnorm, 1, MPI_DOUBLE, p, rank, MPI_COMM_WORLD);
            }
            for(int i = 0; i<szrow[rank]; i++){
                b[i] = b[i]/gnorm;
            }
        }
        else{
            double gnorm;
            MPI_Send(&norm, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
            MPI_Recv(&gnorm, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int i = 0; i<szrow[rank]; i++){
                b[i] = b[i]/gnorm;
            }
        }

        if(iter == ITERS) break;

        for(int p = 0; p<world_size; p++){
            if(p == rank) continue;
            MPI_Send(&b, szrow[rank], MPI_DOUBLE, p, rank, MPI_COMM_WORLD);
        }

        double* newb = (double*) calloc(szrow[rank], sizeof(double));

        for(int i = 0; i<szrow[rank]; i++){
            for(int j = 0; j<szrow[rank]; j++){
                newb[i] += b[j]*A[i*M + row[rank] + j];
            }
        }

        for(int p = 0; p<world_size; p++){
            if(p == rank) continue;
            MPI_Recv(&b, szrow[p], MPI_DOUBLE, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int i = 0; i<szrow[rank]; i++){
                for(int j = 0; j<szrow[p]; j++){
                    newb[i] += b[j]*A[i*M + row[p] + j];
                }
            }
        }

        for(int i = 0; i<szrow[rank]; i++){
            b[i] = newb[i];
        }
        iter++;
    }

    /* Descomentar esta parte si queremos escribir el vector resultante en el archivo vector.txt

    ofstream fileout("vector.txt", std::ios::app);;

    int nada = -1;

    if(rank != 0){
        MPI_Recv(&nada, 1, MPI_INT, rank-1, rank-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    fileout<<fixed<<setprecision(3);
    for(int i = 0; i<szrow[rank]; i++){
        fileout<<b[i]<<" ";
    }

    if(rank != world_size - 1){
        MPI_Send(&nada, 1, MPI_INT, rank+1, rank, MPI_COMM_WORLD);
    }

    fileout.close();
    */
    for(int p = 0; p<world_size; p++){
        if(p == rank) continue;
        MPI_Send(&b, szrow[rank], MPI_DOUBLE, p, rank, MPI_COMM_WORLD);
    }

    double* newb = (double*) calloc(szrow[rank], sizeof(double));
    double oldb[szrow[rank]];
    for(int i = 0; i<szrow[rank]; i++){
        oldb[i] = b[i];
    }

    for(int i = 0; i<szrow[rank]; i++){
        for(int j = 0; j<szrow[rank]; j++){
            newb[i] += b[j]*A[i*M + row[rank] + j];
        }
    }

    for(int p = 0; p<world_size; p++){
        if(p == rank) continue;
        MPI_Recv(&b, szrow[p], MPI_DOUBLE, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = 0; i<szrow[rank]; i++){
            for(int j = 0; j<szrow[p]; j++){
                newb[i] += b[j]*A[i*M + row[p] + j];
            }
        }
    }
    
    double vpropio = 0;

    for(int i = 0; i<szrow[rank]; i++){
        vpropio += newb[i]*oldb[i];
    }

    if(raiz){
        double rpropio;
        double gpropio = vpropio;
        for(int p = 1; p<world_size; p++){
            MPI_Recv(&rpropio, 1, MPI_DOUBLE, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            gpropio += rpropio;
        }
        cerr<<"El valor propio es "<<gpropio<<endl;
        cerr<<"Por lo que el error es de "<<abs(double(10) - gpropio)<<endl;
    }
    else{
        MPI_Send(&vpropio, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    
    return 0;
}