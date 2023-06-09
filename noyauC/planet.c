#include "planet.h"
#include "constante.h"

//------------------------------------------------------------------------//
/* Fonction de création et suppression de la structure */

Planet* initPlanet(char* name, double weight, double perihelion, double eccentricity, double halfAxis){
    //On commence par allouer la mémoire à la structure
    Planet* newPlanet = malloc(sizeof(Planet));
    if(newPlanet==NULL){
        printf("MALLOC ERROR\n");
    }
    else{
        //On récupere le taille du nom de la planète afin d'allouer la mémoire pour le pointeur à char
        int size = strlen(name)+1;
        newPlanet->name = malloc(size*sizeof(char));
        if((newPlanet->name)==NULL)
        {
            printf("MALLOC ERROR\n");
        }
        else{
            //On affecte les différents paramètres à la structure de donnée
            strcpy(newPlanet->name,name);
            newPlanet->perihelion=perihelion;
            newPlanet->weight=weight;

            //Ensuite, il faut initialiser la trajectoire de la planète en placant son premier point à la périhélie
            Path* newPath = createEmptyPath();
            //On récupère la vitesse à la périhélie à l'aide de la formule donnée, on la met dans une variable qui représentera
            //la coordonnée Y du vecteur vitesse, en effet le vecteur vitesse est perpendiculaire au vecteur position, il aura
            //donc une composante non-nulle uniquement sur Y


            double initialSpeedInY = sqrt((GRAVITE*SOLEIL_WEIGHT*(1+eccentricity))/(halfAxis*(1-eccentricity)));
            //On initialise donc le vecteur vitesse à l'aide de la composante sur Y
            Vector* initialSpeed = createVector(0,initialSpeedInY,0);
            //On initialise le vecteur position en affectant la périhélie à la coordonnée X, ce vecteur ne possède qu'en
            //effet qu'une seule composante. (sur X)
            Vector* initialPosition = createVector(perihelion,0,0);
            //On crée donc le point initial, et on l'affecte comme premier point à la trajectoire
            Point* initialPoint = createPoint(initialPosition,initialSpeed,0);
            addPointToPath(newPath,initialPoint);
            newPlanet->path=newPath;
            return newPlanet;
        }
    }
}
Planet* initLune(){
    //On commence par allouer la mémoire à la structure

    double weight = 7.347e22;
    double peri = 3.567e8;
    double eccentri = 0.05490;
    double half = 3.844e8;
    Planet* newPlanet = malloc(sizeof(Planet));
    if(newPlanet==NULL){
        printf("MALLOC ERROR\n");
    }
    else{
        //On récupere le taille du nom de la planète afin d'allouer la mémoire pour le pointeur à char
        int size = 5;
        newPlanet->name = malloc(size*sizeof(char));
        if((newPlanet->name)==NULL)
        {
            printf("MALLOC ERROR\n");
        }
        else{
            //On affecte les différents paramètres à la structure de donnée
            strcpy(newPlanet->name,"lune");
            newPlanet->perihelion=peri;
            newPlanet->weight=weight;

            //Ensuite, il faut initialiser la trajectoire de la planète en placant son premier point à la périhélie
            Path* newPath = createEmptyPath();
            //On récupère la vitesse à la périhélie à l'aide de la formule donnée, on la met dans une variable qui représentera
            //la coordonnée Y du vecteur vitesse, en effet le vecteur vitesse est perpendiculaire au vecteur position, il aura
            //donc une composante non-nulle uniquement sur Y


            double initialSpeedInY = sqrt((GRAVITE*WEIGHT_EARTH*(1+eccentri))/(half*(1-eccentri)));
            //On initialise donc le vecteur vitesse à l'aide de la composante sur Y
            Vector* initialSpeed = createVector(0,initialSpeedInY,0);
            //On initialise le vecteur position en affectant la périhélie à la coordonnée X, ce vecteur ne possède qu'en
            //effet qu'une seule composante. (sur X)
            Vector* initialPosition = createVector(peri,0,0);
            //On crée donc le point initial, et on l'affecte comme premier point à la trajectoire
            Point* initialPoint = createPoint(initialPosition,initialSpeed,0);
            addPointToPath(newPath,initialPoint);
            newPlanet->path=newPath;
            return newPlanet;
        }
    }
}

void deletePlanet(Planet** p){
    Planet* temp = *p;
    //On commence par delete la trajectoire à l'aide de la fonction deletePath que l'on a crée dans la structure Path
    Path* tempPath = getPath(*p);
    deletePath(&tempPath);
    //On libère également la mémoire du nom
    free(temp->name);
    //Et on finit par libérer la mémoire de la structure ainsi que de remettre le pointeur à NULL
    free(temp);
    *p=NULL;
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonction d'affichage de la structure */

void printPlanet(Planet* p)
{
    printf("---------------------\n");
    printf("Name : %s\n", getName(p));
    printf("Weight : %e Kg and Perihélie : %e m\n", getWeight(p), getPerihelion(p));
    printPath(getPath(p));
    printf("---------------------\n");
}
//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'accès aux données de la structure*/

char* getName(Planet* p)
{
    return p->name;
}

double getWeight(Planet* p){
    return p->weight;
}

double getPerihelion(Planet* p){
    return p->perihelion;
}

Path* getPath(Planet* p)
{
    return p->path;
}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'opérations sur la structure*/

void changeName(char* newName, Planet* p){
    //On commence par libérer la mémoire de l'ancien nom
    free(p->name);
    //On calcule la taille que dont on va avoir besoin en mémoire
    int size = strlen(newName)+1;
    //Et ensuite on alloue
    p->name=malloc(size* sizeof(char));
    if(p->name==NULL)
    {
        printf("MALLOC ERROR\n");
    }
    else{
        strcpy(p->name,newName);
    }
}

void changeWeight(double newWeight, Planet* p){
    p->weight=newWeight;
}

void changePerihelion(double newPerihelion, Planet* p)
{
    p->perihelion=newPerihelion;
}

void addPointToPlanetPath(Point* newPoint, Planet* p)
{
    //Ici, on crée cette fonction afin de pouvoir ajouter un point à une planète et non à une trajectoire
    //cela revient un peu au même dans le code, mais cela peut être utile afin de ne pas utiliser tout le temps
    //la fonction getPath(planete) pour ajouter un point à la trajectoire de la planète.
    addPointToPath(getPath(p),newPoint);
}
void deleteAllPlanetOfArray(Planet** arrayPlanet,int size)
{
    //Permet de supprimer toutes les planètes d'un tableau
    for(int i=0;i<size;i++){
        deletePlanet(&(arrayPlanet[i]));
    }
    free(arrayPlanet);
}

Planet** createAllPlanet(){

    //Permet de renvoyer un tableau avec toutes les planètes du système solaire

    Planet* p1 = initPlanet("mercury", WEIGHT_MERCURY,PERI_MERCURY,ECCENTRICITY_MERCURY,HALF_AXIS_MERCURY);
    Planet* p2 = initPlanet("venus", WEIGHT_VENUS,PERI_VENUS,ECCENTRICITY_VENUS,HALF_AXIS_VENUS);
    Planet* p3 = initPlanet("earth", WEIGHT_EARTH,PERI_EARTH,ECCENTRICITY_EARTH,HALF_AXIS_EARTH);
    Planet* p4 = initPlanet("mars", WEIGHT_MARS,PERI_MARS,ECCENTRICITY_MARS,HALF_AXIS_MARS);
    Planet* p5 = initPlanet("jupiter", WEIGHT_JUPITER,PERI_JUPITER,ECCENTRICITY_JUPITER,HALF_AXIS_JUPITER);
    Planet* p7 = initPlanet("saturn", WEIGHT_SATURN,PERI_SATURN,ECCENTRICITY_SATURN,HALF_AXIS_SATURN);
    Planet* p6 = initPlanet("uranus", WEIGHT_URANUS,PERI_URANUS,ECCENTRICITY_URANUS,HALF_AXIS_URANUS);
    Planet* p8 = initPlanet("neptune", WEIGHT_NEPTUNE,PERI_NEPTUNE,ECCENTRICITY_NEPTUNE,HALF_AXIS_NEPTUNE);

    Planet** arrayPlanet = malloc(8*sizeof(Planet*));
    arrayPlanet[0] = p1;
    arrayPlanet[1] = p2;
    arrayPlanet[2] = p3;
    arrayPlanet[3] = p4;
    arrayPlanet[4] = p5;
    arrayPlanet[5] = p6;
    arrayPlanet[6] = p7;
    arrayPlanet[7] = p8;
    return arrayPlanet;

}
//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonctions de TEST pour la structure*/

void testForPlanetStructure(){
    //Création des données nécéssaire au test

    Point* p1 = createPoint(createVector(1,1,1), createVector(2,2,2),5);
    Point* p2 = createPoint(createVector(1,1,5), createVector(2,5,2),5);
    //Fonction de création:
    Planet* p = initPlanet("earth", WEIGHT_EARTH,PERI_EARTH,ECCENTRICITY_EARTH,HALF_AXIS_EARTH);

    printPlanet(p);
    //Fonction d'opérations sur la planète
    addPointToPlanetPath(p1,p);
    addPointToPlanetPath(p2,p);

    //Fonction d'acces à la structure
    printf("Weight : %e  Perihelion : %e  %s \n", getWeight(p), getPerihelion(p), getName(p));

    //Fonction d'affichage de la struct
    printPlanet(p);

    //Fonction d'opération de la structure

    changeName("NEWPLANET",p);
    changePerihelion(25,p);
    changeWeight(30,p);


    printPlanet(p);


    deletePlanet(&p);
}

//------------------------------------------------------------------------//