#include "filters.h"
#include "sensor.h"

struct LPStructure{
	int h;
	int x[13];
	int y;
	int y1;
};

struct HPStructure{
	int h;
	int x[33];
	int y;
};

struct DeStructure{
	int h;
	int x[5];
	int y;
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

	struct HPStructure HPS = {
		.h = 0,
		.x = {0},
		.y = 0
	};

	struct DeStructure DeS = {
			.h = 0,
			.x = {0},
			.y = 0
		};

	for(i=0; i<200; i++){
		LPS = lowPass(LPS,temp);
		HPS = highPass(HPS,LPS.y);
		DeS = derivative(DeS,HPS.y);
		printf("%i \n",(DeS.y));

		temp = getNextData();
	}

}
