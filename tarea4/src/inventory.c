/**
 * @file inventory.c
 * @brief Funciones relacionadas con inventarios de productos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "product.h"
//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS PRODUCTOS DEL INVENTARIO
//==============================================================================

Inventory inv_insert(Product P, Inventory I, InventoryElement Position)
{
    InventoryElement aux;
    if (P.name == NULL || P.provider == NULL) {
        printf("error: producto invalido \n");
        return I;
    }

    aux = malloc(sizeof(struct Node));
    if (aux == NULL) {
        printf("error de asigancion de memoria \n");
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

Inventory inv_insert_first(Product P, Inventory I)
{
    InventoryElement aux;
    InventoryElement Position;
    Position = inv_header(I);
    if (P.name == NULL || P.provider == NULL) {
        printf("error: producto invalido \n");
        return I;
    }
    aux = malloc(sizeof(struct Node));
    if (aux == NULL)
    {
        printf("error de asigancion de memoria");
        return I;
    }
    aux->product = P;
    aux->next = (Position->next)->next;
    aux->prev = Position;

    Position->next = aux;
    (aux->next)->prev = aux;
    /* actualizamos el tamano de la lista */
    I->product.stock++;
    return I;
}

Inventory inv_insert_last(Product P, Inventory I)
{
    InventoryElement aux;
    InventoryElement Position;
    Position = inv_header(I);
    if (P.name == NULL || P.provider == NULL) {
        printf("error: producto invalido \n");
        return I;
    }
    aux = malloc(sizeof(struct Node));
    if (aux == NULL)
    {
        printf("error de asigancion de memoria");
        return I;
    }
    aux->product = P;
    aux->next = Position;
    aux->prev = (Position->prev)->prev;

    Position->prev = aux;
    (aux->next)->prev = aux;
    /* actualizamos el tamano de la lista */
    I->product.stock++;
    return I;
}

Inventory inv_delete(InventoryElement Position, Inventory I)
{
    InventoryElement pos_prev;
    InventoryElement pos_next;
    if (I == NULL) {
        printf("error: imprimir lista nula?\n");
        printf("tambien podemos imprimir hojas en blanco, 150 pesos la unidad\n");
        return;
    }

    if (I == NULL) {
        printf("error: imprimir lista nula?\n");
        printf("tambien podemos imprimir hojas en blanco, 150 pesos la unidad\n");
        return;
    }


    return I;
}

void inv_print(Inventory I)
{
    InventoryElement actual;
    int cont;
    if (I == NULL) {
        printf("error: imprimir lista nula?\n");
        printf("tambien podemos imprimir hojas en blanco, 150 pesos la unidad\n");
        return;
    }

    if (I->product.stock == 0) {
        printf("Inventario vacio, el viernes nos llegan mas productos!!! \n");
        return;
    }

    actual=inv_first(I);
    cont = 0;
    while (actual != inv_header(I)) {
        printf("[%d] \n", cont);
        prod_print(actual->product);
        cont++;
        actual=inv_forward(actual);
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
    InventoryElement pos = inv_header(I);
    return pos->next;
}

InventoryElement inv_last(Inventory I)
{
    InventoryElement pos = inv_header(I);
    return pos->prev;
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

    if ( I == NULL) {
        printf("error: quieres liberar una lista vacia?\n");
        printf("supongo que eres de los que le gusta dividir por 0\n");
        return;

    }
    ptr_header = inv_header(I);
    ptr_actual = inv_first(I);
    while (ptr_actual != ptr_header) {
        ptr_actual = inv_forward(ptr_actual);
        ptr_de = inv_backward(ptr_actual);
        free(ptr_de);
    }
    free(ptr_header);
}

//==============================================================================
//        FUNCIONES DE COMPROBACIÓN DE ESTADO
//==============================================================================

int inv_is_empty(Inventory I)
{
    if (I == NULL || I->product.stock == 0)
        return 1;
    return 0;
}
int inv_is_last(InventoryElement Position, Inventory I)
{

    if (Position->next == NULL || Position->prev == NULL || Position == NULL) {
        printf("error: algo ha pasado, direccion(es) invalida(s)\n");
        printf("error: seguro que el inventario es circular?\n");
        return 0;
    }
    /* 
     * doble check por si 
     * ocurre un error de logica respecto a la lista circular
     */
    if ( Position->next == inv_header(I) && (Position->next)->next == inv_first(I))
        return 1;
    printf("la posicion dada no es la ultima \n");
    return 0;
}
//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================

Product *inv_find_by_name(char *name, Inventory I)
{
    InventoryElement ptr_header;
    InventoryElement ptr_next;
    InventoryElement ptr_prev;
    Product *p;
    int pasadas;

    if (I == NULL) {
        printf("inventario invalido, seguro que existe?\n");
        return NULL;
    }

    if (I->product.stock == 0) {
        printf("El inventario esta vacio, la proxima semana llega mas mercancia!\n");
        return NULL;
    }
    ptr_header = inv_header(I);
    ptr_next = inv_first(I);
    ptr_prev = ptr_header->prev;
    p = NULL;
    pasadas = 0;
    while(1) {
        pasadas++;
        if ( ptr_next != ptr_header && strcmp(name, ptr_next->product.name) == 0 ) {
            printf("se encontro '%s' en la pasada: [%d]\n", name, pasadas);
            printf("encontrada por busqueda: next \n");
            p = &ptr_next->product;
            break;
        } else if ( ptr_prev != ptr_header && strcmp(name, ptr_prev->product.name) == 0 ) {
            printf("se encontro '%s' en la pasada: [%d]\n", name, pasadas);
            printf("encontrada por busqueda: prev \n");
            p = &ptr_prev->product;
            break;
        }

        if (ptr_next == ptr_header || ptr_prev == ptr_header) {
            printf("no se encontro el elemento. \n");
            p = NULL;
            break;
        }

        if (ptr_next == ptr_prev && strcmp(name, ptr_next->product.name) != 0 ) {
            printf("se han cruzado las busquedas, al parecer no hay coincidencias\n");
            printf("esto paso en la pasada numero [%d] para buscar '%s'", pasadas, name);
            p = NULL;
            break;
        }
        if (ptr_next == ptr_prev && strcmp(name, ptr_next->product.name) == 0) {
            printf("se encontro '%s' en la pasada: [%d]\n", name, pasadas);
            printf("encontrada por busqueda: ambos...retornando next\n");
            p = &ptr_next->product;
            break;
        }
        ptr_next=ptr_next->next;
        ptr_prev=ptr_prev->prev;
    }

    return p;
}

