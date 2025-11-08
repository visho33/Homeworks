#include <stdbool.h>
#include "../imagelib/imagelib.h"

typedef struct nodo{

    struct nodo* siguiente[4];
    struct nodo* padre;
    int lh;
    int rh;
    int lv;
    int rv;
    double mu_l;
    double mu_a;
    double mu_b;
    double mu_sq_l;
    double mu_sq_a;
    double mu_sq_b;
    double sigma_l;
    double sigma_a;
    double sigma_b;
    double sigma;
    bool listo;

} Nodo;

Nodo* init_nodo(Image* imagen, Nodo* padre, int lh, int rh, int lv, int rv);
int contar_coloreado(Nodo* nodo, Image* img, double alpha);
void colorear(Nodo* nodo, Image* img, double alpha);
void limpiar(Nodo* nodo);