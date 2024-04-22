#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

volatile int licznik = 0;
sem_t sem;

int zwieksz(){
    for(int i=0;i<5;i++){
        int tmp;
        tmp = licznik;
        tmp = tmp + 1;
        licznik = tmp;
    }
}

void *thread(void *p){
    sem_wait(&sem); 
    printf("\nOpuszczanie semaforu\n"); 
  
    /* sekcja krytyczna */
    zwieksz();
      
    printf("\nPodnoszenie semaforu\n"); 
    sem_post(&sem);
}

int main()
{
    int err = sem_init(&sem, 0, 1); /* Zmienna, 0 dla wątków - 1 dla forków, wartość początkowa */
    assert(err == 0); /* sem_init zwraca 0 dla sukcesu */

    pthread_t tid_1;
    pthread_t tid_2;

    pthread_create(&tid_1, NULL, thread, NULL);
    pthread_create(&tid_2, NULL, thread, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    printf("\nLicznik: %d\n", licznik); 

    return 0;
}