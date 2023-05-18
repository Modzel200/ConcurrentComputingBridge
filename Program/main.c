#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "struct.c"
#include <time.h>
#include "simulation.c"
#include "random.c"

int variable=0;

int main(int argc, char *argv[]) {
   srand(time(NULL));
   if(argc<2)
   {
      printf("Nie podano parametru okreslajacego liczbe samochodow\n");
      return 0;
   }
   printf("Randomowa liczba%d",randValue());
   printf("Liczba pojazdow: %s\n",argv[1]);
   int numberOfThreads = atoi(argv[1]);
   pthread_t *listOfThreads;
   listOfThreads = calloc(numberOfThreads,sizeof(pthread_t));
   Car_t *cars = NULL;
   char *places[3];
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
      addCar(&cars,i,listOfThreads[i],place,rand()%5+1);
   }
   
   /*
   for(int i=0;i<numberOfThreads;i++)
   {
      if(pthread_join(listOfThreads[i],NULL)!=0)
      {
         return 0;
      }      
   }
   */
   printAllCars(cars);
   simulation(&cars);
   printf("Ilość wykonanych iteracji: %d\n",variable);
   return 0;
}

