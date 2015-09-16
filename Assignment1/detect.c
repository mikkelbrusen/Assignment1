#include "filters.h"

void checkThreshold(int);
void storeRPeak(int);
static int x[3] = {0};
static int spkf, npkf, threshold1, threshold2;
static int rr_average1, rr_average2, rr_low, rr_high, rr_miss;

/*
void gatherFT(int mwiValue, int index){
	x[index] = mwiValue;
}

int detect(int mwiValue ){
	x[2] = mwiValue;
	if (x[0] < x[1] && x[1] > x[2]){
		checkThreshold(x[1]);
		return 0; //should return something else than 0
	}
	else {return 0;}
}

void checkThreshold(int x){
	if(x[1] > threshold1){
			storeRPeak(x);
	} else{
		npkf = 0.125*x[1] + 0.875*npkf;
		threshold1 = npkf + 0.25*(spkf-npkf);
		threshold2 = 0.5*threshold2;
	}
}

void storeRPeak(int x){
	//calculate RR
	//Vi skal tælle hvor mange iterationer der har været siden sidste peak

}
*/





