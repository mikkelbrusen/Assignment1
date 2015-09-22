#include "filters.h"

void checkThreshold(int);
void storePeak(int);
static int x[3] = {0};
static int spkf, npkf, threshold1, threshold2;
static int rr_average1, rr_average2, rr_low, rr_high, rr_miss;
static int peaks[500] = {0};
static int hpeaks = 0;

//Reads in the first two data points
void gatherFT(int mwiValue, int index){
	x[index] = mwiValue;
}

void detect(int mwiValue ){
	x[2] = mwiValue;
	if (x[0] < x[1] && x[1] > x[2]){
		storePeak(x[1]);
		checkThreshold(x[1]);
	}
}

void storePeak(int x){
	peaks[hpeaks] = x;
	hpeaks = (hpeaks+1) % 500;
}

void checkThreshold(int x){
	if(x > threshold1){
			checkForRR(x);
	} else{
		npkf = 0.125*x + 0.875*npkf;
		threshold1 = npkf + 0.25*(spkf-npkf);
		threshold2 = 0.5*threshold2;
	}
}

void storeRPeak(int x){
	//calculate RR
	//Vi skal tælle hvor mange iterationer der har været siden sidste peak

}

void peak2Update(int peak){
	storeRPeak(peak);
	spkf = 0.25*peak + 0.75*spkf;
	storeRecentRR(rr);
	rr_average1 = calcRRAve(recentRR);
	commonUpdate(rr_average1);
}

void commonUpdate(int rr_av){
	rr_low = 0.92*rr_av;
	rr_high = 1.16*rr_av;
	rr_miss = 1.66*rr_av;
	threshold1 = npkf + 0.25*(spkf-npkf);
	threshold2 = 0.5*threshold1;
}

int calcRRAve(int x[]){
	int length = sizeof(x)/sizeof(x[0]);
	int average = 0;
	for(int i = 0; i<length; i++){
		average += x[i];
	}
	return average;
}





