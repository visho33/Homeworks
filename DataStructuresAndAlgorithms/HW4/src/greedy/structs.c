#include <stdlib.h>
#include "structs.h"

Tree* init_tree(long long value, int nodo){

    Tree* tree = calloc(1, sizeof(Tree));

    *tree = (Tree){
            .value = value,
            .nodo = nodo,
            .left = NULL,
            .right = NULL,
        };
    
    return tree;
}

Tree* merge(Tree* t1, Tree* t2){
    
    if(t1 == NULL){
        return t2;
    }
    if(t2 == NULL){
        return t1;
    }

    if(t2 -> value < t1 -> value){
        Tree* aux = t1;
        t1 = t2;
        t2 = aux;
    }

    if(rand() & 1){
        Tree* aux = t1->left;
        t1->left = t1->right;
        t1->right = aux;
    }
    
    t1->left = merge(t1->left, t2);

    return t1;
}

Arista* init_arista(int nodo, long long largo){
    Arista* arista = calloc(1, sizeof(Arista));
    *arista = (Arista){
        .siguiente = NULL,
        .nodo = nodo,
        .largo = largo,
    };
    return arista;
}

Lista* init_lista(){
    Lista* lista = calloc(1, sizeof(Lista));
    *lista = (Lista){
        .inicio = NULL,
        .fin = NULL,
    };
    return lista;
}

void agregar_arista(Lista* lista, int nodo, long long largo){
    
    if(lista-> inicio == NULL){
        Arista* new_arista = init_arista(nodo, largo);
        lista -> inicio = new_arista;
        lista -> fin = new_arista; 
        return;
    }

    Arista* new_arista = init_arista(nodo, largo);

    lista -> fin -> siguiente = new_arista;
    lista -> fin = new_arista;

    return;
}
