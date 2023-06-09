# Kepler Project - CIR1 Project - End Year

Creator of **Projet Kepler** : Théo Porodo / Éthan LE PAN

# What is the aim of this project ?

The aim of this end-of-year CIR1 (computer science and networks) project was to create a `C application` that calculates the trajectories of planets in the solar system using several methods, such as the Euler method or the asymmetric Euler method. 
The aim was also to create a `web application` to display the trajectories previously calculated by the C

# Setup the linux machine

### Update
- `sudo apt-get update`
- `sudo apt-get upgrade`

### Install apache2 Version : 2.4.56
- `sudo apt-get install apache2`

### Install gcc : All version

- `sudo apt-get install gcc`

# Clone the repository Github in apache
### Install git
- `apt-get install git git-core`
### Clone the repository
- `cd /var/www/html`
- `sudo git clone https://github.com/Lasssssa/PROJET_KEPLER_CIR1` 
- This may take some time, as the json planet path are a little bit heavy
### Update
- `cd /var/www/html/PROJET_KEPLER_CIR1`
- `sudo git pull https://github.com/Lasssssa/PROJET_KEPLER_CIR1`


# Use of the site

### Utilisation of the current site 

The website include 5 parts
- Home page with a description of the project in French
- The presentation page, which displays planetary trajectories and moving planets. 
- An information page describing the planets of the solar system and the planets of the system. Also in French
- A source page to find all the sources we may have used (photos, etc.). 
- A trajectory page for displaying trajectories at once, for easier analysis. It also allows you to compare the Euler and Euler Asymmetric methods.

### Utilisation of the C application

Go to the C kernel source folder: 
`cd /noyauC`
 the application with the : 
`gcc *.c -o application -lm`
Run the application :
`./application`

The application is divided into 5 parts
- A section for calculations and exports
- Scientific information on the planets of the solar system
- A section on energy audit calculations
- And finally, two parts for generating the json files used by the web application


## Repertory Github : 
https://github.com/Lasssssa/PROJET_KEPLER_CIR1
