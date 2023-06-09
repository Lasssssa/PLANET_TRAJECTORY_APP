#ifndef _LIST_
#define _LIST_

#include "point.h"

struct Cell{
    Point* p;
    struct Cell* next;
};

struct List{
    unsigned int size;
    struct Cell* firstCell;
    struct Cell* lastCell;
};

//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

struct Cell* createCell(Point* p);

struct List* createEmptyList();

void deleteList(struct List** l);

void deleteCell(struct Cell** c);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printList(struct List* l);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

bool isListEmpty(struct List* l);

struct Cell* getLast(struct List* l);

struct Cell* getFirst(struct List* l);

unsigned listSize(struct List* l);

Point* getPointFromCell(struct Cell* c);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations sur la structure*/

void addLast(struct List* l, Point* p);

void deleteFirst(struct List* l);

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/



//------------------------------------------------------------------------//




#endif