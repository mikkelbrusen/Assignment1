#include "filters.h"

int derivative(int hpValue ){
	static int x[5] = {0};
	static int x0 = 0;
	static int x1 = 0;
	static int x3 = 0;
	static int x4 = 0;
	static int h = 0;
	static int y = 0;

	x[h] = hpValue;
	x0 = hpValue;

	h = (h+1)%5;
	x1 = x[h];

	h = (h+2)%5;
	x3 = x[h];

	h = (h+1)%5;
	x4 = x[h];

	y = ((2*x0)+x1-x3-(2*x4))/8;

	return y;
}


