#ifndef PRODUCTOS
#define PRODUCTOS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct _producto {
	float	precio;
	char	**nombre;
	char	proveedor[6];
	int     cantidad;
};

/* definicion de tipo estructura basada en 'struct _producto' */
typedef struct _producto producto;

void inventariar(void);
#endif
