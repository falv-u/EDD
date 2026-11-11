#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "product.h"

/* COLORES ANSI */
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"

static void imprimir_recorridos(SearchTree T, const char* titulo)
{
	printf(CYAN "\n--- %s ---" RESET "\n", titulo);
	printf(YELLOW "Inorder (ordenado por precio):" RESET "\n");
	abb_print_inorder(T);
	printf(YELLOW "Preorder (raiz primero):" RESET "\n");
	abb_print_preorder(T);
	printf(YELLOW "Postorder (raiz al final):" RESET "\n");
	abb_print_postorder(T);
}

int main(void)
{
	SearchTree ABB = NULL;
	Position p;

	printf(MAGENTA "================================================================================\n");
	printf("  ABB de productos\n");
	printf("================================================================================\n" RESET);

	/* ------------------------------------------------------------------ */
	printf(BLUE "\n====== ARBOL VACIO ======" RESET "\n");
	abb_print_inorder(ABB);   /* No debe imprimir nada */
	abb_print_preorder(ABB);  /* No debe imprimir nada */
	abb_print_postorder(ABB); /* No debe imprimir nada */
	p = abb_find(1500, ABB);  /* Avisa: no encontrado */
	p = abb_find_min(ABB);    /* Error: arbol vacio */
	p = abb_find_max(ABB);    /* Error: arbol vacio */

	/* ------------------------------------------------------------------ */
	printf(BLUE "\n====== INSERTANDO PRODUCTOS ======" RESET "\n");
	/*
	 *                 1500 Sopa de miel
	 *                /                \
	 *        800 Agua en polvo      2500 Pan de aire
	 *        /       \              /              \
	 *  400 Sal dulce 1000 Te de piedra 2000 Cafe de nube 3000 Vino sin uva
	 */
	ABB = abb_insert(prod_create("Sopa de miel",      1500, 20, "Colmenar Austral"), ABB);
	ABB = abb_insert(prod_create("Agua en polvo",      800, 15, "Deshidratados Sur"), ABB);
	ABB = abb_insert(prod_create("Pan de aire",       2500,  8, "Panaderia normal"), ABB);
	ABB = abb_insert(prod_create("Sal dulce",          400, 50, "SalinaSA"), ABB);
	ABB = abb_insert(prod_create("Te de piedra",      1000, 30, "rocky infusiones"), ABB);
	ABB = abb_insert(prod_create("Cafe de nube",      2000, 12, "pipipi"), ABB);
	ABB = abb_insert(prod_create("Vino sin uva",      3000,  6, "ELgatote"), ABB);

	printf(BLUE "\n====== PRECIO REPETIDO (debe fallar) ======" RESET "\n");
	ABB = abb_insert(prod_create("Galletas de humo", 1500, 40, "Panadera"), ABB);

	imprimir_recorridos(ABB, "ARBOL INICIAL (7 productos)");

	printf(BLUE "\n====== BUSQUEDAS ======" RESET "\n");
	p = abb_find(1000, ABB);
	if ( p != NULL ) {
		printf(GREEN "Encontrado: " RESET);
		prod_print(p->product);
	}
	p = abb_find(1234, ABB); /* No existe: avisa */
	if ( p == NULL )
		printf(GREEN "OK: " RESET "abb_find retorno NULL\n");

	p = abb_find_min(ABB);
	printf(GREEN "Mas barato: " RESET "%s\n", p->product.name);
	p = abb_find_max(ABB);
	printf(GREEN "Mas caro:   " RESET "%s\n", p->product.name);

	printf(BLUE "\n====== ELIMINAR UNA HOJA (Sal dulce, 400) ======" RESET "\n");
	ABB = abb_delete_price(400, ABB);
	imprimir_recorridos(ABB, "TRAS ELIMINAR HOJA 400");

	printf(BLUE "\n====== ELIMINAR NODO CON DOS HIJOS, NO RAIZ (Te de piedra, 1000) ======" RESET "\n");
	/* Insertamos dos productos nuevos como hijos de Te de piedra (1000)
	 * para que ese nodo tenga de verdad dos hijos. */
	ABB = abb_insert(prod_create("Helado caliente",   900, 10, "Frio Equivocado"), ABB);
	ABB = abb_insert(prod_create("Sopa seca",        1100, 10, "Cocina Paradogica"), ABB);
	imprimir_recorridos(ABB, "ANTES DE ELIMINAR 1000 (dos hijos)");

	ABB = abb_delete_price(1000, ABB);
	imprimir_recorridos(ABB, "TRAS ELIMINAR 1000");

	printf(BLUE "\n====== ELIMINAR NODO CON UN SOLO HIJO (Sopa seca, 1100) ======" RESET "\n");
	ABB = abb_delete_price(1100, ABB);
	imprimir_recorridos(ABB, "TRAS ELIMINAR 1100");

	printf(BLUE "\n====== ELIMINAR LA RAIZ CON DOS HIJOS (Sopa de miel, 1500) ======" RESET "\n");
	ABB = abb_delete_price(1500, ABB);
	imprimir_recorridos(ABB, "TRAS ELIMINAR LA RAIZ 1500");

	printf(BLUE "\n====== ELIMINAR LA NUEVA RAIZ (deberia ser 2000, Cafe de nube) ======" RESET "\n");
	ABB = abb_delete_price(2000, ABB);
	imprimir_recorridos(ABB, "TRAS ELIMINAR 2000");

	printf(BLUE "\n====== ELIMINAR UN PRECIO INEXISTENTE (9999) ======" RESET "\n");
	ABB = abb_delete_price(9999, ABB); /* Avisa, arbol intacto */
	imprimir_recorridos(ABB, "TRAS INTENTAR ELIMINAR 9999 (sin cambios)");

	printf(BLUE "\n====== ELIMINAR TODO LO QUE QUEDA ======" RESET "\n");
	ABB = abb_delete_price(2500, ABB); /* Pan de aire */
	ABB = abb_delete_price(3000, ABB); /* Vino sin uva */
	ABB = abb_delete_price(900,  ABB); /* Helado caliente */
	imprimir_recorridos(ABB, "ARBOL CASI VACIO");

	printf(BLUE "\n====== ELIMINAR SOBRE ARBOL VACIO ======" RESET "\n");
	ABB = abb_delete_price(400, ABB); /* Avisa: no encontrado, arbol vacio */

	printf(BLUE "\n====== LIBERAR TODO EL ARBOL ======" RESET "\n");
	ABB = abb_delete_tree(ABB);
	if ( ABB == NULL )
		printf(GREEN "OK: " RESET "abb_delete_tree retorno NULL\n");

	printf(MAGENTA "\n================================================================================\n");
	printf("  Fin de las pruebas\n");
	printf("================================================================================\n" RESET);

	return 0;
}
