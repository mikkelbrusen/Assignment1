#include "filters.h"
#include "structures.h"

struct HPStructure{
	int h;
	int x[32];
	int y;

};

struct HPStructure highPass(struct HPStructure a, ){
	struct LPStructure b;
	b = a;
	int x0;
	int x16;
	int x17;
	int x32;
	int h = a.h;

	a.x[h] = /*output fra LPS x*/;
	b.x[h] = /*output fra LPS y*/;

	x0 = a.x[h];
	h = (h+6)%13;

	x6 = a.x[h];
	h = (h+6)%13;

	x12 = a.x[h];

	b.y = 2*a.y - a.y1 + ((1.0/32.0)*(x0 - 2*x6 + x12));
	b.y1 = a.y;
	b.h = h;

	return b;
}

