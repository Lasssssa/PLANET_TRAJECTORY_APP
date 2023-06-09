//Importation des différents modules utile à notre fonction main();
import {pathMercury,pathVenus,pathEarth,pathMars,pathJupiter,pathSaturn,pathUranus,pathNeptune,listener} from "./drawTrajectorie.js";

function main()
{
    //Récupération de l'espace canvas de notre page HTML, et récupération du context qui nous sert pour touts les dessins.
    let canvas = document.getElementById("main");
    let context = canvas.getContext("2d");

    //--------Lancement des différents boutons (start, stop,reset)----------//
    
    //Ici on récupère le bouton reset afin de lui attribuer la fonction removeFunction des que le bouton est pressé
    //removeFunction --> (codé dans le fichier canvas.js)

    
    
    let buttonMercury = document.getElementById("buttonMercury");
    buttonMercury.onclick = pathMercury;

    let buttonVenus = document.getElementById("buttonVenus");
    buttonVenus.onclick = pathVenus;

    let buttonEarth = document.getElementById("buttonEarth");
    buttonEarth.onclick = pathEarth;

    let buttonMars = document.getElementById("buttonMars");
    buttonMars.onclick = pathMars ;

    let buttonJupiter = document.getElementById("buttonJupiter");
    buttonJupiter.onclick = pathJupiter;

    let buttonSaturn = document.getElementById("buttonSaturn");
    buttonSaturn.onclick = pathSaturn;

    let buttonUranus = document.getElementById("buttonUranus");
    buttonUranus.onclick = pathUranus;

    let buttonNeptune = document.getElementById("buttonNeptune");
    buttonNeptune.onclick = pathNeptune;

    listener(context);
    


    
}

main();



