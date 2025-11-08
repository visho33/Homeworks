#include <stdbool.h>

typedef struct nodo{

    int value;
    struct nodo* left;
    struct nodo* right;

} Nodo;

Nodo* init_nodo(int value);
void insert_nodo(Nodo* actual, Nodo* nodo);
void get_path(Nodo* actual, int value, FILE* output_file);
void get_deep(Nodo* actual, int value, int deep, FILE* output_file);
void get_order(Nodo* actual, FILE* output_file);
void limpiar(Nodo* actual);
bool check_subtree(Nodo* actual, Nodo* subactual);
Nodo* get_start(Nodo* actual, Nodo* subraiz);