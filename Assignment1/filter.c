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
	int RPeak;

	/*
	for(int i = 0; i<2; i++){
		LP = lowPass(temp);
		HP = highPass(LP);
		DE = derivative(HP);
		SQ = squaring(DE);
		MWI = movingWI(SQ);
		gatherFT(MWI,i);

		printf("%i \n",MWI);
		temp = getNextData();
	} */

	// TODO: Find another way to end while loop
	while(getNextDataValid()){
		LP = lowPass(temp);
		HP = highPass(LP);
		DE = derivative(HP);
		SQ = squaring(DE);
		MWI = movingWI(SQ);
		/*RPeak = detect(MWI);
		if(RPeak){
			printf("%i \n",RPeak);
		} */
		printf("%i \n",MWI);

		temp = getNextData();
	}

}
