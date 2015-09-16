#include "filters.h"
#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>

void filter(){

	int temp = getNextData();
	int LP;
	int HP;
	int DE;
	int SQ;
	int MWI;

	for(int i = 0; i<2; i++){
		LP = lowPass(temp);
		HP = highPass(LP);
		DE = derivative(HP);
		SQ = squaring(DE);
		MWI = movingWI(SQ);

		printf("%i \n",MWI);
		temp = getNextData();
	}

	// TODO: Find another way to end while loop
	while(temp != 9999){
		LP = lowPass(temp);
		HP = highPass(LP);
		DE = derivative(HP);
		SQ = squaring(DE);
		MWI = movingWI(SQ);

		printf("%i \n",MWI);
		temp = getNextData();
	}

}
