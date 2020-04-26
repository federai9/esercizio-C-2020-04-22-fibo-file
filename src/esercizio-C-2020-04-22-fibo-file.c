/*
 * esercizio-C-2020-04-22-fibo-file.c
 *
 *  Created on: 24 apr 2020
 *      Author: utente
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

unsigned long fibonacci(unsigned int n)
{
	if(n==0)
		return 0;
	if(n==1)
		return 1;
	if(n>1)
		return fibonacci(n-1) + fibonacci(n-2);
	else
		exit(EXIT_FAILURE);
}

unsigned long * fibonacci_array(unsigned int n)
{
	unsigned long * f;
	f = calloc(n+1, sizeof(long));

	if (f == NULL)
	{
		perror("Calloc error!");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<=n; i++)
		f[i]=fibonacci(i);

	return f;
}

void swap_long(long unsigned int *x,long unsigned int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

void bubble_sort(unsigned long * array, int array_dimension)
{
  for (int i=0; i<array_dimension-1; i++)
  {
	  for (int j=0; j<array_dimension-i-1; j++)
	  {
		  if (array[j] > array[j+1])
			  swap_long(&array[j], &array[j+1]);
      }

  }
}



char * itoa_printf(unsigned long number) {
	char * result;


	result = calloc(12, sizeof(char));

	snprintf(
			result, // zona di memoria in cui snprintf scriverà la stringa di caratteri
			12, // dimensione della zona di memoria
			"%lu\n", // stringa di formattazione
			number); // numero intero da convertire in stringa

	return result;
}




int main(int argc, char * argv[]) {

	char * text_to_write;
	char * file_name;
	int text_to_write_len;

	if (argc == 1) {
			printf("specificare come parametro il nome del file da creare e su cui scrivere\n");
			exit(EXIT_FAILURE);
		}

	file_name = argv[1];
	printf("scrivo nel file %s\n", file_name);

	int fd = open(file_name,
						  O_CREAT | O_TRUNC | O_WRONLY,
						  S_IRUSR | S_IWUSR // l'utente proprietario del file avrà i permessi di lettura e scrittura sul nuovo file
						 );
	if (fd == -1) { // errore!

		perror("open()");

		exit(EXIT_FAILURE);
	}


	unsigned long *fibonacci_result;
	int dimension = 39;

	fibonacci_result = calloc(dimension+1,sizeof(long));
	fibonacci_result = fibonacci_array(dimension);

	for (int i = 0; i <= dimension; i++) {

		text_to_write = itoa_printf(fibonacci_result[i]);
		text_to_write_len = strlen(text_to_write) + 1;

		int res = write(fd, text_to_write, text_to_write_len);
		// write restituisce il numero di bytes che ha scritto
		// in caso di errore, restuisce -1

		if (res == -1) {
					perror("write()");
					exit(EXIT_FAILURE);
				}

	}

	free(text_to_write);

	// close file

	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	printf("Fatto, bye!\n");

	return 0;
}

