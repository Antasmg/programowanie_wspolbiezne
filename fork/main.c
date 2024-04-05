#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* Jeśli zrobimy builda za pomocą gcc [nazwa_pliku.c] to zrobi nam się plik a.out, który wywołuje się ./a.out */
/* Jeśli zrobimy builda za pomocą ctrl+shift+b to zrobi nam się plik [nazwa_pliku], który wywołuje się ./[nazwa_pliku] */

int main()
{
    /* Ciężki proces - z natury mają być od siebie odizolowane */
	int id = fork();
    int p2 = getpid(); /* potomek zwróci id przodka, a przodek dostanie jakiś inny pid - y */
    int p3 = getppid(); /* przodek dostanie pid shellu, a potomek dostanie y */ /* Get parent parent id */
    int p4 = wait(NULL); /* Zwraca pid procesu który się zakończył - zwróci id przodka, dla potomka zwróci -1 (nie krytyczny error) */

	printf("ID:\t%d\n", id);
	printf("pid:\t%d\n", p2);
	printf("ppid:\t%d\n", p3);
	printf("wait:\t%d\n", p4);

    if(id == 0){
        printf("I am the new guy\n");
    }
    else{
        printf("I am the original guy\n");
    }

	return 0;
}
