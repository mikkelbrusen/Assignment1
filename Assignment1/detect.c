#include "filters.h"

static int x[3] = {0};

void gatherFT(int dataInput, int index){
	x[index] = dataInput;
}

/*struct DetStructure{
	int h;
	int x[3];

	// peaks should be saved in .txt file?
	int peaks[30];
};

struct DetStructure detect(struct DetStructure a, int mwiValue ){
	struct DetStructure b;
	b = a;

	int xMin1, x0, xPlus1;
	int spkf, npkf, threshold1, threshold2;
	int rr_average1, rr_average2, rr_low, rr_high, rr_miss;

	int h = a.h;

	a.x[h] = mwiValue;
	b.x[h] = mwiValue;

	x0 = a.x[h];
	h = (h+1)%3;

	xMin1 = a.x[h];
	h = (h+1)%3;

	xPlus1 = a.x[h];

	int state = 0;
*/
	switch(state){

		case 0 :
			if (xMin1 < x0 && x0 > xPlus1){
			state = 1;
			}
			else {
				state = 99;
			}
			break;
		case 1 :
			//Store in PEAKS
			state = 2;
			break;
		case 2 :
			//check with threshold
			if(peak > threshold1){
				npkf = 0.125*x0 + 0.875*npkf;
				threshold1 = npkf + 0.25*(spkf-npkf);
				threshold2 = 0.5*threshold2;

				state = 99;
			}
			else{
				state = 3;
			}
			break;
		case 3 :
			//calculate RR
			state = 4;
			break;
		case 4 :
			if(RR_low<RR)


		case 99 :
			return 0;
	}
}

	// Equation5
	if (xMin1 < x0 && x0 > xPlus1){
	}

	// Equation6
	spkf = 0.125*x0 + 0.875*spkf;

	// Equation7
	threshold1 = npkf + 0.25*(spkf-npkf);

	// Equation8
	threshold2 = 0.5*threshold2;

	// Equation9
	npkf = 0.125*x0 + 0.875*npkf;

	// Equation10 for searchback BEWARE p_n is not defined yet
	spkf = 0.25*p_n + 0.75*spkf;


}






