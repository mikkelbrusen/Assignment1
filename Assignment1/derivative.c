#include "filters.h"
#include "structures.h"

struct DeStructure{
	int h;
	int x[5];
	int y;
};

struct DeStructure derivative(struct DeStructure a, int hpValue ){
	struct DeStructure b;
	b = a;
	int x0;
	int x1;
	int x3;
	int x4;
	int h = a.h;

	a.x[h] = hpValue;
	b.x[h] = hpValue;

	x0 = a.x[h];
	h = (h+1)%5;

	x1 = a.x[h];
	h = (h+2)%5;

	x3 = a.x[h];
	h = (h+1)%5;

	x4 = a.x[h];

	b.y = ((1.0/8.0)*((2.0*x0)+x1+x3+(2.0*x4)));
	b.h = h;

	return b;
}


