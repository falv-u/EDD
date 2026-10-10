/**
 * @file inventory.h
 * @brief Cabecera para las funciones relacionadas con inventarios de productos
*/

/*
 * TAREA:
 *  1. Define los atributos de `struct Node` (más abajo).
 *  2. Completa la documentación de cada función agregando sus etiquetas
 *     @param (una por parámetro) y @return (si retorna algo).
 *  3. Implementa todas las funciones en src/inventory.c.
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

typedef struct Node* PtrToNode;
typedef PtrToNode Inventory;
typedef PtrToNode InventoryElement;

/**
 * @brief Nodo de la lista doblemente enlazada que representa un inventario
 *
 * Cada nodo debe guardar un producto y una referencia tanto al nodo siguiente
 * como al nodo anterior. El inventario es una lista circular con nodo
 * cabecera: la cabecera no contiene un producto real, el siguiente del ultimo
 * elemento es la cabecera y el anterior del primero también lo es.
 *
 * Además, el inventario debe llevar la cuenta de cuántos productos contiene:
 * esa cantidad se muestra al imprimirlo y sirve para saber si está vacío.
 * Cómo llevar esa cuenta queda a tu criterio.
 *
 * TODO: reemplaza esta declaración por la definición con sus atributos.
 */
struct Node {
	Product product;
	InventoryElement next;
	InventoryElement prev;
};

//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS PRODUCTOS DEL INVENTARIO
//==============================================================================

/**
 * @brief Inserta un producto en el inventario, justo después de una posición
 *
 * El inventario pasa a ser el dueño de los strings del producto. Si la
 * inserción falla (producto inválido, es decir, con name o provider en NULL,
 * o falta de memoria) se imprime "Error", el inventario queda intacto y el
 * producto sigue siendo responsabilidad de quien llama. La posición puede ser
 * la cabecera.
 * @param P Producto a insertar
 * @param I Inventario en el cual se inserta
 * @param Position Posicion de referencia tras la cual se inserta
 * @return Inventory Puntero al inventario modificado
 */
Inventory inv_insert(Product P, Inventory I, InventoryElement Position);

/**
 * @brief Inserta un producto al principio del inventario
 *
 * Equivale a insertar justo después de la cabecera. Aplican las mismas
 * condiciones de error que inv_insert.
 * @param P Producto a insertar
 * @param I Inventario en el cual se inserta
 * @return Inventory Puntero al inventario modificado
 */
Inventory inv_insert_first(Product P, Inventory I);

/**
 * @brief Inserta un producto al final del inventario
 *
 * Equivale a insertar justo después del ultimo elemento. Aplican las mismas
 * condiciones de error que inv_insert.
 * @param P Producto a insertar
 * @param I Inventario en el cual se inserta
 * @return Inventory Puntero al inventario modificado
 */
Inventory inv_insert_last(Product P, Inventory I);

/**
 * @brief Elimina del inventario el producto que se encuentra en una posición
 *
 * Se libera la memoria del producto y del nodo. La cabecera del inventario no
 * contiene un producto real, por lo que no se puede eliminar con esta
 * funcion: se imprime "Error" y no se hace nada.
 * @param Position Posicion del elemento a eliminar
 * @param I Inventario del cual se elimina
 * @return Inventory Puntero al inventario modificado
 */
Inventory inv_delete(InventoryElement Position, Inventory I);

/**
 * @brief Retorna el producto que se encuentra en la posicion indicada
 *
 * Se retorna un puntero al producto que está dentro del nodo, no una copia.
 * La cabecera del inventario no contiene un producto real, por lo que no se
 * puede consultar: se imprime "Error" y se retorna un puntero nulo.
 * @param Position Posicion del producto a consultar
 * @param I Inventario a consultar
 * @return Product* Puntero al producto almacenado, o NULL si la posicion no es valida
 */
Product* inv_retrieve(InventoryElement Position, Inventory I);

//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS ÍNDICES DEL INVENTARIO
//==============================================================================

/**
 * @brief Devuelve la cabecera del inventario
 * @param I Inventario a consultar
 * @return InventoryElement Puntero al nodo cabecera
 */
InventoryElement inv_header(Inventory I);

/**
 * @brief Devuelve el primer elemento del inventario
 *
 * Si el inventario está vacío se retorna la cabecera.
 * @param I Inventario a consultar
 * @return InventoryElement Puntero al primer nodo con datos, o la cabecera si está vacío
 */
InventoryElement inv_first(Inventory I);

/**
 * @brief Devuelve el ultimo elemento del inventario
 *
 * Si el inventario está vacío se retorna la cabecera.
 * @param I Inventario a consultar
 * @return InventoryElement Puntero al ultimo nodo con datos, o la cabecera si está vacío
 */
InventoryElement inv_last(Inventory I);

/**
 * @brief Devuelve el elemento siguiente del inventario
 * @param Position Nodo actual
 * @return InventoryElement Puntero al nodo siguiente
 */
InventoryElement inv_forward(InventoryElement Position);

/**
 * @brief Devuelve el elemento anterior del inventario
 * @param Position Nodo actual
 * @return InventoryElement Puntero al nodo anterior
 */
InventoryElement inv_backward(InventoryElement Position);

//==============================================================================
//        FUNCIONES RELACIONADAS CON LA TOTALIDAD DEL INVENTARIO
//==============================================================================

/**
 * @brief Elimina todos los elementos del inventario, incluida su cabecera
 *
 * Se libera toda la memoria del inventario. Después de llamarla, I deja de
 * ser valido.
 * @param I Inventario a destruir
 */
void inv_destroy(Inventory I);

/**
 * @brief Crea un inventario vacio o vacia uno ya existente
 *
 * Si no hay memoria disponible se imprime "Error" y se retorna un puntero
 * nulo.
 *
 * @warning Si I no es NULL, el inventario se destruye (se libera I y todos sus
 * elementos) y se crea uno nuevo. Cualquier otra referencia al inventario
 * anterior queda invalida, por lo que se debe usar siempre el valor retornado.
 * Si I no está inicializado (ni es NULL ni apunta a un inventario valido) el
 * comportamiento es indefinido.
 * @param I Inventario a vaciar (o NULL para crear uno nuevo)
 * @return Inventory Puntero al nuevo inventario vacio, o NULL si falla la memoria
 */
Inventory inv_make_empty(Inventory I);

/**
 * @brief Imprime por consola un inventario
 *
 * Si I es NULL no se imprime nada. Si el inventario está vacío se indica que
 * está vacío. En otro caso se muestra la cantidad de productos que contiene y
 * luego cada uno de ellos, en orden, usando prod_print.
 * @param I Inventario a imprimir
 */
void inv_print(Inventory I);

//==============================================================================
//        FUNCIONES DE COMPROBACIÓN DE ESTADO
//==============================================================================

/**
 * @brief Devuelve el estado del inventario
 *
 * Retorna 1 si el inventario está vacío y 0 en caso contrario. Un inventario
 * NULL se considera vacío.
 * @param I Inventario a consultar
 * @return int 1 si está vacío o es NULL, 0 en caso contrario
 */
int inv_is_empty(Inventory I);

/**
 * @brief Devuelve si el elemento indicado es el ultimo del inventario
 *
 * Retorna 1 si el elemento es el último y 0 en caso contrario. Si el
 * inventario es NULL retorna 0.
 * @param Position Nodo a evaluar
 * @param I Inventario de referencia
 * @return int 1 si es el último elemento, 0 en caso contrario
 */
int inv_is_last(InventoryElement Position, Inventory I);

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================

/**
 * @brief Busca un producto por su nombre en el inventario
 *
 * La búsqueda revisa ambos extremos del inventario al mismo tiempo: un
 * puntero avanza desde el primer elemento y otro retrocede desde el último,
 * hasta que se encuentra el producto o los punteros se encuentran o se cruzan.
 * Cada vuelta en la que se compara el elemento de cada extremo cuenta como una
 * iteración. Si en una misma iteración coinciden ambos extremos, se prefiere
 * el puntero de avance.
 *
 * Con una cantidad impar de elementos los punteros terminan sobre el elemento
 * central, que también se debe comparar (contando una iteración más). Un
 * inventario vacío no contiene ningún producto.
 *
 * Retorna un puntero al producto encontrado (no una copia) o un puntero nulo
 * si no se encuentra. Cuando se encuentra, se imprime en cuántas iteraciones
 * se encontró y qué puntero lo encontró (el de avance, el de retroceso, o
 * ambos si estaban sobre el elemento central). Cuando no se encuentra, se
 * imprime un aviso indicando el nombre buscado.
 * @param name Cadena con el nombre a buscar
 * @param I Inventario donde buscar
 * @return Product* Puntero al producto encontrado, o NULL si no existe
 */
Product* inv_find_by_name(char* name, Inventory I);

#endif