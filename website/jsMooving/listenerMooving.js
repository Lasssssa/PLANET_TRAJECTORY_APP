//Exportation de la fonction dans les autres modules
export{listenerCanvasMenu};

//----------Déclaration de variables globales que l'on souhaite récupérer dans plusieurs fonctions sans devoir les réecrire---------//

//Déclaration des variables "planete_M" qui servent à savoir si la checkBox dans la page HTML est activée ou pas
let mercury_M = 0;
let venus_M   = 0;
let earth_M   = 0;
let mars_M    = 0;
let jupiter_M = 0;
let saturn_M  = 0;
let uranus_M  = 0;
let neptune_M = 0;


function listenerCanvasMenu(context){
//---------------------Listener des boutons checkBox------------//

    //Le fonctionnement est le même que la fonction listenerCanvasMenu de la page pour afficher les trajectoires
    //Nous allons ici commenter le premier bloc, cependant il est répeté 8 fois pour les 8 checkBox
    //--------------Mercury -------------------//
      //On récupère les informations du checkBox de la planète en question
    let mercuryMooving = document.querySelector("input[name=mercury_mooving]");

    //On ajoute un listener qui capte les changements de position de la checkBox, à cela on lui attribue une fonction à l'aide de "=>""
    mercuryMooving.addEventListener("change", (button) => {
        
    //On vérifie ensuite si le bouton est en position check ou non check
    if (button.target.checked) {
        //En position check, on attribue la valeur 1 
        mercury_M = 1;
    } else {
        //En position check, on attribue la valeur 0
        mercury_M = 0;
    }
    });
    //-------------Earth ----------------//
    let earthMooving = document.querySelector("input[name=earth_mooving]");
    earthMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        earth_M = 1;
    } else {
        earth_M = 0;
    }
    });
    //------------------Venus -----------------//
    let venusMooving = document.querySelector("input[name=venus_mooving]");
    venusMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        venus_M = 1;
    } else {
        venus_M = 0;
    }
    });
    //-------------Mars -----------------//
    let marsMooving = document.querySelector("input[name=mars_mooving]");
    marsMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        mars_M = 1;
    } else {
        mars_M=0;
    }
    });

    //-----------Jupiter----------------//
    let jupiterMooving = document.querySelector("input[name=jupiter_mooving]");
    jupiterMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        jupiter_M=1;
    } else {
       jupiter_M=0;
    }
    });

    //---------------Saturn-----------------//
    let saturnMooving = document.querySelector("input[name=saturn_mooving]");
    saturnMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        saturn_M=1;
    } else {
        saturn_M=0;
    }
    });

    //--------------Uranus-------------//
    let uranusMooving = document.querySelector("input[name=uranus_mooving]");
    uranusMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        uranus_M=1;
    } else {
        uranus_M=0;
    }
    });

    //---------------Neptune-------------//
    let neptuneMooving = document.querySelector("input[name=neptune_mooving]");
    neptuneMooving.addEventListener("change", (button) => {
    if (button.target.checked) {
        neptune_M=1;
    } else {
        neptune_M=0;
    }
    });

    //Une fois qu'on a récupéré toutes les positions des boutons, on les exporte dans un tableau
    return  [mercury_M,venus_M,earth_M,mars_M,jupiter_M,saturn_M,uranus_M,neptune_M];
}