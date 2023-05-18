#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include<unistd.h>
#include "draw.c"
pthread_mutex_t mutex;
void *onBridge(void *car) 
{
    Car_t *currentCar = (struct Car*)car;
    pthread_mutex_lock(&mutex);
    long int selfThread = pthread_self();
    printf("Jestem na moście moje id to: %ld\n",selfThread);
    strcpy(currentCar->cityName,"Bridge");
    sleep(5);
    pthread_mutex_unlock(&mutex);
}

void simulation(Car_t **cars)
{
    pthread_mutex_init(&mutex,NULL);    
    Car_t *currentCar;
    currentCar=*cars;
    char *lastCity;
    while(1)
    {
        printAllCars(*cars);
        currentCar=*cars;
        while(currentCar!=NULL){
            if(currentCar->idleMeter==0)
            {
                currentCar->isWaiting=true;
            }
            else
            {
                currentCar->idleMeter=currentCar->idleMeter-1;
            }
            if(currentCar->isWaiting==true)
            {
                int tmpLen=strlen(currentCar->cityName);
                lastCity = (char*)malloc((tmpLen+1)*sizeof(char));
                strcpy(lastCity,currentCar->cityName);
                pthread_create(&currentCar->threadId,NULL,onBridge,(void*) currentCar);
                pthread_join(currentCar->threadId,NULL);
                currentCar->idleMeter=rand()%5+1;
                currentCar->isWaiting=false;
            }
            //draw(*cars);
            
            if(strcmp(currentCar->cityName,"Bridge")==0)
            {
                if(strcmp(lastCity,"CityA")==0)
                {
                    strcpy(currentCar->cityName,"CityB");
                }
                else
                {
                    strcpy(currentCar->cityName,"CityA");
                }
                free(lastCity);
            }
            currentCar = currentCar->next;
        }
        sleep(2);
    }
    pthread_mutex_destroy(&mutex);

}