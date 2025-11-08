#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../imagelib/imagelib.h"
#include "structs.h"

Nodo* init_nodo(Image* imagen, Nodo* padre, int lh, int rh, int lv, int rv){
    
    Nodo* nodo = calloc(1, sizeof(Nodo));

    if(lh == rh && lv == rv){
        *nodo = (Nodo){
            .siguiente = NULL,
            .padre = padre,
            .lh = lh,
            .rh = rh,
            .lv = lv,
            .rv = rv,
            .mu_l = imagen->pixels[lh][lv].L,
            .mu_a = imagen->pixels[lh][lv].a,
            .mu_b = imagen->pixels[lh][lv].b,
            .mu_sq_l = imagen->pixels[lh][lv].L*imagen->pixels[lh][lv].L,
            .mu_sq_a = imagen->pixels[lh][lv].a*imagen->pixels[lh][lv].a,
            .mu_sq_b = imagen->pixels[lh][lv].b*imagen->pixels[lh][lv].b,
            .sigma_l = 0,
            .sigma_a = 0,
            .sigma_b = 0,
        };
    }
    else{
        Nodo* nodo1 = init_nodo(imagen, nodo, lh, (lh+rh)/2, lv, (lv+rv)/2);
        Nodo* nodo2 = init_nodo(imagen, nodo, (lh+rh)/2 + 1, rh, lv, (lv+rv)/2);
        Nodo* nodo3 = init_nodo(imagen, nodo, lh, (lh+rh)/2, (lv+rv)/2 + 1, rv);
        Nodo* nodo4 = init_nodo(imagen, nodo, (lh+rh)/2 + 1, rh, (lv+rv)/2 + 1, rv);
        double mu_l = (nodo1->mu_l + nodo2->mu_l + nodo3->mu_l + nodo4->mu_l)/4;
        double mu_a = (nodo1->mu_a + nodo2->mu_a + nodo3->mu_a + nodo4->mu_a)/4;
        double mu_b = (nodo1->mu_b + nodo2->mu_b + nodo3->mu_b + nodo4->mu_b)/4;
        double mu_sq_l = nodo1->mu_sq_l + nodo2->mu_sq_l + nodo3->mu_sq_l + nodo4->mu_sq_l;
        double mu_sq_a = nodo1->mu_sq_a + nodo2->mu_sq_a + nodo3->mu_sq_a + nodo4->mu_sq_a;
        double mu_sq_b = nodo1->mu_sq_b + nodo2->mu_sq_b + nodo3->mu_sq_b + nodo4->mu_sq_b;
        double n = (rh - lh + 1)*(rv - lv + 1);
        double sigma_l = sqrt(mu_sq_l/n - mu_l*mu_l);
        double sigma_a = sqrt(mu_sq_a/n - mu_a*mu_a);
        double sigma_b = sqrt(mu_sq_b/n - mu_b*mu_b);
        double tres = 3;
        double sigma = (sigma_l + sigma_a + sigma_b)/tres;
        *nodo = (Nodo){
            .siguiente[0] = nodo1,
            .siguiente[1] = nodo2,
            .siguiente[2] = nodo3,
            .siguiente[3] = nodo4,
            .padre = padre,
            .lh = lh,
            .rh = rh,
            .lv = lv,
            .rv = rv,
            .mu_l = mu_l,
            .mu_a = mu_a,
            .mu_b = mu_b,
            .mu_sq_l = mu_sq_l,
            .mu_sq_a = mu_sq_a,
            .mu_sq_b = mu_sq_b,
            .sigma_l = sigma_l,
            .sigma_a = sigma_a,
            .sigma_b = sigma_b,
            .sigma = sigma
        };
    }
    
    return nodo;
}

int contar_coloreado(Nodo* nodo, Image* img, double alpha){
    int count = 0;
    if(nodo->sigma <= alpha){
		count = count + 1;
        return count;
	}
    count = count + contar_coloreado(nodo->siguiente[0], img, alpha);
    count = count + contar_coloreado(nodo->siguiente[1], img, alpha);
    count = count + contar_coloreado(nodo->siguiente[2], img, alpha);
    count = count + contar_coloreado(nodo->siguiente[3], img, alpha);
    return count;
}

void colorear(Nodo* nodo, Image* img, double alpha){
    if(nodo->sigma <= alpha){
		img_square_paint(img, nodo->lh, nodo->lv, (nodo->rh - nodo->lh  + 1), (Color) {.L = nodo->mu_l, .a = nodo->mu_a, .b = nodo->mu_b});
        return;
	}
    colorear(nodo->siguiente[0], img, alpha);
    colorear(nodo->siguiente[1], img, alpha);
    colorear(nodo->siguiente[2], img, alpha);
    colorear(nodo->siguiente[3], img, alpha);
    return;
}

void limpiar(Nodo* nodo){
    if(nodo->siguiente == NULL){
        free(nodo);
        return;
    }
    limpiar(nodo->siguiente[0]);
    limpiar(nodo->siguiente[1]);
    limpiar(nodo->siguiente[2]);
    limpiar(nodo->siguiente[3]);
    free(nodo);
    return;
}