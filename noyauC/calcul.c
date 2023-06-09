#include "calcul.h"
#include "constante.h"

//---------------------------------------------------------------------------------//
/*--------------------Fonctions de calcul des données------------------------------*/

//------Fonctions de calcul de trajectoire d'une planète ----//

void calculLune(Planet* earth, Planet* lune){

    //Calcul de la trajectoire de la Lune avec la Terre En referentiel
    EulerAsymetricMethod(lune,20000,WEIGHT_EARTH);

    //Modification des données de la Lune afin d'ajouter les coordonées de la Terre
    //Ce qui a pour effet de donner la trajectoire de la lune dans le referentiel solaire
    struct Cell* iter = getFirst(getList(getPath(earth)));
    struct Cell* iterLune = getFirst(getList(getPath(lune)));
    double x;
    double z;
    double y;
    for(int i=0;i<20000;i++){
        //Changement des coordonnées
        x = getX(getPosition(getPointFromCell(iterLune)))*40+ getX(getPosition(getPointFromCell(iter)));
        y = getY(getPosition(getPointFromCell(iterLune)))*40+ getY(getPosition(getPointFromCell(iter)));
        z = getZ(getPosition(getPointFromCell(iterLune)))*40+ getZ(getPosition(getPointFromCell(iter)));
        editVector(getPosition(getPointFromCell(iterLune)),x,y,z);
        iter=iter->next;
        iterLune= iterLune->next;
    }
}
void EulerMethod(Planet* p, int time, double referentialWeight) {
//Déclaration des constante utile à notre programme
    Point* initial;
    double standard;
    Vector* speed;
    Vector* speed1;
    Vector* position;
    Vector* position1;
    double constante;

    for (int i = 1; i < time; i++) {
        //Récupération des composantes du derniers point (date Tn)
        initial = getPointFromCell(getLast(getList(getPath(p))));
        standard = standardOfVector(getPosition(initial));
        position = getPosition(initial);
        speed = getSpeed(initial);

        //Calcul de la nouvelle acceleration à partie de la position date Tn
        constante = ((-GRAVITE * referentialWeight) / (standard * standard * standard));
        Vector* acceleration = multiplicationByNumber(position, constante);

        //Calcul de la nouvelle position
        Vector* tempSpeed = multiplicationByNumber(speed, DELTA_T);
        position1 = sumOfVector(position, tempSpeed);

        //Calcul de la nouvelle vitesse
        Vector* tempAcceleration = multiplicationByNumber(acceleration, DELTA_T);
        speed1 = sumOfVector(speed, tempAcceleration);

        //Suppression des vecteurs temporaire utile au calcul
        deleteVector(&acceleration);
        deleteVector(&tempSpeed);
        deleteVector(&tempAcceleration);

        //Création et ajout du point(position vitesse) à la date t+1
        Point *newPoint = createPoint(position1, speed1, i);
        addPointToPlanetPath(newPoint, p);
    }
}
void EulerAsymetricMethod(Planet* p, int time, double referentialWeight){

    //Déclaration des variables
    Point* initial;
    double standard;
    Vector* speed;
    Vector* speed1;
    Vector* position;
    Vector* position1;
    double constante;

    for (int i = 1; i < time; i++) {
        //Récupération des composantes du dernier point (date Tn)
        initial = getPointFromCell(getLast(getList(getPath(p))));
        position = getPosition(initial);
        speed = getSpeed(initial);

        //Calcul de la nouvelle position
        Vector* tempSpeed = multiplicationByNumber(speed, DELTA_T);
        position1 = sumOfVector(position, tempSpeed);

        //Calcul de formule et d'accélération à l'aide de la nouvelle position
        standard = standardOfVector(position1);
        constante = ((-GRAVITE * referentialWeight) / (standard * standard * standard));
        Vector* acceleration = multiplicationByNumber(position1, constante);

        //Calcul de la nouvelle vitesse
        Vector* tempAcceleration = multiplicationByNumber(acceleration, DELTA_T);
        speed1 = sumOfVector(speed, tempAcceleration);

        //Suppression des vecteurs temporaire utile au calcul
        deleteVector(&acceleration);
        deleteVector(&tempSpeed);
        deleteVector(&tempAcceleration);

        //Création et ajout du point(position vitesse) à la date t+1
        Point *newPoint = createPoint(position1, speed1, i);
        addPointToPlanetPath(newPoint, p);
    }
}

//-----------------------------------------------------------//
//---------Fonctions de calcul lié à l'energie---------------//
double absoluteValue(double value){

    //Fonction qui renvoi la valeur absolue d'une valeur placée en paramètre
    if(value>0){
        return value;
    }
    else{
        return -1*value;
    }
}

double cineticEnergy(Planet* planet, Point* point){

    //Calcul de l'energie cinétique de la planète à un certain point placé en paramètre
    double squareSpeed = standardOfVector(getSpeed(point)) * standardOfVector(getSpeed(point));
    double c = 0.5*(getWeight(planet)*squareSpeed);
    return c;
}

double potentialEnergy(Planet* planet, Point* point){

    //Calcul de l'energie potentiel de la planète à un certain point placé en paramètre
    double squareR = standardOfVector(getPosition(point)) * standardOfVector(getPosition(point));
    double epp = 0.5*(GRAVITE* getWeight(planet)*SOLEIL_WEIGHT)/ squareR;
    return epp;
}

double averageOfArray(double* marginArray, int size){

    //Fonction qui renvoi la moyenne d'un tableau de double placé en paramètre
    double sum = 0;
    for(int i =0;i<size;i++){
        sum =  sum+marginArray[i];
    }
    return sum/size ;
}
double maxOfArray(double* marginArray, int size){

    //Fonction qui renvoi le max d'un tableau à l'aide d'un parcours.
    double max = marginArray[0];
    for(int i= 0; i<size;i++){
        if(marginArray[i]>max){
            max = marginArray[i];
        }
    }
    return max;
}
double errorMarginOfMecanicEnergy(Planet* planet, double* max){
    //Fonction qui effectue la vérification d'energie
    //Va vérifier pour chaque point si l'energie mécanique est constante entre le point Tn et Tn+1

    //Rrécupération de la cellule contenant le point initial de la planète
    Path* path = getPath(planet);
    struct List* l = getList(path);
    struct Cell* iterator = getFirst(l);

    //Création d'un tableau dynamique de taille de la trajectoire de la planète
    int n = PathSize(path);
    double* marginArray = malloc(n*sizeof(double));

    //Déclaration des variables d'energie
    double potentialEnergyOfPoint =0 ;
    double cineticEnergyOfPoint =0;
    double mecanicEnergy = 0;
    double mecanicEnergyBefore = 0;
    double pourcentage =0;

    //Calcul de l'energie mécanique initiale à l'aide de l'energie potentielle et cinétique
    potentialEnergyOfPoint = potentialEnergy(planet,getPointFromCell(iterator));
    cineticEnergyOfPoint = cineticEnergy(planet, getPointFromCell(iterator));
    mecanicEnergy = potentialEnergyOfPoint + cineticEnergyOfPoint;
    mecanicEnergyBefore = mecanicEnergy;

    for(int i = 1 ; i<n ;i++ )
    {
        //Itération dans la trajectoire de la planète
        iterator = iterator->next;

        //Calcul de la nouvelle energie mécanique
        potentialEnergyOfPoint = potentialEnergy(planet,getPointFromCell(iterator));
        cineticEnergyOfPoint = cineticEnergy(planet, getPointFromCell(iterator));
        mecanicEnergy = potentialEnergyOfPoint + cineticEnergyOfPoint;

        //Calcul du pourcentage d'écart entre les deux énergies mécaniques et mise du résultat dans un tableau
        pourcentage = (mecanicEnergy*100)/mecanicEnergyBefore;
        marginArray[i-1] = absoluteValue(pourcentage);
        mecanicEnergyBefore=mecanicEnergy;

    }
    //Calcul de la moyenne des pourcentages d'écart ainsi que la valeur max enregistrée
    double marginError = averageOfArray(marginArray,n-1);
    *max = absoluteValue(100-maxOfArray(marginArray,n-1));
    free(marginArray);
    //Renvoi du résulat sous forme de pourcentage
    double result = absoluteValue(100-marginError);
    return result;
}
//-----------------------------------------------------------//

//----------------------------------------------------------------------------------//
/* Fonction global qui appelle les fonctions de calcul*/

void globalCalcul(char* fileName, int method, int executionMode) {

    //Fonction utilisé par le calculMenu afin d'exporter les planètes en fonction des données utilisateurs

    //Vidage du fichier en amont pour eviter tout soucis.
    emptyFile(fileName);
    int size =0;

    //On utilise la fonction createAllPlanet qui renvoi un tableau contenant toutes les planètes du système solaire
    Planet** arrayOfPlanet = createAllPlanet();
    if (executionMode == 1) {

        //Calcul puis exportation du tableau de planète à l'aide des fonctions calculPathOfPlanetArray et exportationPathOfPlanetArray
        size=8;
        calculPathOfPlanetArray(arrayOfPlanet,size,method);
        exportationPathOfPlanetArray(arrayOfPlanet,size,method,fileName);

    } else if(executionMode==2){

        //Si l'utilisateur de rentrer à la main les planètes, alors lance un petit menu qui lui permet de choisir les planètes
        Planet** arrayPlanetChosen = malloc(8* sizeof(Planet*));
        system("clear");
        printf("---------------------------------------------\n");
        printf("|   Programming phase of your calculation    |\n");
        printf("---------------------------------------------\n");
        printf("\nThe planets will scroll by so you can choose the ones you want or not.\n");
        printf("\nPlease enter 1 if you want to calculate its trajectory and 2 otherwise.\n");

        //Recuperation des données utilisateurs et création d'un tableau de planète utilisant les demandes utilisateurs
        for(int i=0;i<8;i++){
            planetChosenByUser(arrayPlanetChosen, arrayOfPlanet[i], &size);
        }
        if(size!=0)
        {

            //Une fois que l'on a récupéré les données utilisateurs on utilise les fonction calculPathOfPlanetArray et exportationPathOfPlanetArray
            calculPathOfPlanetArray(arrayPlanetChosen,size,method);
            exportationPathOfPlanetArray(arrayPlanetChosen,size,method,fileName);

        }
        else{
            printf("YOU CANNOT EXPORT 0 PLANET !\n");
        }
        free(arrayPlanetChosen);
    }

    //Suppression de toutes les planètes
    deleteAllPlanetOfArray(arrayOfPlanet,8);
}

void verificationOfAllPlanet(int method){

    //Fonction qui affiche le pourcentage d'erreur moyen de conservation d'energie mecanique

    //On crée les planètes du système solaire à l'aide de createAllPlanet() puis on calcul leur trajectoire
    Planet** arrayPlanet = createAllPlanet();
    calculPathOfPlanetArray(arrayPlanet,8,method);

    double errorMargin=0;
    double maxError=0;
    for(int i=0;i<8;i++){
        //Calcul et affichage des pourcentages d'erreur de chaque planète
        errorMargin = errorMarginOfMecanicEnergy(arrayPlanet[i],&maxError);
        printf("-------------------------------------------\n");
        printf("Planet : %s",getName(arrayPlanet[i]));
        printf("Margin of error : %f %",errorMargin);
        printf("Max Error : %f % \n",maxError);
    }
    printf("--------------------------------------------\n");

    //On supprime toutes les planètes
    deleteAllPlanetOfArray(arrayPlanet,8);
}

//------------------------------------------------------------------------//
/* Fonctions de manipulation des fichiers JSON*/

void exportation(char* nameFile, Planet* p, char* method, bool lastOne, bool firstOne){

    //Ouverture du fichier JSON
    FILE* exportedFile = fopen(nameFile,"a");
    if(exportedFile==NULL){
        printf("Error in opening file\n");
        return;
    }
    //On commence par vérifier le paramètre firstOne, celui-ci signifie que la planète qu'on exporte est la première
    // que l'on exporte dans le fichier JSON, si c'est la première alors il faut mettre un "{" dans le fichier pour
    //respecter le format, si ce n'est pas la première planète, cela signifie que le fichier possède deja une planète donc pas de {
    if(firstOne==true){
        fprintf(exportedFile,"{");
    }

    //Ensuite, ici on fait deux petits if afin de savoir si la méthode utiliser est celle d'Euler ou d'EulerAsymétric,
    // cela permet juste de pouvoir nommer notre objet JS de la bonne facon, on place la méthode en paramètre.
    //Par ailleurs on a dans le constante.h défini des variable EULER et EULER_ASYMETRIC pour pouvoir les placer en paramètre
    if(strcmp(method,"euler")==0){
        fprintf(exportedFile,"\"%s-euler\" : [", getName(p));
    }
    else if(strcmp(method,"eulerasymetric")==0){
        fprintf(exportedFile,"\"%s-eulerasymetric\" : [", getName(p));
    }
    //Ensuite, il faut commencer à écrire les points dans le fichier.
    while(!isPathEmpty(getPath(p))){
        //lorsqu'on commence un point, il faut mettre un "["
        fprintf(exportedFile,"[");

        //Récupération du premier point de la trajectoire ainsi que ses composantes
        Point* point = firstPointOfPath(getPath(p));
        Vector* speed = getSpeed(point);
        Vector* position = getPosition(point);

        //Print des infos du point dans le fichier JSON
        fprintf(exportedFile,"[%e, %e, %e],[%e, %e, %e], %d", getX(position), getY(position), getZ(position), getX(speed),
                getY(speed), getZ(speed), getTime(point));

        //Suppression du point de la trajectoire
        deletePointFromPath(getPath(p));

        //Une fois que l'on a afficher le point, il y a plusieurs cas de figure :

        //Case 1 : Il n'y a plus de point mais aussi, c'est la dernière planète que l'on importe dans le fichier
        //alors il ne faut pas mettre de virgule après "]"
        if(isPathEmpty(getPath(p)) && lastOne==true){
            fprintf(exportedFile,"]]\n");
        }

            //Cas 2 : Il n'y a plus de point mais ce n'est pas la dernière planète que l'on importe dans le fichier
            // donc il faut mettre une virgule après (car il faut mettre des virgules entre les objets)
        else if(isPathEmpty(getPath(p)) && lastOne == false)
        {
            fprintf(exportedFile,"]],\n");
        }

            //Cas 3 : Ce n'est pas le dernier point alors on "ferme" seulement le point en cours et on le sépare avec une
            // virgule du point suivant
        else{
            fprintf(exportedFile,"],\n");
        }
    }

    //Si la planète print est la dernière du fichier alors on referme l'accolade
    if(lastOne==true){
        fprintf(exportedFile,"\n}");
    }
    fclose(exportedFile);

}


void emptyFile(char* nameFile){
    //Fonction qui clear un fichier (ouverture en mode w afin de tout supprimer)
    FILE* exportedFile = fopen(nameFile,"w");
    if(exportedFile==NULL){
        printf("Error in opening file\n");
        return;
    }
    fclose(exportedFile);
}

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonction qui manipule des tableaux de planètes*/

void exportationPathOfPlanetArray(Planet** arrayPlanet, int size, int method, char* fileName)
{
    //Fonction qui exporte dun tableau de planète dans un fichier JSON
    if(method==1){
        for (int i = 0; i < size; i++) {

            //Ces différentes verifications sont utile afin d'attribuer les paramètre lastOne ou FisrtOne à la fonction exportation
            if (i == 0) {
                exportation(fileName, arrayPlanet[i], EULER, false, true);
            } else if (i == size - 1) {
                exportation(fileName, arrayPlanet[i], EULER, true, false);
            } else {
                exportation(fileName, arrayPlanet[i], EULER, false, false);
            }
        }
    }
    else{
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                exportation(fileName, arrayPlanet[i], EULER_ASYMETRIC, false, true);
            } else if (i == size - 1) {
                exportation(fileName, arrayPlanet[i], EULER_ASYMETRIC, true, false);
            } else {
                exportation(fileName, arrayPlanet[i], EULER_ASYMETRIC, false, false);
            }
        }
    }
}
void calculPathOfPlanetArray(Planet** arrayPlanet, int size, int method){

    //Fonction qui calcul la trajectoire des planètes d'un tableau en fonction de la méthode
    if(method==1){
        for (int i = 0; i < size; i++) {
            EulerMethod(arrayPlanet[i], getPeriodFromName(getName(arrayPlanet[i])),SOLEIL_WEIGHT);
        }
    }
    else{
        for (int i = 0; i < size; i++) {
            EulerAsymetricMethod(arrayPlanet[i], getPeriodFromName(getName(arrayPlanet[i])),SOLEIL_WEIGHT);
        }
    }


}
void planetChosenByUser(Planet** planetWantedByUser,Planet* planet , int* size){
    int i ;

    //Fonction pour le choix des planètes
    printf("|-| Planet : %s\n", getName(planet));
    scanf("%d",&i);
    if(i==1){
        planetWantedByUser[*size] = planet;
        *size = *size+1;
    }
}
//------------------------------------------------------------------------//

