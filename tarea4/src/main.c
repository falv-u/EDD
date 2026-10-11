#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "product.h"

int main(void)
{
	Inventory I = NULL;
	InventoryElement elem;

	Product *p = NULL;
	Product invalido = {NULL, 0.0, 0, NULL};

	printf("creando inventario vacio\n");
	I = inv_make_empty(I);
	printf("esta vacio? %d\n", inv_is_empty(I));
	inv_print(I);

	printf("\ninsertando productos\n");
	I = inv_insert_first(prod_create("agua en polvo", 69.0, 7, "umagin"), I);
	I = inv_insert_last(prod_create("sopa de miel", 90.0, 12, "pandas-market"), I);
	I = inv_insert(prod_create("gelatina sin agua", 15.0, 3, "PIP"), I, inv_first(I));
	I = inv_insert_last(prod_create("frutos humedos", 420.0, 5, "Sa"), I);
	inv_print(I);

	printf("\nprobando navegacion y recuperacion\n");
	elem = inv_first(I);
	p = inv_retrieve(elem, I);
	if (p != NULL)
		printf("primero: %s\n", p->name);

	elem = inv_last(I);
	p = inv_retrieve(elem, I);
	if (p != NULL)
		printf("ultimo: %s (es ultimo? %d)\n", p->name, inv_is_last(elem, I));

	elem = inv_forward(inv_first(I));
	p = inv_retrieve(elem, I);
	if (p != NULL)
		printf("siguiente del primero: %s\n", p->name);

	elem = inv_backward(elem);
	p = inv_retrieve(elem, I);
	if (p != NULL)
		printf("anterior: %s\n", p->name);

	printf("\nbusqueda con cantidad par (4 items)\n");
	printf("buscando agua en polvo:\n");
	inv_find_by_name("agua en polvo", I);

	printf("buscando frutos humedos:\n");
	inv_find_by_name("frutos humedos", I);

	printf("buscando aire deshidratado (no existe):\n");
	inv_find_by_name("aire deshidratado", I);

	printf("\nbusqueda con cantidad impar (5 items)\n");
	I = inv_insert_last(prod_create("jugo de piedra", 1000.0, 1, "kumag"), I);
	printf("buscando gelatina sin agua (centro) :\n");
	inv_find_by_name("gelatina sin agua", I);

	printf("\ncasos borde e invalidos\n");
	printf("retrieve en header:\n");
	inv_retrieve(inv_header(I), I);

	printf("borrar header:\n");
	I = inv_delete(inv_header(I), I);

	printf("insertar producto nulo:\n");
	I = inv_insert(invalido, I, inv_header(I));

	printf("\neliminando un nodo valido\n");
	I = inv_delete(inv_first(I), I);
	inv_print(I);

	printf("\nvaciando y destruyendo\n");
	I = inv_make_empty(I);
	printf("vacio tras make_empty? %d\n", inv_is_empty(I));
	inv_destroy(I);
	I = NULL;

	return 0;
}
