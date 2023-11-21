#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio2.h>
#include "tad.h"
#include <time.h>

int randomGenerate()
{
    return rand() % 30 + 10;
}

Tree *createTree()
{
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->d.x = randomGenerate();
    node->d.y = randomGenerate();
    node->left = NULL;
    node->right = NULL;
    return node;
}

List *createList(Tree *T)
{
    List *node = (List *)malloc(sizeof(List));
    node->tree = T;
    node->next = NULL;
    return node;
}

void insertList(List **L, Tree *T)
{
    if (*L == NULL)
    {
        *L = createList(T);
    }
    else
    {
        List *aux;
        aux = *L;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = createList(T);
    }
}

void orderByX(List **L)
{
    List *aux;
    aux = *L;
    while (aux != NULL)
    {
        List *aux2;
        aux2 = aux->next;
        while (aux2 != NULL)
        {
            if (aux->tree->d.x > aux2->tree->d.x)
            {
                Tree *aux3;
                aux3 = aux->tree;
                aux->tree = aux2->tree;
                aux2->tree = aux3;
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }
}

void orderByY(List **L)
{
    List *aux;
    aux = *L;
    while (aux != NULL)
    {
        List *aux2;
        aux2 = aux->next;
        while (aux2 != NULL)
        {
            if (aux->tree->d.y > aux2->tree->d.y)
            {
                Tree *aux3;
                aux3 = aux->tree;
                aux->tree = aux2->tree;
                aux2->tree = aux3;
            }
            aux2 = aux2->next;
        }
        aux = aux->next;
    }
}

List *median(List *start, List *end)
{
    List *aux, *aux2;
    aux = start;
    int i = 0;
    while (aux != end)
    {
        aux = aux->next;
        i++;
    }
    if (i % 2 == 0)
    {
        i = i / 2;
    }
    else
    {
        i = (i + 1) / 2;
    }
    aux = start;
    while (i > 1)
    {
        aux = aux->next;
        i--;
    }
    aux2 = aux;
    aux = aux->next;
    aux2->next = NULL;
    return aux;
}

List *buildList()
{
    List *L = NULL;
    List *aux = L;
    int n = randomGenerate();
    for (int i = 0; i < n; i++)
    {
        insertList(&L, createTree());
    }
    return L;
}

List *end(List *L)
{
    while (L->next != NULL)
    {
        L = L->next;
    }
    return L;
}

int countElements(List *L)
{
    int count = 0;
    while (L != NULL)
    {
        count++;
        L = L->next;
    }
    return count;
}

Tree *buildTree(List *L, int level)
{
    if (L == NULL)
    {
        return NULL;
    }
    else if (L->next == NULL)
    {
        return L->tree;
    }
    else
    {
        List *aux;
        if (level % 2 == 0)
            orderByX(&L);
        else
            orderByY(&L);
        aux = median(L, end(L));
        Tree *T = aux->tree;
        T->left = buildTree(L, level + 1);
        T->right = buildTree(aux->next, level + 1);
        return T;
    }
}

void printList(List *L)
{
    while (L != NULL)
    {
        printf("(%d,%d)\n", L->tree->d.x, L->tree->d.y);
        L = L->next;
    }
}

int countNodes(Tree *T)
{
    if (T == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + countNodes(T->left) + countNodes(T->right);
    }
}

void printTree(Tree *tree, int x, int y, int space){
    if(tree != NULL){
        gotoxy(x, y);
        printf("(%d, %d)", tree->d.x, tree->d.y);
        
    	printTree(tree -> left, x-space, y+2, space/2);
    	printTree(tree -> right, x+space, y+2, space/2);
    }
}

void tab(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("\t");
    }
}

int main()
{
	system("MODE con cols=270 lines=120");
    srand(time(NULL));
    Tree *T = NULL;
    List *L = NULL;
    L = buildList();
    orderByX(&L);
    printList(L);
    T = buildTree(L, 0);
    
    gotoxy(80, countNodes(T) + 3);
    printf("Exibindo a arvore");
    printTree(T, 90, countNodes(T) + 6, 40);
    printf("\n\n\n\n\n\n\n\n");
}
