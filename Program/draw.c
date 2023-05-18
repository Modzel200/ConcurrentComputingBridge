#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void draw(Car_t *car, char *lastcity){
    Car_t *firstCar;  
    Car_t *currentCar;
    char napis[4] = "";
    currentCar=car;
    firstCar =car;
    int inA, inB, WaitA, WaitB;
    inA=inB=WaitA=WaitB=0;
    while(currentCar!=NULL){
        if(strcmp(currentCar->cityName,"CityA")==0 && currentCar->idleMeter!=0){
            inA++;
        }else if(strcmp(currentCar->cityName,"CityA")==0 && currentCar->idleMeter==0){
            WaitA++;
        }else if(strcmp(currentCar->cityName,"CityB")==0 && currentCar->idleMeter==0){
            WaitB++;
        }else if(strcmp(currentCar->cityName,"CityB")==0&&currentCar->idleMeter!=0){
            inB++;
        }
        if(strcmp(currentCar->cityName,"Bridge")==0){
            firstCar=currentCar;
            if(strcmp(lastcity,"CityA")==0){
                strcpy(napis,">>>");
            }else{
                strcpy(napis,"<<<");
            }
        }
    currentCar=currentCar->next;
    }
    printf("A=%d %d >>> [%s %d %s] <<< %d %d=B\n",inA,WaitA,napis,firstCar->carId,napis,WaitB,inB);
}