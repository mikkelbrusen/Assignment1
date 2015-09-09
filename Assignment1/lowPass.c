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
	int x0;
	int x6;
	int x12;
	int h = a.h;

	a.x[h] = signal;

	x0 = a.x[h];
	h = (h+6)%13;

	x6 = a.x[h];
	h = (h+6)%13;

	x12 = a.x[h];

	b.y = 2*a.y1 - a.y2 + (1/32)*(x0 - 2*x6 + x12);
	b.y1 = a.y;
	b.y2 = a.y1;
	b.x = a.x;
	b.h = h;

	return b;
}

