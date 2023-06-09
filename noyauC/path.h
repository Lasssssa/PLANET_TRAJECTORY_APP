#ifndef _PATH_
#define _PATH_

#include "list.h"

typedef struct{
    struct List* l;
}Path;


//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

Path* createEmptyPath();

void deletePath(Path** path);
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printPath(Path* path);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

unsigned int PathSize(Path* path);

Point* firstPointOfPath(Path* path);

bool isPathEmpty(Path* path);

struct List* getList(Path* path);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations sur la structure*/

void addPointToPath(Path* path, Point* point);

void deletePointFromPath(Path* path);

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForPathStructure();

//------------------------------------------------------------------------//
#endif