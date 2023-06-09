//Importation et exportation des modules nécéssaire aux fonctions.
//On importe également le fichier JSON afin de l'exploiter
import exportFile from "../json/exportedPath.json" assert {type:"json"};
import lune from "../json/lune.json" assert {type:"json"};
export {drawPath,getRevolutionTime};
import {getScale} from "./canvas.js";

//Fonction getRevolutionTime --> permet de stocker à un endroit les temps de révolution, on utilise ce temps afin d'afficher un seul 
//tour autour du soleil.
function getRevolutionTime(planetName){
    if(planetName=="mercury"){
        return 975;
    }
    if(planetName=="venus"){
        return 2350;
    }
    if(planetName=="earth"){
        return 3700;
    }
    if(planetName=="mars"){
        return 6900;
    }
    if(planetName=="jupiter"){
        return 43900;
    }
    if(planetName=="saturn"){
        return 110000;
    }
    if(planetName=="uranus"){
        return 306650;
    }
    if(planetName=="neptune"){
        return 602300;
    }
}


//Fonction drawPath --> Cette fonction permet de dessiner la trajectoire d'une planète en ayant le context de dessin, la couleur de la 
//trajectoire, la taille de la planète, la méthode de calcul et la période de revolution
function drawPath(context, color, size, method, planet, sizeTime){
    if(planet=="lune"){
        context.save();
        context.beginPath();
        //On récupère l'echelle du dessin
            let scaleMap = getScale();
            let scale;
            if(scaleMap%2==1){

                scale = 800000000;
            }
            else{
 
                scale = 18000000000;
            }

            context.translate(350, 350);

            context.moveTo(lune[planet+"-"+method][0][0][0]/scale,lune[planet+"-"+method][0][0][1]/scale);

            for(let i=1 ; i <sizeTime;i++){
                context.lineTo((lune[planet+"-"+method][i][0][0])/scale,(lune[planet+"-"+method][i][0][1])/scale); 
            }
            context.strokeStyle =color;
            context.lineWidth = 2+size;

        context.stroke();
    context.restore();
    }
    else{
    context.save();
        context.beginPath();
        //On récupère l'echelle du dessin
            let scaleMap = getScale();
            let scale;
            //On rappelle que si getScale() renvoi un nombre pair, on est dans le cas d'une grande echelle (affichage des grandes planètes)
            if(scaleMap%2==1){
                //On met une echelle de 800 000 000 pour le cas des petites planètes
                scale = 800000000;
            }
            else{
                //On met une echelle de 18 000 000 000 pour le cas des grandes planètes
                scale = 17000000000;
            }

            //On se déplace au centre du canvas (au niveau du soleil)
            context.translate(350, 350);

            //Ensuite on deplace notre curseur au niveau du premier point de la trajectoire
            context.moveTo(exportFile[planet+"-"+method][0][0][0]/scale,exportFile[planet+"-"+method][0][0][1]/scale);

            //Ensuite il on se déplace point par point jusqu'a sa période de révolution
            //(En sachant qu'il a fallu faire des test afin de trouver cette periode de revolution)
            for(let i=1 ; i <sizeTime;i++){
                context.lineTo((exportFile[planet+"-"+method][i][0][0])/scale,(exportFile[planet+"-"+method][i][0][1])/scale); 
            }
            context.strokeStyle =color;

            //On écrit 2+size pour pouvoir éffacer la trajectoire, en effet on appelle la fonction avec size =0 afin de faire une trajectoire de 2px
            // et on appelle la fonction avec size = 1 afin de pouvoir effacer la trajectoire (dessine par dessus en plus épais de 1px)
            context.lineWidth = 2+size;

        context.stroke();
    context.restore();
        }
}

