#include "filters.h"

void storePeak(int);
void checkThreshold(int);
void checkForRR();
void storeRPeak(int);
void storeRecentRR(int);
void storeRecentOK(int);
void peak2Update(int);
void commonUpdate(int);
int calcRRAve(int[]);
void searchBack();

static int x[3] = {0};
static int spkf, npkf, threshold1, threshold2;
static int rr,rr_average1, rr_average2, rr_low, rr_high, rr_miss;
static int rPeak[2][500]= {0};
static int recentRR_OK[500]= {0};
static int recentRR[500] = {0};
static int peaks[500] = {0};
static int hpeaks = 0;
static int timer = 0;
static int hRPeak = 0;

//Reads in the first two data points
void gatherFT(int mwiValue, int index){
	x[index] = mwiValue;
}

void detect(int mwiValue ){
	timer++;
	x[2] = mwiValue;
	if (x[0] < x[1] && x[1] > x[2]){
		//TODO: Store time in peak timer array
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
		checkForRR();
	} else{
		npkf = 0.125*x + 0.875*npkf;
		threshold1 = npkf + 0.25*(spkf-npkf);
		threshold2 = 0.5*threshold1;
	}
}

void checkForRR(){
	//Beregner RR (tiden fra sidste peak)
	//TODO:Tjek om hRPEAK+499)%500 er det rigtige (Sami)
	rr = rPeak[1][hRPeak]-rPeak[1][(hRPeak+499)%500];
	//Tjekker om det er en OK RR-interval
	if(rr_low < rr && rr < rr_high){
		storeRPeak(rr);
		storeRecentRR(rr);
		storeRecentOK(rr);
		rr_average2 = calcRRAve(recentRR_OK);
		rr_average1 = calcRRAve(recentRR);
		commonUpdate(rr_average2);
	}
}

void storeRPeak(int x){
	rPeak[0][hRPeak]=x;
	rPeak[1][hRPeak]=timer;
	hRPeak = (hRPeak + 1) % 500;
}

void storeRecentRR(int x){
	static int hRecent = 0;
	recentRR[hRecent]=x;
	hRecent = (hRecent + 1) % 500;
}
void storeRecentOK(int x){
	static int hRecentOK = 0;
	recentRR_OK[hRecentOK] = x;
	hRecentOK = (hRecentOK+1) % 500;
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

void searchBack(){
	int hsB = hpeaks;
	for (int i=0; i<500; i++) {
		if(peaks[hsB] > threshold2) {
			peak2Update(peaks[hsB]);
			break;
		} else {
			hsB = (hsB + 499) % 500;
		}
	}
}

void checkRRMiss(int x){
	if(x>rr_miss){
		searchBack();
	}
}






