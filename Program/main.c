#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "struct.c"
#include <time.h>
pthread_mutex_t mutex;
int variable=0;
void* test()
{
   for(int i=0;i<1000000;i++)
   {
      pthread_mutex_lock(&mutex);
      variable++;
      pthread_mutex_unlock(&mutex);

   }
}

int main(int argc, char *argv[]) {
   if(argc<2)
   {
      printf("Nie podano parametru okreslajacego liczbe samochodow\n");
      return 0;
   }
   time_t tt;
   int seed = time(&tt);
   srand(seed);
   pthread_mutex_init(&mutex,NULL);
   printf("Liczba pojazdow: %s\n",argv[1]);
   int numberOfThreads = atoi(argv[1]);
   pthread_t listOfThreads[numberOfThreads];
   Car_t *cars = NULL;
   char *places[3];
   places[0]="CityA";
   places[1]="CityB";
   places[2]="Bridge";
   char *place;
   for(int i=0;i<numberOfThreads;i++)
   {
      if(pthread_create(&listOfThreads[i],NULL,&test,NULL)!=0)
      {
         //tu będziemy zwracać informacje o błędzie
         return 0;
      }
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
   pthread_mutex_destroy(&mutex);
   printf("Ilość wykonanych iteracji: %d\n",variable);
   return 0;
}

