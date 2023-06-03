#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "struct.c"
#include <time.h>
#include "simulation.c"
#include "random.c"
#include "simulationEnvironmentVariables.c"
/*! \mainpage Strona główna dokumentacji 
 *
 *
 * \section sec Dokumentacja
 * <table style="width:100%">
 * <tr>
 *   <td>Wydział Informatyki Politechniki Białostockiej<br>
 *      Przedmiot: Systemy Operacyjne</td>
 *   <td>Data oddania: 03.06.2023 r.</td>
 * </tr>
 * <tr>
 *   <td>Pracownia specjalistyczna nr 1<br>
 *      Zespół:
 *      1. Mateusz Kondraciuk
 *      2. Jakub Franciszek Modzelewski
 *      3. Dawid Waszkiewicz</td>
 *   <td>Prowadzący:<br>
 *      dr inż. Wojciech Kwedlo<br>
 *      Ocena:</td>
 * </tr>
 * </table>
 * \section sec4 Realizacja zadania
 * W celu sprawdzenia treści zadania proszę udać się pod \ref page1.<br>
 * W celu sprawdzenia wykonanych podpunktów proszę udać się pod \ref page2.<br>
 * W celu sprawdzenia instrukcji obsługi proszę udać się pod \ref page3. 
 * \page page1 Treść Zadania
 * <b>Projekt 2 - wąski most</b><br>
Wąski most. Z miasta A do miasta B prowadzi droga, na której znajduje się wąski most umożliwiający tylko ruch jednokierunkowy. 
Most jest również dość słaby, także może po nim przejeżdżać tylko jeden samochód na raz. 
Napisać program w którym N samochodów (wątków) będzie nieustannie przejeżdżało z miasta do miasta, pokonując po drodze most 
(N przekazywane jako argument linii poleceń). Zsynchronizuj dostęp wątków do mostu:<br>
a) nie wykorzystując zmiennych warunkowych (tylko mutexy/semafory) [17p]<br>
b) wykorzystując zmienne warunkowe (condition variables) [17p] <br>
Aby móc obserwować działanie programu, każdemu samochodowi przydziel numer. Program powinien wypisywać komunikaty według poniższego przykładu:<br>
A-5 10>>> [>> 4 >>] <<<4 6-B<br>
Oznacza to, że po stronie miasta A jest 15 samochodów z czego 10 czeka w kolejce przed mostem, przez most przejeżdża samochód z numerem 4 z miasta A do B, po stronie miasta B jest 10 samochodów, z czego 4 oczekują w kolejce przed mostem. Komunikat należy wypisywać w momencie, kiedy w programie zmieni się którakolwiek z tych wartości.
 *<br>
 * W celu sprawdzenia wykonanych podpunktów proszę udać się pod \ref page2.
 * 
 */
/*! \page page2 Wykonane podpunkty
 * \section sec2 Podpunkty
 * \subsection subsection1 Używając wyłącznie mutexy/semafory
 *  Do realizacji zadania użyliśmy wyłącznie mutexów
 * \subsection subsection2 Wykorzystując zmienne warunkowe (condition variables)
 *  Zadanie zostało zrealizowane wyłącznie z wykorzystaniem zmiennych warunkowych.
 *
 * \page page3 Instrukcja obsługi
 * \section sec3 Kompilacja programu
 * \subsection subsection10 gcc main.c -o program
 * Zostanie stworzony zkompilowany plik o nazwie program, który następnie możemy wywołać w celu uruchomienia skryptu
 * \section sec4 Parametry podawane przy uruchamianiu programu
 * \subsection subsection4 Ilość wątków(samochodów)
 * Pierwszym parametrem do podania jest ilość wątków które będą tworzone przez program.
 * \subsection subsection5 Rodzaj realizacji projektu
 * Paramatr pozwala na wybór formy realizacji projektu: 0- używając mutexów, 1- używając zmienne warunkowe
 * \section Przykłady 
 * \subsection subsection8 ./program 10 0
 * Wywołujemy program, zostanie stworzone 10 wątków, a zadanie będzie realizowane przy pomocy mutexów
 * \subsection subsection9 ./program 15 1
 * Wywołujemy program, zostanie stworzone 15 wątków, a zadanie będzie realizowane przy pomocy zmiennych warunkowych
*/

/**
 * @file
 * @brief Główny plik
 *
 * Plik rozpoczynający pracę całego programu.<br>
 * To tu wątki są rozdzielane na 2 miasta.<br>
 * W tym pliku możemy zmienić nazwy miast.
 */
int variable=0;
/**@brief
*   Główna funkcja programu, rozpoczynająca jego działanie.
@param[in] argc
*   ilość argumentów
@param[in] argv
*   Lista z argumentami
@retval 0 jest zwracane w przypadku sukcesu   
*/
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

