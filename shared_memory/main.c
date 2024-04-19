#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h> /* Ten jest dla O_CREAT i O_RDWR */
#include <sys/mman.h> /* Ten jest dla PROT_READ, PROT_WRITE i MAP_SHARED */
#include <assert.h>

int main(){
    int *ptr, pid, d, err;

    /* funkcja posix - nazwa, uprawnienia (stwórz oraz read/write) , dostęp (właściciel, grupa, reszta) */
    d = shm_open("Buf", O_CREAT | O_RDWR, 0666);
    assert(d!=-1);

    err = ftruncate(d, 100); /* Ustawienie pamięci d na 100 bytes */
    assert(err != -1);

    /* Pod jaki adres dostaniemy segment, miejsce w pamięci, uprawnienia, 
    że ma być wspóldzielenie, co ma być, od którego miejsca współdzielimy */
    /* ptr jest wskaźnikiem na obszar współdzielonys */
    ptr = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, d, 0);
    assert(ptr!=MAP_FAILED);

    *ptr = 7;
    pid = fork();
    assert(pid!=-1);
    if(pid == 0){
        *ptr = 13;
        exit(0);
    }
    wait(NULL); /* A call to wait() blocks the calling process until one of its child processes exits or a signal is received */
    printf("%d\n", *ptr); /* Teraz zwróci 13, ponieważ ptr jest w pamięci współdzielonej */

    return 0;
}