#include <stdio.h>

int main(void)
{
	char *frutas[] = {"Manzana", "Platano", "Pera", "Uva", "Naranja"};
	int cantidades[] = {12, 7, 20, 15, 9};
	int n = 5;
	int i;
	printf("Frutas y cantidades:\n");
	for (i = 0; i < n; i++)
		printf("%s: %d\n", frutas[i], cantidades[i]);

	FILE *fp = fopen("frutas.csv", "w");
	if (fp == NULL)
	{
		perror("Error al abrir frutas.csv");
		return 1;
	}

	fprintf(fp, "fruta,cantidad\n");

	for (i = 0; i < n; i++)
		fprintf(fp, "%s,%d\n", frutas[i], cantidades[i]);

	fclose(fp);

	return 0;
}
