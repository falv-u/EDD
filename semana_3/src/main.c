#include <string.h>
#include "productos.h"
#define MAX_STACK 100
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
precio_pdt(float precio)
{
	precio = 0;
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
inventariar(void)
{
	int i;
	int tam;
	/* definicion de tipo estructura basada en 'struct _producto' */
	typedef struct _producto producto;
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
		if ( pdt[i].nombre != NULL )
			strcpy(*pdt[i].nombre, list_productos[i]);

		pdt[i].cantidad = rand() % MAX_STACK;
		generar_prov(5, pdt[i].proveedor);
		printf("ingrese el costo de %s:",  *pdt[i].nombre);
		pdt[i].precio = precio_pdt(pdt[i].precio);
	}
	for (i = 0; i < tam ; i++) {
			free(*pdt[i].nombre);
			free(pdt[i].nombre);
	}
}
int
main(void)
{
	srand(time(NULL)); /* semilla para numeros pseudo-aleatorios */
	inventariar();
	return 0;
}
