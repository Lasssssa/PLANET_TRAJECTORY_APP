#ifndef _POINT_
#define _POINT_

#include "vector.h"

typedef struct{
    Vector* r;
    Vector* v;
    int t;
}Point;


//------------------------------------------------------------------------//
/* Fonctions de création et suppression de la structure */

Point* createPoint(Vector* position, Vector* speed, int time);

void deletePoint(Point** p);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'affichage de la structure */

void printPoint(Point* p);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

Vector* getPosition(Point* p);

Vector* getSpeed(Point* p);

int getTime(Point* p);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations avec les vecteurs de la structure*/

void editPoint(Point* p, Vector* newPosition, Vector* newSpeed, int newTime);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForPointStruct();

//------------------------------------------------------------------------//
#endif