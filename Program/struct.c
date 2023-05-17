#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Car {
    int carId;
    long int threadId;
    bool isWaiting;
    char cityName[32];
    int idleMeter;
    struct Car * next;
} Car_t;

void addCar(Car_t **carStart, int carId, long int threadId, const char* cityName, int idleMeter){
    if(*carStart ==NULL){
        *carStart = (Car_t*)malloc(sizeof(Car_t));
        (*carStart)->carId = carId;
        (*carStart)->threadId = threadId;
        (*carStart)->isWaiting = false;
        strcpy((*carStart)->cityName,cityName);
        (*carStart)->idleMeter = idleMeter;
        (*carStart)->next = NULL;
    } else {
        Car_t *currentCar = *carStart;
        while(currentCar->next!=NULL){
            currentCar=currentCar->next;
        }
        currentCar->next = (Car_t *)malloc(sizeof(Car_t));
        currentCar->carId = carId;
        currentCar->threadId = threadId;
        currentCar->isWaiting = false;
        strcpy(currentCar->next->cityName,cityName);
        currentCar->next->idleMeter=idleMeter;
        currentCar->next->next=NULL;
    }
    return;
}