#include "filters.h"

int movingWI( int sqValue ){
	static int h = 0;
	static int x[30] = {0};
	static int x_sum = 0;
	int y;

	x_sum -=x[h];
	x_sum += sqValue;
	x[h] = sqValue;

	h = (h+1)%30;
	y = x_sum/30;

	return y;
}


