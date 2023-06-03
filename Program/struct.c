#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/**
 * @file
 * @brief Lista jednokierunkowa samochodów oraz metody do niej
 *
 * Plik z listą jednokierunkową, która przechowuje wszystkie utworzone przez nas samochody oraz metody do czyszczenia pamięci/dodawania samochodu.
 */
/**@brief
*   Struktura przechowywująca wszystkie samochody.
*/
typedef struct Car {
    /**@brief
    *   Przechowuje ID pojazdu.
    */
    int carId;
    /**@brief
    *   Przechowuje ID wątku.
    */
    long int threadId;
    /**@brief
    *   Przechowuje wartość boolean definiującą czy pojazd czeka na możliwość przejechania przez most.
    */
    bool isWaiting;
    /**@brief
    *   Przechowuje nazwę miasta.
    */
    char cityName[32];
    /**@brief
    *   Przechowuje licznik, kiedy wartość wyniesie 0, parametr isWaiting zmieni się na true.
    */
    int idleMeter;
    /**@brief
    *   Przechowuje wskaźnik na następny pojazd bądź null jeśli jest to koniec listy.
    */
    struct Car * next;
} Car_t;

/**@brief
*   Funkcja dodająca nowy pojazd do listy
@param[in] carStart
*   adres początku listy
@param[in] carId
*   id pojazdu
@param[in] threadId
*   id wątku
@param[in] cityName
*   nazwa miasta
@param[in] idleMeter
*   licznik oczekiwania
@retval '' Pusty return nie informuje o błędzie
*/
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
        currentCar->next->carId = carId;
        currentCar->next->threadId = threadId;
        currentCar->next->isWaiting = false;
        strcpy(currentCar->next->cityName,cityName);
        currentCar->next->idleMeter=idleMeter;
        currentCar->next->next=NULL;
    }
    return;
}
/**@brief
*   Funkcja usuwająca listę
@param[in] carStart
*   adres początku listy
@retval '' Pusty return nie informuje o błędzie
*/
void deleteList(Car_t** carStart)
{
    Car_t* currentCar = (*carStart);
    Car_t* nextNode;
    while (currentCar != NULL) {
        nextNode = currentCar->next;
        free(currentCar);
        currentCar = nextNode;
    }
    *carStart = NULL;
}

/*int printAllCars(Car_t *carStart){
    Car_t* currentCar = carStart;
    while(currentCar!=NULL){
        printf("ID: %d, Thread: %ld, Is he waiting: %d, It's city: %s, Idling for: %d\n",currentCar->carId,currentCar->threadId,currentCar->isWaiting,currentCar->cityName,currentCar->idleMeter);
        currentCar = currentCar->next;
    }
    printf("----------------------------------------------------------\n");
    return 1;
}*/

