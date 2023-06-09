//Importation des différents modules JavaScript utile à nos fonctions de listener.js
import {drawPath} from "./drawPlanet.js";
import {getScale} from "./canvas.js";
import {getRevolutionTime} from "./drawPlanet.js";
//Exportation de la fonction listenerCanvasMenu utile aux autres modules.
export{listenerCanvasMenu};

//----------Déclaration de variables globales que l'on souhaite récupérer dans plusieurs fonctions sans devoir les réecrire---------//

//Déclaration des variables concernant la taille des planètes lors de l'affichage
let mercureSize = 4;
let earthSize = 7;
let venusSize = 5.5;
let marsSize = 8;
let jupiterSize = 14;
let saturnSize = 11;
let uranusSize = 11;
let neptuneSize = 11;

//Déclaration des variables concernant la couleur des planètes lors de l'affichage de celles-cis (trajectoire)
let saturnColor = "white";
let uranusColor ="orange";
let mercureColor = "white";
let marsColor = "red";
let jupiterColor = "blue";
let earthColor = "blue";
let venusColor = "yellow";
let neptuneColor = "green";

//Déclaration des variables "planete_P" qui servent à savoir si la checkBox dans la page HTML est activée ou pas
let mercury_P = 0;
let venus_P   = 0;
let earth_P   = 0;
let mars_P    = 0;
let jupiter_P = 0;
let saturn_P  = 0;
let uranus_P  = 0;
let neptune_P = 0;

//Déclaration des variables "planetesTime" afin de récupérer leurs temps de révolution, on récupère ces valeurs à l'aide de la fonction 
//getRevolutionTime, on peut donc changer sa période de révolution en changeant les données renvoyées par cette fonction
//getRevolution --> (codé dans drawPlanet.js)
let mercuryTime = getRevolutionTime("mercury");
let venusTime = getRevolutionTime("venus");
let earthTime = getRevolutionTime("earth");
let marsTime = getRevolutionTime("mars");
let jupiterTime = getRevolutionTime("jupiter");
let saturnTime = getRevolutionTime("saturn");
let uranusTime = getRevolutionTime("uranus");
let neptuneTime = getRevolutionTime("neptune");


//-------------------------Fonction listenerCanvasMenu qui s'occupe de récupérer les données des checkBox---------------------------------/
function listenerCanvasMenu(context){

    //Nous allons ici commenter le premier bloc, cependant il est répeté 8 fois pour les 8 checkBox

    //----------------Mercury -----------------//

    //Récupération de l'echelle via la fonction getScale(), le fonctionnement de cette fonction est expliqué dans le fichier canvas.js
    let scale = getScale();

    //On récupère les informations du checkBox de la planète en question
    let mercuryPath = document.querySelector("input[name=mercury_path]");

    //On ajoute un listener qui capte les changements de position de la checkBox, à cela on lui attribue une fonction à l'aide de "=>""
    mercuryPath.addEventListener("change", (button) => {

    //On vérifie ensuite si le bouton est en position check ou non check
    if (button.target.checked) {

        //En position check, on va vérifier que l'echelle est celle adaptée à la planète en question
        //Si c'est impair alors on est dans le cas d'affichage des petites planètes, sinon les grandes.
        scale = getScale();
        if(scale%2==1){

            //Si on est dans le bon cas d'utilisation, alors on affecte 1 à la variable "planete_P" et on trace le chemin de la planète
            mercury_P = 1;
            drawPath(context,mercureColor,0,"eulerasymetric","mercury",mercuryTime);
        }
    } else {
        scale = getScale();
        if(scale%2==1){
            
            //Si on est dans le bon cas d'utilisation mais que le bouton est non check, alors on dessine une trajectoire plus grosse et noir 
            //afin de recouvrir celle deja tracée.
            //Le problème de cette méthode, c'est que si deux trajectoires sont trop proche, alors cela va cacher l'autre aussi
            mercury_P=0;
            drawPath(context,"black",3,"eulerasymetric","mercury",mercuryTime);   
        }
    }
    });

    //On répète cette verification des checkBox sur toutes les planètes.
    
    //-------------Earth ----------------//
    let earthPath = document.querySelector("input[name=earth_path]");
    earthPath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==1){
            earth_P = 1;
            drawPath(context,"blue",0,"eulerasymetric","earth",earthTime);
        }
    } else {
        scale = getScale();
        if(scale%2==1){
            earth_P = 0;
            drawPath(context,"black",3,"eulerasymetric","earth",earthTime);
        }
    }
    });
    //-------------Venus ----------------//
    let venusPath = document.querySelector("input[name=venus_path]");
    venusPath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==1){
            venus_P = 1;
            drawPath(context,"yellow",0,"eulerasymetric","venus",venusTime);
        }
    } else {
        scale = getScale();
        if(scale%2==1){
            venus_P = 0;
            drawPath(context,"black",3,"eulerasymetric","venus",venusTime);
        }
    }
    });
    //--------------Mars ----------------//
    let marsPath = document.querySelector("input[name=mars_path]");
    marsPath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==1){
        mars_P = 1;
        drawPath(context,"red",0,"eulerasymetric","mars",marsTime);
        }
    } else {
        scale = getScale();
        if(scale%2==1){
            mars_P = 0;
            drawPath(context,"black",3,"eulerasymetric","mars",marsTime);
        }
    }
    });
    //---------------Jupiter----------------//
    let jupiterPath = document.querySelector("input[name=jupiter_path]");

    jupiterPath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==0){
        jupiter_P=1;
        drawPath(context,"blue",0,"eulerasymetric","jupiter",jupiterTime);
        }
    } else {
        scale = getScale();
        if(scale%2==0){
        jupiter_P=0;
        drawPath(context,"black",3,"eulerasymetric","jupiter",jupiterTime);
        }
    }
    });
    //-------------Saturn---------------//
    let saturnPath = document.querySelector("input[name=saturn_path]");
    saturnPath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==0){
        saturn_P=1;
        drawPath(context,"white",0,"eulerasymetric","saturn",saturnTime);
        }
    } else {
        scale = getScale();
        if(scale%2==0){
        saturn_P=0;
        drawPath(context,"black",3,"eulerasymetric","saturn",saturnTime);
        }
    }
    });
    //---------------Uranus--------------//
    let uranusPath = document.querySelector("input[name=uranus_path]");
    uranusPath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==0){
        uranus_P=1;
        drawPath(context,"orange",0,"eulerasymetric","uranus",uranusTime);
        }
    } else {
        scale = getScale();
        if(scale%2==0){
        uranus_P=0;
        drawPath(context,"black",3,"eulerasymetric","uranus",uranusTime);
        }
    }
    });
    //----------------Neptune--------------//
    let neptunePath = document.querySelector("input[name=neptune_path]");
    neptunePath.addEventListener("change", (button) => {
    if (button.target.checked) {
        scale = getScale();
        if(scale%2==0){
        neptune_P=1;
        drawPath(context,"white",0,"eulerasymetric","neptune",neptuneTime);
        }
    } else {
        scale = getScale();
        if(scale%2==0){
        neptune_P=0;
        drawPath(context,"black",3,"eulerasymetric","neptune",neptuneTime);
        }
    }
    });

    //Pour finir on renvoi un tableau contenant la valeur de "planete_P", celle-ci va servir aux autres fonctions pour savoir si le bouton checkbox
    //est en position check ou no-check
    return [mercury_P,venus_P,earth_P,mars_P,jupiter_P,saturn_P,uranus_P,neptune_P];
}