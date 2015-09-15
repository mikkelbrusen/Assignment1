#include "filters.h"
#include "sensor.h"
#include <stdlib.h>

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

struct MWIStructure{
	int h;
	int x[30];
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

	struct MWIStructure MWIS = {
		.h = 0,
		.x = {0},
		.y = 0
	};

	int sq;

	// TODO: Find another way to end while loop
	while(temp != 9999){
		LPS = lowPass(LPS,temp);
		HPS = highPass(HPS,LPS.y);
		DeS = derivative(DeS,HPS.y);
		sq = squaring(DeS.y);
		MWIS = movingWI(MWIS,sq);
		printf("%i \n",(MWIS.y));

		temp = getNextData();
	}

}
