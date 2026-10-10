#include <stdio.h>
#include <string.h>
#include "inventory.h"
#include "product.h"

int main(void)
{
	Inventory I = inv_make_empty(NULL);
	Product *p;
	inv_insert(prod_create("Jugo de agua", 6767, 7, "kumag"), I, inv_header(I));
	inv_insert(prod_create("agua en polvo", 69, 7, "umagin"), I, inv_header(I));
	inv_insert(prod_create("sopa de miel", 90, 7, "pandas-market"), I, inv_header(I));
	inv_insert(prod_create("pulpa de papa", 1000, 7, "Bariel-Sa"), I, inv_header(I));
	inv_print(I);
	p = inv_find_by_name("jugo de agua", I);
	if (p != NULL) {
		printf("%s", p->name);
		printf("%d", p->stock);
	}
	inv_destroy(I);
	return 0;
}
