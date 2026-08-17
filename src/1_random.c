#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   

int main(int argc, char *argv[])
{
	float suma;
	float nota;
	int max;
	int min;
	int n = -1;
	int i;

	srand(time(NULL));
	max = 7;
	min = 1;
	if (argc != 2) {
		printf("solo un argumento por ejecucion...\n");
		return 1;
	}
	/*
	 * atoi ASCII to integer
	 *
	 */
	if (argc == 2) {
		n = atoi(argv[1]);
	}

	printf("Se recibio el numero %d por consola\n", n);
	
	if (n <= 0) {
		printf("la cantidad de notas debe ser > 0\n");
		return 1;
	}
	printf("Notas: ");
	suma = 0.0;
	for ( i = 0; i < n; i++) {
		/* en general num = min + (rand()/MAX_RAND)*(max-min) */
		nota = min + ((float)rand()/(float)RAND_MAX)*(max-min);		
		suma += nota;
		printf("%.1f, ", nota);
	}
	return 0;
}
