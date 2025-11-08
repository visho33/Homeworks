#!/bin/bash

# Nombre del trabajo
#SBATCH --job-name=IMT2112
# Archivo de salida
#SBATCH --output=output_%j.txt
# Cola de trabajo
#SBATCH --partition=full
# Solicitud de cpus
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8

echo "Comenzamos la generación de la matriz"

which python
time python tarea2_generate_matrix.py

echo "Terminamos la generación de la matriz"

