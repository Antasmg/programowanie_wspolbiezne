#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>

#define CONST_TO_SET 13

int main(){
    int *ptr, pid, d, err;

    d = shm_open("Buf", O_CREAT | O_RDWR, 0666);
    assert(d!=-1);

    err = ftruncate(d, 100);
    assert(err != -1);

    ptr = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0);
    assert(ptr!=MAP_FAILED);

    *ptr = 0;
    pid = fork();
    assert(pid!=-1);

    if(pid == 0){ /* Proces potomka */
        for(int i=1; i<100; i++){
            *ptr = i;
            while (*ptr != 0);
        }
    }
    else if (pid > 0) /* Proces przodka */
    {
        for(int i=1; i<100; i++){
            while(*ptr != i);
            printf("ID: %d\td: %d\n", pid, *ptr);
            *ptr = 0;
        }
    }

    return 0;
}