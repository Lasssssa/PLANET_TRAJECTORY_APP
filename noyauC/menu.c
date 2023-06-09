#include "menu.h"
#include "calcul.h"
#include <unistd.h>

#include <time.h>
//------------------------------------------------------------------------//
/* Fonctions de lancement et d'arret du menu */

void principalMenu(){

    //Affichage du Menu Principal
    char optionChar[3];
    int option;
    printf("Start \n");
    sleep(1.5);
    system("clear");
    printf("----------------------------------------------------\n");
    printf("|   Welcome to the Main Menu of this application    |\n");
    printf("----------------------------------------------------\n");
    printf("\n|1- Personalize the calcul and exportation\n \n|2- Read Informations about Planets\n \n|3- Energetic Verification\n \n|4- Calcul and Export All Planet With EulerAsymetric\n \n|5-"
           " Calcul and Export Lune Path \n\n|6- Exit Program\n");

    //Cette méthode de récole des données utilisateurs permet de ne pas avoir de bug si l'utilisateur n'entre pas
    //un int dans un scanf("%d")
    scanf("%s",&optionChar);
    option=atoi(optionChar);

    //Vérification des saisies utilisateurs
    while(option>6 || option<1)
    {
        printf("Invalid Option !\n");
        printf("\n|1- Personalize the calcul and exportation\n \n|2- Read Informations about Planets\n \n|3- Energetic Verification\n \n|4- Calcul and Export All Planet With EulerAsymetric\n \n|5-"
               " Calcul and Export Lune Path \n\n|6- Exit Program\n");
        scanf("%s",&optionChar);
        option=atoi(optionChar);
    }

    //Si l'utilisateur entre le chiffre 4 alors on sort du while et on arrete le programme
    while(option!=6)
    {
        if(option==1) {
            printf("Starting the configuration of the execution..\n");
            sleep(1.5);
            //On ouvre le calculMenu qui permet de demander les paramètres d'execution du calcul
            calculMenu();
        }
        if(option==2) {
            printf("Loading of the informations\n");
            sleep(1.5);
            informationMenu();
        }
        if(option==3) {
            sleep(1.5);
            energeticMenu();
        }
        if(option==4){
            globalCalcul("../website/json/exportedPath.json",2,1);

        }
        if(option==5){

            //Calcul de la trajectoire de la Terre
            Planet* earth = initPlanet("earth",WEIGHT_EARTH,PERI_EARTH,ECCENTRICITY_EARTH,HALF_AXIS_EARTH);
            EulerAsymetricMethod(earth,20000,SOLEIL_WEIGHT);

            //Calcul de la trajectoire de la Lune puis exportation dans un JSON
            Planet* lune = initLune();
            calculLune(earth,lune);
            emptyFile("../website/json/lune.json");
            exportation("../website/json/lune.json",lune,"eulerasymetric",true,true);

            deletePlanet(&lune);
            deletePlanet(&earth);
        }
        //Tout ce bloc "repeté" permet qu'après avoir executé un autre menu on retourne dans le menu principal
        //Et on peut continuer à faire ce que l'on veut

        printf("Back to the Main Menu\n");
        sleep(1);
        system("clear");
        printf("----------------------------------------------------\n");
        printf("|   Welcome to the Main Menu of this application    |\n");
        printf("----------------------------------------------------\n");
        printf("\n|1- Personalize the calcul and exportation\n \n|2- Read Informations about Planets\n \n|3- Energetic Verification\n \n|4- Calcul and Export All Planet With EulerAsymetric\n \n|5-"
               " Calcul and Export Lune Path \n\n|6- Exit Program\n");

        //Saisie utilisateur
        scanf("%s",&optionChar);
        option=atoi(optionChar);

        //Vérification des saisies utilisateurs
        while(option>6 || option<1)
        {
            printf("Invalid Option !\n");
            printf("\n|1- Set Up the calcul and exportation\n \n|2- Read Informations\n \n|3- Energetic Verification\n \n|4- Calcul and Export All Planet With EulerAsymetric\n \n|5-"
                   " Calcul and Export Lune Path \n\n|6- Exit Program\n");
            scanf("%s",&optionChar);
            option=atoi(optionChar);
        }
    }

    //Arret du programe
    printf("Closing the program...\n");
    sleep(1.5);
    printf("Program closed\n");
}

//-----------------Fonction calculMenu--------------------//
void calculMenu(){
    system("clear");

    //On alloue la mémoire pour une chaine de caractère ne pouvant exéder 50 caractères
    char* nameFile = malloc(50*sizeof(char));

    printf("---------------------------------------------\n");
    printf("|   Programming phase of your calculation    |\n");
    printf("---------------------------------------------\n");
    printf("| Now you have to choose the location and the name of the file you are going to export.\n");
    printf("| If you enter the word 'default', then your export will take place in the default file "
           "'../website/json/exportedPath.json'.\n");
    printf("| Be careful, the path must not exceed 50 characters !\n");
    scanf("%s",nameFile);

    //Ici on vérifie si l'utilisateur souhaite utiliser le chemin par defaut, si oui alors on change le nom de nameFile
    //avec le nom par default (chemin vers le dossier JSON de notre projet web)
    if(strcmp(nameFile,"default")==0) {
        nameFile = useDefaultPath(nameFile);
    }
    //On lance ici deux menus afin d'obtenir les paramètres d'execution du calcul
    int optionMethod = chooseOptionMethod();
    int optionExecution = chooseOptionForPlanet();

    //Lancement du calcul avec les paramètres utilisateurs
    globalCalcul(nameFile,optionMethod,optionExecution);
    free(nameFile);
}

//------------------------Fonction Information Menu-----------------------------//
void informationMenu(){
    char optionChar[3];
    int option;
    system("clear");

    //Présentation
    printf(" --------------------------------------\n");
    printf("|   Welcome to the information menu    |\n");
    printf(" --------------------------------------\n");
    printf("\nWhich Informations do you want to see ?\n");
    printf("\n|1- Planet's weight\n \n|2- Planet's périhélion\n \n|3- Planet's eccentricity\n \n4| Planet's "
           "half axis\n \n5| Back to the Main Menu\n");

    //Saisie utilisateur
    scanf("%s",&optionChar);
    option=atoi(optionChar);

    //Vérification des saisies utilisateurs
    while(option>5 || option<1)
    {
        printf("Invalid Option !\n");
        printf("\nWhich Informations do you want to see ?\n");
        printf("\n|1- Planet's weight\n \n|2- Planet's périhélion\n \n|3- Planet's eccentricity\n \n4| Planet's "
               "half axis\n \n5| Back to the Main Menu\n");
        scanf("%s",&optionChar);
        option=atoi(optionChar);
    }

    //Ici on lance simplement une fonction d'affichage qui permet de voir les infos des planètes
    //On appelle également une fonction "confirmToContinue" pour que l'utilisateur ai le temps de voir les informations
    while(option!=5) {
        switch (option) {
            case 1:
                system("clear");
                printPlanetWeight();
                confirmToContinue();
                break;
            case 2:
                system("clear");
                printPlanetPerihelie();
                confirmToContinue();
                break;
            case 3:
                system("clear");
                printPlanetEccentricity();
                confirmToContinue();
                break;
            case 4:
                system("clear");
                printPlanetHalfAxis();
                confirmToContinue();
                break;
        }

        //Répetitions du menu afin de pouvoir l'utiliser tant que l'on veut
        //L'utilisateur doit saisir 5 pour quitter le menu
        system("clear");
        printf(" --------------------------------------\n");
        printf("|   Welcome to the information menu    |\n");
        printf(" --------------------------------------\n");
        printf("\nWhich Informations do you want to see ?\n");
        printf("\n|1- Planet's weight\n \n|2- Planet's périhélion\n \n|3- Planet's eccentricity\n \n4| Planet's "
               "half axis\n \n5| Back to the Main Menu\n");
        scanf("%s",&optionChar);
        option=atoi(optionChar);
        while(option>5 || option<1)
        {
            printf("Invalid Option !\n");
            printf("\nWhich Informations do you want to see ?\n");
            printf("\n|1- Planet's weight\n \n|2- Planet's périhélion\n \n|3- Planet's eccentricity\n \n4| Planet's "
                   "half axis\n \n5| Back to the Main Menu\n");
            scanf("%s",&optionChar);
            option=atoi(optionChar);
        }
    }
}

//------------------Fonction Energetic menu----------------------//
void energeticMenu(){
    char optionMethodChar[3];
    int optionMethod;

    //Présentation
    system("clear");
    printf(" ---------------------------------------------\n");
    printf("|   Programming the Energetic Verification    |\n");
    printf(" ---------------------------------------------\n");
    printf("First, we will calculate the trajectory of all the planets of the solar system.\n");
    printf("Please choose the method used for the calculation\n");
    printf("Contrary to the custom calculation, we will calculate here only the trajectory according to the \"Planet - Sun\" interaction\n");
    printf("\n|1- EulerMethod\n \n|2- EulerMethodAsymetric\n");

    //Saisies utilisateurs
    scanf("%s",&optionMethodChar);
    optionMethod=atoi(optionMethodChar);

    //Vérification des saisies utilisateurs
    while(optionMethod>2 || optionMethod<1)
    {
        printf("Invalid Option !\n");
        printf("\n|1- EulerMethod\n \n|2- EulerMethodAsymetric\n");
        scanf("%s",&optionMethodChar);
        optionMethod=atoi(optionMethodChar);
    }

    //Explication du fonctionnement du calcul
    system("clear");
    printf(" ---------------------------------------------\n");
    printf("|   Programming the Energetic Verification    |\n");
    printf(" ---------------------------------------------\n");
    printf("\n| French Explication | \n");
    printf("-------------------------\n");
    printf("Le programme calcule pour chaque point l'energie mecanique de \n"
           "la planète et vérifie si l'energie mécanique entre deux points qui se suivent est assez proche.\n"
           "De cette façon, on vérifie si la variation d'energie n'est pas trop haute.\nLe programme renvoi le pourcentage moyen"
           "d'écart entre deux energies mécanique qui se suivent\n");
    printf("\n| English Explication |\n");
    printf("-------------------------\n");
    printf("The program calculates for each point the mechanical energy of the \n"
           "planet and checks if the mechanical energy between two points that follow each other is close enough. \n"
           "In this way it is checked if the energy variation is not too high.\nThe program returns the average percentage "
           "difference between two consecutive mechanical energies\n");

    //Appel à la fonction confirmToContinue afin de laisser le temps souhaité à l'utilisateur
    confirmToContinue();

    //Lancement du calcul
    verificationOfAllPlanet(optionMethod);
    confirmToContinue();

}

//------------------------------------------------------------------------//


//------------------------------------------------------------------------//
/* Fonctions d'affichages */

//-----------Ces fonctions ne font pas l'objet de commentaire dans la mesure ou c'est seulement de l'affichage--------//

void printPlanetWeight(){
    printf(" -----------------------------------------\n");
    printf("|   FIND THE PLANET'S WEIGHT HEREUNDER    |\n");
    printf(" -----------------------------------------\n");
    printf("\nOur solar system consists of 8 major planets, below you can find the weight of each of them\n");
    printf("1- Mercury : %e kg\n",WEIGHT_MERCURY);
    printf("2- Venus   : %e kg\n",WEIGHT_VENUS);
    printf("3- Earth   : %e kg\n",WEIGHT_EARTH);
    printf("4- Mars    : %e kg\n",WEIGHT_MARS);
    printf("5- Jupiter : %e kg\n",WEIGHT_JUPITER);
    printf("6- Saturn  : %e kg\n",WEIGHT_SATURN);
    printf("7- Uranus  : %e kg\n",WEIGHT_URANUS);
    printf("8- Neptune : %e kg\n",WEIGHT_NEPTUNE);
}

void printPlanetPerihelie(){
    printf(" --------------------------------------------\n");
    printf("|   FIND THE PLANET'S PERIHELION HEREUNDER    |\n");
    printf(" --------------------------------------------\n");
    printf("\nOur solar system consists of 8 major planets, below you can find the perihelion of each of them\n");
    printf("\nFor those who don't know, the perihelion is the closest distance between the sun and the planet on its trajectory\n");
    printf("1- Mercury : %e m\n",PERI_MERCURY);
    printf("2- Venus   : %e m\n",PERI_VENUS);
    printf("3- Earth   : %e m\n",PERI_EARTH);
    printf("4- Mars    : %e m\n",PERI_MARS);
    printf("5- Jupiter : %e m\n",PERI_JUPITER);
    printf("6- Saturn  : %e m\n",PERI_SATURN);
    printf("7- Uranus  : %e m\n",PERI_URANUS);
    printf("8- Neptune : %e m\n",PERI_NEPTUNE);
}

void printPlanetHalfAxis(){
    printf(" --------------------------------------------\n");
    printf("|   FIND THE PLANET'S HALF AXIS HEREUNDER    |\n");
    printf(" --------------------------------------------\n");
    printf("\nOur solar system consists of 8 major planets, below you can find the half axis of each of them\n");
    printf("1- Mercury : %e m\n",HALF_AXIS_MERCURY);
    printf("2- Venus   : %e m\n",HALF_AXIS_VENUS);
    printf("3- Earth   : %e m\n",HALF_AXIS_EARTH);
    printf("4- Mars    : %e m\n",HALF_AXIS_MARS);
    printf("5- Jupiter : %e m\n",HALF_AXIS_JUPITER);
    printf("6- Saturn  : %e m\n",HALF_AXIS_SATURN);
    printf("7- Uranus  : %e m\n",HALF_AXIS_URANUS);
    printf("8- Neptune : %e m\n",HALF_AXIS_NEPTUNE);
}

void printPlanetEccentricity(){
    printf(" -----------------------------------------------\n");
    printf("|   FIND THE PLANET'S ECCENTRICITY HEREUNDER    |\n");
    printf(" -----------------------------------------------\n");
    printf("\nOur solar system consists of 8 major planets, below you can find the eccentricity of each of them\n");
    printf("1- Mercury : %e\n",ECCENTRICITY_MERCURY);
    printf("2- Venus   : %e\n",ECCENTRICITY_VENUS);
    printf("3- Earth   : %e\n",ECCENTRICITY_EARTH);
    printf("4- Mars    : %e\n",ECCENTRICITY_MARS);
    printf("5- Jupiter : %e\n",ECCENTRICITY_JUPITER);
    printf("6- Saturn  : %e\n",ECCENTRICITY_SATURN);
    printf("7- Uranus  : %e\n",ECCENTRICITY_URANUS);
    printf("8- Neptune : %e\n",ECCENTRICITY_NEPTUNE);
}

void  confirmToContinue(){
    char var[5];
    printf(" \n---------------------------\n");
    printf("|   Enter a key to Continue |\n");
    printf(" ---------------------------\n");
    scanf("%s",var);
}

//------------------------------------------------------------------------//

//------------------------------------------------------------------------//
/* Fonctions auxiliaire */

char* useDefaultPath(char* nameFile){
    strcpy(nameFile,"../website/json/exportedPath.json");
    return nameFile;
}

int chooseOptionForPlanet(){
    system("clear");
    printf("---------------------------------------------\n");
    printf("|   Programming phase of your calculation    |\n");
    printf("---------------------------------------------\n");
    printf("| Now it's time to choose the planets whose trajectory you want to calculate\n");
    printf("| You can choose between :\n");
    printf("1- Calculate the trajectories of all the planets\n");
    printf("2- Choose by hand the planets \n");
    char optionChar[3];
    int option;

    //Saisies utilisateur
    scanf("%s",&optionChar);
    option=atoi(optionChar);

    //Vérification des saisies utilisateurs
    while(option>2 || option<1)
    {
        printf("1- Calculate the trajectories of all the planets\n");
        printf("2- Choose by hand the planets \n");
        scanf("%s",&optionChar);
        option=atoi(optionChar);
    }
    return option;
}

int chooseOptionMethod(){
    system("clear");
    printf("---------------------------------------------\n");
    printf("|   Programming phase of your calculation    |\n");
    printf("---------------------------------------------\n");
    printf("| Please choose a method of trajectory calculation, you can choose between :\n");
    printf("1-  Euler Method\n");
    printf("2- EulerAsymetric Method\n");

    //Saisie utilisateur
    char optionChar[3];
    int option;
    scanf("%s",&optionChar);
    option=atoi(optionChar);

    //Vérification des saisies utilisateurs
    while(option>2 || option<1)
    {
        printf("Invalid Option\n");
        printf("1- Euler Method\n");
        printf("2- EulerAsymetric Method\n");
        scanf("%s",&optionChar);
        option=atoi(optionChar);
    }
    return option;
}
//------------------------------------------------------------------------//
