#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "struct.c"
#include <time.h>
#include "simulation.c"
#include "random.c"
#include "simulationEnvironmentVariables.c"

int variable=0;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if(argc<2)
    {
        printf("Nie podano parametru okreslajacego liczbe samochodow\n");
        return 1;
    }
    if(argc<3){
        printf("Nie podano trybu dzialania programu\n");
        return 1;
    }
    //printf("Randomowa liczba%d",randValue());
    //printf("Liczba pojazdow: %s\n",argv[1]);
    int numberOfThreads = atoi(argv[1]);
    Car_t *cars = NULL;
    char *places[3];
    int workingMode = atoi(argv[2]);
    places[0]="CityA";
    places[1]="CityB";
    places[2]="Bridge";
    char *place;
    for(int i=0;i<numberOfThreads;i++)
    {
        if(rand()%2==0)
        {
            place = places[0];
        }
        else
        {
            place = places[1];
        }
        addCar(&cars,i,0,place,rand()%5+1);
    }
    if(workingMode==0){
        simulation(&cars,numberOfThreads);
    } else {
        simulationEnvironmentVariables(&cars, numberOfThreads);
    }
    return 0;
}

