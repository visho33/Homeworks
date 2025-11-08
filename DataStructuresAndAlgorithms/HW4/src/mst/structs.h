typedef struct tree{

    long long value;
    int nodo1;
    int nodo2;
    struct tree* left;
    struct tree* right;

} Tree;

Tree* init_tree(long long value, int nodo1, int nodo2);
Tree* merge(Tree* t1, Tree* t2);