#include <stdio.h>
#include <stdlib.h>
#define MAX 4
int
main(void)
{
	int	a;
	int	b;
	int	c;
	int	*p;
	int	*q;
	int	*r;
	int	*v;

	a = 5;
	b = 12;
	c = 30;

	v = (int *)malloc(MAX * sizeof(int));

	p = &a;
	q = &b;
	r = p;

	*r += 10;
	q = r;
	*q -5;

	v[0] = a;
	b[1] = b;
	v[2] = c;
	v[3] = *p + *q;

	r = &c;
	*r *= 2;

	printf("a:%d,b:%d,c:%d,v[0]:%d,v[1]:%d,v[2]:%d,v[3]:%d", a,b,c,v[0],v[1],v[2],v[3])
	free(v);
	return 0;
}
