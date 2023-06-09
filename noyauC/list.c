#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"

//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

struct Cell* createCell(Point* p)
{
    //Allocation de la mémoire puis affectation des paramètres à la cellule
    struct Cell* newCell = malloc(sizeof(struct Cell));
    if(newCell!=NULL) {
        newCell->p = p;
        newCell->next = NULL;
        return newCell;
    }
    else{
        printf("MALLOC ERROR\n");
    }
}
struct List* createEmptyList()
{
    struct List* emptyList = malloc(sizeof(struct List));
    //Création de la liste et initialisation de celle ci avec des paramètres nuls, c'est à dire une liste vide.
    if(emptyList!=NULL){
        emptyList->size=0;
        emptyList->firstCell=NULL;
        emptyList->lastCell=NULL;
        return emptyList;
    }
    else{
        printf("MALLOC ERROR\n");
    }
}

void deleteCell(struct Cell** c){
    Point* deletedPoint = (*c)->p;
    //On delete d'abord le point qu'il y a dans la cellule
    deletePoint(&deletedPoint);
    //Puis on libère la mémoire de la cellule en elle même
    free(*c);
    *c =NULL;
}

void deleteList(struct List** l)
{
    if(*l == NULL){
        return;
    }
    struct List* tempList = *l;
    int n = listSize(tempList);
    //On appelle la fonction deleteFirst jusqu'a ce que la liste soit vide afin d'avoir une complexité O(n) car
    // deleteFirst est une fonction O(1)
    while(!isListEmpty(tempList)){
        deleteFirst(tempList);
    }
    //On libère la mémoire de la structure
    free(tempList);
    *l =NULL;
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printList(struct List* l)
{
    if(l->size==0){
        printf("NULL\n");
        return;
    }
    //Fonction qui print une liste en itérant cellule par cellule
    struct Cell* iterator = getFirst(l);
    for(unsigned int i = 0 ; i < l->size ; i++)
    {
        //Affichage du point
        printPoint(iterator->p);
        iterator=iterator->next;
    }
    printf("NULL\n");
}


//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

unsigned listSize(struct List* l)
{
    //Retourne la taille de la liste
    return l->size;
}

bool isListEmpty(struct List* l)
{
    //Retourne un booleen qui dit si la liste est vide
    return(l->size==0);
}

struct Cell* getFirst(struct List* l){
    //Retourne la première cellule de la liste (stocke le premier point de la trajectoire)
    return l->firstCell;
}
struct Cell* getLast(struct List* l){
    //Retourne la dernière cellule de la liste (stocke le dernier point de la trajectoire)
    return l->lastCell;
}
Point* getPointFromCell(struct Cell* c){
    //Retourne le point contenu dans une cellule
    return c->p;
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations sur la structure*/


void deleteFirst(struct List* l)
{
    if(!isListEmpty(l)){
        //On sauvegarde le deuxieme point de la liste
        struct Cell* temp = getFirst(l)->next;
        //On supprime le premier point de la liste
        struct Cell* cellDeleted = l->firstCell;
        deleteCell(&cellDeleted);
        l->size--;
        //On affecte le deuxieme point de la liste à la tete de celle-ci
        l->firstCell=temp;
    }
}

void addLast(struct List* l, Point* p)
{
    struct Cell* newLast = createCell(p);
    //Si la liste est vide alors on initialise celle-ci à l'aide du point que l'on a
    if(isListEmpty(l)){
        l->size++;
        l->firstCell=newLast;
        l->lastCell=newLast;
    }
    else{
        //Sinon, on vient insérer le nouveau point en premier par manipulation des pointeurs
        getLast(l)->next=newLast;
        l->lastCell=newLast;
        l->size++;
    }
}

//------------------------------------------------------------------------//