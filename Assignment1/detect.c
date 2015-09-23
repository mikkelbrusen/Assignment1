#include "filters.h"
#include <stdio.h>

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
void checkRRMiss(int);

static int data[3] = {0};
static int spkf, npkf, threshold1, threshold2;
static int rr;
static int rr_average1 = 0;
static int rr_average2 = 0;
static int rr_low = 0;
static int rr_high = 0;
static int rr_miss = 0;

//rPeak consists of the peak value and a timestamp. Row 0 is peaks and Row 1 is the time
//See storeRpeak
static int rPeak[2][500]= {0};
static int recentRR_OK[500]= {0};
static int recentRR[500] = {0};
static int peaks[500] = {0};
static int hpeaks = 0;
static int timer = 0;
static int hRPeak = 0;


//Reads in the first two data points
void gatherFT(int mwiValue, int index){
	//Increment timer for first to values
	timer++;
	data[index] = mwiValue;
}

//Reads new data, and detects peaks
void detect(int mwiValue ){
	//Increment timer each time we read a new value
	timer++;
	data[2] = mwiValue;
	if (data[0] < data[1] && data[1] > data[2]){
		storePeak(data[1]);
		checkThreshold(data[1]);
	}
	data[0]=data[1];
	data[1]=data[2];
}

//Stores a peak value into peaks
void storePeak(int x){
	peaks[hpeaks] = x;
	hpeaks = (hpeaks+1) % 500;
}

//Checks if peak is higher than threshold1
void checkThreshold(int x){
	if(x > threshold1){
		checkForRR();
	} else{
		npkf = 0.125*x + 0.875*npkf;
		threshold1 = npkf + 0.25*(spkf-npkf);
		threshold2 = 0.5*threshold1;
	}
}

//Checking RRvalue if its higher than rr_low and lower than rr_high
void checkForRR(){
	//Calculating RR which is the time from the current peak to the last peak
	rr = rPeak[1][hRPeak]-rPeak[1][(hRPeak+499)%500];
	//Checks if interval is OK
	if(rr_low < rr && rr < rr_high){
		storeRPeak(rr);
		storeRecentRR(rr);
		storeRecentOK(rr);
		rr_average2 = calcRRAve(recentRR_OK);
		rr_average1 = calcRRAve(recentRR);
		commonUpdate(rr_average2);

	} else {
		checkRRMiss(rr);
	}

}

//stores Rpeak. Takes the peak value as argument. Timer should be known globally within detect.c
void storeRPeak(int x){
	//Stores peak value in row 0, and column number equal the header
	rPeak[0][hRPeak]=x;
	//Stores timer value in row 1, and column number equal the header
	rPeak[1][hRPeak]=timer;
	hRPeak = (hRPeak + 1) % 500;

	// Print the latest R-peak, time and if needed a warning to console
	if (x<2000){
		printf("WARNING! Low R-peak");
	}
	printf("Latest R-peak: %d detected at %d", x, timer);

}

//Stores recent RR value
void storeRecentRR(int x){
	static int hRecent = 0;
	recentRR[hRecent]=x;
	hRecent = (hRecent + 1) % 500;
}

//Stores recent RR value, which was OK (correctly inside the interval)
void storeRecentOK(int x){
	static int hRecentOK = 0;
	recentRR_OK[hRecentOK] = x;
	hRecentOK = (hRecentOK+1) % 500;
}

//Updates peak and relevant values
void peak2Update(int peak){
	storeRPeak(peak);
	spkf = 0.25*peak + 0.75*spkf;
	storeRecentRR(rr);
	rr_average1 = calcRRAve(recentRR);
	commonUpdate(rr_average1);
}

//Updates RR values and thresholds
void commonUpdate(int rr_av){
	rr_low = 0.92*rr_av;
	rr_high = 1.16*rr_av;
	rr_miss = 1.66*rr_av;
	threshold1 = npkf + 0.25*(spkf-npkf);
	threshold2 = 0.5*threshold1;
}

//Calculates Average of RR recent values (both OK and regular)
int calcRRAve(int x[]){
	int length = sizeof(x)/sizeof(x[0]);
	int average = 0;
	for(int i = 0; i<length; i++){
		average += x[i];
	}
	return average;
}

// Looks back to see if there is an R-peak that needs to be classified
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

//Checks if RR value is higher than rr_miss - if not do nothing.
void checkRRMiss(int x){
	if(x>rr_miss){
		searchBack();
	}
}


