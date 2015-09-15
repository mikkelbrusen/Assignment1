#include "filters.h"
#include "sensor.h"

struct LPStructure{
	int h;
	int x[13];
	int y;
	int y1;
};

void filter(){

	int temp = getNextData();
	int i;

	struct LPStructure LPS = {
		.h = 0,
		.x = {0},
		.y = 0,
		.y1 = 0,
	};

	for(i=0; i<20; i++){
		LPS = lowPass(LPS,temp);
		HPS = highPass(HPS,LPS.y)
		printf("%i \n",LPS.y);

		temp = getNextData();
	}

}
