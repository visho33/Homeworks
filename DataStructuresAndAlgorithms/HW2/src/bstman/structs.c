#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

Nodo* init_nodo(int value){
    
    Nodo* nodo = calloc(1, sizeof(Nodo));

    *nodo = (Nodo){
        .value = value,
        .left = NULL,
        .right = NULL,
    };
    
    return nodo;
}

void insert_nodo(Nodo* actual, Nodo* nodo){

    if(nodo->value < actual->value){
        if(actual->left == NULL){
            actual -> left = nodo;
        }
        else{
            insert_nodo(actual->left, nodo);
        }
    }
    else{
        if(actual->right == NULL){
            actual->right = nodo;
        }
        else{
            insert_nodo(actual->right, nodo);
        }
    }

}

void get_path(Nodo* actual, int value, FILE* output_file){

    if(actual-> value == value){
        fprintf(output_file, "%d \n", value);
        return;
    }

    fprintf(output_file, "%d ", actual->value);
    if(value < actual->value){
        if(actual->left == NULL){
            fprintf(output_file, "X \n");
        }
        else{
            get_path(actual->left, value, output_file);
        }
    }
    else{
        if(actual->right == NULL){
            fprintf(output_file, "X \n");
        }
        else{
            get_path(actual->right, value, output_file);
        }
    }
    return;
}

void get_deep(Nodo* actual, int value, int deep, FILE* output_file){

    
    if(actual-> value == value){
        fprintf(output_file, "%d\n", deep);
        return;
    }

    if(value < actual->value){
        get_deep(actual->left, value, deep + 1, output_file);
    }
    else{
        get_deep(actual->right, value, deep + 1, output_file);
    }
    return;

}

void get_order(Nodo* actual, FILE* output_file){

    if(actual->left != NULL){
        get_order(actual->left, output_file);
    }

    fprintf(output_file, "%d ", actual->value);

    if(actual->right != NULL){
        get_order(actual->right, output_file);
    }

    return;
}

void limpiar(Nodo* actual){

    if(actual-> left != NULL){
        limpiar(actual->left);
    }
    if(actual->right != NULL){
        limpiar(actual->right);
    }
    free(actual);

    return;
}

Nodo* get_start(Nodo* actual, Nodo* subraiz){

    if(actual -> value == subraiz -> value){
        return actual;
    }

    if(actual -> value < subraiz -> value){
        if(actual -> right == NULL){
            return NULL;
        }
        else{
            return get_start(actual -> right, subraiz);
        }
    }
    else{
        if(actual -> left == NULL){
            return NULL;
        }
        else{
            return get_start(actual -> left, subraiz);
        }
    }

}

bool check_subtree(Nodo* actual, Nodo* subactual){

    actual = get_start(actual, subactual);
    
    if(actual == NULL){
        return false;
    }

    if(subactual -> left != NULL){
        if(actual -> left == NULL){
            return false;
        }
        if(actual -> left -> value != subactual -> left -> value){
            return false;
        }
        if(check_subtree(actual -> left, subactual -> left) == false){
            return false;
        }
    }

    if(subactual -> right != NULL){
        if(actual -> right == NULL){
            return false;
        }
        if(actual -> right -> value != subactual -> right -> value){
            return false;
        }
        if(check_subtree(actual -> right, subactual -> right) == false){
            return false;
        }
    }

    return true;
}