#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>

int zwieksz(int licznik){
    int tmp;
    tmp = licznik;
    tmp = tmp + 1;
    licznik = tmp;
    return licznik;
}

int main()
{
    int *ptr, pid, d, err;

    d = shm_open("Buf", O_CREAT | O_RDWR, 0666);
    assert(d!=1);

    err = ftruncate(d, 100);
    assert(err!=-1);

    ptr = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0);
    assert(ptr!=MAP_FAILED);

    *ptr = 0;
    pid = fork();
    assert(pid != -1);

    if (pid == 0)
    {
        *ptr = zwieksz(*ptr);
    }
    else if (pid > 0)
    {
        while(*ptr == 0);
        printf("Licznik ustawione. Licznik: %d\n", *ptr);
    }
    
    return 0;
}