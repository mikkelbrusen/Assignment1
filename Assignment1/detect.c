#include "filters.h"

static int x[3] = {0};

void gatherFT(int mwiValue, int index){
	x[index] = mwiValue;
}

int peaks[30];
int Rpeaks[30];

int detect(int mwiValue ){
	int spkf, npkf, threshold1, threshold2;
	int rr_average1, rr_average2, rr_low, rr_high, rr_miss;
	static int timer = 0;
	static int index = 0;
	static enum state{
		CHECK_PEAK,CHECK_THRESHOLD,CALCULATE_RR,STORE_RPEAK
	}

	x[2] = mwiValue;

	int state = 0;

	timer++;

	if (x[0] < x[1] && x[1] > x[2]){
		peaks[index] = x[1];
		timer = 0;
		index++;
		return checkThreshold(x[1]);
	}
	else {return 0;}
}

int checkThreshold(int x){

}


	break;
case CHECK_THRESHOLD :
	if(x[1] > threshold1){
		state = STORE_RPEAK;
	}
	else{
		npkf = 0.125*x[1] + 0.875*npkf;
		threshold1 = npkf + 0.25*(spkf-npkf);
		threshold2 = 0.5*threshold2;
		state = 99;}
	break;
case STORE_RPEAK :
	//calculate RR
	//Vi skal tælle hvor mange iterationer der har været siden sidste peak
	Rpeaks[index]=timer;

	state = 4;
	break;
case 4 :

case 99 :
	return 0;
}

/*
	// Equation5
	if (x[0] < x[1] && x[1] > x[2]){
	}

	// Equation6
	spkf = 0.125*x[1] + 0.875*spkf;

	// Equation7
	threshold1 = npkf + 0.25*(spkf-npkf);

	// Equation8
	threshold2 = 0.5*threshold2;

	// Equation9
	npkf = 0.125*x[1] + 0.875*npkf;

	// Equation10 for searchback BEWARE p_n is not defined yet
	spkf = 0.25*p_n + 0.75*spkf;
*/





