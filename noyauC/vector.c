#include "vector.h"

//------------------------------------------------------------------------//

        /* Fonction de création et suppression de la structure */

Vector* createVector(double x, double y, double z)
{
    //Affectation de la mémoire dynamique à la structure
    Vector* newVector = malloc(sizeof(Vector));
    if(newVector==NULL){
        printf("MALLOC ERROR\n");
    }
    else{
        //Affectation des différentes données placés en paramètres de la fonction.
        newVector->x=x;
        newVector->y=y;
        newVector->z=z;
        return newVector;
    }
}
void deleteVector(Vector** vect){
    //On libère simplement la mémoire et on remet le pointeur à NULL
    free(*vect);
    *vect = NULL;
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printVector(Vector* vect){
    printf("%e %e %e\n", getX(vect), getY(vect), getZ(vect));
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
        /* Fonctions d'accès aux données de la structure*/
double getX(Vector* vector){
    return vector->x;
}

double getY(Vector* vector){
    return vector->y;
}

double getZ(Vector* vector){
    return vector->z;
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations avec les vecteurs de la structure*/

void editVector(Vector* vect, double newX, double newY, double newZ){
    //On vérifie juste que le vecteur ne soit pas à NULL (après une suppréssion) afin d'éviter de seg fault
    if(vect!=NULL){
        vect->x=newX;
        vect->z=newZ;
        vect->y=newY;
    }
}

Vector* sumOfVector(Vector* vect1, Vector* vect2){
    return createVector(getX(vect1)+ getX(vect2), getY(vect1)+ getY(vect2), getZ(vect1)+ getZ(vect2));
}

Vector* subtractionOfVector(Vector* vect1, Vector* vect2){
    return createVector(getX(vect1)- getX(vect2), getY(vect1)- getY(vect2), getZ(vect1)- getZ(vect2));
}

Vector* multiplicationByNumber(Vector* vect, double number){
    //Afin de multiplier un scalaire avec un vecteur, on multiplie chaques composantes par le scalaire.
    return createVector(getX(vect)*number, getY(vect)*number, getZ(vect)*number);
}

double standardOfVector(Vector* vect){
    //La norme d'un vecteur à 3 coordonnées est donné par la racine de la somme des composantes au carré, la formule est
    //donc exprimée en dessous afin de renvoyer la norme
    return sqrt(pow(getX(vect),2)+pow(getZ(vect),2)+pow(getY(vect),2));
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/
//Ces différentes fonctions permettent de tester les différentes opérations de la structure.

void testForVectorStructure(){
    //Fonction d'initialisation des vecteurs
    Vector* v1 = createVector(1,2,3);
    Vector* v2 = createVector(4,5,6);
    Vector* v3 = createVector(2,2,2);
    Vector* v4;
    Vector* v5;
    Vector* v6;

    //Fonction d'opération des vecteurs
    v6 = sumOfVector(v1,v2);
    v5 = subtractionOfVector(v2,v1);
    v4 = multiplicationByNumber(v3,2);

    //Fonction d'affichage
    printf("Vector v6 (v1+v2)\n");
    printVector(v6);
    printf("Vector v5 (v2-v1\n");
    printVector(v5);
    printf("Vector v4 (v3*2)\n");
    printVector(v4);

    //Fonction d'édit, de calcul et d'accès à la struct
    editVector(v4,1,1,1);
    printVector(v4);
    printf("x : %f y : %f z : %f\n", getX(v4), getY(v4), getY(v4));
    int standard = standardOfVector(v4);
    printf("%d\n",standard);

    //Fonction de suppression
    deleteVector(&v1);
    deleteVector(&v2);
    deleteVector(&v3);
    deleteVector(&v4);
    deleteVector(&v5);
    deleteVector(&v6);


}
//------------------------------------------------------------------------//
