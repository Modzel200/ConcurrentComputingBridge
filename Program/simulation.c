#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include<unistd.h>

pthread_mutex_t mutex;
void *onBridge(void **currentCarr) 
{
    pthread_mutex_lock(&mutex);
    Car_t *currentCar = (Car_t*) *currentCarr;
    pthread_t selfThread=pthread_self();
    printf("Jestem na moście moje id to: %ld\n",selfThread);
    if(strcmp(currentCar->cityName,"CityA")==0)
    {
        strcpy(currentCar->cityName,"CityB");
    }
    else
    {
        strcpy(currentCar->cityName,"CityA");
    }
    pthread_mutex_unlock(&mutex);
}

void simulation(Car_t **cars)
{
    pthread_mutex_init(&mutex,NULL);
    Car_t *currentCar;
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
                pthread_create(&currentCar->threadId,NULL,&onBridge,(void*)(&currentCar));
                //pthread_join(currentCar->threadId,NULL);
                currentCar->idleMeter=rand()%5+1;
                currentCar->isWaiting=false;
            }
            currentCar = currentCar->next;
        }
        sleep(2);
    }
    pthread_mutex_destroy(&mutex);

}