#include "filters.h"

void checkThreshold(int);
void storeRPeak(int);
static int x[3] = {0};
static int spkf, npkf, threshold1, threshold2;
static int rr,rr_average1, rr_average2, rr_low, rr_high, rr_miss;
//timer der tæller
static int rPeak[500]= {0};
static int recentRR_OK[500]= {0};
static int recentRR[500] = {0};



//Reads in the first two data points
void gatherFT(int mwiValue, int index){
	x[index] = mwiValue;
}

int detect(int mwiValue ){
	x[2] = mwiValue;
	if (x[0] < x[1] && x[1] > x[2]){
		//Store timer value
		storePeak(x[1]);
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
void checkForRR(int x,int y){
	//Beregner RR (tiden fra sidste peak)
	rr = x-y;
	//Tjekker om det er en OK RR-interval
	if(rr_low<rr<rr_high){
		storeRPeak(rr);
		storeRecentRR(rr);
		storeRecentOK(rr);
		commonUpdate(rr);
		calcRRAve(recentRR_OK);
		calcRRAVE(recentRR);
		commonUpdate()
	}

}
void storeRR(int x){
	//Gemmer Rpeak rPeak
	static int hRR = 0;
	rr[hRR]=x;
	hRR = (hRR + 1) % 500;
}
void storeRecentRR(int x){
	static int hRecent;
	recentRR[hRecent]=x;
	hRecent = (hRecent + 1) % 500;
}
void storeRecentOK(int x){
	static int hRecentOK;
	recentRR_OK[hRecentOK] = x;
	hRecentOK = (hRecentOK+1) % 500;
}





}





