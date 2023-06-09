//Importation des différents modules nécéssaire ainsi que le fichier JSON
import exportFile from "../json/exportedPath.json" assert {type:"json"};
import lune from "../json/lune.json" assert {type :"json"};
import {changeScale, removeFunction, startFunction,getScale} from "./canvasForMooving.js";
import { getRevolutionTime } from "../js/drawPlanet.js";
import {drawPlanet} from "./drawPlanetMooving.js";
import {listenerCanvasMenu} from "./listenerMooving.js";


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

//Déclaration des variables qui stocke la période de révolution des planètes
let mercuryTime = getRevolutionTime("mercury");
let venusTime = getRevolutionTime("venus");
let earthTime = getRevolutionTime("earth");
let marsTime = getRevolutionTime("mars");
let jupiterTime = getRevolutionTime("jupiter");
let saturnTime = getRevolutionTime("saturn");
let uranusTime = getRevolutionTime("uranus");
let neptuneTime = getRevolutionTime("neptune");
let LuneTime = 5000;

//Déclaration de variables globales utile au mouvement des planètes : 
let countMercure =1;
let countEarth =1;
let countVenus =1;
let countMars =1;
let countJupiter =1;
let countSaturn =1;
let countUranus =1;
let countNeptune =1;
let countLune = 1;

//----------------------------Fonction Main que l'on applique une fois au début de programme----------------------------------------//

function main()
{
    //Ce main est le même que celui pour afficher les trajectoires, il déclare des listener sur les boutons start, stop et reset
    //Il initialise également une fonction qui écoute le menu canvas des planètes.
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    let buttonReset = document.getElementById("buttonReset");
    buttonReset.onclick = removeFunction;

    let buttonStart = document.getElementById("buttonStart");
    buttonStart.onclick = startFunction;

    let buttonChangeScale = document.getElementById("buttonChangeScale");
    buttonChangeScale.onclick = changeScale;

    let tabListener = listenerCanvasMenu(context);
}

main();


//------------------Fonction que l'on va appeler à l'aide de requestAnimationFrame afin de la tourner en boucle-------------------// 

function animate(){
    
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    //On initialise un tableau qui renvoi des valeurs (0 ou 1) qui dit si oui ou non les check box sont cochés

    let tab = listenerCanvasMenu(context);

    //On récupère ici l'echelle choisit par l'utilisateur
    let scaleMap = getScale();
    let scale;


    //Comme les autres fonctions, si scaleMap est pair, alors l'utilisateur utilise le mode "large Scale" et sinon on a une petite echelle
    //Cela va déterminer quelle planète peuvent être affichées ou non. (4 première en little scale...)
    if(scaleMap%2==1){
        scale = 800000000;

        //Ici on vérifie si l'utilisateur souhaite afficher la planète Mercure (0eme indice du tableau)
        if(tab[0]==1){

            //A l'aide de cette condition, on vérifie si la planète a fini son tour autour du soleil, si oui alors on remet 
            //notre variable à 1 afin de recommencer le chemin, de ce fait, la planète va tourner en boucle
            //Le probleme de cela, c'est qu'on sait que la trajectoire "s'ecarte" a cause de nos calculs or ici on aura toujours la même trajectoire

            if(countMercure==mercuryTime){
                countMercure=1;
            }
            
            //On récupère les coordonées actuelles de la planète, on récupère également les coordonées précédentes qui nous serviront dans la 
            //fonction drawPlanet (explication dans cette fonction --> drawPlanetMooving.js)
            let x1= (exportFile["mercury-eulerasymetric"][countMercure-1][0][0])/scale;
            let y1 = (exportFile["mercury-eulerasymetric"][countMercure-1][0][1])/scale;
            let x = (exportFile["mercury-eulerasymetric"][countMercure][0][0])/scale;
            let y = (exportFile["mercury-eulerasymetric"][countMercure][0][1])/scale;

            //On dessine la planète à ces coordonées et on incrémente la variable 
            drawPlanet(context,x,y,mercureSize,mercureColor,x1,y1,"mercury");
            countMercure++;
        }

        //Ensuite il en va de même pour les autres
        if(tab[1]==1){
            if(countVenus==venusTime){
                countVenus=1;
            }
            let x1 = (exportFile["venus-eulerasymetric"][countVenus-1][0][0])/scale;
            let y1 = (exportFile["venus-eulerasymetric"][countVenus-1][0][1])/scale;
            let x = (exportFile["venus-eulerasymetric"][countVenus][0][0])/scale;
            let y = (exportFile["venus-eulerasymetric"][countVenus][0][1])/scale;
            drawPlanet(context,x,y,venusSize,venusColor,x1,y1,"venus");
            countVenus++;
        }
        if(tab[2]==1){
            if(countEarth==earthTime){
                countEarth=1;
            }
            let x1= (exportFile["earth-eulerasymetric"][countEarth-1][0][0])/scale;
            let y1 = (exportFile["earth-eulerasymetric"][countEarth-1][0][1])/scale;
            let x = (exportFile["earth-eulerasymetric"][countEarth][0][0])/scale;
            let y = (exportFile["earth-eulerasymetric"][countEarth][0][1])/scale;
            drawPlanet(context,x,y,10,earthColor,x1,y1,"earth");
            countEarth++;

            if(LuneTime==countLune){
                countLune=1;
            }
            let x2= (lune["lune-eulerasymetric"][countEarth-1][0][0])/scale;
            let y2 = (lune["lune-eulerasymetric"][countEarth-1][0][1])/scale;
            let x3 = (lune["lune-eulerasymetric"][countEarth][0][0])/scale;
            let y3 = (lune["lune-eulerasymetric"][countEarth][0][1])/scale;
            drawPlanet(context,x3,y3,5,"white",x2,y2,"lune");
            countLune++;
        }
        if(tab[3]==1){
            if(countMars==marsTime){
                countMars=1;
            }
            let x1= (exportFile["mars-eulerasymetric"][countMars-1][0][0])/scale;
            let y1 = (exportFile["mars-eulerasymetric"][countMars-1][0][1])/scale;
            let x = (exportFile["mars-eulerasymetric"][countMars][0][0])/scale;
            let y = (exportFile["mars-eulerasymetric"][countMars][0][1])/scale;
            drawPlanet(context,x,y,marsSize,marsColor,x1,y1,"mars");
            countMars++;
        }
    }
    else{
        // On rentre dans cette partie du code si l'echelle est pair, ainsi on va effectuer le même principe mais avec une échelle différente
        scale = 17000000000;
        if(tab[4]==1){
            if(countJupiter==jupiterTime){
                countJupiter=1;
            }
            let x1= (exportFile["jupiter-eulerasymetric"][countJupiter-1][0][0])/scale;
            let y1 = (exportFile["jupiter-eulerasymetric"][countJupiter-1][0][1])/scale;
            let x = (exportFile["jupiter-eulerasymetric"][countJupiter][0][0])/scale;
            let y = (exportFile["jupiter-eulerasymetric"][countJupiter][0][1])/scale;
            drawPlanet(context,x,y,jupiterSize,jupiterColor,x1,y1,"jupiter");
            countJupiter+=100;
        }
        if(tab[5]==1){
            if(countSaturn==saturnTime){
                countSaturn=1;
            }
            let x1= (exportFile["saturn-eulerasymetric"][countSaturn-1][0][0])/scale;
            let y1 = (exportFile["saturn-eulerasymetric"][countSaturn-1][0][1])/scale;
            let x = (exportFile["saturn-eulerasymetric"][countSaturn][0][0])/scale;
            let y = (exportFile["saturn-eulerasymetric"][countSaturn][0][1])/scale;
            drawPlanet(context,x,y,saturnSize,saturnColor,x1,y1,"saturn");
            countSaturn+=100;
        }
        if(tab[6]==1){
            if(countUranus==uranusTime){
                countUranus=1;
            }
            let x1= (exportFile["uranus-eulerasymetric"][countUranus-1][0][0])/scale;
            let y1 = (exportFile["uranus-eulerasymetric"][countUranus-1][0][1])/scale;
            let x = (exportFile["uranus-eulerasymetric"][countUranus][0][0])/scale;
            let y = (exportFile["uranus-eulerasymetric"][countUranus][0][1])/scale;
            drawPlanet(context,x,y,uranusSize,uranusColor,x1,y1,"uranus");
            countUranus+=100;
        }
        if(tab[7]==1){
            if(countNeptune==neptuneTime){
                countNeptune=1;
            }
            let x1= (exportFile["neptune-eulerasymetric"][countNeptune-1][0][0])/scale;
            let y1 = (exportFile["neptune-eulerasymetric"][countNeptune-1][0][1])/scale;
            let x = (exportFile["neptune-eulerasymetric"][countNeptune][0][0])/scale;
            let y = (exportFile["neptune-eulerasymetric"][countNeptune][0][1])/scale;
            drawPlanet(context,x,y,neptuneSize,neptuneColor,x1,y1,"neptune");
            countNeptune+=100;
        }
    }
    
    
    //Callback de la fonction à l'aide de requestAnimationFrame
    requestAnimationFrame(animate);
}
requestAnimationFrame(animate);

