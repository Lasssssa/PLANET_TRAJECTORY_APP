#ifndef _CALCUL_
#define _CALCUL_
#include "planet.h"


//---------------------------------------------------------------------------------//
/*--------------------Fonctions de calcul des données------------------------------*/

//------Fonctions de calcul de trajectoire d'une planète ----//
void EulerMethod(Planet* p, int time, double referentialWeight);

void EulerAsymetricMethod(Planet* p, int time, double referentialWeight);


Vector* getAcceleration(int j, Planet** arrayPlanet, int size, Point* actualPoint);
//-----------------------------------------------------------//
//---------Fonctions de calcul lié à l'energie---------------//
double cineticEnergy(Planet* planet, Point* point);

double potentialEnergy(Planet* planet, Point* point);

double averageOfArray(double* marginArray, int size);

double absoluteValue(double value);

double maxOfArray(double* marginArray, int size);

double errorMarginOfMecanicEnergy(Planet* planet, double* max);
//-----------------------------------------------------------//

//----------------------------------------------------------------------------------//
/* Fonction global qui appelle les fonctions de calcul*/
void globalCalcul(char* fileName, int method, int executionMode);

void verificationOfAllPlanet(int method);

void calculLune(Planet* earth, Planet* lune);

//------------------------------------------------------------------------//
/* Fonctions de manipulation des fichiers JSON*/

void exportation(char* nameFile, Planet* p,char* method,bool lastOne,bool firstOne);

void emptyFile(char* nameFile);

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonction qui manipule des tableaux de planètes*/


void planetChosenByUser(Planet** planetWantedByUser,Planet* planet , int* size);

void calculPathOfPlanetArray(Planet** arrayPlanet, int size, int method);

void exportationPathOfPlanetArray(Planet** arrayPlane, int size, int method, char* fileName);


//------------------------------------------------------------------------//



#endif