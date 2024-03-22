#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* Jeśli zrobimy builda za pomocą gcc [nazwa_pliku.c] to zrobi nam się plik a.out, który wywołuje się ./a.out */
/* Jeśli zrobimy builda za pomocą ctrl+shift+b to zrobi nam się plik [nazwa_pliku], który wywołuje się ./[nazwa_pliku] */

int main()
{
	int id = fork();
	id = fork();
	id = fork();
	id = fork();
	printf("Hello from ID:%d\n", id);

    if(id == 0){
        printf("I am the new guy\n");
    }
    else{
        printf("I am the original guy\n");
    }

	return 0;
}
