#ifndef _PLANET_
#define _PLANET_

#include "path.h"

typedef struct{
    char* name;
    Path* path;
    double weight;
    double perihelion;
}Planet;


//------------------------------------------------------------------------//

/* Fonction de création et suppression de la structure */
Planet* initPlanet(char* name, double weight, double perihelion, double eccentricity, double halfAxis);

Planet* initLune();

void deletePlanet(Planet** p);
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printPlanet(Planet* p);
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

char* getName(Planet* p);

double getWeight(Planet* p);

double getPerihelion(Planet* p);

Path* getPath(Planet* p);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations sur la structure*/

void changeName(char* newName, Planet* p);

void changeWeight(double newWeight, Planet* p);

void changePerihelion(double newPerihelion, Planet* p);

void addPointToPlanetPath(Point* newPoint, Planet* p);

void deleteAllPlanetOfArray(Planet** arrayPlanet,int size);

Planet** createAllPlanet();

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForPlanetStructure();

//------------------------------------------------------------------------//
#endif