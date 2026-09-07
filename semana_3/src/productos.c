#include "productos.h"
#define MAX_STACK 100
/*
 * const char * protege el contenido de las palabras
 */
static const char  *list_productos[] = {
	"clavos",
	"martillo",
	"destornillador",
	"taladro",
	"televisor"
};

static const char dicc[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


void
generar_prov(int n, char *destino)
{
	/* se ignora el caracter nulo \0 */
	int largo_dic = sizeof(dicc) - 1;
	for (int i = 0; i < n; i++) {
		int indice = rand() % largo_dic;
		destino[i] = dicc[indice];
	}
	destino[n]='\0';

}
float
precio_pdt(void)
{
	float precio = 0;
	while(precio <= 0.00) {
		scanf("%f", &precio);
		if (precio == 0) {
			printf("por politica de la empresa no regalamos nada\n");
			printf("prueba de nuevo \n");
		}
		if (precio < 0) {
			printf("eso significa que nosotros le pagamos para que se lo lleve? bruh \n");
			printf("prueba de nuevo \n");
		}
	}

	return precio;
}

void
guardar_csv(char *ruta, producto *pdt, int tam)
{
	FILE *archivo = fopen(ruta, "w");
	if (archivo == NULL) {
		perror("Error al abrir archivo CSV");
		return;
	}

	fprintf(archivo, "Nombre,Cantidad,Proveedor,Precio\n");

	for (int i = 0; i < tam; i++) {
		fprintf(archivo, "\"%s\",%d,%s,%.2f\n",
		    *pdt[i].nombre,
		    pdt[i].cantidad,
		    pdt[i].proveedor,
		    pdt[i].precio);
	}
	fclose(archivo);
}

void
inventariar(void)
{
	int i;
	int tam;
	/* cantidad de elementos a inventariar */
	tam = sizeof(list_productos) / sizeof(list_productos[0]);
	producto pdt[tam];
	for (i = 0; i < tam ; i++) {
		/* reserva espacio para puntero a puntero */
		pdt[i].nombre = malloc(sizeof(char *));
		if (pdt[i].nombre == NULL) {
			perror("malloc ptr");
			exit(1);
		}

		/* reserva de memoria para cadena en * */
		*pdt[i].nombre = (char *) malloc(strlen(list_productos[i]) + 1);
		if ( *pdt[i].nombre != NULL )
			strcpy(*pdt[i].nombre, list_productos[i]);

		pdt[i].cantidad = rand() % MAX_STACK;
		generar_prov(5, pdt[i].proveedor);
		printf("ingrese el costo de %s:",  *pdt[i].nombre);
		pdt[i].precio = precio_pdt();
	}

	guardar_csv("inventario.csv", pdt, tam);

	for (i = 0; i < tam ; i++) {
			free(*pdt[i].nombre);
			free(pdt[i].nombre);
	}
}
