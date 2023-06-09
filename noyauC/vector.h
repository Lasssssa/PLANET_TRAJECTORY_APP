#ifndef _VECTOR_
#define _VECTOR_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct{
    double x;
    double y;
    double z;
}Vector;


//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

Vector* createVector(double x, double y, double z);

void deleteVector(Vector** vect);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printVector(Vector* vect);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

double getX(Vector* vector);

double getY(Vector* vector);

double getZ(Vector* vector);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations avec les vecteurs de la structure*/

Vector* sumOfVector(Vector* vect1, Vector* vect2);

Vector* subtractionOfVector(Vector* vect1, Vector* vect2);

Vector* multiplicationByNumber(Vector* vect, double number);

double standardOfVector(Vector* vect);

void editVector(Vector* vect, double newX, double newY, double newZ);

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForVectorStructure();

//------------------------------------------------------------------------//

#endif