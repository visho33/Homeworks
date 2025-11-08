typedef struct tree{

    long long value;
    int nodo;
    struct tree* left;
    struct tree* right;

} Tree;

Tree* init_tree(long long value, int nodo);
Tree* merge(Tree* t1, Tree* t2);

typedef struct arista{

    int nodo;
    long long largo;
    struct arista* siguiente;

} Arista;

typedef struct lista{

    Arista* inicio;
    Arista* fin;

} Lista;

Arista* init_arista(int nodo, long long largo);
Lista* init_lista();
void agregar_arista(Lista* lista, int nodo, long long largo);