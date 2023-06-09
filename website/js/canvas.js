//Importation des différents modules JavaScript et exportation des fonctions
import {getRevolutionTime} from "./drawPlanet.js";
import {listenerCanvasMenu} from "./listener.js";
export {getScale, changeScale, startFunction, createSun,createRectangle,removeFunction};
import {offButton} from "../jsMooving/canvasForMooving.js"

//Initialisation d'une variable globale, celle-ci stocke le choix de l'utilisateur dans le processus suivant : 
// A chaque fois que l'utilsateur change d'echelle, la variable est incrémenter par une fonction
//Ainsi lorsque la variable est impair, on utilise la petite echelle, et lorsque la variable est pair on utilise la grande echelle
let scale =1;

//Déclaration des variables globales portant sur la période de révolution des planètes

let mercuryTime = getRevolutionTime("mercury");
let venusTime = getRevolutionTime("venus");
let earthTime = getRevolutionTime("earth");
let marsTime = getRevolutionTime("mars");
let jupiterTime = getRevolutionTime("jupiter");
let saturnTime = getRevolutionTime("saturn");
let uranusTime = getRevolutionTime("uranus");
let neptuneTime = getRevolutionTime("neptune");


//Fonction startFunction qui est lancé si l'utilisateur clique sur le bouton Start
function startFunction(){

    //Récupération du context
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    //On clear le rectangle de dessin
    context.clearRect(0,0,700,700);

    //On peut potentiellement mettre un fond si on décommente
    //canvas.style.backgroundImage = "url(./images/galaxie.jpeg)";

    //On crée un soleil au centre qui prend en compte l'echelle de l'utilisateur
    createSun(context,scale);
    offButton();
}

//Fonction switchScale qui permet simplement d'incrémenter la variable globale "scale"
function switchScale(){
    scale++;
}

//Fonction changeScale qui est lancé des que l'utilisateur clique sur le bouton ScaleChanger

function changeScale(){

    //Récupération du context canvas
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    //Incrémentation de la variable globale Scale
    switchScale();

    //On redéssine un le fond noir et récupère un tableau (renvoyé par listenerCanvasMenu), ce tableau contient des chiffres (0,1) 
    //0 Si la trajectoire de la planète est dessinée 0 sinon
    createRectangle(context,0,0,700,700,50);
    let tablisteners = listenerCanvasMenu(context);

    //A voir si on change l'echelle, mais pour l'instant, ca clear seulement, peut être rajouté l'option qui décoche les checkbox
    //redrawOldMap(context,tablisteners);
    createSun(context,scale);
    offButton();
}

//Fonction removeFunction qui est lancé lorsque l'utilsateur clique sur Reset
function removeFunction(){
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    //On crée simplement un rectangle noir sur le canvas à l'aide de la fonction createRectangle
    createRectangle(context,0,0,700,700,100);
    offButton(context);
}


function effacerSoleil(context){
    context.save();
        context.beginPath();
            //Afin d'effacer le soleil, on crée un soleil noir un peu plus gros que le classique.
            //La encore, cela pose problème si une planète est trop proche du soleil, cependant ce n'est pas censé arriver.
            context.arc(350, 350, 28, 0, 2*Math.PI);
            context.fillStyle = "black";
        context.closePath();
        context.fill();
    context.restore();
}

function createSun(context, scale){
    // On efface le soleil pour une simple raison :
    // - Si on veut faire un soleil plus petit que l'ancien, alors on ne va pas le voir car il sera plus petit et de même couleur
    //   Cela pose donc un probleme dans notre affichage de changement d'echelle
    effacerSoleil(context);
    context.save();
        context.beginPath();
            //Ici on vérifie la variable scale afin de savoir si on dessine un petit soleil ou un grand
            if(scale%2==1){
                context.arc(350, 350, 27, 0, 2*Math.PI);
            }
            else{
                context.arc(350, 350, 13, 0, 2*Math.PI);
            }
            context.fillStyle = "yellow";
            context.closePath();
        context.fill();
    context.restore();
}

function createRectangle(context, x, y, width, height,radius)
{
    //Fonction qui crée un rectangle et rempli l'intérieur
    context.save();
        context.beginPath();
            let start = x + width ;
            let control = y+ height;
            context.moveTo(x,y);
            context.lineTo(start,y);
            context.lineTo(start,y+height);
            context.lineTo(x , control);
            context.lineTo(x,y+radius);
            context.fill();
            context.stroke();
            context.fillStyle = "black";
        context.closePath();
    context.restore();
} 

//Retourne l'echelle stockée en variable globale.
function getScale(){
    return scale;
}

