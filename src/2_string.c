#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * En ascii desde el 65 al 90 son Mayusculas
 * y desde el 97 al 122 minusculas
 */

void rellenar (char cadena[], int largo)
{
	int i;
	for ( i = 0; i < largo; i++) {
		if (rand() % 2 == 0)
		    cadena[i] = 'A' + (rand() % 26);
		else
		    cadena[i] = 'a' + (rand() % 26);
	}
	cadena[largo] = '\0';
}
void imprimir (char cadena[], int largo)
{
	int i;
	printf("cadena largo %d:\n", largo);
	for( i = 0; i < largo; i++){
		if ( i != largo - 1)
			printf("[%c]-", cadena[i]);
		else
			printf("[%c]", cadena[i]);
	}
	printf("\n---------------------\n");
}
int main(void)
{
	srand(time(NULL));
	char s5[6];
	char s10[11];
	char s15[16];
	char s20[21];

	rellenar(s5, 5);
	rellenar(s10, 10);
	rellenar(s15, 15);
	rellenar(s20, 20);

	imprimir(s5, 5);
	imprimir(s10, 10);
	imprimir(s15, 15);
	imprimir(s20, 20);
	return 0;
}
