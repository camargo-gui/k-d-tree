struct data {
    int x, y;
};

struct tree{
    struct data d;
    struct tree *left, *right;
};

typedef struct tree Tree;

struct list{
    Tree *tree;
    struct list *next;
};

typedef struct list List;

char Folha(Tree *T){
   return T -> left == NULL && T -> right == NULL;
}