export {drawPlanet};
import exportFile from "../json/exportedPath.json" assert {type:"json"};
import lune from "../json/lune.json" assert {type:"json"};
import {createSun,getScale} from "./canvasForMooving.js";
import {getRevolutionTime} from "../js/drawPlanet.js";

//Fonction qui renvoi la période de révolution

function drawPath(context, color, size, method, planet, sizeTime){
    if(planet=="lune"){
        context.save();
        context.beginPath();
        //On récupère l'echelle du dessin
            let scale = 800000000;

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

//Cette fonction nous sert dans la fonction drawPlanet, le but de cette fonction est d'éffacer la planète dessiner avant afin de créer 
//un effet de mouvement, si on ne l'efface pas, cela va simplement faire un gros trait de la largeur de la planète
function deleteOldPlanet(context,oldX,oldY, planetSize){
    context.save();
        context.beginPath();
        context.translate(350,350);
        //On dessine une planète noir à la place de l'ancienne planète (On récupère les coordonées au préalable)
        context.arc(oldX,oldY,planetSize,0,2*Math.PI);
        context.fillStyle = "black";
        context.closePath();
        context.fill();
    context.restore();
}

function drawPlanet(context ,x, y, planetSize, color, oldX, oldY,planet){
    //On récupère l'echelle actuelle choisis par l'utilisateur
    let scaleMap = getScale();
    //On crée un soleil au centre à la taille de l'echelle
    createSun(context,scaleMap);
    
    //On efface la planète au coordonées précédente placé en paramètre
    deleteOldPlanet(context,oldX,oldY,planetSize+1);
    let scale = 1;
    //Ici on vérifie l'echelle, si c'est la grande echelle alors on doit diviser la taille par 2 des planètes car le soleil est également
    //divisé par 2

    drawPath(context,color,0,"eulerasymetric",planet,getRevolutionTime(planet),scaleMap);
    console.log("coucou");
    if(scaleMap%2==0)
    {
        //Cela permet de pouvoir diviser la taille des planètes en deux
        scale=2;
    }
    
    context.save();
        context.beginPath();
        context.translate(350,350);

        //On trace un cerlce que l'on rempli afin de crée une planète
        context.arc(x,y,planetSize/scale,0,2*Math.PI);
        
        context.fillStyle = color;
        context.closePath();
        context.fill();
    context.restore();
    
}
