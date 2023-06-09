#ifndef _CONSTANTE_
#define _CONSTANTE_
#include <math.h>
#include <string.h>

//--------Nom de constante---------//
#define EULER "euler"
#define EULER_ASYMETRIC "eulerasymetric"

//------Constante générale---------//
#define GRAVITE 6.6743e-11
#define SOLEIL_WEIGHT 1.989e30
#define DELTA_T 8640


//----------Constantes Mercure--------//

#define WEIGHT_MERCURY 3.301e23
#define PERI_MERCURY 4.7e10
#define HALF_AXIS_MERCURY 5.79e10
#define ECCENTRICITY_MERCURY 0.205
#define REVOLUTION_TIME_MERCURY 800

//----------Constantes Venus----------//

#define WEIGHT_VENUS 4.867e24
#define PERI_VENUS 1.1e11
#define HALF_AXIS_VENUS 1.1e11
#define ECCENTRICITY_VENUS 6.78e-3
#define REVOLUTION_TIME_VENUS 2350

//---------Constantes Terre----------//

#define WEIGHT_EARTH 5.973e24
#define PERI_EARTH 1.471e11
#define HALF_AXIS_EARTH 1.496e11
#define ECCENTRICITY_EARTH 1.6710e-2
#define REVOLUTION_TIME_EARTH 3700

//-----------Constantes Mars---------//

#define WEIGHT_MARS 6.418e23
#define PERI_MARS 2.06655e11
#define HALF_AXIS_MARS 2.27944e11
#define ECCENTRICITY_MARS 9.339e-2
#define REVOLUTION_TIME_MARS 6900

//---------Constantes Jupiter--------//

#define WEIGHT_JUPITER 1.896e27
#define PERI_JUPITER 7.41e11
#define HALF_AXIS_JUPITER 7.7834e11
#define ECCENTRICITY_JUPITER 4.839e-2
#define REVOLUTION_TIME_JUPITER 110000

//---------Constantes Saturne--------//

#define WEIGHT_SATURN 5.684e26
#define PERI_SATURN 1.3498e12
#define HALF_AXIS_SATURN 1.4267e12
#define ECCENTRICITY_SATURN 5.39e-2
#define REVOLUTION_TIME_SATURN 3000000

//---------Constantes Uranus--------//

#define WEIGHT_URANUS 8.681e25
#define PERI_URANUS 2.735e12
#define HALF_AXIS_URANUS 2.8707e12
#define ECCENTRICITY_URANUS 4.726e-2
#define REVOLUTION_TIME_URANUS 606500

//---------Constantes Neptune--------//

#define WEIGHT_NEPTUNE 102.43e24
#define PERI_NEPTUNE 4.459e12
#define HALF_AXIS_NEPTUNE 4.498e12
#define ECCENTRICITY_NEPTUNE 8.59e-3
#define REVOLUTION_TIME_NEPTUNE 1002300

int getPeriodFromName(char* name);


#endif