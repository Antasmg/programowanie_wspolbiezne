#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

volatile int licznik = 0;

int zwieksz(){
    int tmp;
    tmp = licznik;
    tmp = tmp + 1;
    licznik = tmp;
    return tmp;
}

void *przed_zwieksz(void *p)
{
    int tmp;
    for(int i = 0; i<15; i++){
        tmp = zwieksz();
    }
}

void *odczytaj(void *p){
    while(licznik < 15);
    printf("Licznik: %d\n", licznik);
}

int main()
{
    pthread_t tid_write;
    pthread_t tid_read;

    pthread_create(&tid_write, NULL, przed_zwieksz, NULL);
    pthread_create(&tid_read, NULL, odczytaj, NULL);

    pthread_join(tid_write, NULL);
    pthread_join(tid_read, NULL);

    return 0;
}