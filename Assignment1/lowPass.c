#include "filters.h"
#include "structures.h"

struct LPStructure{
	int h;
	int x[13];
	int y;
	int y1;
	int y2;

};

struct LPStructure lowPass(struct LPStructure a, int signal){
	struct LPStructure b;
	b = a;
	int x0;
	int x6;
	int x12;
	int h = a.h;

	a.x[h] = signal;
	b.x[h] = signal;

	x0 = a.x[h];
	h = (h+6)%13;

	x6 = a.x[h];
	h = (h+6)%13;

	x12 = a.x[h];

	// TODO: Fix this damn line below so that it gives -6 and not 0...!!!
	float test = 2*a.y1 - a.y2 + ((1/32)*(x0 - 2*x6 + x12));
	b.y = test;
	b.y1 = a.y;
	b.y2 = a.y1;
	b.h = h;

	return b;
}

