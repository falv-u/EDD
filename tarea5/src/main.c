#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "product.h"

/* COLORES ANSI */
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"

int main(){
	SearchTree ABB = NULL;
	Position p;

	printf(MAGENTA "================================================================================\n");
	printf("  Programa para probar ABB de productos (la clave es el precio)\n");
	printf("================================================================================" RESET "\n");

	// ------------------------------------------------------------------
	printf(BLUE "\n======ARBOL VACIO======" RESET "\n");
	abb_print_inorder(ABB);  // No imprime nada
	p = abb_find(1500, ABB); // Avisa que no lo encontró
	p = abb_find_min(ABB);   // Error: árbol vacío
	p = abb_find_max(ABB);   // Error: árbol vacío

	// ------------------------------------------------------------------
	printf(BLUE "\n======INSERTANDO PRODUCTOS======" RESET "\n");
	/*
	 *            1500 Pan
	 *           /          \
	 *     800 Leche         2500 Queso
	 *     /      \          /        \
	 * 400 Sal  1000 Te  2000 Cafe  3000 Vino
	 */
	ABB = abb_insert(prod_create("Pan",   1500, 20, "Panaderia Sur"), ABB);
	ABB = abb_insert(prod_create("Leche",  800, 15, "Lacteos Patagonia"), ABB);
	ABB = abb_insert(prod_create("Queso", 2500,  8, "Lacteos Patagonia"), ABB);
	ABB = abb_insert(prod_create("Sal",    400, 50, "Salinas del Sur"), ABB);
	ABB = abb_insert(prod_create("Te",    1000, 30, "Hierbas Australes"), ABB);
	ABB = abb_insert(prod_create("Cafe",  2000, 12, "Tostaduria Austral"), ABB);
	ABB = abb_insert(prod_create("Vino",  3000,  6, "Vinos del Maule"), ABB);

	printf(BLUE "\n======INSERTANDO UN PRECIO REPETIDO======" RESET "\n");
	ABB = abb_insert(prod_create("Galletas", 1500, 40, "Panaderia Sur"), ABB); // Debe fallar

	// ------------------------------------------------------------------
	printf(BLUE "\n======IMPRIMIENDO EN INORDER (de menor a mayor precio)======" RESET "\n");
	abb_print_inorder(ABB);

	// ------------------------------------------------------------------
	printf(BLUE "\n======BUSQUEDAS======" RESET "\n");
	p = abb_find(1000, ABB);
	if(p != NULL){
		printf(GREEN "Encontrado: " RESET);
		prod_print(p->product);
	}
	p = abb_find(1234, ABB); // No existe: avisa
	if(p == NULL){
		printf(GREEN "OK: " RESET "abb_find retornó NULL\n");
	}

	p = abb_find_min(ABB);
	printf(GREEN "Más barato: " RESET "%s\n", p->product.name);
	p = abb_find_max(ABB);
	printf(GREEN "Más caro:   " RESET "%s\n", p->product.name);

	// ------------------------------------------------------------------
	printf(BLUE "\n======ELIMINANDO TODO EL ARBOL======" RESET "\n");
	ABB = abb_delete_tree(ABB);
	if(ABB == NULL){
		printf(GREEN "OK: " RESET "abb_delete_tree retornó NULL\n");
	}

	return 0;
}
