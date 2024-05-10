#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

pthread_t philospohers[5];
pthread_mutex_t forks[5];
int counter, seed;

void eat(int index)
{
    int randomNumber = rand_r(&seed) % 2 + 1000000;

    printf("Philosopher %d starts eatting\n", index);
    usleep(randomNumber);
    printf("Philosopher %d stopped eatting\n", index);
}

void *think(void *arg)
{
    int fork1, fork2 = 0;
    int index = *((int *)arg);
    int eatten = 0;

    while (eatten < 3)
    {
        int randomNumber = rand_r(&seed) % 5 + 1000000;

        printf("Philosopher %d starts to think\n", index);
        usleep(randomNumber);
        printf("Philosopher %d stopped thinking\n", index);

        fork1 = pthread_mutex_trylock(&forks[(index % 5)]);
        fork2 = pthread_mutex_trylock(&forks[((index + 1) % 5)]);

        if (fork1 == 0 && fork2 == 0)
        {
            printf("Philosopher %d got two forks!\n", index);
            eat(index);
            eatten++;
            pthread_mutex_unlock(&forks[index % 5]);
            pthread_mutex_unlock(&forks[(index + 1) % 5]);
        }
        else
        {
            printf("Philosopher %d did not get two forks!\n", index);
            pthread_mutex_unlock(&forks[index % 5]);
            pthread_mutex_unlock(&forks[(index + 1) % 5]);
        }
    }

    printf("Philosopher %d finished eatting\n", index);
    return NULL;
}

int main(void)
{
    int error;
    int threadArgs[5];
    seed = 5;
    for (int i = 0; i < 5; i++)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
    }

    int i = 0;
    while (i < 5)
    {
        threadArgs[i] = i;
        pthread_create(&philospohers[i], NULL, think, &threadArgs[i]);
        i++;
    }

    pthread_join(philospohers[0], NULL);
    pthread_join(philospohers[1], NULL);
    pthread_join(philospohers[2], NULL);
    pthread_join(philospohers[3], NULL);
    pthread_join(philospohers[4], NULL);

    return 0;
}
