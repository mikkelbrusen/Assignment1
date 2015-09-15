#include "filters.h"
#include "structures.h"

struct DeStructure{
	int h;
	int x[5];
	int y;
};

struct HPStructure Derivative(struct DeStructure a, int hpValue ){
	struct HPStructure b;
	b = a;
	int x0;
	int x1;
	int x2;
	int x3;
	int x4;
	int h = a.h;

	a.x[h] = hpValue;
	b.x[h] = hpValue;

	x0 = a.x[h];
	h = (h+1)%5;

	x1 = a.x[h];
	h = (h+1)%5;

	x2 = a.x[h];
	h = (h+1)%5;

	x3 = a.x[h];
	h = (h+1)%5;

	x4 = a.x[h];

	b.y = ;
	b.h = h;

	return b;
}


