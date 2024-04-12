#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

/* gcc -pthread main.c */
/* Wątki dzielą ze sobą pamięć. Wątek to proces lekki */
/* pthread - charakterystyczny przedrostek wątków w specyfikacji posix */
/* Wynikiem funkcji pthread jest kod błędu */

int g = 0; /* Jest współdzielona */
__thread int t = 0; /* Zmienna globalna nie współdzielona przez wątki, każdy wątek ma swoją włącznie z mainem */

void *f_th(void *p){ /* Wskaźnik na coś, kompilator nie wnika na co */
    int a = 0; /* Miejscem jej alokacji jest stos, dlatego każdy wątek ma swoją */
    static int s = 0; /* Są współdzielone */
    a++;
    printf("a = %d\n", a);
    s++;
    printf("s = %d\n", s);
    g++;
    printf("g = %d\n", g);
    t++;
    printf("t = %d\n", t);
    
    printf("Hello\n");
    return NULL; /* To jest proforma jakby kompilator miał się przyczepić */
}

int main()
{
    pthread_t tid1; /* id wątku - parametr wyjściowy */
    pthread_t tid2; 
    
    pthread_create(&tid1, NULL, f_th, NULL); /* f_th - funkcja wykonywana przez program, ostatni parametr to parametry funkcji f_th */ 
    pthread_create(&tid2, NULL, f_th, NULL);

    printf("g in main = %d\n", g);
    printf("t in main = %d\n", t);
    /* Dla każdego wątku detach albo join */
    pthread_detach(tid2); /* Zapomnij o wątku gdy on się skończy, nie można potem joina zrobić */
    printf("g in main = %d\n", g);
    printf("t in main = %d\n", t);
    //pthread_exit(NULL); /* Koniec tego wątku (maina) - nie dochodzimy do startera, gdzie jest exit, reszta wątków będzie działać */
    pthread_join(tid1, NULL); /* Czekamy na zakończenie wątku tid1 */
    //pthread_join(tid2, NULL); /* Czekamy na zakończenie wątku tid1 */
    printf("g in main = %d\n", g);
    printf("t in main = %d\n", t);
	
    return 0;
}