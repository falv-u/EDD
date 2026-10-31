/**
 * @file abb.h
 * @brief Cabecera para las funciones de árboles binarios de búsqueda (ABB) de
 * productos
*/

#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

typedef struct Node* PtrToNode;
typedef PtrToNode SearchTree;
typedef PtrToNode Position;



/**
 * @brief Representa un nodo de un ABB
 *
 * El orden del árbol lo da el precio del producto: los productos más baratos
 * que el del nodo están en el subárbol izquierdo y los más caros en el
 * derecho.
 */
struct Node {
	Product product;
	Position left;
	Position right;
};

//==============================================================================
//        FUNCIONES DE INSERCIÓN
//==============================================================================
SearchTree abb_insert(Product P, SearchTree T);

//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================
Position abb_find(float price, SearchTree T);
Position abb_find_min(SearchTree T);
Position abb_find_max(SearchTree T);

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================
void abb_print_inorder(SearchTree T);
void abb_print_preorder(SearchTree T);
void abb_print_posorder(SearchTree T);
//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================
SearchTree abb_delete_tree(SearchTree T);

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================
float abb_position_get_price(Position P);

#endif
