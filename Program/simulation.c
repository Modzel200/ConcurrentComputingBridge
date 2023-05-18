#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include<unistd.h>

pthread_mutex_t mutex;
void *onBridge(void *car) 
{
    Car_t *currentCar = (struct Car*)car;
    pthread_mutex_lock(&mutex);
    long int selfThread = pthread_self();
    printf("Jestem na moście moje id to: %ld\n",selfThread);
    printf("ID AUTA: %d\n",currentCar->carId);
    currentCar->carId=99;
    printf("ID AUTA: %d\n",currentCar->carId);
    sleep(5);
    pthread_mutex_unlock(&mutex);
}

void simulation(Car_t **cars)
{
    Car_t *firstCar;
    pthread_mutex_init(&mutex,NULL);    
    Car_t *currentCar;
    currentCar=*cars;
    firstCar = *cars;
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
                pthread_create(&currentCar->threadId,NULL,onBridge,(void*) currentCar);
                currentCar->idleMeter=rand()%5+1;
                currentCar->isWaiting=false;
            }
            currentCar = currentCar->next;
        }
        sleep(2);
    }
    pthread_mutex_destroy(&mutex);

}