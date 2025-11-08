#!/bin/bash

read -p "Ingrese el numero de procesos: " NUM_PROCESSES

# Nombre del trabajo
#SBATCH --job-name=IMT2112
# Archivo de salida
#SBATCH --output=output_%j.txt
# Cola de trabajo
#SBATCH --partition=full
# Solicitud de cpus
#SBATCH --ntasks=NUM_PROCESSES
#SBATCH --cpus-per-task=1

echo "Comenzamos la ejecución"

mpic++ tarea2.cpp
time mpirun -np $NUM_PROCESSES a.out

echo "Terminamos la ejecución"

