struct data
{
    int x, y;
};

struct tree
{
    struct data d;
    struct tree *left, *right;
};

typedef struct tree Tree;

struct list
{
    Tree *tree;
    struct list *next;
};

typedef struct list List;

char Folha(Tree *T)
{
    return T->left == NULL && T->right == NULL;
}

void enqueue(List **L, Tree *T)
{
    List *newNode = (List *)malloc(sizeof(List));
    newNode->tree = T;
    newNode->next = NULL;
    if (*L == NULL)
    {
        *L = newNode;
    }
    else
    {
        List *aux = *L;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

void dequeue(List **L, Tree **T)
{
    if (*L == NULL)
    {
        *T = NULL;
    }
    else
    {
        *T = (*L)->tree;
        *L = (*L)->next;
    }
}
