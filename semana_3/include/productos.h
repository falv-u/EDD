#ifndef COMMONS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _producto {
	float	precio;
	char	**nombre;
	char	proveedor[6];
	int     cantidad;
};

/*
 * const char * protege el contenido de las palabras
 */
const char  *list_productos[] = {
	"clavos",
	"martillo",
	"destornillador",
	"taladro",
	"televisor"
};

const char dicc[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";


#endif
