#include "filters.h"

int movingWI( int sqValue ){
	static int h = 0;
	static int x[30] = {0};
	int y;
	int x_sum = 0;

	x[h] = sqValue;

	for(int i = 0;i<30;i++){
		 x_sum += x[i];
	}

	h = (h+1)%30;
	y = x_sum/30;

	return y;
}


