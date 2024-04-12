#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

/* gcc -pthread -O3 experiment.c - -O to optymalizacja (nie trzeba aktualizować pamięci, bo nie ma odczytu zmiennej) */

volatile int g = 0; /* Jest współdzielona, 
                       volatile dodajemy przy optymalizacji (zmienna może być zmodyfikowana w innym bloku kodu) 
                       g jest ulotna */

void *write_global(void *p){ /* Wskaźnik na coś, kompilator nie wnika na co */
    for (int i = 1; i < 10; i++)
    {
        g = i;
        while(g != 0); /* To samo co while(g != 0){} */
    }
    
    return NULL; /* To jest proforma jakby kompilator miał się przyczepić */
}

void *read_global(void *p){ /* Wskaźnik na coś, kompilator nie wnika na co */
    int local;

    for (int j = 1; j < 10; j++)
    {
        do
        {
            local = g;
        } while (local == 0);
        g = 0;
        printf("Local: %d\n", local);
    }
    
    return NULL; /* To jest proforma jakby kompilator miał się przyczepić */
}

int main()
{
    pthread_t tid1; /* id wątku - parametr wyjściowy */
    pthread_t tid2; 
    
    pthread_create(&tid1, NULL, write_global, NULL); 
    //usleep((rand()%10) * 1000); /* opóżnienie mające na celu zapewnienie że najpierw się wykona cały tid1 */
    pthread_create(&tid2, NULL, read_global, NULL);

    pthread_exit(NULL); /* Kończymy wątek main(). Można również użyć 2 lini poniżej - czekać na wątki */
    //pthread_join(tid1, NULL);
    //pthread_join(tid2, NULL);

    return 0;
}