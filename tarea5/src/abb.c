/**
 * @file abb.c
 * @brief Funciones de árboles binarios de búsqueda (ABB) de productos
 *
 * Cada nodo del árbol guarda un producto y sus dos hijos. El orden lo da el
 * precio: en el subárbol izquierdo de un nodo están los productos más baratos
 * y en el derecho los más caros, por lo que no puede haber dos productos con
 * el mismo precio.
 *
 * Un árbol vacío es un puntero nulo. Por eso las funciones que pueden cambiar
 * la raíz (abb_insert y abb_delete_tree) retornan el árbol resultante y se
 * usan siempre de la forma ABB = abb_insert(P, ABB).
*/

/*
 * EN CLASE:
 *  1. Define los atributos de `struct Node` en inc/abb.h.
 *  2. Implementa cada función de este archivo: reemplaza el `;` del final de
 *     su prototipo por el cuerpo de la función `{ ... }`.
 */
#include "abb.h"

//==============================================================================
//        FUNCIONES DE INSERCIÓN
//==============================================================================

/**
 * @brief Inserta un producto en el ABB, según su precio
 *
 * Un producto más barato que el del nodo actual se inserta a la izquierda y
 * uno más caro a la derecha. El árbol pasa a ser el dueño de los strings del
 * producto, por lo que quien llama nunca debe liberarlo después de insertarlo.
 *
 * No se permiten precios repetidos: si ya existe un producto con ese precio se
 * imprime "Error" y se libera el producto entregado. Lo mismo ocurre si no hay
 * memoria para el nodo. Si el producto es inválido (name o provider en NULL,
 * es decir, un prod_create fallido) se imprime "Error" y el árbol queda
 * intacto.
 *
 * @param P Producto a insertar
 * @param T ABB donde se debe insertar el producto
 * @return SearchTree Referencia al ABB con el producto insertado
 */
SearchTree abb_insert(Product P, SearchTree T)
{
    if ( P.name == NULL || P.provider == NULL ) {
        fprintf(stderr, "Error: producto con cadenas invalidas\n");
        prod_delete(P);
        return T;
    }

    if ( T == NULL ) {
        T = malloc(sizeof(struct Node));
        if ( T == NULL ) {
            fprintf(stderr, "Error: falla la asignacion de memoria del arbol\n");
            prod_delete(P);
            return NULL;
        }
        T->product = P;
        T->left = NULL;
        T->right = NULL;
        return T;
    }

    if ( P.price == abb_position_get_price(T) ) {
        fprintf(stderr, "Error: precio igual, liberando producto\n");
        prod_delete(P);
        return T;
    }

    if ( P.price > abb_position_get_price(T) )
        T->right = abb_insert(P, T->right);
    else
        T->left = abb_insert(P, T->left);

    return T;
}
//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================

/**
 * @brief Busca en el ABB el producto que tiene un precio determinado
 *
 * En cada nodo se compara el precio buscado con el del nodo y se sigue por el
 * subárbol izquierdo (si es menor) o por el derecho (si es mayor), descartando
 * el otro. Se retorna el nodo que contiene el producto, no una copia.
 *
 * Si no existe un producto con ese precio, o el árbol está vacío, se imprime
 * un aviso con el precio buscado y se retorna un puntero nulo.
 *
 * @param price Precio del producto a buscar
 * @param T ABB donde se busca
 * @return Position Nodo que contiene el producto, o NULL si no se encuentra
 */
Position abb_find(float price, SearchTree T)
{
    if ( T == NULL ) {
        fprintf(stderr, "Error: producto con precio %.2f no encontrado\n", price);
        return NULL;
    }
    if ( price == abb_position_get_price(T) )
        return T;
    if ( price < abb_position_get_price(T) )
        return abb_find(price, T->left);
    return abb_find(price, T->right);
}

/**
 * @brief Busca el producto más barato del ABB
 *
 * El más barato es siempre el nodo que queda más a la izquierda. Si el árbol
 * está vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return Position Nodo con el producto más barato, o NULL si el árbol está vacío
 */
Position abb_find_min(SearchTree T)
{
	Position P;
	if ( T == NULL ) {
		fprintf(stderr, "Error: Arbol nulo\n");
		return NULL;
	}
	for ( P = T; (P->left) != NULL; P = P->left ) {}

	return P;
}

/**
 * @brief Busca el producto más caro del ABB
 *
 * El más caro es siempre el nodo que queda más a la derecha. Si el árbol está
 * vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return Position Nodo con el producto más caro, o NULL si el árbol está vacío
 */
Position abb_find_max(SearchTree T)
{
	Position P;
	if ( T == NULL ) {
		fprintf(stderr, "Error: Arbol nulo\n");
		return NULL;
	}
	for ( P = T; (P->right) != NULL; P = P->right ) {}

	return P;
}
//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================

/**
 * @brief Imprime el ABB en inorder (izquierda, raíz, derecha)
 *
 * Los productos salen ordenados de menor a mayor precio. Se imprime una línea
 * por producto, con el formato "nombre [precio]". Si el árbol está vacío no se
 * imprime nada.
 *
 * @param T ABB a imprimir
 */
void abb_print_inorder(SearchTree T)
{
	if ( T == NULL )
		return;

	abb_print_inorder(T->left);
	printf("%s [%.2f]\n", T->product.name, T->product.price);
	abb_print_inorder(T->right);
}

void abb_print_preorder(SearchTree T)
{
	if ( T == NULL )
		return;

	printf("%s [%.2f]\n", T->product.name, T->product.price);
	abb_print_preorder(T->left);
	abb_print_preorder(T->right);
}

void abb_print_postorder(SearchTree T)
{
	if ( T == NULL )
		return;

	abb_print_postorder(T->left);
	abb_print_postorder(T->right);
	printf("%s [%.2f]\n", T->product.name, T->product.price);
}

//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================

/**
 * @brief Elimina todos los nodos del ABB
 *
 * Se libera la memoria de todos los productos y nodos. Los nodos se liberan
 * en postorder (primero los dos subárboles y al final la raíz), porque si se
 * liberara la raíz primero se perdería el acceso a sus hijos. Después de
 * llamarla, T deja de ser válido, por lo que se debe asignar el valor
 * retornado: ABB = abb_delete_tree(ABB).
 *
 * @param T ABB a eliminar
 * @return SearchTree Siempre NULL (el árbol vacío)
 */
SearchTree abb_delete_tree(SearchTree T)
{
	if ( T == NULL )
		return T;
	T->left = abb_delete_tree(T->left);
	T->right = abb_delete_tree(T->right);

	prod_delete(T->product);
	free(T);
	T = NULL;
	return T;
	

}
/**
 * @brief Elimina del ABB el producto que tiene un precio determinado
 *
 * Busca el nodo cuyo producto tiene el precio indicado y lo elimina,
 * liberando la memoria del producto y del nodo. Retorna el arbol que queda,
 * que puede tener una raiz distinta (si se elimino la raíz) o quedar sin nada.
 *
 * Se distinguen tres casos  de eliminacin en un ABB:
 *  - Nodo hoja: se libera y se retorna NULL.
 *  - Nodo con un solo hijo: se retorna ese hijo (el abuelo lo enlaza).
 *  - Nodo con dos hijos: se intercambia el producto del nodo con el de su
 *    sucesor inorder y se elimina el nodo
 *    del sucesor, que ahora contiene el producto original. Así se mantiene
 *    la propiedad de ABB y cada nodo sigue siendo dueño de sus strings.
 *
 * Si el precio no existe, se avisa por pantalla y el arbol queda intacto.
 * Si el árbol está vacío, también se avisa y se retorna NULL.
 *
 * @param price Precio del producto a eliminar
 * @param T ABB donde se elimina
 * @return SearchTree Árbol resultante (puede ser NULL o tener otra raíz)
 */
SearchTree abb_delete_price(float price, SearchTree T)
{
	Position succ;
	Product tmp;

	if ( T == NULL ) {
		fprintf(stderr, "Error: producto con precio %.2f no encontrado\n", price);
		return NULL;
	}

	if ( price < abb_position_get_price(T) ) {
		T->left = abb_delete_price(price, T->left);
		return T;
	}
	if ( price > abb_position_get_price(T) ) {
		T->right = abb_delete_price(price, T->right);
		return T;
	}

	/* T es el nodo a eliminar */

	/* Caso 1: hoja */
	if ( T->left == NULL && T->right == NULL ) {
		prod_delete(T->product);
		free(T);
		return NULL;
	}

	/* Caso 2: un solo hijo */
	if ( T->left == NULL ) {
		Position right = T->right;
		prod_delete(T->product);
		free(T);
		return right;
	}
	if ( T->right == NULL ) {
		Position left = T->left;
		prod_delete(T->product);
		free(T);
		return left;
	}

	/* Caso 3: dos hijos -> intercambiar con el sucesor inorder y eliminarlo */
	succ = abb_find_min(T->right);
	tmp = T->product;
	T->product = succ->product;
	succ->product = tmp;

	/* Ahora el producto original de T está en succ; se borra por su precio */
	T->right = abb_delete_price(tmp.price, T->right);
	return T;
}
//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================

/**
 * @brief Devuelve el precio del producto que está en una posición del ABB
 *
 * Si la posición es nula se imprime "Error" y se retorna -1.
 *
 * @param P Posición (nodo) del ABB
 * @return float Precio del producto, o -1 si la posición es nula
 */
float abb_position_get_price(Position P)
{
	if ( P == NULL ) {
		fprintf(stderr, "Error: posicion nula]n");
		return -1;
	}
	return P->product.price;
}
