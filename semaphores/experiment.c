#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <assert.h>

#define MAX_MEMORY 100

sem_t *wolne, *zajete;

int main(){
    int *ptr, pid, d, err;

    d = shm_open("Buf", O_CREAT|O_RDWR, 0666);
    assert(d!=1);

    err = ftruncate(d, MAX_MEMORY);
    assert(err!=-1);

    ptr = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0);
    assert(ptr!=MAP_FAILED);

    wolne = sem_open("wolne_sem_2", O_CREAT | O_RDWR, 0666, MAX_MEMORY);

    zajete = sem_open("zajete_sem_2", O_CREAT | O_RDWR, 0666, 0);

    pid = fork();
    assert(pid!=-1);

    if (pid == 0) //proces zapisywania
    {
        for (int i = 1; i <= MAX_MEMORY; i++)
        {
            sem_wait(wolne);
            ptr[i%MAX_MEMORY] = i;
            sem_post(zajete);
        }
    }
    else if (pid > 0)
    {
        for (int j = 1; j <= MAX_MEMORY; j++)
        {
            sem_wait(zajete);
            printf("Wartość i: %d\n", ptr[j%MAX_MEMORY]);
            sem_post(wolne);
        }
    }

    sem_destroy(wolne);
    sem_destroy(zajete);
    
    return 0;
}