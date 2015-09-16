#include "filters.h"

int highPass( int lpValue ){
	static int x0 = 0;
	static int x16 = 0;
	static int x17 = 0;
	static int x32 = 0;
	static int h = 0;
	static int x[33] = {0};
	static int y[2] = {0};

	x[h] = lpValue;
	x0 = lpValue;

	h = (h+16)%33;
	x16 = x[h];

	h = (h+1)%33;
	x17 = x[h];

	h = (h+15)%33;
	x32 = x[h];

	y[1] = y[0];
	y[0] = y[1] - (x0/32.0) + x16 - x17 + (x32/32.0);

	return y[0];
}

