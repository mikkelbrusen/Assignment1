#include "filters.h"
#include "structures.h"

struct HPStructure{
	int h;
	int x[33];
	int y;
};

struct HPStructure highPass(struct HPStructure a, int lpValue ){
	struct HPStructure b;
	b = a;
	int x0;
	int x16;
	int x17;
	int x32;
	int h = a.h;

	a.x[h] = lpValue;
	b.x[h] = lpValue;

	x0 = a.x[h];
	h = (h+16)%33;

	x16 = a.x[h];
	h = (h+1)%33;

	x17 = a.x[h];
	h = (h+15)%33;

	x32 = a.x[h];

	// TODO: Delete 0.5f when done prototyping
	b.y = a.y - (x0/32.0) + x16 - x17 + (x32/32.0)+ 0.5f;
	b.h = h;

	return b;
}

