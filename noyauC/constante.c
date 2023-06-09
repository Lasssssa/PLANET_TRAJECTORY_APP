#include "constante.h"
int getPeriodFromName(char* name){
    if(strcmp(name,"mercury")==0){
        return 10*REVOLUTION_TIME_MERCURY;
    }
    if(strcmp(name,"venus")==0){
        return 10*REVOLUTION_TIME_VENUS;
    }
    if(strcmp(name,"earth")==0){
        return 10*REVOLUTION_TIME_EARTH;
    }
    if(strcmp(name,"mars")==0){
        return 10*REVOLUTION_TIME_MARS;
    }
    if(strcmp(name,"jupiter")==0) {
        return REVOLUTION_TIME_JUPITER;
    }
    if(strcmp(name,"saturn")==0){
        return REVOLUTION_TIME_SATURN;
    }
    if(strcmp(name,"uranus")==0){
        return REVOLUTION_TIME_URANUS;
    }
    if(strcmp(name,"neptune")==0){
        return REVOLUTION_TIME_NEPTUNE;
    }

}