#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio2.h>
#include "tad.h"
#include <time.h>

int randomGenerate()
{
    return rand() % 90 + 10;
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

void printList(List *L)
{
    while (L != NULL)
    {
        printf("(%d,%d)\n", L->tree->d.x, L->tree->d.y);
        L = L->next;
    }
}

float distance(Tree *T1, Tree *T2)
{
    return sqrt(pow(T1->d.x - T2->d.x, 2) + pow(T1->d.y - T2->d.y, 2));
}

char itsInside(Tree *T, Tree *point, int radius)
{
    if (distance(T, point) - radius <= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void closerPoint(Tree *tree)
{
    int radius = 10;
    Tree *point = createTree(), *aux;
    List *queueTree = NULL;
    List *queueCloserPoints = NULL;
    enqueue(&queueTree, tree);
    while (queueTree != NULL)
    {
        dequeue(&queueTree, &aux);
        if (aux->left != NULL)
        {
            enqueue(&queueTree, aux->left);
        }
        if (aux->right != NULL)
        {
            enqueue(&queueTree, aux->right);
        }
        if (aux != NULL && distance(aux, point) - radius <= 0)
        {
            enqueue(&queueCloserPoints, aux);
        }
    }
    printf("\n\n\nPontos proximos ao ponto: (%d,%d) com raio %d\n", point->d.x, point->d.y, radius);
    printList(queueCloserPoints);
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
    srand(time(NULL));
    Tree *T = NULL;
    List *L = NULL;
    L = buildList();
    orderByX(&L);
    printList(L);
    T = buildTree(L, 0);
    gotoxy(44, countNodes(T) + 3);
    printf("Exibindo a arvore");
    printTree(T, 47, countNodes(T) + 6, 20);
    printf("\n\n\n\n\n\n\n\n");
    closerPoint(T);
}
