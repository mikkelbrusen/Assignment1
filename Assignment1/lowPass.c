#include "filters.h"
#include <math.h>


int lowPass(int signal){
	static int h = 0;
	static int x0 = 0;
	static int x6 = 0;
	static int x12 = 0;
	static int x[13] = {0};
	static int y[3] = {0};

	x[h] = signal;
	x0 = signal;

	h = (h+6)%13;
	x6 = x[h];

	h = (h+6)%13;
	x12 = x[h];

	y[2] = y[1];
	y[1] = y[0];
	y[0] = 2*y[1] - y[2] + ((1.0/32.0)*(x0 - 2*x6 + x12));

	return y[0];
}

