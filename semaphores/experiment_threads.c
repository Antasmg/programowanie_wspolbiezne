#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

volatile int licznik = 0;
sem_t wolne, zajete;

void *dodaj(void *p){
    for (int i = 1; i <= 10; i++)
    {
        sem_wait(&wolne); 
        /* sekcja krytyczna */
        licznik = i;
        sem_post(&zajete);
    }
}

void *dodaj2(void *p){
    for (int i = 101; i <= 111; i++)
    {
        sem_wait(&wolne); 
        /* sekcja krytyczna */
        licznik = i;
        sem_post(&zajete);
    }
}

void *wyswietl(void *p){
    for (int i = 1; i <= 10; i++)
    {
        sem_wait(&zajete);   
        /* sekcja krytyczna */
        printf("i: %d\n", licznik);      
        sem_post(&wolne);
    }
}

int main(){
    int *ptr, pid, d, err;
    
    err = sem_init(&wolne, 0, 1);
    assert(err == 0);

    err = sem_init(&zajete, 0, 0);
    assert(err == 0);

    pthread_t tid_1;
    pthread_t tid_2;
    pthread_t tid_3;
    pthread_t tid_4;

    pthread_create(&tid_1, NULL, dodaj, NULL);
    pthread_create(&tid_2, NULL, wyswietl, NULL);
    pthread_create(&tid_3, NULL, dodaj2, NULL);
    pthread_create(&tid_4, NULL, wyswietl, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    pthread_join(tid_3, NULL);
    pthread_join(tid_2, NULL);
    
    return 0;
}