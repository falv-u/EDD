/**
 * @file product.c
 * @brief Funciones relacionadas con productos
*/

#include "product.h"

/**
 * @brief Crea la instancia de un producto
 *
 * Si no hay memoria suficiente se imprime "Error" y se retorna un producto
 * inválido, es decir, con name y provider en NULL.
 *
 * @param name Nombre del producto
 * @param price Precio del producto
 * @param stock Stock del producto
 * @param provider Proveedor del producto
 * @return Product Instancia de producto
*/
Product prod_create(char* name, float price, int stock, char* provider){
	Product product = {NULL, price, stock, NULL};

	product.name = malloc(strlen(name) + 1);
	if(product.name == NULL){
		printf("Error: no hay memoria disponible\n");
		return product;
	}
	strcpy(product.name, name);

	product.provider = malloc(strlen(provider) + 1);
	if(product.provider == NULL){
		printf("Error: no hay memoria disponible\n");
		free(product.name);
		product.name = NULL;
		return product;
	}
	strcpy(product.provider, provider);

	return product;
}


/**
 * @brief Imprime por consola un producto
 *
 * @param product Instancia de producto
*/
void prod_print(Product product){
	printf("%s\n", product.name);
	printf("  - Precio: %.2f\n", product.price);
	printf("  - Stock: %d\n", product.stock);
	printf("  - Proveedor: %s\n", product.provider);
}

/**
 * @brief Elimina un producto
 *
 * @param product Instancia de producto
*/
void prod_delete(Product product){
	free(product.name);
	free(product.provider);
}
