#include "filters.h"
#include "structures.h"

struct MWIStructure{
	int h;
	int x[30];
	int y;
};

struct MWIStructure movingWI(struct MWIStructure a, int sqValue ){
	struct MWIStructure b;
	b = a;
	int h = a.h;
	int x_sum = 0;

	a.x[h] = sqValue;
	b.x[h] = sqValue;

	for(int i = 0;i<30;i++){
		 x_sum += a.x[i];
	}

	b.h = (h+1)%30;
	b.y = (1/30.0)*x_sum;

	return b;
}


