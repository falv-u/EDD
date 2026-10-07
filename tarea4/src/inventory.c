/**
 * @file inventory.c
 * @brief Funciones relacionadas con inventarios de productos
*/
#include "inventory.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>


//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS PRODUCTOS DEL INVENTARIO
//==============================================================================

Inventory inv_insert(Product P, Inventory I, InventoryElement Position)
{
    InventoryElement aux = malloc(sizeof(struct Node));
    if (aux == NULL)
    {
        printf("error de asigancion de memoria");
        return I;
    }
    aux->product = P;
    aux->next = Position->next;
    aux->prev = Position;

    Position->next = aux;
    (aux->next)->prev = aux;
    /* actualizamos el tamano de la lista */
    I->product.stock++;
    return I;
}

void inv_print(Inventory I)
{
    InventoryElement actual;
    int cont;
    if (I == NULL)
        return;
    if (I->product.stock == 0) {
        printf("Inventario vacio");
        return;
    }

    actual=inv_first(I);
    cont = 0;
    while (actual != inv_header(I)) {
       printf("[%d] \n", cont);
       prod_print(actual->product);
       cont++;
       inv_forward(actual);
    }
}
//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS ÍNDICES DEL INVENTARIO
//==============================================================================

InventoryElement inv_header(Inventory I)
{
	return I;
}

InventoryElement inv_first(Inventory I)
{
	return I;
}

InventoryElement inv_last(Inventory I)
{
	return I;
}

InventoryElement inv_forward(InventoryElement Position)
{
	return Position->next;
}

InventoryElement inv_backward(InventoryElement Position)
{
	return Position->prev;
}



//==============================================================================
//        FUNCIONES RELACIONADAS CON LA TOTALIDAD DEL INVENTARIO
//==============================================================================

Inventory inv_make_empty(Inventory I)
{
	if(I != NULL)
		return I;

	I = malloc(sizeof(struct Node));
	if (I == NULL) {
	printf("error: sin memoria\n");
	}

	I->next = I;
	I->prev = I;

	/* usaremos el stack del centinela para almacenar el tamano de la lista */
	I->product.stock = 0;
	return I;
}

void inv_destroy(Inventory I)
{
	InventoryElement ptr_header;
	InventoryElement ptr_de;
	InventoryElement ptr_actual;

	ptr_header = inv_header(I);
	ptr_actual = inv_first(I);
	while (ptr_actual != ptr_header) {
		ptr_actual = inv_forward(I);
		ptr_de = inv_backward(ptr_actual);
		free(ptr_de);
	}
}

//==============================================================================
//        FUNCIONES DE COMPROBACIÓN DE ESTADO
//==============================================================================


//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================


