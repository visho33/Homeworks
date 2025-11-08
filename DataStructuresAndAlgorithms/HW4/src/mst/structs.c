#include <stdlib.h>
#include "structs.h"

Tree* init_tree(long long value, int nodo1, int nodo2){

    Tree* tree = calloc(1, sizeof(Tree));

    *tree = (Tree){
            .value = value,
            .nodo1 = nodo1,
            .nodo2 = nodo2,
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