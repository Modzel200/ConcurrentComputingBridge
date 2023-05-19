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
    //printf("Jestem na moście moje id to: %ld\n",selfThread);
    strcpy(currentCar->cityName,"Bridge");
    sleep(2);
    pthread_mutex_unlock(&mutex);
}

void simulation(Car_t **cars, int numberOfThreads)
{
    pthread_mutex_init(&mutex,NULL);    
    Car_t *currentCar;
    pthread_t *listOfThreads;
    listOfThreads = calloc(numberOfThreads,sizeof(pthread_t));
    currentCar=*cars;
    int i;
    char *lastCity;

    while(1)
    {
        i=0;
        //printAllCars(*cars);
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
                draw(*cars,lastCity);
                pthread_mutex_lock(&mutex); // Blokuj mutex przed utworzeniem wątku
                int tmpLen = strlen(currentCar->cityName);
                lastCity = (char*)malloc((tmpLen + 1) * sizeof(char));
                strcpy(lastCity, currentCar->cityName);
                pthread_mutex_unlock(&mutex); // Odblokuj mutex po utworzeniu wątku
                pthread_create(&listOfThreads[i], NULL, onBridge, (void*)currentCar);
                pthread_join(listOfThreads[i], NULL);
                pthread_mutex_lock(&mutex); // Blokuj mutex przed aktualizacją danych
                currentCar->threadId=listOfThreads[i];
                currentCar->idleMeter = rand() % 5 + 1;
                currentCar->isWaiting = false;
                pthread_mutex_unlock(&mutex); // Odblokuj mutex po aktualizacji danych
            }
            
            if(strcmp(currentCar->cityName,"Bridge")==0)
            {
                draw(*cars,lastCity);
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
            i++;
        }
        sleep(2);
    }
    pthread_mutex_destroy(&mutex);

}