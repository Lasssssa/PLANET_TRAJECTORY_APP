#include "path.h"

//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

Path* createEmptyPath()
{
    //Tout d'abord on alloue la mémoire à la structure
    Path* newPath = malloc(sizeof(Path));
    if(newPath!=NULL){
        //On crée une liste vide afin de l'affecter à notre trajectoire, en effet, notre "Path" est codé comme une file
        //à l'aide une liste
        newPath->l= createEmptyList();
        return newPath;
    }
    else{
        printf("MALLOC ERROR\n");
    }
}

void deletePath(Path** path) {
    //Il faut d'abord delete la liste entière, pour cela on appelle deleteList codée dans la structure liste.
    struct List *temp = (*path)->l;
    deleteList(&temp);
    //Ensuite on s'occupe de libérer la mémoire et de remettre le pointeur à NULL
    free(*path);
    *path = NULL;
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */
void printPath(Path* path)
{
    //Verification que la trajectoire ne comporte pas aucun point.
    if(isPathEmpty(path)){
        printf("The path is empty\n");
    }
    //Il faut également vérifier s'il n'y a pas un seul point.
    else if(PathSize(path)==1){
        printPoint(getPointFromCell(getLast(getList(path))));
    }
    else
    {
        //On utilise un itérateur qui nous permet d'avancer dans la liste et d'afficher les informations au fur et à mesure
        struct Cell* iterator = getFirst(getList(path));
        int n = PathSize(path);
        printPoint(iterator->p);
        for(int i=0;i<n-2;i++)
        {
            iterator= iterator->next;
            //Utilisation de la fonction printPoint codée auparavant afin de donner les caractéristiques du point.
            printPoint(iterator->p);
        }
        iterator= iterator->next;
        printPoint(iterator->p);
    }

}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

unsigned int PathSize(Path* path)
{
    return(listSize(path->l));
}

bool isPathEmpty(Path* path)
{
    return(isListEmpty(path->l));
}

Point* firstPointOfPath(Path* path){
    //On code cette fonction d'obtenir le dernier élement de la file à savoir le premier point de la trajectoire
    //Le problème de cette fonction est qu'elle possède une complexité O(n).
    int n = PathSize(path)-1;
    bool valid;
    return getPointFromCell(getList(path)->firstCell);
}

struct List* getList(Path* path){
    return path->l;
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations sur la structure*/

void addPointToPath(Path* path, Point* point)
{
    //Utilisant une file, on doit donc mettre au début de la liste les nouveaux points de la trajectoire
    addLast(getList(path),point);
}


void deletePointFromPath(Path* path)
{
    if(isPathEmpty(path)){
        return ;
    }
    else{
        deleteFirst(getList(path));
    }
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForPathStructure(){
    //Initialisation des valeurs nécéssaire :
    Vector* tab[10];
    for(int i = 0 ; i<10;i++){
        tab[i] = createVector(i+2,i+3,i+5);
    }
    Point* p1 = createPoint(tab[0],tab[5],0);
    Point* p2 = createPoint(tab[1],tab[6],1);
    Point* p3 = createPoint(tab[2],tab[7],2);
    Point* p4 = createPoint(tab[3],tab[8],3);
    Point* p5 = createPoint(tab[4],tab[9],4);

    //Fonction de création
    Path* path = createEmptyPath();

    //Fonction d'opération :
    addPointToPath(path,p1);
    addPointToPath(path,p2);
    addPointToPath(path,p3);
    addPointToPath(path,p4);
    addPointToPath(path,p5);

    printf("%d\n", PathSize(path));

    //Fonction d'affichage
    printPath(path);

    //bool valid;
    //deletePointFromPath(path,&valid);

    printPath(path);

    //Fonction d'accès :
    printf("empty : %d size : %d\n", isPathEmpty(path), PathSize(path));
    printPoint(firstPointOfPath(path));


    //Fonction de suppression
    deletePath(&path);

}

//------------------------------------------------------------------------//