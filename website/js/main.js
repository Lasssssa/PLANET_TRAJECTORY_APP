//Importation des différents modules utile à notre fonction main();
import {changeScale, removeFunction, startFunction} from "./canvas.js";
import {listenerCanvasMenu} from "./listener.js";

function main()
{
    //Récupération de l'espace canvas de notre page HTML, et récupération du context qui nous sert pour touts les dessins.
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    //--------Lancement des différents boutons (start, stop,reset)----------//
    
    //Ici on récupère le bouton reset afin de lui attribuer la fonction removeFunction des que le bouton est pressé
    //removeFunction --> (codé dans le fichier canvas.js)
    let buttonReset = document.getElementById("buttonReset");
    buttonReset.onclick = removeFunction;

    //Ici on récupère le bouton start afin de lui attribuer la fonction startFunction des que le bouton est pressé
    //startFunction --> (codé dans le fichier canvas.js)
    let buttonStart = document.getElementById("buttonStart");
    buttonStart.onclick = startFunction;


    //Ici on récupère le bouton changeScale afin de lui attribuer la fonction changeScale des que le bouton est pressé
    //changeScale --> (codé dans le fichier canvas.js)
    let buttonChangeScale = document.getElementById("buttonChangeScale");
    buttonChangeScale.onclick = changeScale;

    //Ici on lance la fonction listenerCanvasMenu qui va nous permettre de récupérer toutes les actions de l'utilisateur sur le menus des planètes
    //On met cela dans un tableau pour l'exploiter dans d'autres fonctions
    //listenerCanvasMenu --> (Codé dans listener.js) 
    let tabListener = listenerCanvasMenu(context);
}

main();



