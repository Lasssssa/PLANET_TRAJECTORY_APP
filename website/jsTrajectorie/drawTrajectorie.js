//Importation et exportation des modules nécéssaire aux fonctions.
//On importe également le fichier JSON afin de l'exploiter
import exportFileAsymetric from "../json/exportedPath.json" assert {type:"json"};
import exportFileEuler from "../json/exportedPathEuler.json" assert {type:"json"};
//Fonction getRevolutionTime --> permet de stocker à un endroit les temps de révolution, on utilise ce temps afin d'afficher un seul 
//tour autour du soleil.

let canvas = document.getElementById("main");
let context = canvas.getContext("2d");
let method = "euler";


function listener(context){
    //Fonction qui initialise des listeners  qui ecoute les boutons
    //Ils servent à changer la methode de dessin 
    let buttonEuler = document.getElementById("euler");
    buttonEuler.addEventListener("click", (button) => {
        method="euler";
    });

    let buttonEulerasymetric = document.getElementById("eulerasymetric");
    buttonEulerasymetric.addEventListener("click", (button) => {
        method ="eulerasymetric";
    });

}
//Fonction de callBack sur les boutons de la page HTML
function pathMercury(){
    drawPath(context,"grey",method,"mercury",800000000);
}
function pathVenus(){

    drawPath(context,"pink",method,"venus",800000000);
}
function pathEarth(){
    
    drawPath(context,"blue",method,"earth",800000000);
}
function pathMars(){

    drawPath(context,"red",method,"mars",800000000);
}
function pathJupiter(){

    drawPath(context,"yellow",method,"jupiter",18000000000);
}
function pathSaturn(){

    drawPath(context,"brown",method,"saturn",18000000000);
}
function pathUranus(){

    drawPath(context,"cyan",method,"uranus",18000000000);
}
function pathNeptune(){

    drawPath(context,"blue",method,"neptune",18000000000);
}

//Permet de redessiner le canvas avec un fond blanc
function clearZone(context){
    context.save();
        context.beginPath();
            context.moveTo(0,0);
            context.lineTo(850,0);
            context.lineTo(850,850);
            context.lineTo(0 , 850);
            context.lineTo(0,0);
            context.fillStyle = "white";
            context.fill();
        context.closePath();
    context.restore();
}
//Fonction drawPath --> Cette fonction permet de dessiner la trajectoire d'une planète en ayant le context de dessin, la couleur de la 
//trajectoire, la taille de la planète, la méthode de calcul et la période de revolution
function drawPath(context, color, method, planet,scale){

    //Permet de redraw le fond à chaque fois
    clearZone(context);
    createSun();
    let option = 0
    if(method=="eulerasymetric"){
        option = 1;
    }else{
        option = 2;
    }

    
    if(option==1){
        context.save();
        context.beginPath();

            //On se déplace au centre du canvas (au niveau du soleil)
            context.translate(425.5, 312.5);

            //Ensuite on deplace notre curseur au niveau du premier point de la trajectoire
            
            context.moveTo((exportFileAsymetric[planet+"-"+method][0][0][0])/scale,(exportFileAsymetric[planet+"-"+method][0][0][1])/scale);

            //Ensuite il on se déplace point par point jusqu'a sa période de révolution
            //(En sachant qu'il a fallu faire des test afin de trouver cette periode de revolution)
            for(let i=1 ; i <(exportFileAsymetric[planet+"-"+method].length) ;i++){

                context.lineTo((exportFileAsymetric[planet+"-"+method][i][0][0])/scale,(exportFileAsymetric[planet+"-"+method][i][0][1])/scale); 
            }
            context.strokeStyle =color;

        
        context.lineWidth = 2;
        context.stroke();
        context.closePath();
        
    context.restore();
    }else{
        context.save();
        context.beginPath();

            //On se déplace au centre du canvas (au niveau du soleil)
            context.translate(425.5, 312.5);

            //Ensuite on deplace notre curseur au niveau du premier point de la trajectoire
            
            context.moveTo((exportFileEuler[planet+"-"+method][0][0][0])/scale,(exportFileEuler[planet+"-"+method][0][0][1])/scale);

            //Ensuite il on se déplace point par point jusqu'a sa période de révolution
            //(En sachant qu'il a fallu faire des test afin de trouver cette periode de revolution)
            for(let i=1 ; i <(exportFileEuler[planet+"-"+method].length) ;i++){

                context.lineTo((exportFileEuler[planet+"-"+method][i][0][0])/scale,(exportFileEuler[planet+"-"+method][i][0][1])/scale); 
            }
            context.strokeStyle =color;

        
        context.lineWidth = 2;
        context.stroke();
        context.closePath();
        
    context.restore();
    }
    
    
    
}
function createSun(){
    context.save();
    context.beginPath();
        context.arc(425, 312.5, 15, 0, 2*Math.PI);
        context.fillStyle = "yellow";
        context.closePath();
    context.fill();
context.restore();
}

export {pathMercury,pathVenus,pathEarth,pathMars,pathJupiter,pathSaturn,pathUranus,pathNeptune,listener,drawPath};