#include "point.h"
//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

Point* createPoint(Vector* position, Vector* speed, int time){
    //Allocation de la mémoire dynamique à la structure
    Point* newPoint = malloc(sizeof(Point));
    if(newPoint==NULL){
        printf("MALLOC ERROR\n");
    }
    else{
        //Affectation des différents paramètres à la structure puis renvoi du nouveau point crée
        newPoint->r=position;
        newPoint->v=speed;
        newPoint->t=time;
        return newPoint;
    }
}

void deletePoint(Point** p){
    //On commence par delete les vecteurs qui constitue le point. A savoir le vecteur vitesse et position
    // Pour cela on fait simplement appelle à notre fonction deleteVector codée auparavant
    Vector* tempVect = (*p)->r;
    deleteVector(&tempVect);
    tempVect = (*p)->v;
    deleteVector(&tempVect);
    //Ensuite il suffit de libérer la mémoire utilisée par le point et remettre le pointeur à NULL
    free(*p);
    *p=NULL;
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */
void printPoint(Point* p){
    printf("------------------------\n");
    printf("Position Vector :\n");
    //On utilise les fonctions codées auparavant afin d'afficher les différentes caractéristiques du point.
    printVector(getPosition(p));
    printf("Speed Vector\n");
    printVector(getSpeed(p));
    printf("Time : %d\n", getTime(p));
    printf("------------------------\n");
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/
Vector* getPosition(Point* p){
    return p->r;
}

Vector* getSpeed(Point* p){
    return p->v;
}

int getTime(Point* p){
    return p->t;
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations avec les points de la structure*/

void editPoint(Point* p, Vector* newPosition, Vector* newSpeed, int newTime){
    //On vérifie simplement que le point n'est pas un point supprimé (pointeur à NULL) pour éviter les segm fault
    //Puis on affecte simplemeent les nouvelles composantes du point.
    if(p!=NULL){
        p->t=newTime;
        p->v=newSpeed;
        p->r=newPosition;
    }
}

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForPointStruct(){
    //Initialisation des vecteurs nécéssaire
    int t =5;
    Vector* v = createVector(1,2,3);
    Vector* r = createVector(4,5,6);

    //Fonction de création :
    Point* p1 = createPoint(r,v,t);

    //Fonction d'affichage
    printPoint(p1);

    //Fonction d'Edit
    editPoint(p1,v,r,10);
    printPoint(p1);

    //Fonction d'affichage :
    printVector(getSpeed(p1));
    printVector(getPosition(p1));
    printf("Time : %d\n", getTime(p1));

    //Fonction de suppression
    deletePoint(&p1);

}

//------------------------------------------------------------------------//