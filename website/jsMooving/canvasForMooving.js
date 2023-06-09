//Importation et Exportation des modules nécéssaires
export {getScale, changeScale, startFunction, createSun,createRectangle,removeFunction, offButton};

let scale =1;

//Cette fonction est appelée lorsque l'utilisateur clique sur Start, elle initialise un soleil et clear les potentiels choses qu'il y avait
//dans le canvas
function startFunction(){
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    context.clearRect(0,0,700,700);
    //canvas.style.backgroundImage = "url(./images/galaxie.jpeg)";
    createSun(context,scale);

}
//fonction qui incrémente la variable globale scale stockant l'echelle du dessin
function switchScale(){
    scale++;
}

//Fonction appelée lorsque l'utilisateur clique sur scale Changer
function changeScale(){
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");


    //Cette fonction remet à notre espace et change l'echelle afin de pouvoir afficher les autres planètes
    switchScale();
    createRectangle(context,0,0,700,700,50);
    createSun(context,scale);
}

function removeFunction(){
    
    //Fonction qui clear le canvas lorsque l'utilisateur clique sur Reset
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");
    createRectangle(context,0,0,700,700,100);

   offButton(context);
}

function offButton(context){
    let array = document.querySelectorAll(".form-check-input");
    console.log(array);
    for(let checkBox of array)
    {
        checkBox.checked = false;
    }
}


function effacerSoleil(context){

    //Fonction qui efface le soleil en créant un cercle noir de la même façon.
    context.save();
        context.beginPath();
            context.arc(350, 350, 28, 0, 2*Math.PI);
            context.fillStyle = "black";
        context.closePath();
        context.fill();
    context.restore();
}

function createSun(context, scale){
    //On commence par effacer le potentiel ancien soleil 
    effacerSoleil(context);
    context.save();
        context.beginPath();
            //On dessine un soleil suivant l'echelle du dessin actuelle
            if(scale%2==1){
                context.arc(350, 350, 30, 0, 2*Math.PI);
            }
            else{
                context.arc(350, 350, 15, 0, 2*Math.PI);
            }
            context.fillStyle = "yellow";
            context.closePath();
        context.fill();
    context.restore();
}

function createRectangle(context, x, y, width, height,radius)
{
    //Fonction qui crée un rectangle noir dans le champ de canvas
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
            context.fillStyle = "red";
        context.closePath();
    context.restore();
} 
//Renvoi la valeur stockée dans la variable globale scale
function getScale(){
    return scale;
}


