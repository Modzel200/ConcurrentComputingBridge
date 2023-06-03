#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * @file
 * @brief Plik wyświetlający komunikaty o przejazdach samochodów.
 *
 * Plik którego funkcja służy do wyświetlania przemieszczenia samochodów w mieście
 */
/**@brief
*   Funkcja sprawdza pozycję każdego samochodu w mieście i obsługuje wyświetlanie przejazdu przez most
@param[in] *car
*   Znacznik do pierwszego samochodu z listy
@param[in] *lastcity
*   Ostatnie miasto w jakim znajdował się samochód na moście
*/
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